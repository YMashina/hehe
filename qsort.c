#include <stdio.h>
#include <stdlib.h> 

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition (int* array,int start,int end){
    int pivot = array[end];
    int pivotIndex = start;
    for(int i = start; i < end; i++){
        if(array[i] <= pivot){
            swap (&array[i],&array[pivotIndex]);
            pivotIndex++;
            }
    }
    swap(&array[pivotIndex], &array[end]);
    return pivotIndex;
}

void qSort(int* array, int start, int end){
    if (start >= end) return;
    int pivotIndex = partition(array, start, end);
    qSort (array, start, pivotIndex-1);
    qSort (array, pivotIndex+1, end);
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

    qSort(array, 0, N-1);

    printf("Sorted:\n");
    for (i = 0; i < N; i++){
        printf("%d\n", array[i]);
    }

    free(array);
    
    return 0;
}
