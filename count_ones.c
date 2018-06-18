#include <stdio.h>
#include <stdlib.h>

int ones(){
    int n, count=0;
    scanf("%d",&n);
    if(n==1) count++;
    if(n==0) scanf("%d",&n);
    if(n==0) return 0;
    count+=ones();
    return count;
}



int main() {
    printf("%d",ones());
  return 0;
}