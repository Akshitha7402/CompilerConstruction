%{
#include "header.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include "y.tab.h"

#define MAX_SYMBOLS 256 // You need to define how many symbols you expect

// line number, lexeme, and tokens
typedef struct {
    int line_num;     // Line number in the source file
    char *lexeme;     // The actual text (string) of the token
    char *token;      // Token type
} SymbolTable;

SymbolTable table[MAX_SYMBOLS]; // Fixed size for simplicity
int line = 1;
int table_size = 0;

void add_to_table(const char* lex, const char* tok) {
    
    table[table_size].line_num = line;
    table[table_size].lexeme = strdup(lex); // strdup allocates and copies
    table[table_size].token = strdup(tok);
    table_size++;

    //printf("\n lines = %d\n", line);
}

%}

%option noyywrap

%%


\r?\n          { 
    //printf("\n SKIPPING Newlines"); 
    line++; 
}

[ \t]+         { 
    //printf("\n SKIPPING Spaces"); /* Skip whitespace. */ 
}

"//"[^\n]*  { 

    //printf("\nComment found"); 
    add_to_table(yytext, "Comment");  
}

\"[ ]*([^\"\n]*)[ ]*\"|['][ ]*([^\"\n]*)[ ]*['] {
    
    //add_to_table(yytext, "Message");
    strcpy(yylval.string, yytext);
    return T_STRING;
}

\'[^\n\"]*\'  {
    //printf("\nsaw quotes");
    //add_to_table(yytext, "Message");
}

[o|O][f|F]  {

    //printf("\nlex: Of: %s", yytext);
    strcpy(yylval.string, yytext);
    return T_OF;
}

[a|A][n|N][d|D]  { 
    
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return T_AND;
}

[o|O][r|R]    { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return T_OR;
}

[n|N][o|O][t|T]   { 
    //printf("\nLex: NOT Operator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return T_NOT;
}

[p|P][r|R][o|O][g|G][r|R][a|A][m|M]     {

    //printf("\nProgram begins"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_PROGRAM;
}

[v|V][a|A][r|R]          { 
    //printf("\nSaw var"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_VAR;
}

[i|I][n|N][t|T]      { 

    //printf("\nInteger found"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_INTEGER; 
}

[i|I][n|N][t|T][e|E][g|G][e|R][r|R]       { 
    //printf("\nInteger found"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_INTEGER; 
}

[r|R][e|E][a|A][l|L]          { 
    //printf("\nReal"); 
    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_REAL;
}

[c|C][h|H][a|A][r|R]        { 
    //printf("\nChar"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_CHAR;
}

[b|B][o|O][o|O][l|L][e|E][a|A][n|N]      { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_BOOLEAN;
}

[f|F][o|O][r|R]      { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_FOR;
}

[i|I][f|F]       {

    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_IF;
}

[e|E][l|L][s|S][e|E]       {

    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_ELSE;
}

[t|T][h|H][e|E][n|N]       {

    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_THEN;
}

[d|D][o|O]      { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_DO;
}

[d|D][o|O][w|W][n|N][t|T][o|O]  {
    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_DOWNTO;
}

[t|T][o|O]     { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext); 
    return T_TO;
}

[w|W][h|H][i|I][l|L][e|E]     { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_WHILE;
}

[a|A][r|R][r|R][a|A][y|Y]     { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_ARRAY;
}

[b|B][e|E][g|G][i|I][n|N]        { 

    //printf("\nbegin"); 
    add_to_table(yytext, "Keyword"); 
    strcpy(yylval.string, yytext);
    return T_BEGIN;
}

[e|E][n|N][d|D]          { 

    //printf("\nend"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_END;
}

[t|T][r|R][u|U][e|E]    { 

    //printf("\nend"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_TRUE;
}

[f|F][a|A][l|L][s|S][e|E]    { 

    //printf("\nend"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_FALSE;
}


[w|W][r|R][i|I][t|T][e|E]       {  
    //printf("\nWrite"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_write;
}

[w|W][r|R][i|I][t|T][e|E][l|L][n|N]       {  
    //printf("\nWrite"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_write;
}

[r|R][e|E][a|A][d|D]      {  
    //printf("\nren"); 
    add_to_table(yytext, "Keyword");
    strcpy(yylval.string, yytext);
    return T_READ;
}

[a-zA-Z][a-zA-Z0-9_]*   { 
    //printf("\nLex:Identifier: %s", yytext); 
    add_to_table(yytext, "Identifier"); 
    strcpy(yylval.string, yytext);
    return ID;
}

[a-zA-Z][a-zA-Z0-9_]*[ ]*"["[ ]*[a-zA-Z0-9]+[ ]*"]"[ ]*   {
    strcpy(yylval.string, yytext);
        return ArrElement;
}

[a-zA-Z]    { 
                //yylval.t.v.cval=yytext[0]; //printf("\nLex : Reading Char"); 
                strcpy(yylval.string, yytext);
                return T_CHAR; 
            }

[0-9]+      { 

    //printf("\nLex : Found a number: %s", yytext);
    strcpy(yylval.string, yytext);
    return NUM; 
}

[0-9]+".."[0-9]+  { 
    //printf("\nLex : Found RANGE %s", yytext);
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return RANGE; 
}

"."     { 
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return DOT;
}

[0-9]+\.[0-9]*   { 

    //printf("\nFLOAT"); 
    strcpy(yylval.string, yytext);
    return FLOAT; 
}

","   {
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return COMMA;
}

";"    { 
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return SC;
}

":"     { 
    //printf("\nColon"); 
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return COL;
}

"("     { 
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return OB;
}

")"     { 
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return CB;
}

":="     { 
    //printf("\nAssignment operator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return AS;
}

"+"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return PLUS;
}

"-"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return MINUS;
}

"/"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return DIV;
}

"*"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return MUL;
}

"%"       { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return REM;
}

"="       { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return EQUAL;
}

"<>"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return NEQ;
}

"<"        { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return LT;
}

">"         { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return GT;
}

"<="        { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return LE;
}

">="        { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    strcpy(yylval.string, yytext);
    return GE;
}

"["     {
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return SOB;
}

"]"     {
    add_to_table(yytext, "Seperator");
    strcpy(yylval.string, yytext);
    return SCB;
}

.      { 
    //printf("\nsaw something");
    /* Handle other tokens */ 
}

%%

