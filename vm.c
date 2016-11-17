// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

// Included libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// constants
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

// arrays containing opcode information
char * opCodes[] = { "Nil",
	"LIT", "OPR", "LOD", "STO", "CAL",
	"INC", "JMP", "JPC", "SIO"
};
char * OPR[] = {
	"RET", "NEG", "ADD", "SUB", "MUL",
	"DIV", "ODD", "MOD", "EQL", "NEQ",
	"LSS", "LEQ", "GTR", "GEQ"
};
char * SIO[] = {
	"OUT", "INP", "HLT"
};

// instruction struct
typedef struct instruction
{
	int op;
	int l;
	int m;
} instruction;

// function prototypes
void initStack(int stack[]);
void readFile(const char * fileName, instruction code[]);
void printCode(int size, instruction code[]);
void printInstruction(instruction ir, int i);
void printContents(instruction ir, int i, int pc, int bp, int sp, int stack[]);
void printStack(int stack[], int sp, int bp);
int base(int level, int b, int stack[]);
void fetchCycle(instruction code[], int stack[], int * pc, int * bp, int * sp, int * ir);
void executeCycle(instruction ir, int stack[], int * pc, int * bp, int * sp, int * halt);

// main function
int main(int argc, const char * argv[]) {
	
	// define program variables
	const char * fileName = argv[1];
	instruction code[MAX_CODE_LENGTH];
	int stack[MAX_STACK_HEIGHT];
	int * pc, * bp, * sp, * ir;

	// initialize the stack
	initStack(stack);

	// initialize pc, bp, sp, and ir
	pc = (int *) malloc(sizeof(int));
	bp = (int *) malloc(sizeof(int));
	sp = (int *) malloc(sizeof(int));
	ir = (int *) malloc(sizeof(int));

	// read in the provided file
	readFile(fileName, code);

	// execute code
	fetchCycle(code, stack, pc, bp, sp, ir);

	// free allocated memory
	free(pc);
	free(bp);
	free(sp);
	free(ir);

	return 0;
}

// void function to initiate the stack
void initStack(int stack[]) {

	int i;

	// initiate the stack to zero
	for (i = 0; i < MAX_STACK_HEIGHT; i++)
		stack[i] = 0;

	return;
}

// void function to read in file 
void readFile(const char * fileName, instruction code[]) {

	FILE * ifp;
	int i = 0;
	
	// opens file
	ifp = fopen(fileName, "r");

	// if there is no file, execute print statement and exits function
	if (ifp == NULL) {
		printf("Error: File not found\n");
		exit(0);
	}

	// reads in file contents and places them in the instruction struct
	while(fscanf(ifp, "%d %d %d", &code[i].op, &code[i].l, &code[i].m) != EOF) {
		if (code[i].l > MAX_LEXI_LEVELS)
			code[i].l = MAX_LEXI_LEVELS;
			
		i++;
	}
	
	// closes file
	fclose(ifp);
	
	// calls printCode function
	printCode(i, code);

	return;
}

// void function to print instruction code
void printCode(int size, instruction code[]) {

	int i;

	printf("PL/0 code:\n\n");

	// loop through instruction code, sending it to the function printInstruction to determine proper print procedure
	for (i = 0; i < size; i++) {
		printInstruction(code[i], i);
		printf("\n");
	}

	return;
}

// void function to prin instruction struct
void printInstruction(instruction ir, int i) {

	char * opCode;
	int printL, printM;

	printL = 0;
	printM = 0;

	// assigns the char variable opCode, the int variable printL and printM depending on the passed thru struct
	// uses the contents of the declared arrays OPR[], SIO[] and opCodes[]
	if (ir.op == 2)
		opCode = OPR[ir.m];
	else if (ir.op == 9)
		opCode = SIO[ir.m];
	else {
		opCode = opCodes[ir.op];
		printM = 1;
	}

	if (ir.op >= 3 && ir.op <= 5)
		printL = 1;

	// prints out variable i and opCode. i being the step number and opCode the operation
	printf(" %2d  %3s  ", i, opCode);

	// prints out level if assigned
	if (printL)
		printf("%3d ", ir.l);
	else
		printf("    ");

	// prints out modifier if assigned
	if (printM)
		printf("%3d   ", ir.m);
	else
		printf("      ");

	return;
}

void printContents(instruction ir, int i, int pc, int bp, int sp, int stack[]) {

	// print program counter, base pointer, and stack pointer
	printf("%4d %4d %4d   ", pc, bp, sp);
	printStack(stack, sp, bp); // prints stack
	printf("\n");

	return;
}

