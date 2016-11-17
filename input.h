// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokens.h"

sourceCode * handleInput(int argc, const char * argv[], sourceCode * code, const char * outputFileName[], int * s, int * c, int * t, int * p);
sourceCode * readFile(const char * fileName, sourceCode * code);
void writeFile(const char * fileName, instruction * code, int size);
