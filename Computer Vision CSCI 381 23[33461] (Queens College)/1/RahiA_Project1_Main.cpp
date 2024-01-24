#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;

int maxHeight;
int r, c, minN, maxX;
int *histArr;
int *GausArr;

void setZero(int *arr)
{
    int i = 0;
    while (arr[i] != '\0')
    {
        arr[i] = 0;
    }
}

int calculateThreshold(ofstream &myfile, char inFileName[], int *arr, int max)
{
    ifstream take(inFileName);
    double x1, y1, x2, y2;
    take >> x1 >> y1 >> x2 >> y2;
    double slope = (double)(y2 - y1) / (double)(x2 - x1);
    double b = (double)y1 - (slope * (double)x1);
    int maxDiff = INT_MIN;
    int idx;
    int *diffArr = new int[max + 1];
    myfile << "Two Peak points: (" << x1 << ", " << y1 << "), "
           << "(" << x2 << ", " << y2 << ")" << endl;
    setZero(diffArr);
    for (int i = x1; i <= x2; i++)
    {
        int yValue = (int)slope * i + b;
        diffArr[i] = abs(arr[i] - yValue);

        if (diffArr[i] > maxDiff)
        {
            maxDiff = diffArr[i];
            idx = i;
        }
    }

    take.close();

    return idx;
}

int displayHist(ofstream &myfile, char **argv)
{
    ifstream take(argv[1]);
    take >> r;
    take >> c;
    take >> minN;
    take >> maxX;
    histArr = new int[maxX + 1];
    setZero(histArr);
    for (int i = 0; i < r; i++)
    {
        int idx;
        int val;
        take >> idx;
        take >> val;
        histArr[idx] = val;
    }

    for (int i = 0; i <= maxX; i++)
    {
        myfile << i << " "
               << "(" << histArr[i] << "):";
        int c = 0;
        while (c < histArr[i])
        {
            myfile << "+";
            c++;
        }
        myfile << "\n";
    }

    int thrsHold = calculateThreshold(myfile, argv[2], histArr, maxX);
    myfile << "DeepestThrVal: " << thrsHold << endl;

    take.close();

    return thrsHold;
}

double computeMean(ofstream &debugFile, char **argv, int l1, int l2, int &max, int *histArr)
{
    debugFile << "Entering computeMean method" << endl;
    double top = 0;
    double bottom = 0;
    max = 0;
    for (int i = l1; i < l2; i++)
    {
        top += (histArr[i] * i);
        bottom += histArr[i];
        if (max < histArr[i])
        {
            max = histArr[i];
        }
    }

    double result = ((double)top / (double)bottom);

    debugFile
        << "Leaving computeMean method. MaxHeight = " << maxHeight << ", Result = " << result << endl;

    return ((double)top / (double)bottom);
}

double computeVariance(ofstream &debugFile, char **argv, int l1, int l2, int mean, int *histArr)
{
    debugFile << "Entering computeVariance method" << endl;
    double top = 0;
    double bottom = 0;
    for (int i = l1; i < l2; i++)
    {
        top += (double)histArr[i] * ((double)i - mean) * ((double)i - mean);
        bottom += histArr[i];
    }

    debugFile << "Leaving computeVariance method" << endl;
    return ((double)top / (double)bottom);
}

double modifiedGauss(int idx, double mean, double var, int max)
{
    double Gval = 0;
    Gval = max * exp(-(((idx - mean) * (idx - mean)) / (2 * var)));
    return Gval;
}

double fitGaussian(ofstream &debugFile, char **argv, int *GausArr, int l1, int l2, int max, int *histArr)
{
    int maxt;
    debugFile << "Entering fitGauss method" << endl;
    double mean = computeMean(debugFile, argv, l1, l2, maxHeight, histArr);
    double var = computeVariance(debugFile, argv, l1, l2, mean, histArr);
    double Gval = 0.0;
    double sum = 0.0;
    for (int i = l1; i <= l2; i++)
    {
        Gval = modifiedGauss(i, mean, var, maxHeight);
        sum += abs(Gval - (double)histArr[i]);
        GausArr[i] = (int)Gval;
    }
    debugFile << "Leaving fitGauss method, sum is: " << sum << endl;

    return sum;
}

int biGaussian(ofstream &debugFile, ofstream &myfile, char **argv)
{

    debugFile << "Entering fitGauss method" << endl;
    GausArr = new int[maxX + 1];
    int offSet = (int)(maxX - minN) / 10;

    int divPtr = offSet;
    int bestThr = divPtr;
    double minSumDiff = 999999.0;
    double total = 0.0;

    while (divPtr < maxX - offSet)
    {
        setZero(GausArr);
        double leftSum = (double)fitGaussian(debugFile, argv, GausArr, 0, divPtr, maxX, histArr);
        cout << "Sum1: " << leftSum << endl;
        double rightSum = (double)fitGaussian(debugFile, argv, GausArr, divPtr, maxX, maxX, histArr);
        cout << "Sum2: " << rightSum << endl;
        total = (leftSum + rightSum);
        cout << "Total: " << total << endl;
        if (total < minSumDiff)
        {
            minSumDiff = total;
            bestThr = divPtr;
            cout << "Total < MinDiff, so BestThr: " << bestThr << endl;
        }
        divPtr++;
    }
    debugFile << "Leaving biGaussian method, minSumDiff = " << minSumDiff << ", bestThr = " << bestThr << endl;
    myfile << "BiGaussThrVal: " << bestThr << endl;

    return bestThr;
}

void loadHist(int &maxHeight, int *histArr)
{
    maxHeight = INT_MIN;
    int i = 0;
    while (histArr[i] != '\0')
    {
        if (histArr[i] > maxHeight)
        {
            maxHeight = histArr[i];
        }
        i++;
    }
    cout << maxHeight << endl;
}

int main(int argc, char **argv)
{
    ofstream myfile(argv[3]);
    ofstream debugFile(argv[4]);
    displayHist(myfile, argv);
    loadHist(maxHeight, histArr);
    biGaussian(debugFile, myfile, argv);

    myfile.close();
    debugFile.close();

    return 0;
}
