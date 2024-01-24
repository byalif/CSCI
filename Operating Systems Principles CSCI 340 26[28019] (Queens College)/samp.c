#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int arr[12] = {1, 55, 90, 4, 3, 33, -40, 5, -40, 4444, 5, 875};
int sum[4] = {0};
int avg[4];
int geoAvg[4];

void *findSum(void *param)
{
    int start = *(int *)param;

    int end = start + 3;

    int sumOfNum = 0;
    for (int i = start; i < end; i++)
    {
        sum[start] += arr[i];
    }

    printf("%d = %d\n", start, sum[start]);

    pthread_exit(0);
}

void *findAvg(void *param)
{
    int start = *(int *)param;
    int end = start + 3;

    // int sumOfNum = 0;
    // for (int i = start; i < end; i++)
    // {
    //     sumOfNum += arr[i];
    // }

    // avg[start] = sumOfNum / 4;
    pthread_exit(0);
}

void *doComp(void *param)
{

    pthread_t t1, t2;
    int index = *(int *)param;
    free(param);

    pthread_create(&t1, NULL, &findAvg, &index);
    pthread_create(&t2, NULL, &findSum, &index);
    // pthread_create(&t3, NULL, findGeo, &index);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    // sumz = malloc(5 * sizeof(*sumz));
    pthread_t thread[4];
    int start = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i * 3;
        pthread_create(&thread[i], NULL, doComp, a);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(thread[i], NULL);
        printf("%d\n", sum[i]);
    }

    return 0;
}