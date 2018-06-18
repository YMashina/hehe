#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct pair{
    char word[30];
    char trans[30];
}pair;

int main() {
    int M=0; pair **arr=(pair**)malloc(20*sizeof(pair*)); 
    int i=0, q=0, w=1, prev=0; char uga[]="ugabuga"; 
    char phrase[100], word[30]; int foundtranslation=0;

    while(i < 20){
        arr[i]=(pair*)malloc(sizeof(pair));
        scanf("%s",arr[i]->word);

        if(strcmp(uga,arr[i]->word)==0) break;
        getchar();
        fgets(arr[i]->trans,30,stdin);
        arr[i]->trans[strlen(arr[i]->trans)-1]='\0';
        
        i++;
    }
getchar();
    int N=i;
    printf("entered %d\n", N);
    fgets(phrase,100, stdin);
    int length= strlen(phrase);
    phrase[length-1]='\0';
    
    for (i=0;i<length;i++){
        if (phrase[i]!=' ')
        phrase[i]=tolower(phrase[i]);
    }
    
    char *pch = strtok (phrase," ");
    while (pch != NULL)
    {
        for(i=0;i<N;i++){
            
                if(strcmp(pch, arr[i]->word)==0){
                printf("%s", arr[i]->trans);
                foundtranslation=1;
                break;
                }
        }
            if(foundtranslation==0) printf("<unknown>");

        if(w<=N) printf(" "); 
        w++;
        foundtranslation=0;
        
        pch = strtok (NULL, " ");
    }

  return 0;
}