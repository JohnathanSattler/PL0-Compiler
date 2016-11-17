// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

// Included libraries
#include "lexer.h"
#include "string.h"

char * reservedWords[] = {
	"const", "var", "procedure", "call",
	"begin", "end", "if", "then", "else",
	"while", "do", "read", "write", "odd"
};

int numReservedWords = 14;

char * symbols[] = {
	"+", "-", "*", "/", "=", "<>",
	"<=", "<", ">=", ">", ":=",
	",", ";", ".", "(", ")"
};

int numSymbols = 16;

tok * lex(tok * toks, sourceCode * code) {

	sourceCode * currentCode = code;
	tok * currentTok = NULL;
    tok * lastTok = NULL;
    int i, reserved, skips, comment = 0;
    char num[100];

	while (currentCode != NULL) {

        // if space, skip
        if (currentCode -> c == ' ' || currentCode -> c == '\t' || currentCode -> c == '\n') {
            currentCode = currentCode -> next;
            continue;
        }

        // if starting comment, skip
        if (comment == 0 && currentCode -> next != NULL && currentCode -> c == '/' && currentCode -> next -> c == '*') {
            comment = 1;
            currentCode = currentCode -> next -> next;
            continue;
        }

        // end comment if */ encountered
        if (comment == 1 && currentCode -> next != NULL && currentCode -> c == '*' && currentCode -> next -> c == '/') {
            comment = 0;
            currentCode = currentCode -> next -> next;
            continue;
        }

        // if in comment, skip
        if (comment == 1) {
            currentCode = currentCode -> next;
            continue;
        }

        // get next token
		currentTok = getNextTok(currentCode);

        if (currentTok == NULL) {
            currentCode = currentCode -> next;
            continue;
        }

        reserved = 0;

        // Number too big error
        if (currentTok -> id == numbersym && currentTok -> number > pow(2, 16) - 1) {
            currentTok -> error = 1;
            currentTok -> msg = "Number too big";
        }

        // Identifier too long error
		if (currentTok -> id == identsym && strlen(currentTok -> str) > 12) {
            currentTok -> error = 1;
            currentTok -> msg = "Identifier too long";
        }

        // check for reserved word
        for (i = 0; i < numReservedWords; i++) {
            if (currentTok -> error == 1 || currentTok -> id == numbersym) {
                i = -1;
                break;
            }

            if (strcmp(reservedWords[i], currentTok -> str) == 0) {
                break;
            }
        }

        // continue checking for reserved word
        switch(i) {
            case 0: // const
                currentTok -> id = constsym;
                break;

            case 1: // var
                currentTok -> id = varsym;
                break;

            case 2: // procedure
                currentTok -> id = procsym;
                break;

            case 3: // call
                currentTok -> id = callsym;
                break;

            case 4: // begin
                currentTok -> id = beginsym;
                break;

            case 5: // end
                currentTok -> id = endsym;
                break;

            case 6: // if
                currentTok -> id = ifsym;
                break;

            case 7: // then
                currentTok -> id = thensym;
                break;

            case 8: // else
                currentTok -> id = elsesym;
                break;

            case 9: // while
                currentTok -> id = whilesym;
                break;

            case 10: // do
                currentTok -> id = dosym;
                break;

            case 11: // read
                currentTok -> id = readsym;
                break;

            case 12: // write
                currentTok -> id = writesym;
                break;

            case 13: // odd
                currentTok -> id = oddsym;
                break;

            default:
                break;
        }

        // check for known symbols
        for (i = 0; i < numSymbols; i++) {
            if (currentTok -> error == 1 || currentTok -> id == numbersym) {
                i = -1;
                break;
            }

            if (strcmp(symbols[i], currentTok -> str) == 0) {
                break;
            }
        }

        // continue checking if symbol is known or unknown
        switch(i) {
            case 0: // +
                currentTok -> id = plussym;
                break;

            case 1: // -
                currentTok -> id = minussym;
                break;

            case 2: // *
                currentTok -> id = multsym;
                break;

            case 3: // /
                currentTok -> id = slashsym;
                break;

            case 4: // =
                currentTok -> id = eqlsym;
                break;

            case 5: // <>
                currentTok -> id = neqsym;
                break;

            case 6: // <=
                currentTok -> id = leqsym;
                break;

            case 7: // <
                currentTok -> id = lessym;
                break;

            case 8: // >=
                currentTok -> id = geqsym;
                break;

            case 9: // >
                currentTok -> id = gtrsym;
                break;

            case 10: // :=
                currentTok -> id = becomessym;
                break;

            case 11: // ,
                currentTok -> id = commasym;
                break;

            case 12: // ;
                currentTok -> id = semicolonsym;
                break;

            case 13: // .
                currentTok -> id = periodsym;
                break;

            case 14: // (
                currentTok -> id = lparentsym;
                break;

            case 15: // )
                currentTok -> id = rparentsym;
                break;

            default: // check for unknown symbol
                if (currentTok -> id == numbersym || isalnum(currentTok -> str[0]))
                    break;
                else {
                    currentTok -> id = nulsym;
                    currentTok -> error = 1;
                    currentTok -> msg = "Invalid token";
                }
                break;
        }

        // set first tok to currentTok
        if (lastTok == NULL) {
            lastTok = currentTok;
            toks = lastTok;
        } else { // add the currentTok to toks->next if toks is not null
            lastTok -> next = currentTok;
            lastTok = lastTok -> next;
        }

        // skip over used characters in the code
        if (currentTok -> id == numbersym) {
            sprintf(num, "%d", currentTok -> number);
            skips = strlen(num);
        } else {
            skips = strlen(currentTok -> str);
        }

        for (i = 0; i < skips; i++) {
            currentCode = currentCode -> next;
        }
	}

	return toks;
}

