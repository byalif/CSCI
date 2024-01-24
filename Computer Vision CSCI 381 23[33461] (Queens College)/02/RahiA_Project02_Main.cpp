#include <iostream>
#include <fstream>
using namespace std;

void processing(char inFileName[], char outFileName[], int thrVal);

int main(int argc, char **argv)
{
    int row, col, min, max;
    if (argc >= 3)
    {
        processing(argv[1], argv[2], 6);
    }
    else
    {
        cout << "Incorrect arguements." << endl;
    }
    return 0;
}

void processing(char inFileName[], char outFileName[], int thrVal)
{
    int r, c, min, max;
    ifstream take(inFileName);
    ofstream myfile(outFileName);
    take >> r;
    take >> c;
    take >> min;
    take >> max;
    myfile << r << " " << c << " " << 0 << " " << max << "\n";

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int pixelValue;
            take >> pixelValue;
            if (pixelValue >= thrVal)
            {
                // write pixelValue to output.txt
                myfile << pixelValue << " ";
            }
            else
            {
                // write 0 to output.txt
                myfile << "0 ";
            }
        }
        myfile << "\n";
    }
    myfile.close();
    take.close();
}