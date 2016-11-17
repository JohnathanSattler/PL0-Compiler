// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

// Included libraries
#include "compile.h"

// main function
int main(int argc, const char * argv[]) {

	// initalize pointers/variables
	sourceCode * code = NULL;
	tok * toks = NULL;
	int error;
	const char * outputFileName[100];

	// initalize variables with dynamic memory. acts as booleans - used to determine operations
	int * source = (int *) malloc(sizeof(int));
	int * clean = (int *) malloc(sizeof(int));
	int * printTok = (int *) malloc(sizeof(int));
	int * compiled = (int *) malloc(sizeof(int));

	// determine operations based on command line input. additionally read the file
	code = handleInput(argc, argv, code, outputFileName, source, clean, printTok, compiled);

	// prints the code to the screen, based on the arguments source and clean
	printCode(code, *source, *clean);

	// traces through the code and identifies all tokens within. additionally identifies errors in the code
	toks = lex(toks, code);

	// prints out only the tokens
	if (*printTok)
		printToks(toks);

	// identifies if no errors are present among tokens, and prints a response if none are present
	if (printToksErrors(toks) == 0)
		if (program(toks, *outputFileName, *compiled) == 0)
			printf("No errors, program syntactically correct\n");

	return 0;
}
