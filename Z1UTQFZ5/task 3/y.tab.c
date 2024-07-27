/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "Z1UTQFZ5.y"

//final for task 3 and 4

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "y.tab.h"
//int yylex();
float fans = 0.0;
int ians = 0;
extern int yylineno;
int currLine = 1;
//value that identifiers hols => can be of different types
typedef union {
    int ival;
    float fval;
    char cval;
    int bval;
    // Other types as needed.
} Value;

//for identifiers
typedef struct Symbol {
    char* id;
    char* type;
    int isArray;
    int size;
    int initialized; // 0 for no, 1 for yes
    Value value;     // To store the value
    struct Symbol* next;
} Symbol;

Symbol* symbolTable = NULL;
Symbol *varlist = NULL;
char ids[100][100];

#include <stdio.h>

void traverseVarList(Symbol *varlist) 
{
    Symbol *current = varlist;
    initializeSymbol(current->id);
    current = current->next;
    
}

char* trimWhitespace(char *str) {
    char *end;
    // Trim leading space
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

void printChars(const char* str) {
    while (*str) {
        printf("%d ", (unsigned char)*str); // Print ASCII value of each character
        str++;
    }
    printf("\n");
}

Symbol* lookupSymbol(char* id) {

    //printf("\nLooking for %s: ", id);
    trimWhitespace(id);
    //printChars(id);
    for (Symbol* sym = symbolTable; sym; sym = sym->next) {
        //printf("\nAt %s: ", sym->id);
        //printChars(sym->id);
        if (strcmp(sym->id, id) == 0) {
            return sym;
        }
    }
    return NULL;
}

void addSymbol(char* id, char* type, int isArray) {
    Symbol* sym = lookupSymbol(id);
    if (sym != NULL) {
        // Symbol already present, just update the type if it's currently set as 'dummy'
        if (strcmp(sym->type, "dummy") == 0) {
            free(sym->type);
            sym->type = strdup(type);
        }
    } else {
        // Add new symbol to the table
        sym = (Symbol*)malloc(sizeof(Symbol));
        sym->id = strdup(id);
        sym->type = strdup(type);
        sym->initialized = 0; // Default as uninitialized
        sym->isArray = isArray;
        sym->next = symbolTable;
        symbolTable = sym;
    }

    if (strcmp(type, "int") == 0) {
        sym->value.ival = 0; // Assuming integer type
    } 
    else if (strcmp(type, "float") == 0) {
        sym->value.fval = 0.0f; // Assuming float type
    }
    else if (strcmp(type, "char") == 0) {
        sym->value.cval = 'z'; // Assuming char type
    }
    else if (strcmp(type, "boolean") == 0) {
        sym->value.bval = 1; // Assuming boolean type
    }
}

void addArrayToSymbolTable(char* id, char* type, int size)
{
    Symbol* sym = lookupSymbol(id);
    if (sym != NULL) {
        // Symbol already present, just update the type if it's currently set as 'dummy'
        if (strcmp(sym->type, "dummy") == 0) {
            free(sym->type);
            sym->type = strdup(type);
        }
    } else {
        // Add new symbol to the table
        sym = (Symbol*)malloc(sizeof(Symbol));
        sym->id = strdup(id);
        sym->type = strdup(type);
        sym->initialized = 0; // Default as uninitialized
        sym->isArray = 1;
        sym->size = size; 
        sym->next = symbolTable;
        symbolTable = sym;
    }

    if (strcmp(type, "int") == 0) {
        sym->value.ival = 0; // Assuming integer type
    } 
    else if (strcmp(type, "float") == 0) {
        sym->value.fval = 0.0f; // Assuming float type
    }
    else if (strcmp(type, "char") == 0) {
        sym->value.cval = 'z'; // Assuming char type
    }
    else if (strcmp(type, "boolean") == 0) {
        sym->value.bval = 1; // Assuming boolean type
    }
}

void addIdToList(Symbol** head, const char* id) {
    // Create a new symbol node
    Symbol* newSymbol = (Symbol*) malloc(sizeof(Symbol));
    if (newSymbol == NULL) {
        fprintf(stderr, "Failed to allocate memory for new symbol\n");
        return;
    }

    // Set the id field with a copy of the provided identifier
    newSymbol->id = strdup(id);
    if (newSymbol->id == NULL) {
        fprintf(stderr, "Failed to allocate memory for symbol id\n");
        free(newSymbol);
        return;
    }

    // Optionally set default values for other fields
    newSymbol->type = NULL; // No type since we are just storing ids
    newSymbol->initialized = 0; // Not initialized
    memset(&newSymbol->value, 0, sizeof(Value)); // Reset value

    // Link the new node into the list
    newSymbol->next = *head;
    *head = newSymbol;
}

void printIdList(const Symbol* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("List of Identifiers:\n");
    while (head != NULL) {
        printf("%s\n", head->id); // Print the identifier
        head = head->next; // Move to the next element in the list
    }
}

void freeSymbolList(Symbol* head) {
    Symbol* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->id); // Free the duplicated string
        free(temp); // Free the node itself
    }
}

void initializeSymbol(char* id) {
    Symbol* sym = lookupSymbol(id);
    if (sym) {
        sym->initialized = 1;
    }
}

int isInitialized(char *id){
    Symbol *sym = lookupSymbol(id);
    if(sym->initialized == 0)
        return 0;   // not initialized
    else
        return 1;
}

char* getSymbolType(char* id) {
    Symbol* sym = symbolTable;
    while (sym != NULL) {
        if (strcmp(sym->id, id) == 0) {
            return sym->type;
        }
        sym = sym->next;
    }
    return NULL; // Return NULL if the ID is not found
}

void printSymbolTable() {
    Symbol* sym = symbolTable;
    printf("Symbol Table:\n");
    // Assuming 'ID' width is 10 characters, 'Type' is 8 characters, 'Initialized' is 12 characters, and 'Value' is 10 characters.
    printf("%-10s %-8s %-12s %-10s\n", "ID", "Type", "Initialized", "Value");
    printf("--------------------------------------------------\n");
    while (sym != NULL) {
        printf("%-10s %-8s %-12s ", sym->id, sym->type, sym->initialized ? "Yes" : "No");
        if (sym->initialized) {
            if (strcmp(sym->type, "int") == 0) {
                printf("%-10d", sym->value.ival);
            } 
            else if (strcmp(sym->type, "float") == 0) {
                printf("%-10f", sym->value.fval); // You may want to limit the decimal places using %.2f, for example
            }
            else if (strcmp(sym->type, "char") == 0) {
                printf("%-10c", sym->value.cval);
            }
            else if (strcmp(sym->type, "boolean") == 0) {
                if(sym->value.bval == 0)
                    printf("false");
                else if(sym->value.bval == 1)
                    printf("true");
            }
        } else {
            printf("%-10s", "N/A"); // For uninitialized values, you could print "N/A" or leave it empty
        }
        printf("\n");
        sym = sym->next;
    }
}

void updateSymbolTable() {
    Symbol *sym = symbolTable;
    Symbol *temp = NULL; // Pointer to remember the position of the last dummy
    
    while (sym != NULL) {
        if (strcmp(sym->type, "dummy") == 0) {
            if (!temp) { // First dummy in the sequence
                temp = sym;
            }
        } 
        else {
            if (temp) {
                while (temp != sym) {
                    temp->type = sym->type;
                    temp = temp->next;
                }
                temp = NULL; // Reset temp as all dummies have been updated
            }
        }
        sym = sym->next; 
    }

    // If the list ends with a sequence of dummies and no valid type found afterwards
    if (temp) {
        printf("\nError: No valid type available for trailing dummies starting with ID: %s", temp->id);
    }
}

/*
void updateSymbolValue(char* id, Value value, char* type) {

    printf("\n1.Trying to update value :%s", id);
    
    Symbol* sym = lookupSymbol(id);
    if (sym != NULL && strcmp(sym->type, type) == 0) {
        printf("\n2.Trying to update value");
        if(strcmp(type, "int") == 0) {
            printf("\n3.Trying to update value");
            sym->value.ival = value.ival;
        } 
        else if(strcmp(type, "float") == 0) {
            sym->value.fval = value.fval;
        } 
        else if(strcmp(type, "char") == 0) {
            sym->value.cval = value.cval;
            //printf("\nValue updated to: %c", sym->value.cval); // For debugging
        }
        else if(strcmp(type, "boolean") == 0) {
            sym->value.bval = value.bval;
        } 
        // Add more else if blocks for other types if necessary.
        sym->initialized = 1; // Mark as initialized
    }
}
*/

void updateSymbolValue(char* id, Value value, char* type) {
    //printf("\n1.Trying to update value :%s", id);
    Symbol* sym = lookupSymbol(id);
    if (sym == NULL) {
        printf("\nError: No such symbol found for ID %s", id);
    } else if (strcmp(sym->type, type) != 0) {
        printf("\nError: Type mismatch. Symbol type is %s, attempted update type is %s", sym->type, type);
    } else {
        //printf("\n2.Type matches, attempting to update value.");
        if(strcmp(type, "int") == 0) {
            //printf("\n3.Int type confirmed, updating value to %d.", value.ival);
            sym->value.ival = value.ival;
        } 
        else if(strcmp(type, "float") == 0) {
            //printf("\nFloat type confirmed, updating value to %f.", value.fval);
            sym->value.fval = value.fval;
        } 
        else if(strcmp(type, "char") == 0) {
            //printf("\nChar type confirmed, updating value to %c.", value.cval);
            sym->value.cval = value.cval;
        }
        else if(strcmp(type, "boolean") == 0) {
            //printf("\nBoolean type confirmed, updating value to %d.", value.bval);
            sym->value.bval = value.bval;
        }
        sym->initialized = 1;
    }
}

int temp_counter = 0;  // Global counter for temporary variables
int ifcounter = 0;
int whileCounter = 0;
int forcounter = 0;

char* newTemp() {
    char *temp = (char*) malloc(10);
    sprintf(temp, "t%d", temp_counter++);
    return temp;
}

char* ifLable() {
    char *temp = (char*) malloc(10);
    sprintf(temp, "IL%d", ifcounter);
    return temp;
}

char* ifLableBefore() {
    char *temp = (char*) malloc(10);
    sprintf(temp, "IL%d", ifcounter-1);
    return temp;
}

char* whileLable() {
    char *temp = (char*) malloc(10);
    sprintf(temp, "WL%d", whileCounter);
    return temp;
}

char* whileLableBefore() {
    char *temp = (char*) malloc(10);
    sprintf(temp, "WL%d", whileCounter - 1);
    return temp;
}

char* forLable() {
    char *temp = (char*) malloc(10);
    sprintf(temp, "FL%d", forcounter);
    return temp;
}

char* forLableBefore() {
    char *temp = (char*) malloc(10);
    sprintf(temp, "FL%d", forcounter-1);
    return temp;
}

