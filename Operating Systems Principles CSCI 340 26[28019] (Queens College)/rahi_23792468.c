// Alif rahi 23792468
// Project 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

// Array for 16000 input numbers from Prj2InpSect26.txt
int arr[16000];

// file descriptor for output file
FILE *fp;

// Arrays for 16*3 worker threads
int sum[16];
double avg[16];
float geo[16];

// Max variables
int maxSum = 0;
double maxAvg = 0;
float maxGeo = 0;

// struct to make writing messages to output easier
typedef struct
{
    char sum[128];
    char geo[128];
    char avg[128];
    char msg[128];
    char workerMsg[128];

} Message;

void *geoAvg(void *arg)
{
    // start and end dictate the group of numbers we will compute on
    // Notice its only 1000 numbers each, hence, 1000 * 16 == 16000
    int start = *(int *)arg;
    int end = start + 1000;
    float mult = 1;
    for (int j = start; j < end; j++)
    {
        // The tmp variable stores the 1000th root of arr[j] which is one of 16000 numbers in the input file
        // If arr[j] is zero, the the entire product of these 1000 numbers will also be zero
        float tmp = pow(arr[j], 1.0 / 1000.0);
        mult *= tmp;
    }
    *(float *)arg = mult;

    // return the geometric average of these 1000 numbers
    return arg;
}

void *getAvg(void *arg)
{
    // start and end dictate the group of numbers we will compute on
    // Notice its only 1000 numbers each
    int start = *(int *)arg;
    int end = start + 1000;
    int sum = 0;
    for (int j = start; j < end; j++)
    {
        sum += arr[j];
    }
    double g = sum / 1000.0;

    *(double *)arg = g;

    // return the arithmetic average of these 1000 numbers
    return arg;
}

void *getSum(void *arg)
{
    // start and end dictate the group of numbers we will compute on
    // Notice its only 1000 numbers each, hence, 1000 * 16 == 16000
    int start = *(int *)arg;
    int end = start + 1000;
    int sum = 0;
    for (int j = start; j < end; j++)
    {
        sum += arr[j];
    }

    *(int *)arg = sum;

    // return the sum of these 1000 numbers
    return arg;
}

void *routine(void *arg)
{
    // Create three worker threads for computations
    pthread_t t1, t2, t3;

    // This number dictates where we start in the array of 16000 numbers
    int start = *(int *)arg;

    pthread_attr_t attr1, attr2, attr3;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    // Pass the start values to each of the three threads to do computations
    // Instead of doing stroi() its better to pass memmory addresses for integers
    int *a = malloc(sizeof(int));
    *a = start;
    pthread_create(&t1, NULL, &getSum, a);

    int *b = malloc(sizeof(int));
    *b = start;
    pthread_create(&t2, NULL, &getAvg, b);

    int *c = malloc(sizeof(int));
    *c = start;
    pthread_create(&t3, NULL, &geoAvg, c);

    // We delcare r to store the return value from the getSum function
    // The index of (start / 1000) is obviously a number representing one of the 16 threads
    int *r;
    pthread_join(t1, (void **)&r);
    sum[start / 1000] = *r;

    // We delcare av to store the return value from the getAvg function
    double *av;
    pthread_join(t2, (void **)&av);
    avg[start / 1000] = *av;

    // We delcare g to store return value from the geoAvg function
    float *g;
    pthread_join(t3, (void **)&g);
    geo[start / 1000] = *g;

    // use snprintf to copy message
    Message msg;
    snprintf(msg.workerMsg, 128, "Worker Child Pthread Number = %d : \t Geometric Average = %f \t Arithmetic Average = %f \t Sum = %d \n", start / 1000, *g, *av, *r);

    // write worker thread computations into output file
    fputs(msg.workerMsg, fp);

    // free all the variables we used to store the return values of functions
    free(r);
    free(av);
    free(g);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("oops, too few inputs!\n");
        return 1;
    }

    // Open output file
    fp = fopen(argv[2], "w+");
    // Open input file
    FILE *InputFile = fopen(argv[1], "r");

    int j = 0;
    int num;
    while (fscanf(InputFile, "%d", &num) == 1)
    {
        // fscanf stores input file numbers into memmory address &num and then stores into array
        arr[j] = num;
        j++;
    }

    pthread_attr_t attr[16];
    pthread_t th[16];
    int i;

    // Loop to create 16 worker threads
    for (i = 0; i < 16; i++)
    {
        // This variable is passed as the start index of each group of 16 threads
        int *a = malloc(sizeof(int));
        // multiply i * 1000 to get the start indexes [0, 1000, 2000, 3000 ... 15000]
        *a = i * 1000;
        pthread_attr_init(&attr[i]);
        pthread_create(&th[i], NULL, &routine, a);
    }

    // Wait for each thread to finish before doing computations
    for (i = 0; i < 16; i++)
    {
        pthread_join(th[i], NULL);
    }

    // Calculate the Max of each arrays
    for (int i = 0; i < 16; i++)
    {
        if (sum[i] > maxSum)
            maxSum = sum[i];
        if (avg[i] > maxAvg)
            maxAvg = avg[i];
        if (geo[i] > maxGeo)
            maxGeo = geo[i];
    }

    // use snprintf to copy message outputs into struct
    Message msg;
    snprintf(msg.sum, 128, "Main program thread: Max of the Sums = %d \n", maxSum);
    snprintf(msg.avg, 128, "Main program thread: Max of the Arithmetic Averages = %f \n", maxAvg);
    snprintf(msg.geo, 128, "Main program thread: Max of the Geometric Averages = %f \n", maxGeo);
    snprintf(msg.msg, 128, "Main program thread: Terminating. \n");

    // count the lengths of all these messages we just created
    int len1 = 0;
    int len2 = 0;
    int len3 = 0;
    int len4 = 0;
    int k = 0;
    while (msg.geo[k++] != '\0')
        len1++;
    k = 0;
    while (msg.avg[k++] != '\0')
        len2++;
    k = 0;
    while (msg.sum[k++] != '\0')
        len3++;
    k = 0;
    while (msg.msg[k++] != '\0')
        len4++;

    // write final output to STDOUT
    write(STDOUT_FILENO, msg.geo, len1);
    write(STDOUT_FILENO, msg.avg, len2);
    write(STDOUT_FILENO, msg.sum, len3);
    write(STDOUT_FILENO, msg.msg, len4);

    // write final outputs to the output file
    fputs(msg.geo, fp);
    fputs(msg.avg, fp);
    fputs(msg.sum, fp);
    fputs(msg.msg, fp);

    // close input and output files
    fclose(fp);
    fclose(InputFile);

    return 0;
}