tok * getNextTok(sourceCode * code) {

    int isNum = 0, isAlp = 0, isSym = 0;
    char tokenString[100] = "";
    int tokenNum = 0, i, containsFirst = 0, containsSecond = 0;
    char p[2], c = code -> c;
    tok * returnTok;

    if (code == NULL) // null checking
        return NULL;

    returnTok = (tok *) malloc(sizeof(tok));
    returnTok -> error = 0;
    returnTok -> next = NULL;
    returnTok -> str = (char *) malloc(sizeof(char) * 2);

    /*
    This is to check if the first char in token
    is a symbol or not, if it changes after
    then we know its end of a token
    */
    if (isalpha(c)) {
        isAlp = 1;
        returnTok -> id = identsym;
    } else if (isdigit(c)) {
        isNum = 1;
        returnTok -> id = numbersym;
    } else {
        isSym = 1;
        returnTok -> id = nulsym;
    }

    /*
    if its not the end of the token, keep adding
    */
    while (!isEnd(c, isSym, isNum, isAlp)) {

        containsFirst = 0;
        containsSecond = 0;

        p[0] = c;
        p[1] = '\0';

        if (code -> next != NULL && c == '/' && code -> next -> c == '*')
            break;

        // check if the current symbol is known
        for (i = 0; i < numSymbols; i++)
            if (strcmp(symbols[i], tokenString) == 0) {
                containsFirst = 1;
                break;
            }

        // If variable starts with num
        if (isNum && isalpha(c)) {
            isNum = 0;
            isAlp = 1;
            returnTok -> id = identsym;
            returnTok -> error = 1;
            returnTok -> msg = "Identifier begins with number";
        }

        if (isNum)
            tokenNum = tokenNum * 10 + (c - '0');

        strcat(tokenString, p);

        // check if the new symbol is known
        for (i = 0; i < numSymbols; i++) {
            if (strcmp(symbols[i], tokenString) == 0) {
                containsSecond = 1;
                break;
            }
        }

        // if the older symbol is known, but not the new one, then use the older one
        if (isSym && containsFirst && !containsSecond) {
            tokenString[strlen(tokenString) - 1] = '\0';
            break;
        }

        code = code -> next;

        if (code == NULL)
            break;

        c = code -> c;
    }  

    if (isNum)
        returnTok -> number = tokenNum;
    else
        strcpy(returnTok -> str, tokenString);

    return returnTok;
}

int isEnd(char c, int isSym, int isNum, int isAlp) {

    /*
    This base case checks to see if the next char
    to be added is null, new line, white space,
    or tab, if it is any of these we have reached
    the end of a token
    */
    if (c == '\n' || c == ' ' || c == '\t')
        return 1;
    /*
    This base case checks if it was a symbol and the
    next char to add is not a symbol, and vice-versa
    if either of these occur we have reached the end of a token
    */
    if ((isSym == 1 && isalnum(c)) || (isNum == 1 && !isalnum(c)) || (isAlp && !isalnum(c)))
        return 1;

    return 0;
}
