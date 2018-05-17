#include <stdio.h>
#include <stdlib.h> 

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int cmp(const void* a, const void* b)
{
    int ia = *(const int*) a;
    int ib = *(const int*) b;
    return (ia > ib) - (ia < ib);
}

void qSort(int* array, int start, int end, int (*cmp)(const void* a, const void* b)){
    if (cmp(&start,&end)!=-1) return;

    int pivot = array[end];
    int pivotIndex = start;
    for(int i = start; i < end; i++){
        if(cmp(&array[i],&pivot)!=1){
            swap (&array[i],&array[pivotIndex]);
            pivotIndex++;
            }
    }
    swap(&array[pivotIndex], &array[end]);
    
    qSort (array, start, pivotIndex-1, cmp);
    qSort (array, pivotIndex+1, end, cmp);
}

int main(){
    int N, i =0;
    int* array = NULL;

    printf("-Sorting an array of integers-\nNumber of elements:\n");
    scanf("%d", &N);

    array = (int*)malloc(N * sizeof(int));
    for (; i < N; i++)
            {
                printf("[max=%d] element %d:\n", N, i + 1);
                scanf("%d", &array[i]);
            }

    qSort(array, 0, N-1, cmp);

    printf("Sorted:\n");
    for (i = 0; i < N; i++){
        printf("%d\n", array[i]);
    }

    free(array);

    return 0;
}
