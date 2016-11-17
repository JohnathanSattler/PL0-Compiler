// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

#include <stdio.h>
#include "tokens.h"

void printCode(sourceCode * code, int source, int clean);
void printSourceCode(sourceCode * code);
void printCleanCode(sourceCode * code);
void printToks(tok * toks);
int printToksErrors(tok * toks);
void printAssembly(instruction code[], int size);