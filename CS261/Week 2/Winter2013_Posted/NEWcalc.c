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

   /* Checking for correct number of digts */
    if(sizeDynArr(stack) < 2){
         printf("--  ERROR: INVALID USE OF '+'            -- \n");
         printf("--      REASON: '+' NEEDS TWO DIGITS     --  \n");

         return;
     }
    double a;
    double b;

    a = topDynArr(stack);
    popDynArr(stack);

    b = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, a + b);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{

   /* Checking for correct number of digts */
   if(sizeDynArr(stack) < 2){
        printf("--  ERROR: INVALID USE OF '-'            -- \n");
        printf("--      REASON: '-' NEEDS TWO DIGITS     --  \n");

        return;
    }
    double a;
    double b;

    a = topDynArr(stack);
    popDynArr(stack);

    b = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, b - a);

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
   /* Checking for correct number of digts */
   if(sizeDynArr(stack) < 2){
        printf("--  ERROR: INVALID USE OF '/'            -- \n");
        printf("--      REASON: '/' NEEDS TWO DIGITS     --  \n");

        return;
    }

	double a;
    double b;

    a = topDynArr(stack);
    popDynArr(stack);

    b = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, b/a);
}

void multiply(struct DynArr *stack)
{ 

   /* Checking for correct number of digts */
   if(sizeDynArr(stack) < 2){
        printf("--  ERROR: INVALID USE OF 'x'            -- \n");
        printf("--      REASON: 'x' NEEDS TWO DIGITS     --  \n");

        return;
    }

    double a;
    double b;

    a = topDynArr(stack);
    popDynArr(stack);

    b = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, a * b);
}

void power(struct DynArr *stack)
{ 

    /* Checking for correct number of digts */
    if(sizeDynArr(stack) < 2){
        printf("--  ERROR: INVALID USE OF '^'           -- \n");
        printf("--      REASON: 'x' NEEDS TWO DIGITS    --  \n");

        return;
    }

    double a;
    double b;

    a = topDynArr(stack);
    popDynArr(stack);

    b = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, pow(b,a));

}

void square(struct DynArr *stack)
{
   /* Checking for correct number of digts */
   if(sizeDynArr(stack) < 1){
        printf("--  ERROR: INVALID USE OF '^2'  -- \n");
        printf("--      REASON: NOTHING TO '^2' --  \n");

        return;
    }
    double a;

    a = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, pow(a,2));
}

void cube(struct DynArr *stack)
{
   /* Checking for correct number of digts */
   if(sizeDynArr(stack) < 1){
        printf("--  ERROR: INVALID USE OF '^3'  -- \n");
        printf("--      REASON: NOTHING TO '^3' --  \n");

        return;
    }

    double a;

    a = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, pow(a,3));
}

void absolute(struct DynArr *stack)
{ 
    if(sizeDynArr(stack) < 1){
        printf("--  ERROR: INVALID USE OF 'abs'  -- \n");
        printf("--      REASON: NOTHING TO 'abs' --  \n");

        return;
    }
    double a;
    
    a = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, abs(a));

}

void squarert(struct DynArr *stack)
{
    if(sizeDynArr(stack) < 1){
        printf("--  ERROR: INVALID USE OF 'sqrt'  -- \n");
        printf("--      REASON: NOTHING TO 'sqrt' --  \n");

        return;
    }
    double a;

    a = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, sqrt(a));

}

void exponential(struct DynArr *stack){
    if(sizeDynArr(stack) < 1){
        printf("--  ERROR: INVALID USE OF 'exp'  -- \n");
        printf("--      REASON: NOTHING TO 'exp' --  \n");

        return;
    }   
    double a;

    a = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, exp(a));
}

void natualLog(struct DynArr *stack){

    if(sizeDynArr(stack) < 1){
        printf("--  ERROR: INVALID USE OF 'ln'  -- \n");
        printf("--      REASON: NOTHING TO 'ln' --  \n");

        return;
    }

    double a;

    a = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, log(a));
}

void tenLog(struct DynArr *stack)
{
   if(sizeDynArr(stack) < 1){
        printf("--  ERROR: INVALID USE OF 'log'  -- \n");
        printf("--      REASON: NOTHING TO 'log' --  \n");
        return;
    } 
    double a;

    a = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack, log10(a));
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;
    double num;

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
		else if(strcmp(s, "^") == 0)
            power(stack);
		else if(strcmp(s, "^2") == 0)
            square(stack);
		else if(strcmp(s, "^3") == 0)
            cube(stack);
		else if(strcmp(s, "abs") == 0)
            absolute(stack);
		else if(strcmp(s, "sqrt") == 0)
            squarert(stack);
		else if(strcmp(s, "exp") == 0)
            exponential(stack);
		else if(strcmp(s, "ln") == 0)
            natualLog(stack);
		else if(strcmp(s, "log") == 0)
            tenLog(stack);
		else if(isNumber(s, &num))
            pushDynArr(stack, num);
        else if(strcmp(s, "pi") == 0)
            pushDynArr(stack, 3.14159265);
        else if(strcmp(s, "e") == 0)
            pushDynArr(stack, 2.7182818); 

	} 

	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */
	if(sizeDynArr(stack) == 1){
         printf("Answer = %f\n", topDynArr(stack));
	     return result;
    }
    else {
        printf("ERROR! Trailing numbers! \n");
        return 0;
    }
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