void printValuesFromList(const Symbol* idList) {
    if (idList == NULL) {
        printf("The list of IDs is empty.\n");
        return;
    }

    Symbol* symbol;
    printf("Values of Variables:\n");
    while (idList != NULL) {
        symbol = lookupSymbol(idList->id);
        if (symbol != NULL) {
            // Check type and print value
            if (strcmp(symbol->type, "int") == 0) {
                printf("%d\n", symbol->value.ival);
            } else if (strcmp(symbol->type, "float") == 0) {
                printf("%f\n", symbol->value.fval);
            } else if (strcmp(symbol->type, "char") == 0) {
                printf("%c\n", symbol->value.cval);
            }
            else if (strcmp(symbol->type, "boolean") == 0) {
                printf("%s\n", symbol->value.bval);
            } 
            else {
                printf("Unknown type or uninitialized variable\n");
            }
        } else {
            printf("Identifier '%s' not found in symbol table.\n", idList->id);
        }
        idList = idList->next; // Move to the next node in the ID list
    }
}

char str[100];

/*******************************/

typedef struct ThreeAddressCode {
    char *code;                       // To store the three-address code string
    struct ThreeAddressCode *next;    // Pointer to the next code entry
} ThreeAddressCode;

ThreeAddressCode *codeList = NULL;   // Head of the list

void addCodeToList(const char *str) {
    ThreeAddressCode *newCode = (ThreeAddressCode *)malloc(sizeof(ThreeAddressCode));
    if (newCode == NULL) {
        fprintf(stderr, "Failed to allocate memory for new code entry\n");
        return;
    }

    newCode->code = strdup(str);  // Duplicate the string for safe storage
    if (newCode->code == NULL) {
        fprintf(stderr, "Failed to allocate memory for code string\n");
        free(newCode);
        return;
    }

    // Link the new node into the list
    newCode->next = codeList;
    codeList = newCode;
}

void printAllCodesInReverse(const ThreeAddressCode *current) {
    if (current == NULL) return; // Base case: end of list
    printAllCodesInReverse(current->next); // Recursive call: go to the end of the list
    printf("\n%s", current->code); // Print on the way back
}

// Then call this function from your existing function
void printAllCodes() {
    printf("\nStored Three-Address Codes in Reverse:\n");
    printAllCodesInReverse(codeList);
}

char* extractArrayName(const char* expression) {
    char* name = strdup(expression);  // Make a copy of the expression to work with
    char* p = strchr(name, '[');      // Find the opening bracket
    if (p) {
        *p = '\0';  // Replace the '[' with a null terminator to end the string
    }
    return name;   // Return the newly created string which stops at '['
}

char* extractIndex(const char* expression) {
    char* start = strchr(expression, '[');
    if (!start) {
        return NULL;  // No '[' found, return NULL
    }
    start++;  // Move past the '['

    char* end = strchr(start, ']');
    if (!end) {
        return NULL;  // No ']' found, return NULL
    }

    // Allocate memory for the index string
    int length = end - start;
    char* index = malloc(length + 1);
    if (index) {
        strncpy(index, start, length);
        index[length] = '\0';  // Null-terminate the string
    }
    return index;
}


