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
void block();
void constDeclaration();
void varDeclaration();
void statement();
void condition();
void relOp();
void expression();
void term();
void factor();
void advance();
void error(int num);
void eat(int id);
void emit(int op, int l, int m);
int symbolExists(char * name);
void addSymbol(int kind, char * name, int val, int level, int addr);
