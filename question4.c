// 4.	( points) Create code that allows you to create an ordered list of tokens. This code should take in a file as input and process that file for the following lexemes:
// • Perl style identifiers

/* front.c - a lexical analyzer system for simple
 arithmetic expressions */


 
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define FLOAT 2
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

#define DECIMAL_FLOAT_LIT 27
#define HEX_FLOAT_LIT 28
#define DECIMAL_DIGITS 29
#define DECIMAL_EXPONENT 30
#define HEX_MANTISSA 31
#define HEX_DIGITS 32

#define LEFT_BRACKET 33
#define RIGHT_BRACKET 34
#define LOGIC_OR 35

//  PERL IDENTIFIER
#define AT_THE_RATE_OP 36 // for @
#define MODULO_OP 37      // for % operator
#define DOLLAR_OP 38      // for $ operator

/******************************************************/
/* main driver */
int main(void)
{
  /* Open the input data file and process its contents */
  if ((in_fp = fopen("front.in", "r")) == NULL)
    printf("ERROR - cannot open front.in \n");
  else
  {
    getChar();
    do
    {
      lex();
    } while (nextToken != EOF);
  }
  return 0;
}
/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch)
{
  switch (ch)
  {
  case '(':
    addChar();
    nextToken = LEFT_PAREN;
    break;
  case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    break;
  case '+':
    addChar();
    nextToken = ADD_OP;
    break;
  case '-':
    addChar();
    nextToken = SUB_OP;
    break;
  case '*':
    addChar();
    nextToken = MULT_OP;
    break;
  case '/':
    addChar();
    nextToken = DIV_OP;
    break;

  case '[':
    addChar();
    nextToken = LEFT_BRACKET;
    break;

  case ']':
    addChar();
    nextToken = RIGHT_BRACKET;
    break;

  case '|':
    addChar();
    nextToken = LOGIC_OR;
    break;
  case '@':
    addChar();
    nextToken = AT_THE_RATE_OP;
    break;

  case '%':
    addChar();
    nextToken = MODULO_OP;
    break;

  case '$':
    addChar();
    nextToken = DOLLAR_OP;
    break;

  default:
    addChar();
    nextToken = EOF;
    break;
  }
  return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void)
{
  if (lexLen <= 98)
  {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = '\0';
  }
  else
    printf("Error - lexeme is too long \n");
}

/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void)
{
  if ((nextChar = getc(in_fp)) != EOF)
  {
    if (isalpha(nextChar))
      charClass = LETTER;
    else if (isdigit(nextChar))
      charClass = DIGIT;
    else if (isdouble(nextChar))
      charClass = FLOAT;
    else
      charClass = UNKNOWN;
  }
  else
    charClass = EOF;
}

/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void)
{
  while (isspace(nextChar))
    getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void)
{
  lexLen = 0;
  getNonBlank();
  switch (charClass)
  {
    /* Identifiers */
  case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT)
    {
      //Perl style is caughtup from here
      // as we added their identifier
      addChar();
      getChar();
    }
    nextToken = IDENT;
    break;
    /* Integer literals */
  case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT)
    {
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    break;
    /* floating-point literals */
  case FLOAT:
    addChar();
    getChar();
    while (charClass == FLOAT)
    {
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    break;
    /* Parentheses and operators */
  case UNKNOWN:
    lookup(nextChar);
    getChar();
    break;
    /* EOF */
  case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = '\0';
    break;
  } /* End of switch */
  printf("Next token is: %d, Next lexeme is %s\n",
         nextToken, lexeme);
  return nextToken;
} /* End of function lex */