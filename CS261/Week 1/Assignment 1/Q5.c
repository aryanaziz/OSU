/* CS261- Assignment 1 - Q.5*/
/* Name: Aryan Aziz
 * Date: 6-29-14
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
	for(int i = 0; i < strlen(word); i++) {
		if(i % 2 == 0) {
			if(islower(word[i])) {
				word[i] = toUpperCase(word[i]);
			}
		}
		else {
			if(isupper(word[i])) {
				word[i] = toLowerCase(word[i]);
			}
		}
	}
}

int main(){
    /*Read word from the keyboard using scanf*/
    char word[256];
    char *input;
    input = word;
    printf("Enter a word: ");
    scanf("%s", input);
    
    /*Call sticky*/
    sticky(input);
    
    /*Print the new word*/
    printf("%s", input);
    
    return 0;
}
