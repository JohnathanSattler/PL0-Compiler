// Compiler Builder 8
// Lester Young
// Timothy Konzel
// Remington Howell
// Johnathan Sattler
// John Herold

#ifndef _tokensh_
#define _tokensh_

#define MAX_SYMBOL_TABLE_SIZE 100
#define MAX_CODE_LENGTH 500

typedef enum tokens {
  nulsym = 1, identsym, numbersym, plussym, minussym,
  multsym, slashsym, oddsym, eqlsym, neqsym, lessym, leqsym,
  gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
  periodsym, becomessym, beginsym, endsym, ifsym, thensym,
  whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
  readsym , elsesym
} token_type;

typedef enum opCodes {
  LIT = 1, OPR, LOD, STO,
  CAL, INC, JMP, JPC, SIO
} ops;

typedef enum OPR {
  OPR_RET = 0, OPR_NEG, OPR_ADD, OPR_SUB,
  OPR_MUL, OPR_DIV, OPR_ODD, OPR_MOD, OPR_EQL,
  OPR_NEQ, OPR_LSS, OPR_LEQ, OPR_GTR, OPR_GEQ
} opr;

typedef enum SIO {
  SIO_OUT = 0, SIO_INP, SIO_HLT
} sio;

typedef struct sourceCode {
  char c;
  struct sourceCode * next;
} sourceCode;

typedef struct tok {
  union {
   	char * str;
   	int number;
  };
  int error;
  int id;
  char * msg;
  struct tok * next;
} tok;

// instruction struct
typedef struct instruction
{
  int op;
  int l;
  int m;
} instruction;

typedef struct symbol {
  int kind;      // const = 1, var = 2, proc = 3
  char name[12]; // name up to 11 chars
  int val;     // number (ASCII value)
  int level;     // L level
  int addr;      // M address
} symbol;

#endif
