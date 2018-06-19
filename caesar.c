#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int caesarCipher(char* plainText, char* text2){
	
	int i=0, q=0,key=0;
	int cypherValue;
	char* cypher=(char*)malloc(sizeof(char)*strlen(text2));
	
	for(key = 0;key<25;key++){
		//encryption of the word
		i=0;
	while( text2[i] != '\0' && strlen(text2)-1 > i){
		cypherValue = ((int)text2[i] -97 + key) % 26 + 97;
		cypher[i] = (char)(cypherValue);
		i++;
	}

	if(strstr(plainText,cypher)) return key;
	}
	
	return -1;
}

int main(void){
	
	char* plainText=(char*)malloc(100*sizeof(char));
	char* text2=(char*)malloc(20*sizeof(char));

	scanf("%s %s",plainText,text2);
	
	printf("%d",caesarCipher(plainText, text2));
	
	return 0;
}
