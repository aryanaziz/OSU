/* Program 4 - Keygen
** Author: Aryan Aziz
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[]) {

	int first = (int)argv[1];
	int second = (int)argv[2];
	int sum = first + second; 

	printf("%d : %c", sum, sum);

	return 0;
}