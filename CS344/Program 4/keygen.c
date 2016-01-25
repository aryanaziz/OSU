/* Program 4 - Keygen
** Author: Aryan Aziz
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[]) {
	srand(time(NULL));

	int i;
	for(i = 0; i < atoi(argv[1]); i++) {
		printf("%c", rand() % 26 + 65);
	}

	return 0;
}