#line 572 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    T_INTEGER = 259,               /* T_INTEGER  */
    T_REAL = 260,                  /* T_REAL  */
    T_CHAR = 261,                  /* T_CHAR  */
    T_BOOLEAN = 262,               /* T_BOOLEAN  */
    T_ARRAY = 263,                 /* T_ARRAY  */
    NUM = 264,                     /* NUM  */
    CHAR = 265,                    /* CHAR  */
    FLOAT = 266,                   /* FLOAT  */
    MSG = 267,                     /* MSG  */
    SOB = 268,                     /* SOB  */
    SCB = 269,                     /* SCB  */
    T_OF = 270,                    /* T_OF  */
    RANGE = 271,                   /* RANGE  */
    ArrElement = 272,              /* ArrElement  */
    T_TRUE = 273,                  /* T_TRUE  */
    T_FALSE = 274,                 /* T_FALSE  */
    T_STRING = 275,                /* T_STRING  */
    T_AND = 276,                   /* T_AND  */
    T_OR = 277,                    /* T_OR  */
    T_NOT = 278,                   /* T_NOT  */
    T_PROGRAM = 279,               /* T_PROGRAM  */
    T_VAR = 280,                   /* T_VAR  */
    T_FOR = 281,                   /* T_FOR  */
    T_DO = 282,                    /* T_DO  */
    T_WHILE = 283,                 /* T_WHILE  */
    T_BEGIN = 284,                 /* T_BEGIN  */
    T_END = 285,                   /* T_END  */
    T_write = 286,                 /* T_write  */
    T_READ = 287,                  /* T_READ  */
    COMMA = 288,                   /* COMMA  */
    SC = 289,                      /* SC  */
    COL = 290,                     /* COL  */
    DOT = 291,                     /* DOT  */
    MINUS = 292,                   /* MINUS  */
    DIV = 293,                     /* DIV  */
    MUL = 294,                     /* MUL  */
    REM = 295,                     /* REM  */
    EQUAL = 296,                   /* EQUAL  */
    NEQ = 297,                     /* NEQ  */
    LT = 298,                      /* LT  */
    GT = 299,                      /* GT  */
    LE = 300,                      /* LE  */
    GE = 301,                      /* GE  */
    COMMENT = 302,                 /* COMMENT  */
    OB = 303,                      /* OB  */
    CB = 304,                      /* CB  */
    AS = 305,                      /* AS  */
    PLUS = 306,                    /* PLUS  */
    T_TO = 307,                    /* T_TO  */
    T_ELSE = 308,                  /* T_ELSE  */
    T_THEN = 309,                  /* T_THEN  */
    T_IF = 310,                    /* T_IF  */
    T_DOWNTO = 311                 /* T_DOWNTO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define T_INTEGER 259
#define T_REAL 260
#define T_CHAR 261
#define T_BOOLEAN 262
#define T_ARRAY 263
#define NUM 264
#define CHAR 265
#define FLOAT 266
#define MSG 267
#define SOB 268
#define SCB 269
#define T_OF 270
#define RANGE 271
#define ArrElement 272
#define T_TRUE 273
#define T_FALSE 274
#define T_STRING 275
#define T_AND 276
#define T_OR 277
#define T_NOT 278
#define T_PROGRAM 279
#define T_VAR 280
#define T_FOR 281
#define T_DO 282
#define T_WHILE 283
#define T_BEGIN 284
#define T_END 285
#define T_write 286
#define T_READ 287
#define COMMA 288
#define SC 289
#define COL 290
#define DOT 291
#define MINUS 292
#define DIV 293
#define MUL 294
#define REM 295
#define EQUAL 296
#define NEQ 297
#define LT 298
#define GT 299
#define LE 300
#define GE 301
#define COMMENT 302
#define OB 303
#define CB 304
#define AS 305
#define PLUS 306
#define T_TO 307
#define T_ELSE 308
#define T_THEN 309
#define T_IF 310
#define T_DOWNTO 311

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 502 "Z1UTQFZ5.y"
 
  struct { 
    char type[10]; 
    char *code; //for storing t0,t1,...
    union { 
      char *string;      
      int ival;
      int c1;
      int c2;
      float fval; 
      char cval; 
      char *op;
      int bval;
    } v; 
  } t; 

#line 754 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_T_INTEGER = 4,                  /* T_INTEGER  */
  YYSYMBOL_T_REAL = 5,                     /* T_REAL  */
  YYSYMBOL_T_CHAR = 6,                     /* T_CHAR  */
  YYSYMBOL_T_BOOLEAN = 7,                  /* T_BOOLEAN  */
  YYSYMBOL_T_ARRAY = 8,                    /* T_ARRAY  */
  YYSYMBOL_NUM = 9,                        /* NUM  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_FLOAT = 11,                     /* FLOAT  */
  YYSYMBOL_MSG = 12,                       /* MSG  */
  YYSYMBOL_SOB = 13,                       /* SOB  */
  YYSYMBOL_SCB = 14,                       /* SCB  */
  YYSYMBOL_T_OF = 15,                      /* T_OF  */
  YYSYMBOL_RANGE = 16,                     /* RANGE  */
  YYSYMBOL_ArrElement = 17,                /* ArrElement  */
  YYSYMBOL_T_TRUE = 18,                    /* T_TRUE  */
  YYSYMBOL_T_FALSE = 19,                   /* T_FALSE  */
  YYSYMBOL_T_STRING = 20,                  /* T_STRING  */
  YYSYMBOL_T_AND = 21,                     /* T_AND  */
  YYSYMBOL_T_OR = 22,                      /* T_OR  */
  YYSYMBOL_T_NOT = 23,                     /* T_NOT  */
  YYSYMBOL_T_PROGRAM = 24,                 /* T_PROGRAM  */
  YYSYMBOL_T_VAR = 25,                     /* T_VAR  */
  YYSYMBOL_T_FOR = 26,                     /* T_FOR  */
  YYSYMBOL_T_DO = 27,                      /* T_DO  */
  YYSYMBOL_T_WHILE = 28,                   /* T_WHILE  */
  YYSYMBOL_T_BEGIN = 29,                   /* T_BEGIN  */
  YYSYMBOL_T_END = 30,                     /* T_END  */
  YYSYMBOL_T_write = 31,                   /* T_write  */
  YYSYMBOL_T_READ = 32,                    /* T_READ  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_SC = 34,                        /* SC  */
  YYSYMBOL_COL = 35,                       /* COL  */
  YYSYMBOL_DOT = 36,                       /* DOT  */
  YYSYMBOL_MINUS = 37,                     /* MINUS  */
  YYSYMBOL_DIV = 38,                       /* DIV  */
  YYSYMBOL_MUL = 39,                       /* MUL  */
  YYSYMBOL_REM = 40,                       /* REM  */
  YYSYMBOL_EQUAL = 41,                     /* EQUAL  */
  YYSYMBOL_NEQ = 42,                       /* NEQ  */
  YYSYMBOL_LT = 43,                        /* LT  */
  YYSYMBOL_GT = 44,                        /* GT  */
  YYSYMBOL_LE = 45,                        /* LE  */
  YYSYMBOL_GE = 46,                        /* GE  */
  YYSYMBOL_COMMENT = 47,                   /* COMMENT  */
  YYSYMBOL_OB = 48,                        /* OB  */
  YYSYMBOL_CB = 49,                        /* CB  */
  YYSYMBOL_AS = 50,                        /* AS  */
  YYSYMBOL_PLUS = 51,                      /* PLUS  */
  YYSYMBOL_T_TO = 52,                      /* T_TO  */
  YYSYMBOL_T_ELSE = 53,                    /* T_ELSE  */
  YYSYMBOL_T_THEN = 54,                    /* T_THEN  */
  YYSYMBOL_T_IF = 55,                      /* T_IF  */
  YYSYMBOL_T_DOWNTO = 56,                  /* T_DOWNTO  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_Program = 58,                   /* Program  */
  YYSYMBOL_59_1 = 59,                      /* $@1  */
  YYSYMBOL_VarSec = 60,                    /* VarSec  */
  YYSYMBOL_VarDecl = 61,                   /* VarDecl  */
  YYSYMBOL_CodeBlock = 62,                 /* CodeBlock  */
  YYSYMBOL_stmt_list = 63,                 /* stmt_list  */
  YYSYMBOL_stmt = 64,                      /* stmt  */
  YYSYMBOL_A = 65,                         /* A  */
  YYSYMBOL_Read = 66,                      /* Read  */
  YYSYMBOL_Write = 67,                     /* Write  */
  YYSYMBOL_VarList_Read = 68,              /* VarList_Read  */
  YYSYMBOL_VarList_Write = 69,             /* VarList_Write  */
  YYSYMBOL_IfStmt = 70,                    /* IfStmt  */
  YYSYMBOL_71_2 = 71,                      /* $@2  */
  YYSYMBOL_S = 72,                         /* S  */
  YYSYMBOL_73_3 = 73,                      /* $@3  */
  YYSYMBOL_S1 = 74,                        /* S1  */
  YYSYMBOL_S2 = 75,                        /* S2  */
  YYSYMBOL_Condition = 76,                 /* Condition  */
  YYSYMBOL_WhileLoop = 77,                 /* WhileLoop  */
  YYSYMBOL_78_4 = 78,                      /* $@4  */
  YYSYMBOL_ForLoop = 79,                   /* ForLoop  */
  YYSYMBOL_80_5 = 80,                      /* $@5  */
  YYSYMBOL_81_6 = 81,                      /* $@6  */
  YYSYMBOL_Expr = 82,                      /* Expr  */
  YYSYMBOL_Term = 83,                      /* Term  */
  YYSYMBOL_Factor = 84,                    /* Factor  */
  YYSYMBOL_Operand = 85,                   /* Operand  */
  YYSYMBOL_Type = 86,                      /* Type  */
  YYSYMBOL_Content = 87,                   /* Content  */
  YYSYMBOL_RelOp = 88                      /* RelOp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   187

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   311


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   539,   539,   539,   542,   543,   546,   559,   586,   608,
     611,   614,   615,   618,   619,   620,   621,   622,   623,   624,
     629,   685,   688,   689,   694,   706,   717,   730,   742,   759,
     775,   792,   811,   811,   829,   829,   837,   845,   848,   858,
     902,   933,   967,  1003,  1040,  1041,  1042,  1047,  1047,  1077,
    1077,  1138,  1138,  1196,  1255,  1318,  1326,  1334,  1360,  1423,
    1486,  1512,  1536,  1559,  1585,  1595,  1600,  1608,  1655,  1656,
    1657,  1658,  1661,  1676,  1703,  1704,  1705,  1706,  1707,  1708,
    1709
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "T_INTEGER",
  "T_REAL", "T_CHAR", "T_BOOLEAN", "T_ARRAY", "NUM", "CHAR", "FLOAT",
  "MSG", "SOB", "SCB", "T_OF", "RANGE", "ArrElement", "T_TRUE", "T_FALSE",
  "T_STRING", "T_AND", "T_OR", "T_NOT", "T_PROGRAM", "T_VAR", "T_FOR",
  "T_DO", "T_WHILE", "T_BEGIN", "T_END", "T_write", "T_READ", "COMMA",
  "SC", "COL", "DOT", "MINUS", "DIV", "MUL", "REM", "EQUAL", "NEQ", "LT",
  "GT", "LE", "GE", "COMMENT", "OB", "CB", "AS", "PLUS", "T_TO", "T_ELSE",
  "T_THEN", "T_IF", "T_DOWNTO", "$accept", "Program", "$@1", "VarSec",
  "VarDecl", "CodeBlock", "stmt_list", "stmt", "A", "Read", "Write",
  "VarList_Read", "VarList_Write", "IfStmt", "$@2", "S", "$@3", "S1", "S2",
  "Condition", "WhileLoop", "$@4", "ForLoop", "$@5", "$@6", "Expr", "Term",
  "Factor", "Operand", "Type", "Content", "RelOp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-47)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -14,    13,    31,     1,  -106,    48,    35,    56,    88,  -106,
    -106,    35,   144,    27,  -106,  -106,  -106,  -106,  -106,    43,
      83,  -106,  -106,    89,    58,    66,    76,    58,    97,    27,
    -106,    27,    27,    27,    27,    27,    27,    84,   120,    35,
     109,  -106,  -106,  -106,    30,    72,    58,    61,    98,    96,
     115,  -106,  -106,    81,    22,    37,    74,   124,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,    61,   147,  -106,    61,  -106,
    -106,  -106,    67,  -106,    58,    58,  -106,    61,   140,  -106,
    -106,  -106,  -106,  -106,    61,    61,    80,    80,    80,   129,
     131,   116,   117,   134,   135,   121,   118,  -106,    78,   154,
      49,  -106,  -106,   150,   145,  -106,  -106,  -106,    -4,  -106,
    -106,  -106,    57,    57,   141,   142,    37,    37,   143,   149,
    -106,  -106,   139,    61,    61,    27,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,    27,  -106,  -106,   146,   -24,    -1,
     151,   152,   126,    35,  -106,  -106,   153,   153,   145,  -106,
     145,   145,  -106,  -106,  -106,  -106
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     5,     9,     0,     0,     4,
       2,     9,     0,    19,     6,    68,    69,    70,    71,     0,
       0,    72,    73,     0,     0,     0,     0,     0,     0,    10,
      12,    19,    19,    19,    19,    19,    19,     0,     0,     9,
       0,    64,    65,    66,    55,    56,     0,     0,     0,    44,
      57,    61,    63,    67,     0,     0,    32,     0,    11,    13,
      14,    15,    16,    17,    18,     0,     0,     7,     0,    40,
      55,    56,     0,    67,     0,     0,    47,     0,    74,    75,
      76,    77,    78,    79,     0,     0,     0,     0,     0,    30,
      31,     0,     0,    26,    27,     0,     0,     3,     0,     0,
       0,    62,    41,    42,     0,    54,    80,    53,    39,    59,
      58,    60,     0,     0,     0,     0,     0,     0,     0,     0,
      33,    20,     0,     0,     0,    19,    48,    28,    29,    23,
      22,    24,    25,    21,    19,    34,    36,     0,     0,     0,
       0,     0,     0,     9,    49,    51,     0,    37,     0,     8,
       0,     0,    38,    35,    50,    52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,  -106,  -106,   -11,  -106,  -106,   -27,  -106,  -106,
    -106,    -6,    18,  -106,  -106,  -106,  -106,  -106,  -105,    -9,
    -106,  -106,  -106,  -106,  -106,   -36,  -106,    70,  -106,    51,
     -12,  -106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    13,     7,     9,    28,    29,    30,    31,    32,
      33,    95,    92,    34,    96,   120,   142,   135,   126,    48,
      35,   104,    36,   150,   151,    49,    50,    51,    52,    20,
      73,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    37,    58,   144,    59,    60,    61,    62,    63,    64,
       1,    72,    53,    77,   136,    53,     3,    37,    56,    37,
      37,    37,    37,    37,    37,    89,   145,    84,    67,    98,
      21,     4,   100,    77,    53,     5,    77,    69,     8,    90,
      93,   105,    91,   153,    22,   154,   155,    84,   107,   108,
      84,   -45,   -45,    23,    94,    24,    38,   -45,    25,    26,
      89,    21,    53,    53,    21,   102,   103,    41,    42,    43,
      41,    42,    43,     6,    90,    22,    44,    45,    22,    70,
      71,    46,    27,    21,   -45,    10,    77,   138,   139,    41,
      42,    43,    40,   -46,   -46,    74,    75,    22,   140,   -46,
      84,   123,   -43,   -43,    77,   124,    47,   141,   -43,    47,
     131,   132,   121,    37,    54,    77,   101,    39,    84,    74,
      75,    11,    37,    12,    55,    76,   -46,    57,    47,    84,
     127,   128,   149,    77,    65,   -43,    66,    78,    79,    80,
      81,    82,    83,    15,    16,    17,    18,    84,    15,    16,
      17,    18,    19,    86,    87,    88,   109,   110,   111,    68,
      97,    99,   112,   106,   113,   114,   115,   116,   117,   122,
     118,    74,   119,   137,   125,   129,   130,   133,   134,   148,
     143,   146,   147,     0,     0,     0,     0,   152
};

static const yytype_int16 yycheck[] =
{
      11,    13,    29,    27,    31,    32,    33,    34,    35,    36,
      24,    47,    24,    37,   119,    27,     3,    29,    27,    31,
      32,    33,    34,    35,    36,     3,    27,    51,    39,    65,
       3,     0,    68,    37,    46,    34,    37,    46,     3,    17,
       3,    77,    20,   148,    17,   150,   151,    51,    84,    85,
      51,    21,    22,    26,    17,    28,    13,    27,    31,    32,
       3,     3,    74,    75,     3,    74,    75,     9,    10,    11,
       9,    10,    11,    25,    17,    17,    18,    19,    17,    18,
      19,    23,    55,     3,    54,    29,    37,   123,   124,     9,
      10,    11,     3,    21,    22,    21,    22,    17,   125,    27,
      51,    52,    21,    22,    37,    56,    48,   134,    27,    48,
     116,   117,    34,   125,    48,    37,    49,    34,    51,    21,
      22,    33,   134,    35,    48,    27,    54,    30,    48,    51,
     112,   113,   143,    37,    50,    54,    16,    41,    42,    43,
      44,    45,    46,     4,     5,     6,     7,    51,     4,     5,
       6,     7,     8,    38,    39,    40,    86,    87,    88,    50,
      36,    14,    33,    23,    33,    49,    49,    33,    33,    15,
      49,    21,    54,   122,    29,    34,    34,    34,    29,    53,
      34,    30,    30,    -1,    -1,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    24,    58,     3,     0,    34,    25,    60,     3,    61,
      29,    33,    35,    59,    61,     4,     5,     6,     7,     8,
      86,     3,    17,    26,    28,    31,    32,    55,    62,    63,
      64,    65,    66,    67,    70,    77,    79,    87,    13,    34,
       3,     9,    10,    11,    18,    19,    23,    48,    76,    82,
      83,    84,    85,    87,    48,    48,    76,    30,    64,    64,
      64,    64,    64,    64,    64,    50,    16,    61,    50,    76,
      18,    19,    82,    87,    21,    22,    27,    37,    41,    42,
      43,    44,    45,    46,    51,    88,    38,    39,    40,     3,
      17,    20,    69,     3,    17,    68,    71,    36,    82,    14,
      82,    49,    76,    76,    78,    82,    23,    82,    82,    84,
      84,    84,    33,    33,    49,    49,    33,    33,    49,    54,
      72,    34,    15,    52,    56,    29,    75,    69,    69,    34,
      34,    68,    68,    34,    29,    74,    75,    86,    82,    82,
      64,    64,    73,    34,    27,    27,    30,    30,    53,    61,
      80,    81,    34,    75,    75,    75
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    59,    58,    60,    60,    61,    61,    61,    61,
      62,    63,    63,    64,    64,    64,    64,    64,    64,    64,
      65,    66,    67,    67,    68,    68,    68,    68,    69,    69,
      69,    69,    71,    70,    73,    72,    72,    74,    75,    76,
      76,    76,    76,    76,    76,    76,    76,    78,    77,    80,
      79,    81,    79,    82,    82,    82,    82,    82,    83,    83,
      83,    83,    84,    84,    85,    85,    85,    85,    86,    86,
      86,    86,    87,    87,    88,    88,    88,    88,    88,    88,
      88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     2,     0,     3,     5,    10,     0,
       1,     2,     1,     2,     2,     2,     2,     2,     2,     0,
       4,     5,     5,     5,     3,     3,     1,     1,     3,     3,
       1,     1,     0,     4,     0,     5,     2,     3,     4,     3,
       2,     3,     3,     1,     1,     1,     1,     0,     5,     0,
       9,     0,     9,     3,     3,     1,     1,     1,     3,     3,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 539 "Z1UTQFZ5.y"
                                         { updateSymbolTable();}
#line 2064 "y.tab.c"
    break;

  case 6: /* VarDecl: ID COMMA VarDecl  */
