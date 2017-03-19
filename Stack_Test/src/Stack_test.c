/*
 ============================================================================
 Name        : Stack_Test.c
 Author      : Ahsan Uddin
 Version     :
 Date        : March 08, 2017
 Copyright   : Sunnahwalker Production 2017
 Description : Check the direction of stack growth
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Local defines
#define STACK_CHECK_DEPTH 100

void check_addr(int *pA, int b);
void check_stack_direction(int *var, int depth);

int gVar = 0;

int main(void) {

	printf("Welcome to Shadow Walker's Scratchpad App!!!\n");
	printf("Code compiled at: %s %s\n\n", __DATE__, __TIME__);

	int lVar_main = 50;

	check_addr(&lVar_main, lVar_main);

	printf("Check Stack direction with depth %d\n\n", STACK_CHECK_DEPTH);
	check_stack_direction(NULL, STACK_CHECK_DEPTH);

	return EXIT_SUCCESS;
}

void check_addr(int *pA, int b) {
	static int lVar_static = 0;
	int lVar = 0;

	void (*p_func)() = (void *) __func__;		//Extracting the address of this function itself

	printf("%s: Address of this func  = 0x%08X\n", __func__, p_func);

	printf("%s: Local static int      = 0x%08X\n", __func__, &lVar_static);
	printf("%s: Local int             = 0x%08X\n", __func__, &lVar);
	printf("%s: Global int            = 0x%08X\n", __func__, &gVar);
	printf("%s: Local Main value      = %d		(this is in the stack)\n", __func__, b);
	printf("%s: Local Main pointer    = 0x%08X 	(this is in the stack)\n", __func__, &b);
	printf("%s: Original Main pointer = 0x%08X\n", __func__, pA);

	printf("\n");

	return;
}

void check_stack_direction(int *var, int depth) {

	int local = 0;

	if (depth == 0) {
		assert(var != NULL);			//Need to check if we got a corrupt value or not

		printf("Local Var addr  = 0x%08X\n", &local);
		printf("Passed Var addr = 0x%08X\n", var);

		printf("Stack is going %s", ((&local < var) ? "LOW":"HIGH"));

		printf("\n");
	}
	else {
		check_stack_direction(((var == NULL)? &local:var), depth - 1);
	}

	return;
}
