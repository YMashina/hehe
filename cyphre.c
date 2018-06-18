#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char arr[100], a; int i=0; char arr2[100];
    fgets(arr,100,stdin);
    int length=strlen(arr);

    while(i<length){
      arr2[i]=arr[i-i/2]; i+=1;
      arr2[i]=arr[length/2+i/2];
      
      i++;
    }
    printf("%s",arr2);
    
    return 0;
}