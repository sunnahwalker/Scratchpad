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

// Local defines
#define STACK_CHECK_DEPTH 100

void check_addr(int *a);
void check_stack_direction(int *var, int depth);

int global = 0;

int main(void) {

	printf("Welcome to Shadow Walker's Scratchpad App!!!\n");
	printf("Code compiled at: %s %s\n\n", __DATE__, __TIME__);

	int local_main = 0;

	check_addr(&local_main);

	printf("Check Stack direction with depth %d\n\n", STACK_CHECK_DEPTH);
	check_stack_direction(NULL, STACK_CHECK_DEPTH);

	return EXIT_SUCCESS;
}

void check_addr(int *a) {
	static int local_static = 0;
	int local_volatile = 0;

	printf("Local static    = 0x%08X\n", &local_static);
	printf("Local volatile  = 0x%08X\n", &local_volatile);
	printf("Global          = 0x%08X\n", &global);
	printf("Local main      = 0x%08X\n", a);

	printf("\n");

	return;
}

void check_stack_direction(int *var, int depth) {

	int local = 0;
	if (depth == 0) {
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
