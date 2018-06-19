# include <stdio.h> 
# include <string.h>
#include <stdlib.h>

//C[i] = (p[i] + k[i mod klength] ) mod N, C = cipher, k = secret key (word), p = text, N = number of letters in the alphabet
void vigenereCipher(char* text, char* k){
	
	int i;
	char cipher;
	int cipherValue;
	int len = strlen(k);
	
	//Loop through the length of the plain text string
	for(i=0; i<strlen(text); i++){
		//for lowercase, range is [97 -122]
			cipherValue = ( (int)text[i]-97 + (int)(k[i % len])-97 ) % 26 +97;
			cipher = (char)cipherValue;
			printf("%c", cipher);
	}
}

int main(){
	
	char* k = (char*)malloc(20*sizeof(char));
	char* text = (char*)malloc(60*sizeof(char));
	
	scanf("%s %s",k, text);

	vigenereCipher(text, k);

	return 0;
}
