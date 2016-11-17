// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "tokens.h"

tok * lex(tok * toks, sourceCode * code);
tok * getNextTok(sourceCode * code);
int isEnd(char c, int isSym, int isNum, int isAlp);