/* Program 4 - Keygen
** Author: Aryan Aziz
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[]) {
	FILE *source = fopen("key", "r");
	fseek(source, 0, SEEK_END);
	int byteCount = ftell(source);
	fclose(source);

	printf("%d Characters\n", byteCount);

	return 0;
}