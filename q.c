#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(void)
{
	int N=1200,M=10, i=0, e=0, w=0;
	char** arr=(char**)malloc(N*sizeof(char*));// to store names of directories and files
	//char* word=(char*)malloc((M+1)*sizeof(char));
	//fgets(word,M,stdin);
	//word[strlen(word)]='\0';
char word[M];
for (; e < M; ++e)
{
	word[e]=getchar();
	if (word[e]=='\n'){
		word[e]='\0';
		break;
	}
}



 /*   struct dirent *de;  // Pointer for directory entry
 
    // opendir() returns a pointer of DIR type. 
    DIR *dr = opendir(".");
 
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }
 
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL){
    	//printf("%s\n", de->d_name);
    	arr[i]=de->d_name; i++;
    }
            for (int q = 0; q < i; ++q)
            {
            	printf("%s\n", arr[q]);
            }
*/
for (; w < e; ++w)
{
	for (int r = 0; r < i; ++r)
	{
		if(strcmp(arr[r],word+w)==0){

		}
	}
}
 	
    closedir(dr);   

    free(arr); 
    return 0;
}
