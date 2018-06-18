#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int intcheck(const void* a) {
    if (*(int*)a%2==1)
    return 0;
    else
    return 1;
}

int doublecheck(const void* a) {
    double q; double b = modf(*(double*)a, &q); 
    if (fabs(b)<0.000000000001){
        int i=(int)q; 
        if(i%2==1)
        return 0;
        else
        return 1;
    }
    return 0;
}

int count_if(void* base, size_t num, size_t elsize, int (*check)(const void*)){
    int count=0, i=0;
    while(i<num){
        if(check(base+i*elsize)) 
            count++;
        
        i++;
    }
    return count;
}


//   -23.000001 123.213 5.523 -2.222 -2.54


int main() {
    int elsize, N=5, i=0; void* arr;
    int* iarr=NULL; double* darr=NULL;
    int (*check)(const void*);
    scanf("%d", &elsize);

        switch (elsize) {
    case 4:
    
    iarr=(int*)malloc(N*elsize);
    for (;i<N;i++)
    scanf("%d", &iarr[i]);

                arr=iarr;
                check=intcheck;
        break;
    case 8:
    
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