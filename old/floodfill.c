
 /*void printarr(int n, int m, int arr[n][m]){
 	int row, columns; 
 	printf("your array is\n");
for (int row=0; row<n; row++) 
{ 
for(int columns=0; columns<m; columns++) 
{ 
printf("%d ", arr[row][columns]); 
} 
printf("\n"); 
}

}*/

#include <stdio.h>
#include <stdlib.h>

void printarr(int n, int m, int arr[n][m]){
 	int row, columns; 
 	printf("your array is\n");
for (int row=0; row<n; row++) 
{ 
for(int columns=0; columns<m; columns++) 
{ 
printf("%d ", arr[row][columns]); 
} 
printf("\n"); 
}

}

void floodFill(int n, int m, int screen[n][m], int x, int y, int prevC, int newC)
{
    if (x < 0 || x >= n || y < 0 || y >= m)
        return;
    if (screen[x][y] != prevC)
        return;
    
    screen[x][y] = newC;
 
    floodFill(n,m,screen, x+1, y, prevC, newC);
    floodFill(n,m,screen, x-1, y, prevC, newC);
    floodFill(n,m,screen, x, y+1, prevC, newC);
    floodFill(n,m,screen, x, y-1, prevC, newC);
}


int main() {
  int n,m,i=0,q=0,e=0; int newcolor=2;
    scanf("%d %d",&n,&m); int arr[n][m];
    //int** arr2=(int**)malloc(n*m*sizeof(int*));

    for (i=0;i<n;i++)
        for(q=0;q<m;q++)
            scanf("%d",&arr[i][q]);
        printarr(n,m,arr);
    for (i=0;i<n;i++)
        for(q=0;q<m;q++)
            if(arr[i][q]==1){
    floodFill(n,m,arr,i,q,1,newcolor);
                //oldcolor=newcolor;
                newcolor++;
            }
            printarr(n,m,arr);
    int color=newcolor-1, firstcolor = 2, count=0, max=0;
    printf("color=%d\n", color);
    //for(firstcolor=2;firstcolor<color;firstcolor++)
    while(firstcolor<color){
        for (i=0;i<n;i++){
            for(q=0;q<m;q++){
                if(arr[i][q]==firstcolor)
                	count+=1;
            }
        }
        //count-=1;
    	printf("for color %d count = %d\n", firstcolor,count);
    	firstcolor+=1;
    	if (count>max)
    		max=count;
        count=0;
    }
    printf("%d",max);
  return 0;
}