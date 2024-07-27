%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>
    #include<limits.h>
    #include<string.h>
    #include<ctype.h>
    #include "graph.c"
    extern FILE *yyin;
    int yylex();
    int ex (nodeType *p, int flag);
	/* function prototype to create a node for an operation */ 
	nodeType *opr(int oper, int nops, ...);
	/* function prototype to create a node for an identifier */
	nodeType *id(char *identifier);
	/* function prototype to create a node for a constat */
	nodeType *con(char *value);

%}
%union{
    int ival;
    nodeType *nPtr;
    char string[100];
} 
%token  MSG SOB SCB T_OF RANGE T_TRUE T_FALSE 

%token  T_AND T_OR T_NOT T_PROGRAM T_VAR T_INTEGER T_REAL T_CHAR T_BOOLEAN
%token T_FOR T_DO T_WHILE T_ARRAY T_BEGIN T_END T_write T_READ
%token COMMA SC COL DOT MINUS DIV MUL REM EQUAL NEQ LT GT LE GE
%token COMMENT OB CB AS PLUS
%token  T_TO T_ELSE T_THEN T_IF T_DOWNTO
%token READ WRITE PRO ASS IF FOR WHILE NOT AND OR
%left T_OR
%left T_AND
%left EQUAL NEQ LT GT LE GE
%left PLUS MINUS
%left MUL DIV REM
%right T_NOT
%type <nPtr> CodeBlock Program VarSec stmt stmt_list A Read Write IfStmt WhileLoop ForLoop Content Expr VarList Condition S2 S1 Term Factor Operand
%type <nPtr> VarDecl 
%token <string> ID T_STRING ArrElement NUM FLOAT 
%%
S : Program {printf("\nFinished\n");ex($1,0);}
  ;
Program : T_PROGRAM ID SC VarSec T_BEGIN CodeBlock T_END DOT  {$$=opr(PRO,2,$4,$6);}  
        ;

VarSec : T_VAR VarDecl  {$$=$2;}   
        |
       ;

VarDecl : ID COMMA VarDecl  {$$=opr(',',2,id($1),$3);}      
        | ID COL Type SC VarDecl  {$$=opr(';',2,id($1),$5);}  
        | ID COL T_ARRAY SOB RANGE SCB T_OF Type SC VarDecl  {$$=opr(';',2,id($1),$10);} 
    |
        ;  

Type : T_INTEGER            
     | T_REAL
     | T_CHAR
     | T_BOOLEAN            
     ;

CodeBlock : stmt  {$$=$1;}  
          ;
stmt : A stmt {$$=opr(';',2,$1,$2);}         
     | Read stmt {$$=opr(';',2,$1,$2);}  
     | Write stmt {$$=opr(';',2,$1,$2);}  
     | IfStmt stmt {$$=opr(';',2,$1,$2);}  
     | WhileLoop stmt {$$=opr(';',2,$1,$2);}  
     | ForLoop stmt {$$=opr(';',2,$1,$2);}  
     | 
     ;

A : Content AS Expr SC  {$$ = opr(';', 2, $1, $3);}      
  ;

Read : T_READ OB VarList CB SC  {$$ = opr(READ,1,$3);} 
     ;

Content : ID {$$=id($1);}
        | ArrElement  {$$=id($1);}
        ;

Write : T_write OB VarList CB SC   {$$ = opr(WRITE,1,$3);} 
      | T_write OB T_STRING CB SC    {$$ = opr(READ,1,id($3));} 
      ;

VarList : ID COMMA VarList {$$=opr(',',2,id($1),$3);}  
        | ArrElement COMMA VarList {$$=opr(',',2,id($1),$3);}  
        | ID {$$ = id($1);}
        | ArrElement {$$ = id($1);}
        ;

IfStmt : T_IF Condition T_THEN S2 {$$=opr(IF,2,$2,$4);}              
       | T_IF Condition T_THEN S1 T_ELSE S2    {$$=opr(IF,3,$2,$4,$6);} 
       ;

S1 : T_BEGIN stmt T_END {$$=$2;}
   ;

S2 : T_BEGIN stmt T_END SC {$$=$2;}
   ;

Condition : Expr EQUAL Expr   {$$ = opr(EQUAL, 2, $1, $3);} 
            |  Expr GT Expr     {$$ = opr(GT, 2, $1, $3);}
            | Expr LT Expr  {$$ = opr(LT, 2, $1, $3);}
            | Expr LE Expr  {$$ = opr(LE, 2, $1, $3);}
            | Expr GE Expr  {$$ = opr(GE, 2, $1, $3);}
            | Expr NEQ Expr  {$$ = opr(NEQ, 2, $1, $3);}
          | OB Condition CB  {$$=$2;}        
          | T_NOT Condition   {$$=opr(NOT,1,$2);}        
          | Condition T_AND Condition {$$=opr(AND,2,$1,$3);}
          | Condition T_OR Condition  {$$=opr(OR,2,$1,$3);}
          | Expr EQUAL T_NOT Expr {$$=opr(EQUAL,2,$1,opr(NOT,1,$4));}
          | Content {$$=$1;}
          ;

WhileLoop : T_WHILE Condition T_DO S2 {$$=opr(WHILE,2,$2,$4);} 
          ;

ForLoop : T_FOR ID AS Expr T_TO Expr T_DO S2    {$$=opr(FOR,3,opr(ASS,id($2),$4),$6,$8);}         
        | T_FOR ID AS Expr T_DOWNTO Expr T_DO S2     {$$=opr(FOR,3,opr(ASS,id($2),$4),$6,$8);}  
        ;

Expr : Expr PLUS Expr       {$$ = opr('+', 2, $1, $3);}
     | Expr MINUS Expr      {$$ = opr('+', 2, $1, $3);}
     | MINUS Expr           {$$=opr('-',1,$2);}
     | Term               {$$=$1;}  
     ;

Term : Term MUL Factor      {$$ = opr('*', 2, $1, $3);}
     | Term DIV Factor      {$$ = opr('/', 2, $1, $3);}
     | Term REM Factor     {$$ = opr('%', 2, $1, $3);}
     | Factor    {$$=$1;}             
     ;

Factor : OB Expr CB      {$$=$2;}     
       | Operand       {$$=$1;}       
       ;

Operand : NUM       {$$ = con($1);}        
        | FLOAT         {$$ = con($1);}    
        | Content {$$=$1;}
        ;
RelOp : EQUAL               
      | NEQ
      | LT
      | GT
      | LE
      | GE
      ;


%%

int main(int argc, char *argv[]) 
{

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    extern FILE *yyin;
    yyin = file; // Set yyin to the file stream
    yyparse();

    
    // Clean up and close the input file
    fclose(file);
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
nodeType *con(char *value)
{
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");
	/* copy information */
	p->type = typeCon;
	strcpy(p->con.value, value);
	return p;
}
nodeType *id(char *identifier) {
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");
	/* copy information */
	p->type = typeId;
	strcpy(p->id.name,identifier);
//	printf("The copied identifier %s\n", p->id.name);
	return p;
}

nodeType *opr(int oper, int nops, ...)
{
	va_list ap;
	nodeType *p;
	int i;
	/* allocate node, extending op array */
	if ((p = malloc(sizeof(nodeType) +(nops-1) * sizeof(nodeType *))) == NULL)
		yyerror("out of memory");
	/* copy information */
	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i = 0; i < nops; i++)
		p->opr.op[i] = va_arg(ap, nodeType*);
	va_end(ap);
	return p;
}