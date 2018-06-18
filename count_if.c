#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int floatcheck(const void* a) {
    if (*(float*)a<0.000001)
    return 1;
    else
    return 0;
}

int doublecheck(const void* a) {
    if (*(double*)a<0.000000000001)
    return 1;
    else
    return 0;
}

int count_if(void* base, size_t num, size_t elsize, int (*check)(const void*)){
    int count=0, i=1;
    while(i<num){
        if(check(base+i*elsize)) 
            count++; 
        i+=2;
    }
    return count;
}


//   -23.000001 123.213 5.523 -2.222 -2.54


int main() {
    int elsize, N=100, i=0; void* arr;
    float* farr=NULL; double* darr=NULL;
    int (*check)(const void*);
    scanf("%d", &elsize); printf("entered elsize\n");

        switch (elsize) {
    case 4:
    printf("float\n");
    farr=(float*)malloc(N*elsize);
    for (;i<N;i++)
    scanf("%f", &farr[i]);
printf("entered array\n");
                arr=farr;
                check=floatcheck;
        break;
    case 8:
    printf("double\n");
    darr=(double*)malloc(N*elsize);
    for (;i<N;i++)
    scanf("%lf", &darr[i]);
                arr=darr;
                check=doublecheck;
        break;
    }
    printf("here\n");
    printf("%d",count_if(arr,N,elsize,check));
  return 0;
}