void printStack(int stack[], int sp, int bp) {

	int i;

	//loop through the code
	for (i = 1; i <= sp; i++) {
		
		// add a spacing line where necessary
		if (bp == i && bp > 1)
			printf("| ");

		//print the stack
		printf("%d ", stack[i]);
	}

	return;
}

int base(int level, int b, int stack[]) {

	// return base of activation record at given level
	while (level > 0) {
		b = stack[b + 1];
		level--;
	}

	return b;
}

// handles the execution of the program
void fetchCycle(instruction code[], int stack[], int * pc, int * bp, int * sp, int * ir) {

	int * halt;

	// initialize all of the pointers
	halt = (int *) malloc(sizeof(int));

	*pc = 0;
	*bp = 1;
	*sp = 0;
	*ir = 0;

	*halt = 0;

	printf("\nExecution:\n");
	printf("                      pc   bp   sp   stack\n");
	printf("                    ");
	printContents(code[*ir], *ir, *pc, *bp, *sp, stack);

	// loop through the code and stop at the halt condition
	while (*halt != 1 && *pc < MAX_CODE_LENGTH) {
		// fetch the current instruction, and increment pc
		*ir = *pc;
		(*pc)++;
		
		// print the current instruction
		printInstruction(code[*ir], *ir);

		// run the current instruction
		executeCycle(code[*ir], stack, pc, bp, sp, halt);

		// print the contents of each pointer, and the stack
		printContents(code[*ir], *ir, *pc, *bp, *sp, stack);
	}

	free(halt);

	return;
}

void executeCycle(instruction ir, int stack[], int * pc, int * bp, int * sp, int * halt) {

	switch(ir.op) {
		case 1: // LIT
			(*sp)++;
			stack[*sp] = ir.m;
			break;
		case 2: // OPR
			switch(ir.m) {
				case 0: // RET
					*sp = *bp - 1;
					*pc = stack[*sp + 4];
					*bp = stack[*sp + 3];
					break;
				case 1: // NEG
					stack[*sp] = -stack[*sp];
					break;
				case 2: // ADD
					(*sp)--;
					stack[*sp] = stack[*sp] + stack[*sp + 1];
					break;
				case 3: // SUB
					(*sp)--;
					stack[*sp] = stack[*sp] - stack[*sp + 1];
					break;
				case 4: // MUL
					(*sp)--;
					stack[*sp] = stack[*sp] * stack[*sp + 1];
					break;
				case 5: // DIV
					(*sp)--;
					stack[*sp] = stack[*sp] / stack[*sp + 1];
					break;
				case 6: // ODD
					stack[*sp] = stack[*sp] % 2;
					break;
				case 7: // MOD
					(*sp)--;
					stack[*sp] = stack[*sp] % stack[*sp + 1];
					break;
				case 8: // EQL
					(*sp)--;
					stack[*sp] = stack[*sp] == stack[*sp + 1];
					break;
				case 9: // NEQ
					(*sp)--;
					stack[*sp] = stack[*sp] != stack[*sp + 1];
					break;
				case 10: // LSS
					(*sp)--;
					stack[*sp] = stack[*sp] < stack[*sp + 1];
					break;
				case 11: // LEQ
					(*sp)--;
					stack[*sp] = stack[*sp] <= stack[*sp + 1];
					break;
				case 12: // GTR
					(*sp)--;
					stack[*sp] = stack[*sp] > stack[*sp + 1];
					break;
				case 13: // GEQ
					(*sp)--;
					stack[*sp] = stack[*sp] >= stack[*sp + 1];
					break;
				default:
					break;
			}
			break;
		case 3: // LOD
			(*sp)++;
			stack[*sp] = stack[base(ir.l, *bp, stack) + ir.m];
			break;
		case 4: // STO
			stack[base(ir.l, *bp, stack) + ir.m] = stack[*sp];
			(*sp)--;
			break;
		case 5: // CAL
			stack[*sp + 1] = 0;
			stack[*sp + 2] = base(ir.l, *bp, stack);
			stack[*sp + 3] = *bp;
			stack[*sp + 4] = *pc;
			*bp = *sp + 1;
			*pc = ir.m;
			break;
		case 6: // INC
			*sp = *sp + ir.m;
			break;
		case 7: // JMP
			*pc = ir.m;
			break;
		case 8: // JPC
			if (stack[*sp] == 0) {
				*pc = ir.m;
			}
			(*sp)--;
			break;
		case 9: // SIO
			switch(ir.m) {
				case 0: // OUT
					printf("%2d\n", stack[*sp]);
					(*sp)--;
					break;
				case 1: // INP
					(*sp)++;
					scanf("%d", &stack[*sp]);
					printf("read %d from input\n", stack[*sp]);
					break;
				case 2: // HLT
					*halt = 1;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return;
}