#line 546 "Z1UTQFZ5.y"
                           {
            
            //printf("\n1.ID1");
            //printf("\n1.ID1: %s", $<t.v.string>1);
            if(lookupSymbol((yyvsp[-2].t.v.string))) {
                printf("\n%d : Duplicate declareation: %s",currLine, (yyvsp[-2].t.v.string));
                //exit(1);
                currLine++;
            }
            else
                addSymbol((yyvsp[-2].t.v.string), "dummy", 0);
            free((yyvsp[-2].t.v.string));
        }
#line 2082 "y.tab.c"
    break;

  case 7: /* VarDecl: ID COL Type SC VarDecl  */
#line 559 "Z1UTQFZ5.y"
                                 {
            
            //printf("\n2.ID: %s\n", $<t.v.string>1);
            if(lookupSymbol((yyvsp[-4].t.v.string))) {
                printf("\n%d : Duplicate declareation: %s", currLine, (yyvsp[-4].t.v.string));
                //exit(1);
                currLine++;
            }
            else if(strcmp((yyvsp[-2].t.type), "int") == 0) {
                //printf("\nint");
                addSymbol((yyvsp[-4].t.v.string), "int", 0);
            }
            else if(strcmp((yyvsp[-2].t.type), "char") == 0) {
                //printf("\nchar");
                addSymbol((yyvsp[-4].t.v.string), "char", 0);
            }
            else if(strcmp((yyvsp[-2].t.type) , "float") == 0) {
                //printf("\nfloat");
                addSymbol((yyvsp[-4].t.v.string), "float", 0);
            }
            else if(strcmp((yyvsp[-2].t.type), "boolean") == 0) {
                //printf("\nboolean");
                addSymbol((yyvsp[-4].t.v.string), "boolean", 0);
            }
            free((yyvsp[-4].t.v.string));
            
        }
#line 2114 "y.tab.c"
    break;

  case 8: /* VarDecl: ID COL T_ARRAY SOB RANGE SCB T_OF Type SC VarDecl  */
#line 586 "Z1UTQFZ5.y"
                                                            {            
            
            //addArrayToSymbolTable($<t.v.string>1, $<t.type>8, $<t.v.ival>5);
            if(lookupSymbol((yyvsp[-9].t.v.string)))
                printf("\nDuplicate declaration: %s", (yyvsp[-9].t.v.string));
            else {
                // Add the whole array to the symbol table with its complete type
                addArrayToSymbolTable((yyvsp[-9].t.v.string), (yyvsp[-2].t.type), (yyvsp[-5].t.v.ival));
                //printf("\nlower : %d", $<t.v.c1>5);
                //printf("\nUpper : %d", $<t.v.c2>5);
                // Loop to add each element
                for(int i = 0; i <= (yyvsp[-5].t.v.c2); i++) {
                    // Construct the name for each element, e.g., numbers[1], numbers[2], etc.
                    char elementName[100]; // Adjust size as needed
                    sprintf(elementName, "%s[%d]", (yyvsp[-9].t.v.string), i);
                    // Add each element to the symbol table as an individual entry
                    addSymbol(elementName, (yyvsp[-2].t.type), 1);
                }
            //free(baseType);
    }
                            
        }
#line 2141 "y.tab.c"
    break;

  case 20: /* A: Content AS Expr SC  */
#line 629 "Z1UTQFZ5.y"
                        {    
                            //printf("\n$<t.v.string>1 = %s",$<t.v.string>1);                 
                            if(strcmp((yyvsp[-3].t.type), "int") == 0 && strcmp((yyvsp[-1].t.type), "int") == 0){
                                Value val;
                                val.ival = (yyvsp[-1].t.v.ival);
                                updateSymbolValue((yyvsp[-3].t.v.string), val, "int");
                                char buffer1[100];
                                sprintf(buffer1, "%d : %s = %d", currLine, (yyvsp[-3].t.v.string), (yyvsp[-1].t.v.ival));
                                currLine++;
                                addCodeToList(buffer1);
                            }
                            else if(strcmp((yyvsp[-3].t.type), "float") == 0 && strcmp((yyvsp[-1].t.type), "int") == 0){
                                Value val;
                                val.fval = (yyvsp[-1].t.v.ival);
                                updateSymbolValue((yyvsp[-3].t.v.string), val, "float");
                                char buffer2[100];
                                sprintf(buffer2, "%d : %s = %d", currLine, (yyvsp[-3].t.v.string), (yyvsp[-1].t.v.ival));
                                currLine++;
                                addCodeToList(buffer2);
                            }                            
                            else if(strcmp((yyvsp[-3].t.type), "float") == 0 && strcmp((yyvsp[-1].t.type), "float") == 0){
                                Value val;
                                val.fval = (yyvsp[-1].t.v.fval);
                                updateSymbolValue((yyvsp[-3].t.v.string), val, "float");
                                char buffer3[100];
                                sprintf(buffer3, "%d : %s = %d", currLine, (yyvsp[-3].t.v.string), (yyvsp[-1].t.v.ival));
                                currLine++;
                                addCodeToList(buffer3);
                            }
                            else if(strcmp((yyvsp[-3].t.type), "char") == 0 && strcmp((yyvsp[-1].t.type), "char") == 0){
                                Value val;
                                val.cval = (yyvsp[-1].t.v.cval);
                                updateSymbolValue((yyvsp[-3].t.v.string), val, "char");
                                char buffer4[100];
                                sprintf(buffer4, "%d : %s = %d", currLine, (yyvsp[-3].t.v.string), (yyvsp[-1].t.v.ival));
                                currLine++;
                                addCodeToList(buffer4);
                            }
                            else if(strcmp((yyvsp[-3].t.type), "boolean") == 0 && strcmp((yyvsp[-1].t.type), "boolean") == 0){
                                Value val;                                
                                val.bval = (yyvsp[-1].t.v.bval);                                
                                char buffer5[100];
                                updateSymbolValue((yyvsp[-3].t.v.string), val, "boolean");                            
                                sprintf(buffer5, "%d : %s = %d", currLine, (yyvsp[-3].t.v.string), (yyvsp[-1].t.v.ival));
                                currLine++;
                                addCodeToList(buffer5);
                            }
                            else
                            {
                                printf("\n...Assignment operation types are mismatched\n");
                                printf("\n$<t.type>1 = %s and $<t.type>3 = %s", (yyvsp[-3].t.type), (yyvsp[-1].t.type));
                                //exit(1);
                            }     
                        }
#line 2200 "y.tab.c"
    break;

  case 23: /* Write: T_write OB T_STRING CB SC  */
#line 689 "Z1UTQFZ5.y"
                                   {
                                        strcpy((yyvsp[-2].t.type), "string");                                                                                
                                   }
#line 2208 "y.tab.c"
    break;

  case 24: /* VarList_Read: ID COMMA VarList_Read  */
#line 694 "Z1UTQFZ5.y"
                                      {                                
                                Symbol* sym = lookupSymbol((yyvsp[-2].t.v.string));
                                if(!sym) {
                                    printf("\nUndeclared Identifier: %s", (yyvsp[-2].t.v.string));
                                    //exit(1);
                                }
                                else {
                                    strcpy((yyval.t.type), sym->type);
                                    addIdToList(&varlist, (yyvsp[-2].t.v.string));
                                }                                
                            }
#line 2224 "y.tab.c"
    break;

  case 25: /* VarList_Read: ArrElement COMMA VarList_Read  */
#line 706 "Z1UTQFZ5.y"
                                         {
                                        Symbol* sym = lookupSymbol(extractArrayName((yyvsp[-2].t.v.string)));
                                            if(!sym) {
                                                printf("\nUndeclared Identifier: %s", extractArrayName((yyvsp[-2].t.v.string)));
                                                //exit(1);
                                            }
                                            else {
                                                strcpy((yyval.t.type), sym->type);
                                                addIdToList(&varlist, (yyvsp[-2].t.v.string)); //add the whole numbers[i];
                                            }                                
                                    }
#line 2240 "y.tab.c"
    break;

  case 26: /* VarList_Read: ID  */
#line 717 "Z1UTQFZ5.y"
                {                    
                    Symbol* sym = lookupSymbol((yyvsp[0].t.v.string));
                    sym->initialized = 1;
                    //traverseVarList(varlist);
                    if(!sym) {
                        printf("\n...mmUndeclared Identifier: %s", (yyvsp[0].t.v.string));
                        //exit(1);
                    } 
                    else {
                        strcpy((yyval.t.type), sym->type);
                        addIdToList(&varlist, (yyvsp[0].t.v.string));
                    }                    
                }
#line 2258 "y.tab.c"
    break;

  case 27: /* VarList_Read: ArrElement  */
#line 730 "Z1UTQFZ5.y"
                        {
                            Symbol* sym = lookupSymbol(extractArrayName((yyvsp[0].t.v.string)));
                            if(!sym) {
                                printf("\n...Undeclared Identifier: %s", extractArrayName((yyvsp[0].t.v.string)));
                                //exit(1);
                            } 
                            Symbol *sym1 = lookupSymbol((yyvsp[0].t.v.string));
                            strcpy((yyval.t.type), sym->type);
                            addIdToList(&varlist, (yyvsp[0].t.v.string));
                        }
#line 2273 "y.tab.c"
    break;

  case 28: /* VarList_Write: ID COMMA VarList_Write  */
#line 742 "Z1UTQFZ5.y"
                                        {                                
                                Symbol* sym = lookupSymbol((yyvsp[-2].t.v.string));
                                if(!sym) {
                                    printf("\nUndeclared Identifier: %s", (yyvsp[-2].t.v.string));
                                    //exit(1);
                                } 
                                else if(sym->initialized == 0 && sym->isArray != 0)
                                {
                                    printf("\nNot initialized: %s", (yyvsp[-2].t.v.string));
                                    //exit(1);
                                } 
                                else {
                                    strcpy((yyval.t.type), sym->type);
                                    addIdToList(&varlist, (yyvsp[-2].t.v.string));
                                }                                
                            }
#line 2294 "y.tab.c"
    break;

  case 29: /* VarList_Write: ArrElement COMMA VarList_Write  */
