#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pcharcmp(const void* a, const void* b)
{
    return strcmp((*(char**)a), (*(char**)b));
}

int intcmp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int floatcmp(const void* a, const void* b)
{
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    return (fa > fb) - (fa < fb);
}

void swap(void* a, void* b, size_t elsize)
{
    char *q = a, *w = b, tmp;
    for (int i = 0; i != elsize; i++)
    {
        tmp = q[i];
        q[i] = w[i];
        w[i] = tmp;
    }
}

void bubbleSort(void* arr, int arrl, size_t elsize, int (*cmp)(const void*, const void*))
{
    int i, j;
    char* p = arr;
    for (i = 0; i < arrl - 1; i++)
        for (j = 0; j < arrl - i - 1; j++)
            if (cmp(&p[elsize * j], &p[elsize * j + elsize]) > 0)
                swap(&p[elsize * j], &p[elsize * j + elsize], elsize);
}

void printarr(void* arr, int size, size_t elsize, int choice)
{
    char** a1 = arr;
    int* a2 = arr;
    float* a3 = arr;
    int q = 0;
    switch (choice)
    {
        case 1:

            for (; q < size; q++)
                printf("%s\n", (char*)a1[q]);
            break;
        case 2:

            for (; q < size; q++)
                printf("%d\n", (int)a2[q]);
            break;
        case 3:

            for (; q < size; q++)
                printf("%f\n", (float)a3[q]);
            break;
    }
}

int main()
{
    int choice, N, i = 0;
    size_t elsize;
    void* arr;
    char** carr = NULL;
    int* iarr = NULL;
    float* farr = NULL;
    int (*cmp)(const void*, const void*);
    printf(
        "Sorting an array of following types:\nChoose type:\n1-char* (strings)\n2-int\n3-float\n");
    scanf("%d", &choice);
    printf("Set number of elements:\n");
    scanf("%d", &N); getchar();
    printf("Separate elements by Enter please\n");
    switch (choice)
    {
        case 1:
            elsize = sizeof(char*);
            carr = (char**)malloc(N * sizeof(char*));
            for (i = 0; i < N; i++)
            {

                printf("[max=%d] element %d:\n", N, i + 1);
                carr[i] = (char*)malloc(31 * sizeof(char));
                fgets(carr[i], 30, stdin);
                carr[i][strlen(carr[i]) - 1] = '\0';
            }
            carr[i] = '\0';
            arr = carr;
            cmp = pcharcmp;
            break;

        case 2:
            elsize = sizeof(int);
            iarr = (int*)malloc(N * sizeof(int));
            for (; i < N; i++)
            {
                printf("[max=%d] element %d:\n", N, i + 1);
                scanf("%d", &iarr[i]);
            }
            arr = iarr;
            cmp = intcmp;
            break;

        case 3:
            elsize = sizeof(float);
            farr = (float*)malloc(N * sizeof(float));
            for (; i < N; i++)
            {
                printf("[max=%d] element %d:\n", N, i + 1);
                scanf("%f", &farr[i]);
            }
            arr = farr;
            cmp = floatcmp;
            break;
    }

    bubbleSort(arr, N, elsize, cmp);
    printf("\nSorted:\n");
    printarr(arr, N, elsize, choice);
    return 0;
}
