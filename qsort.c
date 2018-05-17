#include <stdio.h>
#include <stdlib>
void swap(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}

int partition (int* array,int start,int end){
    int pivot = array[end];
    int pivotIndex = start;
    for(int i = 0; i < end-1; i++){
        if(array[i] <= pivot){
            swap (array[i],array[pivotIndex]);
            pivotIndex++;
            }
    }
    swap(array[pivotIndex], array[end]);
    return pivotIndex;
}

void qSort(int* array, int start, int end){
    if (start < end) return;
    int pivotIndex = partition(array, start, end);
    qSort (array, start, pivotIndex-1);
    qSort (array, pivotIndex-1, end);
}

int main(){
    int N, i =0;
    int* array = NULL;
    printf("-Sorting an array of integers-\nNumber of elements:\n);
    scanf("%d", N);
    array = (int*)malloc(100*(sizeof(int)));
    for (; i < N; i++)
            {
                printf("[max=%d] element %d:\n", N, i + 1);
                scanf("%d", &iarr[i]);
            }
    qSort(array, 0, N-1);
    printf("Sorted:\n");
    for (; i < N; i++){
        printf("%d\n");
    }
    return 0;
}