#line 759 "Z1UTQFZ5.y"
                                          {
                                        Symbol* sym = lookupSymbol(extractArrayName((yyvsp[-2].t.v.string)));
                                            if(!sym) {
                                                printf("\nUndeclared Identifier: %s", extractArrayName((yyvsp[-2].t.v.string)));
                                                //exit(1);
                                            } 
                                            else if(sym->initialized == 0)
                                            {
                                                printf("\nNot initialized: %s", extractArrayName((yyvsp[-2].t.v.string)));
                                                //exit(1);
                                            } 
                                            else {
                                                strcpy((yyval.t.type), sym->type);
                                                addIdToList(&varlist, (yyvsp[-2].t.v.string)); //add the whole numbers[i];
                                            }                                
                                    }
#line 2315 "y.tab.c"
    break;

  case 30: /* VarList_Write: ID  */
#line 775 "Z1UTQFZ5.y"
                {                    
                    Symbol* sym = lookupSymbol((yyvsp[0].t.v.string));
                    //traverseVarList(varlist);
                    if(!sym) {
                        printf("\n...mmUndeclared Identifier: %s", (yyvsp[0].t.v.string));
                        //exit(1);
                    } 
                    else if(sym->initialized == 0)
                    {                       
                        printf("\n...Not initialized: %s", (yyvsp[0].t.v.string));
                        //exit(1);
                    }
                    else {
                        strcpy((yyval.t.type), sym->type);
                        addIdToList(&varlist, (yyvsp[0].t.v.string));
                    }                    
                }
#line 2337 "y.tab.c"
    break;

  case 31: /* VarList_Write: ArrElement  */
#line 792 "Z1UTQFZ5.y"
                        {
                            Symbol* sym = lookupSymbol(extractArrayName((yyvsp[0].t.v.string)));
                            if(!sym) {
                                printf("\n...Undeclared Identifier: %s", extractArrayName((yyvsp[0].t.v.string)));
                                //exit(1);
                            } 
                            Symbol *sym1 = lookupSymbol((yyvsp[0].t.v.string));
                            if(sym1 != NULL && sym1->initialized == 0)
                            {
                                printf("\n??Not initialized: %s", (yyvsp[0].t.v.string));
                                //exit(1);
                            }
                            else {
                                strcpy((yyval.t.type), sym->type);
                                addIdToList(&varlist, (yyvsp[0].t.v.string));
                            }
                        }
#line 2359 "y.tab.c"
    break;

  case 32: /* $@2: %empty  */
#line 811 "Z1UTQFZ5.y"
                         {      
                                char buffer1[100];
                                char buffer2[100];
                                char buffer3[100];
                                strcpy((yyvsp[0].t.type), "int");
                                char *IL0 = ifLable();
                                sprintf(buffer1, "%d : if %s then goto %s", currLine, (yyvsp[0].t.code), IL0); currLine++; //IL0
                                ifcounter++;                       
                                char *IL1 = ifLable();
                                sprintf(buffer2, "%d : goto %s", currLine, IL1); currLine++; //IL1                                
                                sprintf(buffer3, "%d : %s", currLine, IL0); currLine++; // IL0
                                addCodeToList(buffer1);
                                addCodeToList(buffer2);
                                addCodeToList(buffer3);
                            }
#line 2379 "y.tab.c"
    break;

  case 34: /* $@3: %empty  */
#line 829 "Z1UTQFZ5.y"
              {
                char buffer4[100];
                ifcounter++;
                char *IL1 = ifLable();
                sprintf(buffer4, "%d : %s", currLine, IL1); currLine++; //IL1
                addCodeToList(buffer4);
              }
#line 2391 "y.tab.c"
    break;

  case 36: /* S: T_THEN S2  */
#line 837 "Z1UTQFZ5.y"
                {
                    char buffer5[100];
                    char *IL1 = ifLable(); //IL1
                    sprintf(buffer5, "%d : %s", currLine, IL1); currLine++; //L1
                    addCodeToList(buffer5);
                }
#line 2402 "y.tab.c"
    break;

  case 38: /* S2: T_BEGIN stmt T_END SC  */
#line 848 "Z1UTQFZ5.y"
                           {
    // StmtList is a list of statements inside the block
    // for (int i = 0; i < stmt_list.size(); i++) {
    //     // executeStatement(stmt_list[i]);
    //     printf("here1");
    // }
    //printf("Hello");
}
#line 2415 "y.tab.c"
    break;

  case 39: /* Condition: Expr RelOp Expr  */
#line 858 "Z1UTQFZ5.y"
                                {
                                    strcpy((yyval.t.type), "boolean");
                                    if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "int") == 0)
                                    {
                                        char buffer1[100];
                                        char *temp = newTemp();
                                        (yyval.t.code) = temp;
                                        sprintf(buffer1, "%d : %s = %s %s %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[-1].t.code), (yyvsp[0].t.code));
                                        currLine++;
                                        addCodeToList(buffer1);                                                                  
                                    }
                                    else if(strcmp((yyvsp[-2].t.type), "boolean") == 0 && strcmp((yyvsp[0].t.type), "boolean") == 0)
                                    {
                                        char buffer2[100];
                                        char *temp = newTemp();
                                        (yyval.t.code) = temp;
                                        sprintf(buffer2, "%d : %s = %s %s %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[-1].t.code), (yyvsp[0].t.code));
                                        currLine++;
                                        addCodeToList(buffer2);
                                        
                                    }
                                    else if(strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "char") == 0)
                                    {
                                        char buffer3[100];
                                        char *temp = newTemp();
                                        (yyval.t.code) = temp;
                                        sprintf(buffer3, "%d : %s = %s %s %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[-1].t.code), (yyvsp[0].t.code));
                                        currLine++;
                                        addCodeToList(buffer3);                             
                                    }
                                    else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "float") == 0)
                                    {
                                        char buffer4[100];
                                        char *temp = newTemp();
                                        (yyval.t.code) = temp;
                                        sprintf(buffer4, "%d : %s = %s %s %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[-1].t.code), (yyvsp[0].t.code));
                                        currLine++;
                                        addCodeToList(buffer4);                             
                                    }
                                    else{
                                        printf("\nError in Condition, check types, %s RelOp %s", (yyvsp[-2].t.type), (yyvsp[0].t.type));
                                        //exit(1);
                                    }
                                }
#line 2464 "y.tab.c"
    break;

  case 40: /* Condition: T_NOT Condition  */
#line 902 "Z1UTQFZ5.y"
                                {
                                    strcpy((yyval.t.type), "boolean");
                                    if(strcmp((yyvsp[0].t.type), "int") == 0 || strcmp((yyvsp[0].t.type), "boolean") == 0)
                                    {
                                        Value val;
                                        if(strcmp((yyvsp[0].t.type), "int") == 0) {                                
                                            if((yyvsp[0].t.v.ival) > 0)
                                                val.bval = 0;
                                            else
                                                val.bval = 1;
                                        }
                                        else if(strcmp((yyvsp[0].t.type), "boolean") == 0){                                 
                                            if((yyvsp[0].t.v.bval) == 1)
                                                val.bval = 0;
                                            else
                                                val.bval = 1;
                                        }   
                                        (yyval.t.v.bval) = val.bval;
                                        char *temp = newTemp();
                                        (yyval.t.code) = temp;
                                        char buffer1[100];
                                        sprintf(buffer1, "%d : %s = NOT %s",currLine, (yyval.t.code), (yyvsp[0].t.code));
                                        addCodeToList(buffer1);
                                        currLine++;
                                    }
                                    else
                                    {
                                        printf("\nError in Condition\n");
                                        //exit(1);
                                    }                                    
                                }
#line 2500 "y.tab.c"
    break;

  case 41: /* Condition: Condition T_AND Condition  */
#line 933 "Z1UTQFZ5.y"
                                        {
                                            strcpy((yyval.t.type), "boolean"); 
                                            if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "int") == 0 
                                            || strcmp((yyvsp[-2].t.type), "boolean") == 0 && strcmp((yyvsp[0].t.type), "boolean") == 0 ) {
                                            
                                                char *temp = newTemp();
                                                (yyval.t.code) = temp;
                                                char buffer1[100];                                            
                                                sprintf(buffer1, "%d : %s = %s AND %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                                currLine++;
                                                addCodeToList(buffer1);
                                                Value val;
                                                if(strcmp((yyvsp[-2].t.type), "int") == 0)
                                                {
                                                    if((yyvsp[-2].t.v.ival) > 0 && (yyvsp[0].t.v.ival) > 0)
                                                        val.bval = 1;
                                                    else
                                                        val.bval = 0;
                                                }
                                                if(strcmp((yyvsp[-2].t.type), "boolean") == 0)
                                                {
                                                    if((yyvsp[-2].t.v.bval) == 1 && (yyvsp[0].t.v.bval) == 1)
                                                        val.bval = 1;
                                                    else
                                                        val.bval = 0;
                                                }
                                                (yyval.t.v.bval) = val.bval;                                               
                                            }                                            
                                            else
                                            {
                                                printf("\nError in Condition\n");
                                                //exit(1);
                                            }
                                        }
#line 2539 "y.tab.c"
    break;

  case 42: /* Condition: Condition T_OR Condition  */
#line 967 "Z1UTQFZ5.y"
                                        {
                                            if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "int") == 0 
                                            || strcmp((yyvsp[-2].t.type), "boolean") == 0 && strcmp((yyvsp[0].t.type), "boolean") == 0 
                                            || strcmp((yyvsp[-2].t.type), "boolean") == 0 && strcmp((yyvsp[0].t.type), "int") == 0
                                            || strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "boolean") == 0) {
                                                //printf("\nFine");                                                
                                                strcpy((yyval.t.type), "boolean");
                                                char *temp = newTemp();                                                
                                                (yyval.t.code) = temp;
                                                char buffer1[100];
                                                sprintf(buffer1, "%d : %s = %s OR %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                                currLine++;
                                                addCodeToList(buffer1);
                                                Value val;
                                                if(strcmp((yyvsp[-2].t.type), "int") == 0)
                                                {
                                                    if((yyvsp[-2].t.v.ival) > 0 || (yyvsp[0].t.v.ival) > 0)
                                                        val.bval = 1;
                                                    else
                                                        val.bval = 0;
                                                }
                                                if(strcmp((yyvsp[-2].t.type), "boolean") == 0)
                                                {
                                                    if((yyvsp[-2].t.v.bval) == 1 || (yyvsp[0].t.v.bval) == 1)
                                                        val.bval = 1;
                                                    else
                                                        val.bval = 0;
                                                }
                                                (yyval.t.v.bval) = val.bval;                                              
                                            }
                                            else
                                            {
                                                printf("\nError in Condition\n");
                                                //(1);
                                            }
                                        }
#line 2580 "y.tab.c"
    break;

  case 43: /* Condition: Content  */
