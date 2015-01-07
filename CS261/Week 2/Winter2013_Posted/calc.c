#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/

void add (struct DynArr *stack)
{
	double firstNum;
	double secondNum;

	firstNum = topDynArr(stack); //Set the first number
    popDynArr(stack); //Remove the first number from the stack
    secondNum = topDynArr(stack); //Set the second number
    popDynArr(stack); //Remove the second number from the stack

    pushDynArr(stack, firstNum + secondNum); //Add them together and put them into the stack
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	double firstNum;
	double secondNum;

	firstNum = topDynArr(stack); //Set the first number
    popDynArr(stack); //Remove the first number from the stack
    secondNum = topDynArr(stack); //Set the second number
    popDynArr(stack); //Remove the second number from the stack

    pushDynArr(stack, secondNum - firstNum); //Subtract them together and put them into the stack
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	double firstNum;
	double secondNum;

	firstNum = topDynArr(stack); //Set the first number
    popDynArr(stack); //Remove the first number from the stack
    secondNum = topDynArr(stack); //Set the second number
    popDynArr(stack); //Remove the second number from the stack

    pushDynArr(stack, secondNum/firstNum); //divide them together and put them into the stack
}

void multiply(struct DynArr *stack) {
	double firstNum;
	double secondNum;

	firstNum = topDynArr(stack); //Set the first number
    popDynArr(stack); //Remove the first number from the stack
    secondNum = topDynArr(stack); //Set the second number
    popDynArr(stack); //Remove the second number from the stack

    pushDynArr(stack, firstNum * secondNum); //multiply them together and put them into the stack
}

void exponent(struct DynArr *stack) {
	double firstNum;
	double secondNum;

	firstNum = topDynArr(stack); //Set the first number
    popDynArr(stack); //Remove the first number from the stack
    secondNum = topDynArr(stack); //Set the second number
    popDynArr(stack); //Remove the second number from the stack

    pushDynArr(stack, pow(secondNum,firstNum));
}

void squared(struct DynArr *stack) {
	double firstNum;

	firstNum = topDynArr(stack); //Set firstNum
    popDynArr(stack); //Remove firstNum from the stack

    pushDynArr(stack, pow(firstNum,2)); 
}

void cubed(struct DynArr *stack) {
	double firstNum;

	firstNum = topDynArr(stack); //Set firstNum
    popDynArr(stack); //Remove firstNum from the stack

    pushDynArr(stack, pow(firstNum,3)); 
}

void absoluteValue(struct DynArr *stack) {
	double firstNum;

	firstNum = topDynArr(stack); //Set firstNum
    popDynArr(stack); //Remove firstNum from the stack

    pushDynArr(stack, abs(firstNum)); 
}

void squareRoot(struct DynArr *stack) {
	double firstNum;

	firstNum = topDynArr(stack); //Set firstNum
    popDynArr(stack); //Remove firstNum from the stack

    pushDynArr(stack, sqrt(firstNum)); 	
}

void exponential(struct DynArr *stack) {
	double firstNum;

	firstNum = topDynArr(stack); //Set firstNum
    popDynArr(stack); //Remove firstNum from the stack

    pushDynArr(stack, exp(firstNum)); 
}

void ln(struct DynArr *stack) {
	double firstNum;

	firstNum = topDynArr(stack); //Set firstNum
    popDynArr(stack); //Remove firstNum from the stack

    pushDynArr(stack, log(firstNum)); 
}

void logb10(struct DynArr *stack) {
	double firstNum;

	firstNum = topDynArr(stack); //Set firstNum
    popDynArr(stack); //Remove firstNum from the stack

    pushDynArr(stack, log10(firstNum)); 
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;
	double number;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0)
			add(stack);
		else if(strcmp(s,"-") == 0)
			subtract(stack);
		else if(strcmp(s, "/") == 0)
			divide(stack);
		else if(strcmp(s, "x") == 0)
			multiply(stack);
			//printf("Multiplying\n");		Had to comment this out because it was producing weird errors. 
		else if(strcmp(s, "^") == 0)
			exponent(stack);
			//printf("Power\n");
		else if(strcmp(s, "^2") == 0)
			squared(stack);
			//printf("Squaring\n");
		else if(strcmp(s, "^3") == 0)
			cubed(stack);
			//printf("Cubing\n");
		else if(strcmp(s, "abs") == 0)
			absoluteValue(stack);
			//printf("Absolute value\n");
		else if(strcmp(s, "sqrt") == 0)
			squareRoot(stack);
			//printf("Square root\n");
		else if(strcmp(s, "exp") == 0)
			exponential(stack);
			//printf("Exponential\n");
		else if(strcmp(s, "ln") == 0)
			ln(stack);
			//printf("Natural Log\n");
		else if(strcmp(s, "log") == 0)
			logb10(stack);
			//printf("Log\n");
		else 
		{
			// FIXME: You need to develop the code here (when s is not an operator)
			// Remember to deal with special values ("pi" and "e")
			if(isNumber(s, &number)) { //Checks if the next item is a number
				pushDynArr(stack, number); //Places that baby in the stack
			}
        	else if(strcmp(s, "pi") == 0) { //Turns pi into a number
            	pushDynArr(stack, 3.14159265);
            }
        	else if(strcmp(s, "e") == 0) { //Turns e into a number
            	pushDynArr(stack, 2.7182818);
            }
		}
	}	//end for 

	 //Everything should look ok if there is only 1 item left in the stack
	if(sizeDynArr(stack) == 1){
         printf("Answer = %f\n", topDynArr(stack));
	     return result;
    }
    else {
        printf("YOU DUN GOOFED, why there be more than 1 item left in the stack eh? \n");
        return 0;
    }
	
	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	calculate(argc,argv);
	return 0;
}
