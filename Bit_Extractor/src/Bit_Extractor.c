/*
 ============================================================================
 Name        : Bit_Extractor.c
 Author      : Ahsan Uddin
 Version     : 3/8/2017
 Copyright   : Sunnahwalker Production
 Description : Test a bit for 0/1 bit
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define BITS_IN_BYTE	8

bool bit_test(int var, int bit_pos);

int main(void) {

	printf("Welcome to Shadow Walker's Scratchpad App!!!\n");
	printf("Code compiled at: %s %s\n\n", __DATE__, __TIME__);

	int test_var = 0b11001100;
	int pos = 2;
	printf("Bit Test for 0x%X at position %d is: %s!!!\n", test_var, pos, ((bit_test(test_var, pos)) ? "PASS" : "FAIL"));

	pos = 1;
	printf("Bit Test for 0x%X at position %d is: %s!!!\n", test_var, pos, ((bit_test(test_var, pos)) ? "PASS" : "FAIL"));

	return 0;

}

bool bit_test(int var, int bit_pos) {

	bool ret = false;

	assert(bit_pos < (sizeof(int) * BITS_IN_BYTE));

	if ((var >> bit_pos) & 0x1) {
		ret = true;

		return ret;
	}

	return ret;
}