#line 1003 "Z1UTQFZ5.y"
                                    {
                                        Symbol *sym = lookupSymbol((yyvsp[0].t.v.string));
                                        if(!sym)
                                        {
                                            printf("\nError: variable not declared");
                                            //exit(1);
                                        }
                                        else if(sym->initialized == 0)
                                        {
                                            printf("\nError: variable not Initialized");
                                            //exit(1);
                                        }                                     
                                    
                                        (yyval.t.code) = (yyvsp[0].t.code);
                                        strcpy((yyval.t.type), (yyvsp[0].t.type));
                                        if(strcmp((yyvsp[0].t.type), "int") == 0)
                                        {
                                            (yyval.t.v.ival) = (yyvsp[0].t.v.ival);
                                        }
                                        else if(strcmp((yyvsp[0].t.type), "boolean") == 0)
                                        {
                                            (yyval.t.v.bval) = (yyvsp[0].t.v.bval);
                                        }
                                        else if(strcmp((yyvsp[0].t.type), "char") == 0)
                                        {
                                            (yyval.t.v.cval) = (yyvsp[0].t.v.cval);
                                        }
                                        else if(strcmp((yyvsp[0].t.type), "float") == 0)
                                        {
                                            (yyval.t.v.fval) = (yyvsp[0].t.v.fval);
                                        }                                        
                                        else{
                                            printf("\nError in Condition\n");
                                            //exit(1);
                                        }
                                    }
#line 2621 "y.tab.c"
    break;

  case 44: /* Condition: Expr  */
#line 1040 "Z1UTQFZ5.y"
                                    { (yyval.t.code) = (yyvsp[0].t.code); strcpy((yyval.t.type), (yyvsp[0].t.type)); }
#line 2627 "y.tab.c"
    break;

  case 45: /* Condition: T_TRUE  */
#line 1041 "Z1UTQFZ5.y"
                                    { (yyval.t.code) = (yyvsp[0].t.code); strcpy((yyval.t.type), "boolean"); (yyvsp[0].t.v.bval) = 1; (yyval.t.v.bval) = 1; }
#line 2633 "y.tab.c"
    break;

  case 46: /* Condition: T_FALSE  */
#line 1042 "Z1UTQFZ5.y"
                                    { (yyval.t.code) = (yyvsp[0].t.code); strcpy((yyval.t.type), "boolean"); (yyvsp[0].t.v.bval) = 0; (yyval.t.v.bval) = 0; }
#line 2639 "y.tab.c"
    break;

  case 47: /* $@4: %empty  */
#line 1047 "Z1UTQFZ5.y"
                                    {
                                        char *WL0 = whileLable();
                                        whileCounter++;
                                        char *WL1 = whileLable();
                                        char buffer1[100];
                                        char buffer2[100];
                                        char buffer3[100];
                                        sprintf(buffer1, "%d : %s : if %s then goto %s", currLine, WL0, (yyvsp[-1].t.code), WL1); currLine++;
                                        whileCounter++;
                                        char *WL2 = whileLable();
                                        sprintf(buffer2, "%d : goto %s", currLine, WL2); currLine++;
                                        WL1 = whileLableBefore();
                                        sprintf(buffer3,"%d : %s", currLine, WL1); currLine++;
                                        addCodeToList(buffer1);
                                        addCodeToList(buffer2);
                                        addCodeToList(buffer3);
                                    }
#line 2661 "y.tab.c"
    break;

  case 48: /* WhileLoop: T_WHILE Condition T_DO $@4 S2  */
#line 1063 "Z1UTQFZ5.y"
                                            {
                                                char buffer1[100];
                                                char buffer2[100];
                                                whileCounter--;
                                                char *WL0 = whileLableBefore();
                                                sprintf(buffer1, "%d : goto %s", currLine, WL0); currLine++;
                                                whileCounter++;
                                                char *WL2 = whileLable();
                                                sprintf(buffer2, "%d : %s", currLine, WL2); currLine++;
                                                addCodeToList(buffer1);
                                                addCodeToList(buffer2);
                                            }
#line 2678 "y.tab.c"
    break;

  case 49: /* $@5: %empty  */
#line 1077 "Z1UTQFZ5.y"
                                          {  //check point 2 : removed loop variable initialised or not
                                                char buffer1[100];
                                                char buffer2[100];
                                                char buffer3[100];
                                                char *FL0 = forLable(); forcounter++;
                                                char *FL1 = forLable(); forcounter++;
                                                char *FL2 = forLable();
                                                sprintf(buffer1, "%d : %s : if %s <= %s then goto %s", currLine, FL0, (yyvsp[-5].t.v.string), (yyvsp[-1].t.code), FL1); currLine++;
                                                sprintf(buffer2, "%d : goto %s", currLine, FL2); currLine++;
                                                sprintf(buffer3, "%d : %s :", currLine, FL1); currLine++;

                                                addCodeToList(buffer1);
                                                addCodeToList(buffer2);
                                                addCodeToList(buffer3);
                                                
                                            }
#line 2699 "y.tab.c"
    break;

  case 50: /* ForLoop: T_FOR ID AS Expr T_TO Expr T_DO $@5 S2  */
#line 1093 "Z1UTQFZ5.y"
                                                {
                                                    Symbol* sym = lookupSymbol((yyvsp[-7].t.v.string));
                                                    if(sym == NULL) {
                                                        printf("\nError: Loop variable not declared: %s", (yyvsp[-7].t.v.string));
                                                        //exit(1);
                                                    }
                                                    else if(strcmp(sym->type, "int") != 0)
                                                    {
                                                        printf("\nControl assignment ID not int type");
                                                        //exit(1);
                                                    }                                                    
                                                    else if((strcmp((yyvsp[-5].t.type), "int") != 0 || strcmp((yyvsp[-3].t.type), "int") != 0))
                                                    {
                                                        printf("\nControls are not int");
                                                        //exit(1);
                                                    }                                                    
                                                    else if((yyvsp[-5].t.v.ival) <= (yyvsp[-3].t.v.ival)){ 
                                                        printf("\nInitializing loop variable : %s", (yyvsp[-7].t.v.string));
                                                        initializeSymbol((yyvsp[-7].t.v.string));
                                                        Value val;
                                                        val.ival = (yyvsp[-5].t.v.ival);
                                                        updateSymbolValue((yyvsp[-7].t.v.string), val, "int");                           
                                                        sym->value.ival = (yyvsp[-5].t.v.ival);
                                                        sym->initialized = 1;  
                                                        //printf("\ncontro1 : %d", $<t.v.ival>4);
                                                        //printf("\ncontro2 : %d", $<t.v.ival>6);
                                                        //for loop functionality                                                  
                                                    }
                                                    else{
                                                        printf("\nError: Controls are wrongly arranged");
                                                        //exit(1);
                                                    }
                                                    
                                                    char buffer1[100];
                                                    char buffer2[100];
                                                    char *FL2 = forLable(); 
                                                    char *FL1 = forLableBefore(); forcounter--;
                                                    char *FL0 = forLableBefore(); 
                                                    sprintf(buffer1, "%d : goto %s",currLine, FL0); currLine++;
                                                    sprintf(buffer2, "%d : %s",currLine, FL2); currLine++;
                                                    addCodeToList(buffer1);
                                                    addCodeToList(buffer2);
                                                }
#line 2747 "y.tab.c"
    break;

  case 51: /* $@6: %empty  */
#line 1138 "Z1UTQFZ5.y"
                                                {
                                                    
                                                    char buffer1[100];
                                                    char buffer2[100];
                                                    char buffer3[100];
                                                    char *FL0 = forLable(); forcounter++;
                                                    char *FL1 = forLable(); forcounter++;
                                                    char *FL2 = forLable();
                                                    sprintf(buffer1, "%d : %s : if %s >= %s then goto %s", currLine, FL0, (yyvsp[-5].t.v.string), (yyvsp[-1].t.code), FL1); currLine++;
                                                    sprintf(buffer2, "%d : goto %s", currLine, FL2); currLine++;
                                                    sprintf(buffer3, "%d : %s :", currLine, FL1); currLine++;
                                                    addCodeToList(buffer1);
                                                    addCodeToList(buffer2);
                                                    addCodeToList(buffer3);

                                                }
#line 2768 "y.tab.c"
    break;

  case 52: /* ForLoop: T_FOR ID AS Expr T_DOWNTO Expr T_DO $@6 S2  */
#line 1153 "Z1UTQFZ5.y"
                                                        {
                                                    Symbol* sym = lookupSymbol((yyvsp[-7].t.v.string));
                                                    if(sym == NULL) {
                                                        printf("\nError: Loop variable not declared: %s", (yyvsp[-7].t.v.string));
                                                    }
                                                    else if(strcmp(sym->type, "int") != 0)
                                                    {
                                                        printf("\nControl assignment ID not int type");
                                                        //exit(1);
                                                    }
                                                    else if((strcmp((yyvsp[-5].t.type), "int") != 0 || strcmp((yyvsp[-3].t.type), "int") != 0))
                                                    {
                                                        printf("\nControls are not int");
                                                        //exit(1);
                                                    }
                                                    else if((yyvsp[-5].t.v.ival) > (yyvsp[-3].t.v.ival)){                            
                                                        sym->value.ival = (yyvsp[-5].t.v.ival);
                                                        sym->initialized = 1;
                                                        printf("\nInitializing loop variable : %s", (yyvsp[-7].t.v.string));
                                                        initializeSymbol((yyvsp[-7].t.v.string));
                                                        Value val;
                                                        val.ival = (yyvsp[-5].t.v.ival);
                                                        updateSymbolValue((yyvsp[-7].t.v.string), val, "int");
                                                        printf("\ncontro1 : %d", (yyvsp[-5].t.v.ival));
                                                        printf("\ncontro2 : %d", (yyvsp[-3].t.v.ival));
                                                        //for loop functionality                                                  
                                                    }
                                                    else{
                                                        printf("\nError: Controls are wrongly arranged");
                                                        //exit(1);
                                                    }
                                                    char buffer1[100];
                                                    char buffer2[100];
                                                    char *FL2 = forLable(); 
                                                    char *FL1 = forLableBefore(); forcounter--;
                                                    char *FL0 = forLableBefore(); 
                                                    sprintf(buffer1, "%d : goto %s",currLine, FL0); currLine++;
                                                    sprintf(buffer2, "%d : %s",currLine, FL2); currLine++;
                                                    addCodeToList(buffer1);
                                                    addCodeToList(buffer2);
                                                }
#line 2814 "y.tab.c"
    break;

  case 53: /* Expr: Expr PLUS Expr  */
