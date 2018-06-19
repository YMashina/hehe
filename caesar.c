#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void caesarCipher(char* plainText, char* text2){
	
	int i=0, q=0,key=0;
	int cypherValue;
	char* cypher=(char*)malloc(sizeof(char)*strlen(text2));
	
	for(key = 0;key<26;key++){
	while( text2[i] != '\0' && strlen(text)-1 > i){
		cypherValue = ((int)text[i] -97 + key) % 26 + 97;
		cypher[i] = (char)(cypherValue);
		i++;
	}
	if(strstr(plainText,text2)!=NULL) return key;
	}
	
return -1;
}

int main(void){
	
	int key = 1;
	char plainText=(char*)malloc(100*sizeof(char));
	char* text2=(char*)malloc(20*sizeof(char));

	scanf("%s %s",&plainText,&text2);
	
	printf("%d",caesarCipher(plainText, text2));
	
	return 0;
}

