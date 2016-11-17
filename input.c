// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

// Included libraries
#include "input.h"

// handle the arguments passed into the program
sourceCode * handleInput(int argc, const char * argv[], sourceCode * code, const char * outputFileName[], int * s, int * c, int * t, int * p) {

	// varaible declarations
	const char * inputFile, * outputFile;
	int i, source = 0, clean = 0, printTokens = 0, pm0 = 0;

	// identify the arguments in argv. aborts the program if the command line format is incorrect
	for (i = 1; i < argc; i++)
		// compares the argument in argv[i] to the valid arguments. sets them to 1 if present
		if (strcmp(argv[i], "--source") == 0)
			source = 1;
		else if (strcmp(argv[i], "--clean") == 0)
			clean = 1;
		else if (strcmp(argv[i], "--tokens") == 0)
			printTokens = 1;
		else if (strcmp(argv[i], "--pm0") == 0)
			pm0 = 1;
	
		// if arguments don't match, check for invalidity
		else {
			inputFile = argv[i];
			i++;
			if (i >= argc) {
				printf("Invalid Arguments. Usage: ./compile (arguments) (inputfile) (outputfile)\n");
				exit(1);
			}
			outputFile = argv[i];
		}

	// update the pointers in the function input with values obtained in the above for loop
	*s = source;
	*c = clean;
	*t = printTokens;
	*p = pm0;

	// assign output file to following char array
	*outputFileName = outputFile;

	// scans the input from the input file and copies it into a char array for parsing
	code = readFile(inputFile, code);

	// return the char array with the input to be parsed later
	return code;
}

// read the input file
sourceCode * readFile(const char * fileName, sourceCode * code) {

	// variable declarations
	FILE * ifp;
	char temp;
	sourceCode * last = code;

	// opens file
	ifp = fopen(fileName, "r");

	// if there is no file, execute print statement and exits function
	if (ifp == NULL) {
		printf("Error: File not found\n");
		exit(0);
	}

	// trace through the file, continue to grab inputs and add to code until the end of file
	while(fscanf(ifp, "%c", &temp) != EOF) {
		// allocate space for a new current source code object
		sourceCode * current = (sourceCode *) malloc(sizeof(sourceCode));
		current -> c = temp;
		current -> next = NULL;

		// fix pointers
		if (last == NULL) {
			last = current;
			code = last;
		} else {
			last -> next = current;
			last = last -> next;
		}
	}

	// closes file
	fclose(ifp);

	return code;
}

// write PM/0 to an output file
void writeFile(const char * fileName, instruction * code, int size) {

	FILE * ofp;
	int i;

	// open or create the file
	ofp = fopen(fileName, "w");

	// write the code
	for (i = 0; i < size; i++) {
		fprintf(ofp, "%d %d %d\n", code[i].op, code[i].l, code[i].m);
	}

	// close the file
	fclose(ofp);

	return;
}