#line 1196 "Z1UTQFZ5.y"
                        {
                            //printf("\nIn Plus");    
                            if((strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) ||
                                (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                (strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) ) {
                                printf("At least One of the operands is char type cannot perform arithmetic\n");
                                //exit(1);
                            } 
                            else if (strcmp((yyvsp[-2].t.type), "boolean") == 0 || strcmp((yyvsp[0].t.type), "boolean") == 0) {
                                printf("Error: cannot perform '+' operation on boolean types.\n");
                                //exit(1);
                            }
                            else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) {
                                (yyval.t.v.fval) = (yyvsp[-2].t.v.fval) + (yyvsp[0].t.v.fval);
                                fans = (yyval.t.v.fval);
                                strcpy((yyval.t.type), "float");
                                char *temp = newTemp();
                                (yyval.t.code) = temp;
                                char buffer1[100];                           
                                sprintf(buffer1, "%d : %s = %s + %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));  
                                currLine++;
                                addCodeToList(buffer1);                           
                            } 
                            else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                (yyval.t.v.fval) = (yyvsp[-2].t.v.fval) + (yyvsp[0].t.v.ival);
                                fans = (yyval.t.v.fval);
                                strcpy((yyval.t.type), "float");
                                char *temp = newTemp();
                                (yyval.t.code) = temp;                               
                                char buffer1[100];                           
                                sprintf(buffer1, "%d : %s = %s + %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));  
                                currLine++;
                                addCodeToList(buffer1);
                            } 
                            else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) {
                                (yyval.t.v.fval) = (yyvsp[-2].t.v.ival) + (yyvsp[0].t.v.fval);
                                fans = (yyval.t.v.fval);
                                strcpy((yyval.t.type), "float");
                                char *temp = newTemp();
                                (yyval.t.code) = temp;                               
                                char buffer1[100];                           
                                sprintf(buffer1, "%d : %s = %s + %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));  
                                currLine++;
                                addCodeToList(buffer1);
                            } 
                            else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                (yyval.t.v.ival) = (yyvsp[-2].t.v.ival) + (yyvsp[0].t.v.ival);
                                ians = (yyval.t.v.ival);
                                strcpy((yyval.t.type), "int");
                                char *temp = newTemp();
                                (yyval.t.code) = temp;                               
                                char buffer1[100];                           
                                sprintf(buffer1, "%d : %s = %s + %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));  
                                currLine++;
                                addCodeToList(buffer1);
                            } 
                        }
#line 2878 "y.tab.c"
    break;

  case 54: /* Expr: Expr MINUS Expr  */
#line 1255 "Z1UTQFZ5.y"
                            { 
                                if((strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "int") == 0)) {
                                    printf("5.At least One of the operands is char type cannot perform arithmetic\n");
                                    //exit(1);
                                }
                                else if (strcmp((yyvsp[-2].t.type), "boolean") == 0 || strcmp((yyvsp[0].t.type), "boolean") == 0) {
                                    printf("Error: cannot perform '-' operation on boolean types.\n");
                                    //exit(1);
                                }
                                else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.fval) - (yyvsp[0].t.v.fval);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("\n6.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                           
                                    sprintf(buffer1, "%d : %s = %s - %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));  
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.fval) - (yyvsp[0].t.v.ival);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("\n7.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                           
                                    sprintf(buffer1, "%d : %s = %s - %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));  
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.ival) - (yyvsp[0].t.v.fval);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("\n8.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                           
                                    sprintf(buffer1, "%d : %s = %s - %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));  
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                    (yyval.t.v.ival) = (yyvsp[-2].t.v.ival) - (yyvsp[0].t.v.ival);
                                    ians = (yyval.t.v.ival);
                                    strcpy((yyval.t.type), "int");
                                    //printf("\n9.Result of expression is %s and value is: %d", $<t.type>$, ians);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                           
                                    sprintf(buffer1, "%d : %s = %s - %s", currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));  
                                    currLine++;
                                    addCodeToList(buffer1);
                                }
                                //return 0; 
                            }
#line 2946 "y.tab.c"
    break;

  case 55: /* Expr: T_TRUE  */
#line 1318 "Z1UTQFZ5.y"
                {
                    strcpy((yyval.t.type), "boolean");
                    (yyval.t.v.bval) = 1;
                    int num = 1;                                        
                    (yyvsp[0].t.code) = (char *)malloc(20 * sizeof(char));
                    sprintf((yyvsp[0].t.code), "%d", num);
                    (yyval.t.code) = (yyvsp[0].t.code);
                }
#line 2959 "y.tab.c"
    break;

  case 56: /* Expr: T_FALSE  */
#line 1326 "Z1UTQFZ5.y"
                 {
                    strcpy((yyval.t.type), "boolean");
                    (yyval.t.v.bval) = 0;
                    int num = 0;                                            
                    (yyvsp[0].t.code) = (char *)malloc(20 * sizeof(char));
                    sprintf((yyvsp[0].t.code), "%d", num);
                    (yyval.t.code) = (yyvsp[0].t.code);
                }
#line 2972 "y.tab.c"
    break;

  case 57: /* Expr: Term  */
#line 1334 "Z1UTQFZ5.y"
                            {
                                if(strcmp((yyvsp[0].t.type), "int") == 0){
                                    strcpy((yyval.t.type), "int");
                                    (yyval.t.v.ival) = (yyvsp[0].t.v.ival);
                                    (yyval.t.code) = (yyvsp[0].t.code);
                                }

                                else if(strcmp((yyvsp[0].t.type), "char") == 0){
                                    strcpy((yyval.t.type), "char");
                                    (yyval.t.v.cval) = (yyvsp[0].t.v.cval);
                                    (yyval.t.code) = (yyvsp[0].t.code);
                                }

                                else if(strcmp((yyvsp[0].t.type), "float") == 0){
                                    strcpy((yyval.t.type), "float");
                                    (yyval.t.v.fval) = (yyvsp[0].t.v.fval);
                                    (yyval.t.code) = (yyvsp[0].t.code);
                                }
                                else if(strcmp((yyvsp[0].t.type), "boolean") == 0){
                                    strcpy((yyval.t.type), "boolean");
                                    (yyval.t.v.bval) = (yyvsp[0].t.v.bval);
                                    (yyval.t.code) = (yyvsp[0].t.code);
                                }                              
                            }
#line 3001 "y.tab.c"
    break;

  case 58: /* Term: Term MUL Factor  */
#line 1360 "Z1UTQFZ5.y"
                            {   //printf("\n3. $<t.type>1 = %s", $<t.type>1);
                                if((strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "int") == 0)) {
                                    printf("At least One of the operands is char type cannot perform arithmetic\n");
                                    //exit(1);
                                } 
                                else if (strcmp((yyvsp[-2].t.type), "boolean") == 0 || strcmp((yyvsp[0].t.type), "boolean") == 0) {
                                    printf("Error: cannot perform '*' operation on boolean types.\n");
                                    //exit(1);
                                }
                                else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.fval) * (yyvsp[0].t.v.fval);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("\n10.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s * %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.fval) * (yyvsp[0].t.v.ival);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("\n11.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s * %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.ival) * (yyvsp[0].t.v.fval);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("\n12.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s * %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                    (yyval.t.v.ival) = (yyvsp[-2].t.v.ival) * (yyvsp[0].t.v.ival);
                                    ians = (yyval.t.v.ival);
                                    strcpy((yyval.t.type), "int");
                                    //printf("\n13.Result of expression is %s and value is: %d", $<t.type>$, ians);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s * %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                }
                                //return 0; 
                            }
#line 3069 "y.tab.c"
    break;

  case 59: /* Term: Term DIV Factor  */
#line 1423 "Z1UTQFZ5.y"
                            {
                                //printf("\n4. $<t.type>1 = %s", $<t.type>1);
                                if((strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "int") == 0)) {
                                    printf("At least One of the operands is char type cannot perform arithmetic\n");
                                } 
                                else if (strcmp((yyvsp[-2].t.type), "boolean") == 0 || strcmp((yyvsp[0].t.type), "boolean") == 0) {
                                    printf("Error: cannot perform '/' operation on boolean types.\n");
                                    //exit(1);
                                }
                                else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.fval) / (yyvsp[0].t.v.fval);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("14.Result of expression is %s and value is: %f\n", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.fval) / (yyvsp[0].t.v.ival);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("15.Result of expression is %s and value is: %f\n", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) {
                                    (yyval.t.v.fval) = (yyvsp[-2].t.v.ival) / (yyvsp[0].t.v.fval);
                                    fans = (yyval.t.v.fval);
                                    strcpy((yyval.t.type), "float");
                                    //printf("16.Result of expression is %s and value is: %f\n", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                    (yyval.t.v.ival) = (yyvsp[-2].t.v.ival) / (yyvsp[0].t.v.ival);
                                    ians = (yyval.t.v.ival);
                                    strcpy((yyval.t.type), "int");
                                    //printf("17.Result of expression is %s and value is: %d\n", $<t.type>$, ians);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                }
                                //return 0; 
                            }
#line 3137 "y.tab.c"
    break;

  case 60: /* Term: Term REM Factor  */
#line 1486 "Z1UTQFZ5.y"
                            { 
                                if((strcmp((yyvsp[-2].t.type), "float") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "float") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "char") == 0) ||
                                    (strcmp((yyvsp[-2].t.type), "char") == 0 && strcmp((yyvsp[0].t.type), "int") == 0)) {
                                    printf("At least One of the operands is char type cannot perform arithmetic\n");
                                }
                                else if (strcmp((yyvsp[-2].t.type), "boolean") == 0 || strcmp((yyvsp[0].t.type), "boolean") == 0) {
                                    printf("Error: cannot perform (%) operation on boolean types.\n");
                                    //exit(1);
                                }
                                else if(strcmp((yyvsp[-2].t.type), "int") == 0 && strcmp((yyvsp[0].t.type), "int") == 0) {
                                    (yyval.t.v.ival) = (yyvsp[-2].t.v.ival) % (yyvsp[0].t.v.ival);
                                    ians = (yyval.t.v.ival);
                                    strcpy((yyval.t.type), "int");
                                    //printf("17.Result of expression is %s and value is: %d\n", $<t.type>$, ians);
                                    char *temp = newTemp();
                                    (yyval.t.code) = temp;
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, (yyval.t.code), (yyvsp[-2].t.code), (yyvsp[0].t.code));
                                    currLine++;
                                    addCodeToList(buffer1);
                                }
                                //return 0; 
                            }
#line 3168 "y.tab.c"
    break;

  case 61: /* Term: Factor  */
#line 1512 "Z1UTQFZ5.y"
                            { 
                                if(strcmp((yyvsp[0].t.type), "int") == 0){
                                    strcpy((yyval.t.type), "int");
                                    (yyval.t.v.ival) = (yyvsp[0].t.v.ival);
                                    (yyval.t.code) = (yyvsp[0].t.code);
                                }
                                else if(strcmp((yyvsp[0].t.type), "char") == 0){
                                    strcpy((yyval.t.type), "char");
                                    (yyval.t.v.cval) = (yyvsp[0].t.v.cval);
                                    (yyval.t.code) = (yyvsp[0].t.code);
                                }
                                else if(strcmp((yyvsp[0].t.type), "float") == 0){
                                    strcpy((yyval.t.type), "float");
                                    (yyval.t.v.fval) = (yyvsp[0].t.v.fval);
                                    (yyval.t.code) = (yyvsp[0].t.code);
                                }
                                else if(strcmp((yyvsp[0].t.type), "boolean") == 0){
                                    strcpy((yyval.t.type), "boolean");
                                    (yyval.t.v.bval) = (yyvsp[0].t.v.bval);
                                    (yyval.t.code) = (yyvsp[0].t.code);
                                }       
                            }
#line 3195 "y.tab.c"
    break;

  case 62: /* Factor: OB Expr CB  */
