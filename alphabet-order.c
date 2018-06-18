#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct country {
char name[30];
char name2[30];
unsigned int population;
char capital[30];
}country;


int cmpfunc (const void * a, const void * b) {
   if ((strcmp(((country*)b)->name,((country*)a)->name))!=0)
       return strcmp(((country*)b)->name,((country*)a)->name);
    else 
        return strcmp(((country*)b)->name2,((country*)a)->name2);
    
}


int main(){
    int n= -1, i=0, q=0;
    scanf("%d", &n);
    country countries[n];
    for (;i<n;i++){
    scanf("%s ", countries[i].name);
    scanf("%s ", countries[i].name2); 
    scanf("%u ", &countries[i].population);
    fgets(countries[i].capital, 31, stdin);
    countries[i].capital[strlen(countries[i].capital)-1] = '\0';
  }
    qsort(countries,n,sizeof(country),cmpfunc);
    for (i=0;i<n;i++){
    printf("%s %s %u %s",countries[i].name, countries[i].name2, countries[i].population,countries[i].capital); 
    if(i!=n-1) printf(" ");
    }
    return 0;
}