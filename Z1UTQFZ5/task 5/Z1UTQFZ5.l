%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
%option yylineno

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
    //printf("\nLex : saw msg : %s", yytext);
    yylval.t.v.string = strdup(yytext);
    return T_STRING;
}

\'[^\n\"]*\'  {
    //printf("\nsaw quotes");
    //add_to_table(yytext, "Message");
}

[o|O][f|F]  {

    //printf("\nlex: Of: %s", yytext);
    return T_OF;
}

[a|A][n|N][d|D]  { 
    
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return T_AND;
}

[o|O][r|R]    { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return T_OR;
}

[n|N][o|O][t|T]   { 
    //printf("\nLex: NOT Operator"); 
    add_to_table(yytext, "Operator");
    return T_NOT;
}

[p|P][r|R][o|O][g|G][r|R][a|A][m|M]     {

    //printf("\nProgram begins"); 
    add_to_table(yytext, "Keyword");
    return T_PROGRAM;
}

[v|V][a|A][r|R]          { 
    //printf("\nSaw var"); 
    add_to_table(yytext, "Keyword");
    return T_VAR;
}

[i|I][n|N][t|T]      { 

    //printf("\nInteger found"); 
    add_to_table(yytext, "Keyword");
    return T_INTEGER; 
}

[i|I][n|N][t|T][e|E][g|G][e|R][r|R]       { 
    //printf("\nInteger found"); 
    add_to_table(yytext, "Keyword");
    return T_INTEGER; 
}

[r|R][e|E][a|A][l|L]          { 
    //printf("\nReal");
    //yylval.string = strdup("real"); 
    add_to_table(yytext, "Keyword"); 
    return T_REAL;
}

[c|C][h|H][a|A][r|R]        { 
    //printf("\nChar"); 
    //yylval.string = strdup("char");
    add_to_table(yytext, "Keyword");
    return T_CHAR;
}

[b|B][o|O][o|O][l|L][e|E][a|A][n|N]      { 
    //printf("\nboolean"); 
    //yylval.string = strdup("boolean");
    add_to_table(yytext, "Keyword"); 
    return T_BOOLEAN;
}

[f|F][o|O][r|R]      { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    return T_FOR;
}

[i|I][f|F]       {

    add_to_table(yytext, "Keyword"); 
    return T_IF;
}

[e|E][l|L][s|S][e|E]       {

    add_to_table(yytext, "Keyword"); 
    return T_ELSE;
}

[t|T][h|H][e|E][n|N]       {

    add_to_table(yytext, "Keyword"); 
    return T_THEN;
}

[d|D][o|O]      { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    return T_DO;
}

[d|D][o|O][w|W][n|N][t|T][o|O]  {
    add_to_table(yytext, "Keyword"); 
    return T_DOWNTO;
}

[t|T][o|O]     { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    return T_TO;
}

[w|W][h|H][i|I][l|L][e|E]     { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    return T_WHILE;
}

[a|A][r|R][r|R][a|A][y|Y]     { 
    //printf("\nboolean"); 
    add_to_table(yytext, "Keyword"); 
    return T_ARRAY;
}

[b|B][e|E][g|G][i|I][n|N]        { 

    //printf("\nbegin"); 
    add_to_table(yytext, "Keyword"); 
    return T_BEGIN;
}

[e|E][n|N][d|D]          { 

    //printf("\nend"); 
    add_to_table(yytext, "Keyword");
    return T_END;
}

[w|W][r|R][i|I][t|T][e|E]       {  
    //printf("\nWrite"); 
    add_to_table(yytext, "Keyword");
    return T_write;
}

[w|W][r|R][i|I][t|T][e|E][l|L][n|N]       {  
    //printf("\nWrite"); 
    add_to_table(yytext, "Keyword");
    return T_write;
}

[r|R][e|E][a|A][d|D]      {  
    //printf("\nren"); 
    add_to_table(yytext, "Keyword");
    return T_READ;
}

[t|T][r|R][u|U][e|E]    {
    add_to_table(yytext, "Keyword");
    return T_TRUE;
}

[f|F][a|A][l|L][s|S][e|E]   {
    add_to_table(yytext, "Keyword");
    return T_FALSE;
}

[a-zA-Z][a-zA-Z0-9_]*   { 
    //printf("\nLex:Identifier: %s", yytext); 
    yylval.t.v.string = strdup(yytext);
    add_to_table(yytext, "Identifier"); 
    return ID;
}

[a-zA-Z][a-zA-Z0-9_]*[ ]*"["[ ]*[a-zA-Z0-9]+[ ]*"]"[ ]*   {
    yylval.t.v.string = strdup(yytext);
    return ArrElement;
}

[a-zA-Z]    { 
                yylval.t.v.cval=yytext[0]; //printf("\nLex : Reading Char"); 
                return CHAR; 
            }

[0-9]+      { 
    //printf("\nLex: yylval.ival = %d", yylval.t.v.ival);
    yylval.t.v.ival = atoi(yytext);
    return NUM; 
}

[0-9]+".."[0-9]+  { 
    // Debug print the found range
    //printf("\nLex : Found RANGE %s", yytext);
    add_to_table(yytext, "Seperator");

    char *ptr = yytext;
    int lower = atoi(ptr);  // Convert starting numbers to int
    while (*ptr && *ptr != '.') ptr++; // Move pointer to the first dot in ".."

    if (*ptr == '.') {
        ptr += 2; // Move past the ".." to start of upper range
        int upper = atoi(ptr); // Convert ending numbers to int

        yylval.t.v.c1 = lower; // Store lower bound in yylval.t.v.c1
        yylval.t.v.c2 = upper; // Store upper bound in yylval.t.v.c2

        // Additional debug prints to verify correct parsing
        //printf("\nLex : lower = %d", lower);
        //printf("\nLex : higher = %d", upper);

        int size = upper - lower + 1; // Compute size of the array
        if (size > 0) {
            yylval.t.v.ival = size; // Store the size in yylval to use in your parser
            add_to_table(yytext, "Range");
            return RANGE; // Return the RANGE token
        } else {
            fprintf(stderr, "Invalid array range: %s\n", yytext);
            return -1; // Return an error token or handle as needed
        }
    } else {
        fprintf(stderr, "Invalid range format: %s\n", yytext);
        return -1; // Return an error token or handle as needed
    }
}

"."     { 
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    return DOT;
}

[0-9]*[.][1-9]+[0-9]*  {yylval.t.v.fval=atof(yytext);return FLOAT;}

","   {
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    return COMMA;
}

";"    { 
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    return SC;
}

":"     { 
    //printf("\nColon"); 
    add_to_table(yytext, "Seperator");
    return COL;
}

"("     { 
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    return OB;
}

")"     { 
    //printf("\nSeperator"); 
    add_to_table(yytext, "Seperator");
    return CB;
}

":="     { 
    //printf("\nAssignment operator"); 
    add_to_table(yytext, "Operator");
    return AS;
}

"+"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return PLUS;
}

"-"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return MINUS;
}

"/"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return DIV;
}

"*"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return MUL;
}

"%"       { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return REM;
}

"="       { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return EQUAL;
}

"<>"      { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return NEQ;
}

"<"        { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return LT;
}

">"         { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return GT;
}

"<="        { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return LE;
}

">="        { 
    //printf("\nOperator"); 
    add_to_table(yytext, "Operator");
    return GE;
}

"["     {
    add_to_table(yytext, "Seperator");
    return SOB;
}

"]"     {
    add_to_table(yytext, "Seperator");
    return SCB;
}

.      { 
    //printf("\nsaw something");
    /* Handle other tokens */ 
}

%%