#line 1536 "Z1UTQFZ5.y"
                        { 
                            //printf("\nFound brackets");
                            if(strcmp((yyvsp[-1].t.type), "int") == 0){
                                strcpy((yyval.t.type), "int");
                                (yyval.t.v.ival) = (yyvsp[-1].t.v.ival);
                                (yyval.t.code) = (yyvsp[-1].t.code);
                            }
                            else if(strcmp((yyvsp[-1].t.type), "char") == 0){
                                strcpy((yyval.t.type), "char");
                                (yyval.t.v.cval) = (yyvsp[-1].t.v.cval);
                                (yyval.t.code) = (yyvsp[-1].t.code);
                            }
                            else if(strcmp((yyvsp[-1].t.type), "float") == 0){
                                strcpy((yyval.t.type), "float");
                                (yyval.t.v.fval) = (yyvsp[-1].t.v.fval);
                                (yyval.t.code) = (yyvsp[-1].t.code);
                            }
                            else if(strcmp((yyvsp[-1].t.type), "boolean") == 0){
                                strcpy((yyval.t.type), "boolean");
                                (yyval.t.v.bval) = (yyvsp[-1].t.v.bval);
                                (yyval.t.code) = (yyvsp[-1].t.code);
                            }                                    
                        }
#line 3223 "y.tab.c"
    break;

  case 63: /* Factor: Operand  */
#line 1559 "Z1UTQFZ5.y"
                        { 
                            if(strcmp((yyvsp[0].t.type), "int") == 0){
                                strcpy((yyval.t.type), "int");
                                (yyval.t.v.ival) = (yyvsp[0].t.v.ival);
                                (yyval.t.code) = (yyvsp[0].t.code);
                                //printf("\nOperand: $<t.code>$ = %s", $<t.code>$);
                                //printf("\nOperand: $<t.code>1 = %s", $<t.code>1);
                            }
                            else if(strcmp((yyvsp[0].t.type), "char") == 0){
                                strcpy((yyval.t.type), "char");
                                (yyval.t.v.cval) = (yyvsp[0].t.v.cval);
                                (yyval.t.code) = (yyvsp[0].t.code);
                            }
                            else if(strcmp((yyvsp[0].t.type), "float") == 0){
                                strcpy((yyval.t.type), "float");
                                (yyval.t.v.fval) = (yyvsp[0].t.v.fval);
                                (yyval.t.code) = (yyvsp[0].t.code);
                            } 
                            else if(strcmp((yyvsp[0].t.type), "boolean") == 0){
                                strcpy((yyval.t.type), "boolean");
                                (yyval.t.v.bval) = (yyvsp[0].t.v.bval);
                                (yyval.t.code) = (yyvsp[0].t.code);
                            }                             
                        }
#line 3252 "y.tab.c"
    break;

  case 64: /* Operand: NUM  */
#line 1585 "Z1UTQFZ5.y"
                    { 
                        strcpy((yyval.t.type), "int");
                        (yyval.t.v.ival) = (yyvsp[0].t.v.ival); 
                        int num = (yyvsp[0].t.v.ival);                                               
                        (yyvsp[0].t.code) = (char *)malloc(20 * sizeof(char)); // Allocate memory for the string.
                        sprintf((yyvsp[0].t.code), "%d", num);
                        (yyval.t.code) = (yyvsp[0].t.code);
                        //printf("\nNUM: $<t.code>$ = %s", $<t.code>$);
                        //printf("\nNUM: $<t.code>1 = %s", $<t.code>1);
                    }
#line 3267 "y.tab.c"
    break;

  case 65: /* Operand: CHAR  */
#line 1595 "Z1UTQFZ5.y"
                    {
                        strcpy((yyval.t.type), "char");
                        (yyval.t.v.cval) = (yyvsp[0].t.v.cval);
                        (yyval.t.code) = (yyvsp[0].t.v.cval);
                    }
#line 3277 "y.tab.c"
    break;

  case 66: /* Operand: FLOAT  */
#line 1600 "Z1UTQFZ5.y"
                    {
                        strcpy((yyval.t.type), "float");
                        (yyval.t.v.fval) = (yyvsp[0].t.v.fval);
                        double numf = (yyvsp[0].t.v.fval);                                               
                        (yyvsp[0].t.code) = (char *)malloc(20 * sizeof(char)); // Allocate memory for the string.
                        sprintf((yyvsp[0].t.code), "%f", numf);
                        (yyval.t.code) = (yyvsp[0].t.code);
                    }
#line 3290 "y.tab.c"
    break;

  case 67: /* Operand: Content  */
#line 1608 "Z1UTQFZ5.y"
                    {
                        Symbol* sym = lookupSymbol((yyvsp[0].t.v.string));
                        
                        if(!sym) {
                            printf("\n Undeclared Identifier: %s", (yyvsp[0].t.v.string));
                            char *name = extractArrayName((yyvsp[0].t.v.string));
                            Symbol *sym1 = lookupSymbol(name);
                            //printf("\n is it an array = %d", sym1->isArray); 
                            if(sym1->isArray == 1)                           
                                printf("\nUninitialised Array Element = %s", (yyvsp[0].t.v.string) );
                            //else
                                //exit(1);
                        } 
                        else if(!sym->initialized && sym->isArray == 0) {
                            printf("\nUninitialized Identifier: %s", (yyvsp[0].t.v.string));
                            strcpy((yyval.t.type), "string");
                            strcpy((yyval.t.v.string), (yyvsp[0].t.v.string));                            
                            //exit(1);
                        }
                        else {
                            // type of the content is type of the ID
                            strcpy((yyval.t.type), sym->type);
                            // Retrieve and set the value based on the type
                            if(strcmp(sym->type, "int") == 0) 
                            {
                                (yyval.t.v.ival) = sym->value.ival;
                                (yyval.t.code) = (yyvsp[0].t.code);
                            } 
                            else if(strcmp(sym->type, "float") == 0)
                            {
                                (yyval.t.v.fval) = sym->value.fval;
                                (yyval.t.code) = (yyvsp[0].t.code);
                            } 
                            else if(strcmp(sym->type, "char") == 0)
                            {
                                (yyval.t.v.cval) = sym->value.cval;
                                (yyval.t.code) = (yyvsp[0].t.code);
                            }
                            else if(strcmp(sym->type, "boolean") == 0)
                            {
                                (yyval.t.v.bval) = sym->value.bval;
                                (yyval.t.code) = (yyvsp[0].t.code);
                            } 
                        }
                    }
#line 3340 "y.tab.c"
    break;

  case 68: /* Type: T_INTEGER  */
#line 1655 "Z1UTQFZ5.y"
                    { strcpy((yyval.t.type), "int"); }
#line 3346 "y.tab.c"
    break;

  case 69: /* Type: T_REAL  */
#line 1656 "Z1UTQFZ5.y"
                    { strcpy((yyval.t.type), "float"); }
#line 3352 "y.tab.c"
    break;

  case 70: /* Type: T_CHAR  */
#line 1657 "Z1UTQFZ5.y"
                    { strcpy((yyval.t.type), "char"); }
#line 3358 "y.tab.c"
    break;

  case 71: /* Type: T_BOOLEAN  */
#line 1658 "Z1UTQFZ5.y"
                    { strcpy((yyval.t.type), "boolean"); }
#line 3364 "y.tab.c"
    break;

  case 72: /* Content: ID  */
#line 1661 "Z1UTQFZ5.y"
             {
                updateSymbolTable();
                //printf("\n1.Here");
                //printSymbolTable();
                (yyval.t.v.string) = (yyvsp[0].t.v.string);
                Symbol* sym = lookupSymbol((yyvsp[0].t.v.string));
                if(!sym) {
                    printf("\nUndeclared Identifier: %s", (yyvsp[0].t.v.string));
                    //exit(1);
                } 
                else {
                    strcpy((yyval.t.type), sym->type);
                    (yyval.t.code) = (yyvsp[0].t.v.string);
                }
            }
#line 3384 "y.tab.c"
    break;

  case 73: /* Content: ArrElement  */
#line 1676 "Z1UTQFZ5.y"
                        {
                            //printf("\n2.Here");
                            Symbol* sym = lookupSymbol(extractArrayName((yyvsp[0].t.v.string)));
                            if(!sym){
                                printf("\nUndeclared Array Element: %s", (yyvsp[0].t.v.string));
                                //exit(1);
                            }
                            else{
                                strcpy((yyval.t.type), sym->type);
                                (yyval.t.code) = (yyvsp[0].t.v.string);
                                if (sym->initialized) {
                                    if (strcmp(sym->type, "int") == 0) {
                                        (yyval.t.v.ival) = sym->value.ival;
                                    } else if (strcmp(sym->type, "float") == 0) {
                                        (yyval.t.v.fval) = sym->value.fval;
                                    } else if (strcmp(sym->type, "char") == 0) {
                                        (yyval.t.v.cval) = sym->value.cval;
                                    } else if (strcmp(sym->type, "boolean") == 0) {
                                        (yyval.t.v.bval) = sym->value.bval;
                                    }
                                }
                            }
                        }
#line 3412 "y.tab.c"
    break;

  case 74: /* RelOp: EQUAL  */
#line 1703 "Z1UTQFZ5.y"
                 { (yyval.t.v.op) = "=";  strcpy((yyval.t.type), "op"); (yyval.t.code) = (yyval.t.v.op); }
#line 3418 "y.tab.c"
    break;

  case 75: /* RelOp: NEQ  */
#line 1704 "Z1UTQFZ5.y"
                 { (yyval.t.v.op) = "!="; strcpy((yyval.t.type), "op"); (yyval.t.code) = (yyval.t.v.op); }
#line 3424 "y.tab.c"
    break;

  case 76: /* RelOp: LT  */
#line 1705 "Z1UTQFZ5.y"
                 { (yyval.t.v.op) = "<";  strcpy((yyval.t.type), "op"); (yyval.t.code) = (yyval.t.v.op); }
#line 3430 "y.tab.c"
    break;

  case 77: /* RelOp: GT  */
#line 1706 "Z1UTQFZ5.y"
                 { (yyval.t.v.op) = ">";  strcpy((yyval.t.type), "op"); (yyval.t.code) = (yyval.t.v.op); }
#line 3436 "y.tab.c"
    break;

  case 78: /* RelOp: LE  */
#line 1707 "Z1UTQFZ5.y"
                 { (yyval.t.v.op) = "<="; strcpy((yyval.t.type), "op"); (yyval.t.code) = (yyval.t.v.op); }
#line 3442 "y.tab.c"
    break;

  case 79: /* RelOp: GE  */
#line 1708 "Z1UTQFZ5.y"
                 { (yyval.t.v.op) = ">="; strcpy((yyval.t.type), "op"); (yyval.t.code) = (yyval.t.v.op); }
#line 3448 "y.tab.c"
    break;

  case 80: /* RelOp: EQUAL T_NOT  */
#line 1709 "Z1UTQFZ5.y"
                        { (yyval.t.v.op) = "= not"; strcpy((yyval.t.type), "op"); (yyval.t.code) = (yyval.t.v.op); }
#line 3454 "y.tab.c"
    break;


#line 3458 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1712 "Z1UTQFZ5.y"


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

    // Parse the input
    if (!yyparse()) {
        printf("\nParsing complete!\n");
    } else {
        printf("\nParsing failed.\n");
    }
    
    // Clean up and close the input file
    fclose(file);

    printSymbolTable();   

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
