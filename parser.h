// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

// Included libraries
#include <stdio.h>
#include <string.h>
#include "tokens.h"
#include "input.h"
#include "printing.h"

// Function prototypes
int program(tok * allTokens, const char * outputFileName, int pm0);
void block(int level);
void constDeclaration(int level);
void varDeclaration(int level, int * numVar);
void procedureDeclaration(int level);
void statement(int level);
void condition(int level);
void relOp();
void expression(int level);
void term(int level);
void factor(int level);
void advance();
void error(int num);
void eat(int id);
void emit(int op, int l, int m);
int symbolExists(char * name, int level);
void addSymbol(int kind, char * name, int val, int level, int addr);
