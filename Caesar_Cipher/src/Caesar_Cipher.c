///////////////////////////////////////////////////////////////////////////////////////////////////
//
//		Caesar Cipher!!!
//		Author: Ahsan Uddin
//		Date: April 6th, 2017
//		Description:
//			This code implements Caesar Cipher
//			Learn more here: https://learncryptography.com/classical-encryption/caesar-cipher
//
//			Use either one of the 2 defines:
//				1. CHANGE_CAP -> To flip the Capital and small letters
//				2. SHIFT_CHAR -> Shift each letters by ENCRYPTION_KEY
//
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define noCHANGE_CAP
#define SHIFT_CHAR

#if defined(CHANGE_CAP) && defined(SHIFT_CHAR)
#error	Can't have both encryption type!!!
#endif

#if !(defined(CHANGE_CAP) || defined(SHIFT_CHAR))
#error	You should have atleast one type of encryption!!!
#endif

#define ENCRYPTION_SIZE 	40
#define CAPS_DIFFERENCE 	('a'-'A')
#define MAX_LETTERS		 	('Z'-'A' + 1)
#define ENCRYPTION_KEY		(3)

void encrypt(char* input);

int main(void) {

	char *line = "The Quick Brown Fox Jumps Over The Lazy Dog";

	printf("Welcome to Shadow Walker's Scratchpad App!!!\n");
	printf("Code compiled at: %s %s\n\n", __DATE__, __TIME__);

	encrypt(line);

	return EXIT_SUCCESS;
}

void encrypt(char* input) {



	char encryted_line[ENCRYPTION_SIZE];

	for (int i = 0; i < ENCRYPTION_SIZE; i++) {

		// If its a space leave it alone
		if (input[i] == ' ') {
			encryted_line[i] = ' ';
		}

		// CAPS detection
		else if ((input[i] >= 'A') && (input[i] <= 'Z')) {
#ifdef CHANGE_CAP
			encryted_line[i] = (((input[i]) + CAPS_DIFFERENCE) % 'z');
#endif
#ifdef SHIFT_CHAR
			encryted_line[i] = input[i] - 'Z';
			encryted_line[i] = (((encryted_line[i] ) + ENCRYPTION_KEY) % (MAX_LETTERS));
			encryted_line[i] += 'Z';
#endif
		}
		// smalls detection
		else if ((input[i] >= 'a') && (input[i] <= 'z')) {
#ifdef CHANGE_CAP
			encryted_line[i] = (((input[i]) - CAPS_DIFFERENCE) % 'z');
#endif
#ifdef SHIFT_CHAR
			encryted_line[i] = input[i] - 'a';
			encryted_line[i] = (((encryted_line[i] ) + ENCRYPTION_KEY) % (MAX_LETTERS));
			encryted_line[i] += 'a';
#endif
		}

		// If its none of them then.....:(
		else {
			assert(0);
		}
	}

	encryted_line[ENCRYPTION_SIZE - 1] = NULL;

	printf("%s: Input line: \t\t%s\n", __func__, input);

	printf("%s: Encrypted line: \t%s\n", __func__, encryted_line);

	return;
}
