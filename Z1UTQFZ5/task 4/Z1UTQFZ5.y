%{
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

%}

%union { 
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
}

%locations
%token ID T_INTEGER T_REAL T_CHAR T_BOOLEAN T_ARRAY 
%token NUM CHAR FLOAT

%token MSG SOB SCB T_OF RANGE ArrElement T_TRUE T_FALSE T_STRING
%token T_AND T_OR T_NOT T_PROGRAM T_VAR
%token T_FOR T_DO T_WHILE T_BEGIN T_END T_write T_READ
%token COMMA SC COL DOT MINUS DIV MUL REM EQUAL NEQ LT GT LE GE
%token COMMENT OB CB AS PLUS
%token T_TO T_ELSE T_THEN T_IF T_DOWNTO

%left T_OR
%left T_AND
%left EQUAL NEQ LT GT LE GE
%left PLUS MINUS
%left MUL DIV REM
%right T_NOT

%%

Program : T_PROGRAM ID SC VarSec T_BEGIN { updateSymbolTable();} CodeBlock T_END DOT  { printAllCodes(); }
        ;

VarSec : T_VAR VarDecl      
       | /* empty */
       ;

VarDecl : ID COMMA VarDecl {
            
            //printf("\n1.ID1");
            //printf("\n1.ID1: %s", $<t.v.string>1);
            if(lookupSymbol($<t.v.string>1)) {
                printf("\n%d : Duplicate declareation: %s",currLine, $<t.v.string>1);
                exit(1);
                currLine++;
            }
            else
                addSymbol($<t.v.string>1, "dummy", 0);
            free($<t.v.string>1);
        }
        | ID COL Type SC VarDecl {
            
            //printf("\n2.ID: %s\n", $<t.v.string>1);
            if(lookupSymbol($<t.v.string>1)) {
                printf("\n%d : Duplicate declareation: %s", currLine, $<t.v.string>1);
                exit(1);
                currLine++;
            }
            else if(strcmp($<t.type>3, "int") == 0) {
                //printf("\nint");
                addSymbol($<t.v.string>1, "int", 0);
            }
            else if(strcmp($<t.type>3, "char") == 0) {
                //printf("\nchar");
                addSymbol($<t.v.string>1, "char", 0);
            }
            else if(strcmp($<t.type>3 , "float") == 0) {
                //printf("\nfloat");
                addSymbol($<t.v.string>1, "float", 0);
            }
            else if(strcmp($<t.type>3, "boolean") == 0) {
                //printf("\nboolean");
                addSymbol($<t.v.string>1, "boolean", 0);
            }
            free($<t.v.string>1);
            
        }
        | ID COL T_ARRAY SOB RANGE SCB T_OF Type SC VarDecl {            
            
            //addArrayToSymbolTable($<t.v.string>1, $<t.type>8, $<t.v.ival>5);
            if(lookupSymbol($<t.v.string>1))
                printf("\nDuplicate declaration: %s", $<t.v.string>1);
            else {
                // Add the whole array to the symbol table with its complete type
                addArrayToSymbolTable($<t.v.string>1, $<t.type>8, $<t.v.ival>5);
                //printf("\nlower : %d", $<t.v.c1>5);
                //printf("\nUpper : %d", $<t.v.c2>5);
                // Loop to add each element
                for(int i = 0; i <= $<t.v.c2>5; i++) {
                    // Construct the name for each element, e.g., numbers[1], numbers[2], etc.
                    char elementName[100]; // Adjust size as needed
                    sprintf(elementName, "%s[%d]", $<t.v.string>1, i);
                    // Add each element to the symbol table as an individual entry
                    addSymbol(elementName, $<t.type>8, 1);
                }
            //free(baseType);
    }
                            
        }   
        |
        ;

CodeBlock : stmt_list           
          ;

stmt_list : stmt_list stmt
          | stmt
          ;

stmt : A stmt           
     | Read stmt
     | Write stmt
     | IfStmt stmt
     | WhileLoop stmt
     | ForLoop stmt
     | 
     ;



A : Content AS Expr SC  {    
                            //printf("\n$<t.v.string>1 = %s",$<t.v.string>1);                 
                            if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0){
                                Value val;
                                val.ival = $<t.v.ival>3;
                                updateSymbolValue($<t.v.string>1, val, "int");
                                char buffer1[100];
                                sprintf(buffer1, "%d : %s = %d", currLine, $<t.v.string>1, $<t.v.ival>3);
                                currLine++;
                                addCodeToList(buffer1);
                            }
                            else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "int") == 0){
                                Value val;
                                val.fval = $<t.v.ival>3;
                                updateSymbolValue($<t.v.string>1, val, "float");
                                char buffer2[100];
                                sprintf(buffer2, "%d : %s = %d", currLine, $<t.v.string>1, $<t.v.ival>3);
                                currLine++;
                                addCodeToList(buffer2);
                            }                            
                            else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "float") == 0){
                                Value val;
                                val.fval = $<t.v.fval>3;
                                updateSymbolValue($<t.v.string>1, val, "float");
                                char buffer3[100];
                                sprintf(buffer3, "%d : %s = %d", currLine, $<t.v.string>1, $<t.v.ival>3);
                                currLine++;
                                addCodeToList(buffer3);
                            }
                            else if(strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "char") == 0){
                                Value val;
                                val.cval = $<t.v.cval>3;
                                updateSymbolValue($<t.v.string>1, val, "char");
                                char buffer4[100];
                                sprintf(buffer4, "%d : %s = %d", currLine, $<t.v.string>1, $<t.v.ival>3);
                                currLine++;
                                addCodeToList(buffer4);
                            }
                            else if(strcmp($<t.type>1, "boolean") == 0 && strcmp($<t.type>3, "boolean") == 0){
                                Value val;                                
                                val.bval = $<t.v.bval>3;                                
                                char buffer5[100];
                                updateSymbolValue($<t.v.string>1, val, "boolean");                            
                                sprintf(buffer5, "%d : %s = %d", currLine, $<t.v.string>1, $<t.v.ival>3);
                                currLine++;
                                addCodeToList(buffer5);
                            }
                            else
                            {
                                printf("\n...Assignment operation types are mismatched\n");
                                printf("\n$<t.type>1 = %s and $<t.type>3 = %s", $<t.type>1, $<t.type>3);
                                exit(1);
                            }     
                        }
  ;

Read : T_READ OB VarList_Read CB SC 
     ;

Write : T_write OB VarList_Write CB SC   
      | T_write OB T_STRING CB SC  {
                                        strcpy($<t.type>3, "string");                                                                                
                                   }
      ;

VarList_Read : ID COMMA VarList_Read  {                                
                                Symbol* sym = lookupSymbol($<t.v.string>1);
                                if(!sym) {
                                    printf("\nUndeclared Identifier: %s", $<t.v.string>1);
                                    exit(1);
                                }
                                else {
                                    strcpy($<t.type>$, sym->type);
                                    addIdToList(&varlist, $<t.v.string>1);
                                }                                
                            }

        | ArrElement COMMA VarList_Read  {
                                        Symbol* sym = lookupSymbol(extractArrayName($<t.v.string>1));
                                            if(!sym) {
                                                printf("\nUndeclared Identifier: %s", extractArrayName($<t.v.string>1));
                                                exit(1);
                                            }
                                            else {
                                                strcpy($<t.type>$, sym->type);
                                                addIdToList(&varlist, $<t.v.string>1); //add the whole numbers[i];
                                            }                                
                                    }
        | ID    {                    
                    Symbol* sym = lookupSymbol($<t.v.string>1);
                    sym->initialized = 1;
                    //traverseVarList(varlist);
                    if(!sym) {
                        printf("\n...mmUndeclared Identifier: %s", $<t.v.string>1);
                        exit(1);
                    } 
                    else {
                        strcpy($<t.type>$, sym->type);
                        addIdToList(&varlist, $<t.v.string>1);
                    }                    
                }
        | ArrElement    {
                            Symbol* sym = lookupSymbol(extractArrayName($<t.v.string>1));
                            if(!sym) {
                                printf("\n...Undeclared Identifier: %s", extractArrayName($<t.v.string>1));
                                exit(1);
                            } 
                            Symbol *sym1 = lookupSymbol($<t.v.string>1);
                            strcpy($<t.type>$, sym->type);
                            addIdToList(&varlist, $<t.v.string>1);
                        }
        ;

VarList_Write : ID COMMA VarList_Write  {                                
                                Symbol* sym = lookupSymbol($<t.v.string>1);
                                if(!sym) {
                                    printf("\nUndeclared Identifier: %s", $<t.v.string>1);
                                    exit(1);
                                } 
                                else if(sym->initialized == 0 && sym->isArray != 0)
                                {
                                    printf("\nNot initialized: %s", $<t.v.string>1);
                                    exit(1);
                                } 
                                else {
                                    strcpy($<t.type>$, sym->type);
                                    addIdToList(&varlist, $<t.v.string>1);
                                }                                
                            }

        | ArrElement COMMA VarList_Write  {
                                        Symbol* sym = lookupSymbol(extractArrayName($<t.v.string>1));
                                            if(!sym) {
                                                printf("\nUndeclared Identifier: %s", extractArrayName($<t.v.string>1));
                                                exit(1);
                                            } 
                                            else if(sym->initialized == 0)
                                            {
                                                printf("\nNot initialized: %s", extractArrayName($<t.v.string>1));
                                                exit(1);
                                            } 
                                            else {
                                                strcpy($<t.type>$, sym->type);
                                                addIdToList(&varlist, $<t.v.string>1); //add the whole numbers[i];
                                            }                                
                                    }
        | ID    {                    
                    Symbol* sym = lookupSymbol($<t.v.string>1);
                    //traverseVarList(varlist);
                    if(!sym) {
                        printf("\n...mmUndeclared Identifier: %s", $<t.v.string>1);
                        exit(1);
                    } 
                    else if(sym->initialized == 0)
                    {                       
                        printf("\n...Not initialized: %s", $<t.v.string>1);
                        exit(1);
                    }
                    else {
                        strcpy($<t.type>$, sym->type);
                        addIdToList(&varlist, $<t.v.string>1);
                    }                    
                }
        | ArrElement    {
                            Symbol* sym = lookupSymbol(extractArrayName($<t.v.string>1));
                            if(!sym) {
                                printf("\n...Undeclared Identifier: %s", extractArrayName($<t.v.string>1));
                                exit(1);
                            } 
                            Symbol *sym1 = lookupSymbol($<t.v.string>1);
                            if(sym1 != NULL && sym1->initialized == 0)
                            {
                                printf("\n??Not initialized: %s", $<t.v.string>1);
                                exit(1);
                            }
                            else {
                                strcpy($<t.type>$, sym->type);
                                addIdToList(&varlist, $<t.v.string>1);
                            }
                        }
        ;

IfStmt : T_IF Condition  {      
                                char buffer1[100];
                                char buffer2[100];
                                char buffer3[100];
                                strcpy($<t.type>2, "int");
                                char *IL0 = ifLable();
                                sprintf(buffer1, "%d : if %s then goto %s", currLine, $<t.code>2, IL0); currLine++; //IL0
                                ifcounter++;                       
                                char *IL1 = ifLable();
                                sprintf(buffer2, "%d : goto %s", currLine, IL1); currLine++; //IL1                                
                                sprintf(buffer3, "%d : %s", currLine, IL0); currLine++; // IL0
                                addCodeToList(buffer1);
                                addCodeToList(buffer2);
                                addCodeToList(buffer3);
                            }
                            S                     
       ;

S : T_THEN S1 {
                char buffer4[100];
                ifcounter++;
                char *IL1 = ifLable();
                sprintf(buffer4, "%d : %s", currLine, IL1); currLine++; //IL1
                addCodeToList(buffer4);
              } 
              T_ELSE S2 
  | T_THEN S2   {
                    char buffer5[100];
                    char *IL1 = ifLable(); //IL1
                    sprintf(buffer5, "%d : %s", currLine, IL1); currLine++; //L1
                    addCodeToList(buffer5);
                }
  ;

S1 : T_BEGIN stmt T_END 
   ;

S2 : T_BEGIN stmt T_END SC {
    // StmtList is a list of statements inside the block
    // for (int i = 0; i < stmt_list.size(); i++) {
    //     // executeStatement(stmt_list[i]);
    //     printf("here1");
    // }
    //printf("Hello");
}
   ;

Condition : Expr RelOp Expr     {
                                    strcpy($<t.type>$, "boolean");
                                    if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0)
                                    {
                                        char buffer1[100];
                                        char *temp = newTemp();
                                        $<t.code>$ = temp;
                                        sprintf(buffer1, "%d : %s = %s %s %s", currLine, $<t.code>$, $<t.code>1, $<t.code>2, $<t.code>3);
                                        currLine++;
                                        addCodeToList(buffer1);                                                                  
                                    }
                                    else if(strcmp($<t.type>1, "boolean") == 0 && strcmp($<t.type>3, "boolean") == 0)
                                    {
                                        char buffer2[100];
                                        char *temp = newTemp();
                                        $<t.code>$ = temp;
                                        sprintf(buffer2, "%d : %s = %s %s %s", currLine, $<t.code>$, $<t.code>1, $<t.code>2, $<t.code>3);
                                        currLine++;
                                        addCodeToList(buffer2);
                                        
                                    }
                                    else if(strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "char") == 0)
                                    {
                                        char buffer3[100];
                                        char *temp = newTemp();
                                        $<t.code>$ = temp;
                                        sprintf(buffer3, "%d : %s = %s %s %s", currLine, $<t.code>$, $<t.code>1, $<t.code>2, $<t.code>3);
                                        currLine++;
                                        addCodeToList(buffer3);                             
                                    }
                                    else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "float") == 0)
                                    {
                                        char buffer4[100];
                                        char *temp = newTemp();
                                        $<t.code>$ = temp;
                                        sprintf(buffer4, "%d : %s = %s %s %s", currLine, $<t.code>$, $<t.code>1, $<t.code>2, $<t.code>3);
                                        currLine++;
                                        addCodeToList(buffer4);                             
                                    }
                                    else{
                                        printf("\nError in Condition, check types, %s RelOp %s", $<t.type>1, $<t.type>3);
                                        exit(1);
                                    }
                                }
          | T_NOT Condition     {
                                    strcpy($<t.type>$, "boolean");
                                    if(strcmp($<t.type>2, "int") == 0 || strcmp($<t.type>2, "boolean") == 0)
                                    {
                                        Value val;
                                        if(strcmp($<t.type>2, "int") == 0) {                                
                                            if($<t.v.ival>2 > 0)
                                                val.bval = 0;
                                            else
                                                val.bval = 1;
                                        }
                                        else if(strcmp($<t.type>2, "boolean") == 0){                                 
                                            if($<t.v.bval>2 == 1)
                                                val.bval = 0;
                                            else
                                                val.bval = 1;
                                        }   
                                        $<t.v.bval>$ = val.bval;
                                        char *temp = newTemp();
                                        $<t.code>$ = temp;
                                        char buffer1[100];
                                        sprintf(buffer1, "%d : %s = NOT %s",currLine, $<t.code>$, $<t.code>2);
                                        addCodeToList(buffer1);
                                        currLine++;
                                    }
                                    else
                                    {
                                        printf("\nError in Condition\n");
                                        exit(1);
                                    }                                    
                                }
          | Condition T_AND Condition   {
                                            strcpy($<t.type>$, "boolean"); 
                                            if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0 
                                            || strcmp($<t.type>1, "boolean") == 0 && strcmp($<t.type>3, "boolean") == 0 ) {
                                            
                                                char *temp = newTemp();
                                                $<t.code>$ = temp;
                                                char buffer1[100];                                            
                                                sprintf(buffer1, "%d : %s = %s AND %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                                currLine++;
                                                addCodeToList(buffer1);
                                                Value val;
                                                if(strcmp($<t.type>1, "int") == 0)
                                                {
                                                    if($<t.v.ival>1 > 0 && $<t.v.ival>3 > 0)
                                                        val.bval = 1;
                                                    else
                                                        val.bval = 0;
                                                }
                                                if(strcmp($<t.type>1, "boolean") == 0)
                                                {
                                                    if($<t.v.bval>1 == 1 && $<t.v.bval>3 == 1)
                                                        val.bval = 1;
                                                    else
                                                        val.bval = 0;
                                                }
                                                $<t.v.bval>$ = val.bval;                                               
                                            }                                            
                                            else
                                            {
                                                printf("\nError in Condition\n");
                                                exit(1);
                                            }
                                        }
          | Condition T_OR Condition    {
                                            if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0 
                                            || strcmp($<t.type>1, "boolean") == 0 && strcmp($<t.type>3, "boolean") == 0 
                                            || strcmp($<t.type>1, "boolean") == 0 && strcmp($<t.type>3, "int") == 0
                                            || strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "boolean") == 0) {
                                                //printf("\nFine");                                                
                                                strcpy($<t.type>$, "boolean");
                                                char *temp = newTemp();                                                
                                                $<t.code>$ = temp;
                                                char buffer1[100];
                                                sprintf(buffer1, "%d : %s = %s OR %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                                currLine++;
                                                addCodeToList(buffer1);
                                                Value val;
                                                if(strcmp($<t.type>1, "int") == 0)
                                                {
                                                    if($<t.v.ival>1 > 0 || $<t.v.ival>3 > 0)
                                                        val.bval = 1;
                                                    else
                                                        val.bval = 0;
                                                }
                                                if(strcmp($<t.type>1, "boolean") == 0)
                                                {
                                                    if($<t.v.bval>1 == 1 || $<t.v.bval>3 == 1)
                                                        val.bval = 1;
                                                    else
                                                        val.bval = 0;
                                                }
                                                $<t.v.bval>$ = val.bval;                                              
                                            }
                                            else
                                            {
                                                printf("\nError in Condition\n");
                                                exit(1);
                                            }
                                        }
          | Content                 {
                                        Symbol *sym = lookupSymbol($<t.v.string>1);
                                        if(!sym)
                                        {
                                            printf("\nError: variable not declared");
                                            exit(1);
                                        }
                                        else if(sym->initialized == 0)
                                        {
                                            printf("\nError: variable not Initialized");
                                            exit(1);
                                        }                                     
                                    
                                        $<t.code>$ = $<t.code>1;
                                        strcpy($<t.type>$, $<t.type>1);
                                        if(strcmp($<t.type>1, "int") == 0)
                                        {
                                            $<t.v.ival>$ = $<t.v.ival>1;
                                        }
                                        else if(strcmp($<t.type>1, "boolean") == 0)
                                        {
                                            $<t.v.bval>$ = $<t.v.bval>1;
                                        }
                                        else if(strcmp($<t.type>1, "char") == 0)
                                        {
                                            $<t.v.cval>$ = $<t.v.cval>1;
                                        }
                                        else if(strcmp($<t.type>1, "float") == 0)
                                        {
                                            $<t.v.fval>$ = $<t.v.fval>1;
                                        }                                        
                                        else{
                                            printf("\nError in Condition\n");
                                            exit(1);
                                        }
                                    }
       
          | Expr                    { $<t.code>$ = $<t.code>1; strcpy($<t.type>$, $<t.type>1); }
          | T_TRUE                  { $<t.code>$ = $<t.code>1; strcpy($<t.type>$, "boolean"); $<t.v.bval>1 = 1; $<t.v.bval>$ = 1; }
          | T_FALSE                 { $<t.code>$ = $<t.code>1; strcpy($<t.type>$, "boolean"); $<t.v.bval>1 = 0; $<t.v.bval>$ = 0; }

          ;


WhileLoop : T_WHILE Condition T_DO  {
                                        char *WL0 = whileLable();
                                        whileCounter++;
                                        char *WL1 = whileLable();
                                        char buffer1[100];
                                        char buffer2[100];
                                        char buffer3[100];
                                        sprintf(buffer1, "%d : %s : if %s then goto %s", currLine, WL0, $<t.code>2, WL1); currLine++;
                                        whileCounter++;
                                        char *WL2 = whileLable();
                                        sprintf(buffer2, "%d : goto %s", currLine, WL2); currLine++;
                                        WL1 = whileLableBefore();
                                        sprintf(buffer3,"%d : %s", currLine, WL1); currLine++;
                                        addCodeToList(buffer1);
                                        addCodeToList(buffer2);
                                        addCodeToList(buffer3);
                                    } S2    {
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
          ;

ForLoop : T_FOR ID AS Expr T_TO Expr T_DO {  //check point 2 : removed loop variable initialised or not
                                                char buffer1[100];
                                                char buffer2[100];
                                                char buffer3[100];
                                                char *FL0 = forLable(); forcounter++;
                                                char *FL1 = forLable(); forcounter++;
                                                char *FL2 = forLable();
                                                sprintf(buffer1, "%d : %s : if %s <= %s then goto %s", currLine, FL0, $<t.v.string>2, $<t.code>6, FL1); currLine++;
                                                sprintf(buffer2, "%d : goto %s", currLine, FL2); currLine++;
                                                sprintf(buffer3, "%d : %s :", currLine, FL1); currLine++;

                                                addCodeToList(buffer1);
                                                addCodeToList(buffer2);
                                                addCodeToList(buffer3);
                                                
                                            }
                                            S2  {
                                                    Symbol* sym = lookupSymbol($<t.v.string>2);
                                                    if(sym == NULL) {
                                                        printf("\nError: Loop variable not declared: %s", $<t.v.string>2);
                                                        exit(1);
                                                    }
                                                    else if(strcmp(sym->type, "int") != 0)
                                                    {
                                                        printf("\nControl assignment ID not int type");
                                                        exit(1);
                                                    }                                                    
                                                    else if((strcmp($<t.type>4, "int") != 0 || strcmp($<t.type>6, "int") != 0))
                                                    {
                                                        printf("\nControls are not int");
                                                        exit(1);
                                                    }                                                    
                                                    else if($<t.v.ival>4 <= $<t.v.ival>6){ 
                                                        printf("\nInitializing loop variable : %s", $<t.v.string>2);
                                                        initializeSymbol($<t.v.string>2);
                                                        Value val;
                                                        val.ival = $<t.v.ival>4;
                                                        updateSymbolValue($<t.v.string>2, val, "int");                           
                                                        sym->value.ival = $<t.v.ival>4;
                                                        sym->initialized = 1;  
                                                        //printf("\ncontro1 : %d", $<t.v.ival>4);
                                                        //printf("\ncontro2 : %d", $<t.v.ival>6);
                                                        //for loop functionality                                                  
                                                    }
                                                    else{
                                                        printf("\nError: Controls are wrongly arranged");
                                                        exit(1);
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
                                            ;
                                            
        | T_FOR ID AS Expr T_DOWNTO Expr T_DO   {
                                                    
                                                    char buffer1[100];
                                                    char buffer2[100];
                                                    char buffer3[100];
                                                    char *FL0 = forLable(); forcounter++;
                                                    char *FL1 = forLable(); forcounter++;
                                                    char *FL2 = forLable();
                                                    sprintf(buffer1, "%d : %s : if %s >= %s then goto %s", currLine, FL0, $<t.v.string>2, $<t.code>6, FL1); currLine++;
                                                    sprintf(buffer2, "%d : goto %s", currLine, FL2); currLine++;
                                                    sprintf(buffer3, "%d : %s :", currLine, FL1); currLine++;
                                                    addCodeToList(buffer1);
                                                    addCodeToList(buffer2);
                                                    addCodeToList(buffer3);

                                                } S2    {
                                                    Symbol* sym = lookupSymbol($<t.v.string>2);
                                                    if(sym == NULL) {
                                                        printf("\nError: Loop variable not declared: %s", $<t.v.string>2);
                                                    }
                                                    else if(strcmp(sym->type, "int") != 0)
                                                    {
                                                        printf("\nControl assignment ID not int type");
                                                        exit(1);
                                                    }
                                                    else if((strcmp($<t.type>4, "int") != 0 || strcmp($<t.type>6, "int") != 0))
                                                    {
                                                        printf("\nControls are not int");
                                                        exit(1);
                                                    }
                                                    else if($<t.v.ival>4 > $<t.v.ival>6){                            
                                                        sym->value.ival = $<t.v.ival>4;
                                                        sym->initialized = 1;
                                                        printf("\nInitializing loop variable : %s", $<t.v.string>2);
                                                        initializeSymbol($<t.v.string>2);
                                                        Value val;
                                                        val.ival = $<t.v.ival>4;
                                                        updateSymbolValue($<t.v.string>2, val, "int");
                                                        printf("\ncontro1 : %d", $<t.v.ival>4);
                                                        printf("\ncontro2 : %d", $<t.v.ival>6);
                                                        //for loop functionality                                                  
                                                    }
                                                    else{
                                                        printf("\nError: Controls are wrongly arranged");
                                                        exit(1);
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
        ;

Expr :  Expr PLUS Expr  {
                            //printf("\nIn Plus");    
                            if((strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "float") == 0) ||
                                (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                (strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "int") == 0) ) {
                                printf("At least One of the operands is char type cannot perform arithmetic\n");
                                exit(1);
                            } 
                            else if (strcmp($<t.type>1, "boolean") == 0 || strcmp($<t.type>3, "boolean") == 0) {
                                printf("Error: cannot perform '+' operation on boolean types.\n");
                                exit(1);
                            }
                            else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "float") == 0) {
                                $<t.v.fval>$ = $<t.v.fval>1 + $<t.v.fval>3;
                                fans = $<t.v.fval>$;
                                strcpy($<t.type>$, "float");
                                char *temp = newTemp();
                                $<t.code>$ = temp;
                                char buffer1[100];                           
                                sprintf(buffer1, "%d : %s = %s + %s", currLine, $<t.code>$, $<t.code>1, $<t.code>3);  
                                currLine++;
                                addCodeToList(buffer1);                           
                            } 
                            else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "int") == 0) {
                                $<t.v.fval>$ = $<t.v.fval>1 + $<t.v.ival>3;
                                fans = $<t.v.fval>$;
                                strcpy($<t.type>$, "float");
                                char *temp = newTemp();
                                $<t.code>$ = temp;                               
                                char buffer1[100];                           
                                sprintf(buffer1, "%d : %s = %s + %s", currLine, $<t.code>$, $<t.code>1, $<t.code>3);  
                                currLine++;
                                addCodeToList(buffer1);
                            } 
                            else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "float") == 0) {
                                $<t.v.fval>$ = $<t.v.ival>1 + $<t.v.fval>3;
                                fans = $<t.v.fval>$;
                                strcpy($<t.type>$, "float");
                                char *temp = newTemp();
                                $<t.code>$ = temp;                               
                                char buffer1[100];                           
                                sprintf(buffer1, "%d : %s = %s + %s", currLine, $<t.code>$, $<t.code>1, $<t.code>3);  
                                currLine++;
                                addCodeToList(buffer1);
                            } 
                            else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0) {
                                $<t.v.ival>$ = $<t.v.ival>1 + $<t.v.ival>3;
                                ians = $<t.v.ival>$;
                                strcpy($<t.type>$, "int");
                                char *temp = newTemp();
                                $<t.code>$ = temp;                               
                                char buffer1[100];                           
                                sprintf(buffer1, "%d : %s = %s + %s", currLine, $<t.code>$, $<t.code>1, $<t.code>3);  
                                currLine++;
                                addCodeToList(buffer1);
                            } 
                        }
     |  Expr MINUS Expr     { 
                                if((strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "float") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "int") == 0)) {
                                    printf("5.At least One of the operands is char type cannot perform arithmetic\n");
                                    exit(1);
                                }
                                else if (strcmp($<t.type>1, "boolean") == 0 || strcmp($<t.type>3, "boolean") == 0) {
                                    printf("Error: cannot perform '-' operation on boolean types.\n");
                                    exit(1);
                                }
                                else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "float") == 0) {
                                    $<t.v.fval>$ = $<t.v.fval>1 - $<t.v.fval>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("\n6.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                           
                                    sprintf(buffer1, "%d : %s = %s - %s", currLine, $<t.code>$, $<t.code>1, $<t.code>3);  
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "int") == 0) {
                                    $<t.v.fval>$ = $<t.v.fval>1 - $<t.v.ival>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("\n7.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                           
                                    sprintf(buffer1, "%d : %s = %s - %s", currLine, $<t.code>$, $<t.code>1, $<t.code>3);  
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "float") == 0) {
                                    $<t.v.fval>$ = $<t.v.ival>1 - $<t.v.fval>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("\n8.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                           
                                    sprintf(buffer1, "%d : %s = %s - %s", currLine, $<t.code>$, $<t.code>1, $<t.code>3);  
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0) {
                                    $<t.v.ival>$ = $<t.v.ival>1 - $<t.v.ival>3;
                                    ians = $<t.v.ival>$;
                                    strcpy($<t.type>$, "int");
                                    //printf("\n9.Result of expression is %s and value is: %d", $<t.type>$, ians);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                           
                                    sprintf(buffer1, "%d : %s = %s - %s", currLine, $<t.code>$, $<t.code>1, $<t.code>3);  
                                    currLine++;
                                    addCodeToList(buffer1);
                                }
                                //return 0; 
                            }
     | T_TRUE   {
                    strcpy($<t.type>$, "boolean");
                    $<t.v.bval>$ = 1;
                    int num = 1;                                        
                    $<t.code>1 = (char *)malloc(20 * sizeof(char));
                    sprintf($<t.code>1, "%d", num);
                    $<t.code>$ = $<t.code>1;
                }
     | T_FALSE   {
                    strcpy($<t.type>$, "boolean");
                    $<t.v.bval>$ = 0;
                    int num = 0;                                            
                    $<t.code>1 = (char *)malloc(20 * sizeof(char));
                    sprintf($<t.code>1, "%d", num);
                    $<t.code>$ = $<t.code>1;
                }
     |  Term                {
                                if(strcmp($<t.type>1, "int") == 0){
                                    strcpy($<t.type>$, "int");
                                    $<t.v.ival>$ = $<t.v.ival>1;
                                    $<t.code>$ = $<t.code>1;
                                }

                                else if(strcmp($<t.type>1, "char") == 0){
                                    strcpy($<t.type>$, "char");
                                    $<t.v.cval>$ = $<t.v.cval>1;
                                    $<t.code>$ = $<t.code>1;
                                }

                                else if(strcmp($<t.type>1, "float") == 0){
                                    strcpy($<t.type>$, "float");
                                    $<t.v.fval>$ = $<t.v.fval>1;
                                    $<t.code>$ = $<t.code>1;
                                }
                                else if(strcmp($<t.type>1, "boolean") == 0){
                                    strcpy($<t.type>$, "boolean");
                                    $<t.v.bval>$ = $<t.v.bval>1;
                                    $<t.code>$ = $<t.code>1;
                                }                              
                            }
     ;

Term : Term MUL Factor      {   //printf("\n3. $<t.type>1 = %s", $<t.type>1);
                                if((strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "float") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "int") == 0)) {
                                    printf("At least One of the operands is char type cannot perform arithmetic\n");
                                    exit(1);
                                } 
                                else if (strcmp($<t.type>1, "boolean") == 0 || strcmp($<t.type>3, "boolean") == 0) {
                                    printf("Error: cannot perform '*' operation on boolean types.\n");
                                    exit(1);
                                }
                                else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "float") == 0) {
                                    $<t.v.fval>$ = $<t.v.fval>1 * $<t.v.fval>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("\n10.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s * %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "int") == 0) {
                                    $<t.v.fval>$ = $<t.v.fval>1 * $<t.v.ival>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("\n11.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s * %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "float") == 0) {
                                    $<t.v.fval>$ = $<t.v.ival>1 * $<t.v.fval>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("\n12.Result of expression is %s and value is: %f", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s * %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0) {
                                    $<t.v.ival>$ = $<t.v.ival>1 * $<t.v.ival>3;
                                    ians = $<t.v.ival>$;
                                    strcpy($<t.type>$, "int");
                                    //printf("\n13.Result of expression is %s and value is: %d", $<t.type>$, ians);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s * %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                }
                                //return 0; 
                            }   
     | Term DIV Factor      {
                                //printf("\n4. $<t.type>1 = %s", $<t.type>1);
                                if((strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "float") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "int") == 0)) {
                                    printf("At least One of the operands is char type cannot perform arithmetic\n");
                                } 
                                else if (strcmp($<t.type>1, "boolean") == 0 || strcmp($<t.type>3, "boolean") == 0) {
                                    printf("Error: cannot perform '/' operation on boolean types.\n");
                                    exit(1);
                                }
                                else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "float") == 0) {
                                    $<t.v.fval>$ = $<t.v.fval>1 / $<t.v.fval>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("14.Result of expression is %s and value is: %f\n", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "int") == 0) {
                                    $<t.v.fval>$ = $<t.v.fval>1 / $<t.v.ival>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("15.Result of expression is %s and value is: %f\n", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "float") == 0) {
                                    $<t.v.fval>$ = $<t.v.ival>1 / $<t.v.fval>3;
                                    fans = $<t.v.fval>$;
                                    strcpy($<t.type>$, "float");
                                    //printf("16.Result of expression is %s and value is: %f\n", $<t.type>$, fans);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                } 
                                else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0) {
                                    $<t.v.ival>$ = $<t.v.ival>1 / $<t.v.ival>3;
                                    ians = $<t.v.ival>$;
                                    strcpy($<t.type>$, "int");
                                    //printf("17.Result of expression is %s and value is: %d\n", $<t.type>$, ians);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;                               
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                }
                                //return 0; 
                            }
     | Term REM Factor      { 
                                if((strcmp($<t.type>1, "float") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "float") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "char") == 0) ||
                                    (strcmp($<t.type>1, "char") == 0 && strcmp($<t.type>3, "int") == 0)) {
                                    printf("At least One of the operands is char type cannot perform arithmetic\n");
                                }
                                else if (strcmp($<t.type>1, "boolean") == 0 || strcmp($<t.type>3, "boolean") == 0) {
                                    printf("Error: cannot perform (%) operation on boolean types.\n");
                                    exit(1);
                                }
                                else if(strcmp($<t.type>1, "int") == 0 && strcmp($<t.type>3, "int") == 0) {
                                    $<t.v.ival>$ = $<t.v.ival>1 % $<t.v.ival>3;
                                    ians = $<t.v.ival>$;
                                    strcpy($<t.type>$, "int");
                                    //printf("17.Result of expression is %s and value is: %d\n", $<t.type>$, ians);
                                    char *temp = newTemp();
                                    $<t.code>$ = temp;
                                    char buffer1[100];                            
                                    sprintf(buffer1, "%d : %s = %s / %s",currLine, $<t.code>$, $<t.code>1, $<t.code>3);
                                    currLine++;
                                    addCodeToList(buffer1);
                                }
                                //return 0; 
                            }      
     | Factor               { 
                                if(strcmp($<t.type>1, "int") == 0){
                                    strcpy($<t.type>$, "int");
                                    $<t.v.ival>$ = $<t.v.ival>1;
                                    $<t.code>$ = $<t.code>1;
                                }
                                else if(strcmp($<t.type>1, "char") == 0){
                                    strcpy($<t.type>$, "char");
                                    $<t.v.cval>$ = $<t.v.cval>1;
                                    $<t.code>$ = $<t.code>1;
                                }
                                else if(strcmp($<t.type>1, "float") == 0){
                                    strcpy($<t.type>$, "float");
                                    $<t.v.fval>$ = $<t.v.fval>1;
                                    $<t.code>$ = $<t.code>1;
                                }
                                else if(strcmp($<t.type>1, "boolean") == 0){
                                    strcpy($<t.type>$, "boolean");
                                    $<t.v.bval>$ = $<t.v.bval>1;
                                    $<t.code>$ = $<t.code>1;
                                }       
                            }
     ;

Factor : OB Expr CB     { 
                            //printf("\nFound brackets");
                            if(strcmp($<t.type>2, "int") == 0){
                                strcpy($<t.type>$, "int");
                                $<t.v.ival>$ = $<t.v.ival>2;
                                $<t.code>$ = $<t.code>2;
                            }
                            else if(strcmp($<t.type>2, "char") == 0){
                                strcpy($<t.type>$, "char");
                                $<t.v.cval>$ = $<t.v.cval>2;
                                $<t.code>$ = $<t.code>2;
                            }
                            else if(strcmp($<t.type>2, "float") == 0){
                                strcpy($<t.type>$, "float");
                                $<t.v.fval>$ = $<t.v.fval>2;
                                $<t.code>$ = $<t.code>2;
                            }
                            else if(strcmp($<t.type>2, "boolean") == 0){
                                strcpy($<t.type>$, "boolean");
                                $<t.v.bval>$ = $<t.v.bval>2;
                                $<t.code>$ = $<t.code>2;
                            }                                    
                        }
        | Operand       { 
                            if(strcmp($<t.type>1, "int") == 0){
                                strcpy($<t.type>$, "int");
                                $<t.v.ival>$ = $<t.v.ival>1;
                                $<t.code>$ = $<t.code>1;
                                //printf("\nOperand: $<t.code>$ = %s", $<t.code>$);
                                //printf("\nOperand: $<t.code>1 = %s", $<t.code>1);
                            }
                            else if(strcmp($<t.type>1, "char") == 0){
                                strcpy($<t.type>$, "char");
                                $<t.v.cval>$ = $<t.v.cval>1;
                                $<t.code>$ = $<t.code>1;
                            }
                            else if(strcmp($<t.type>1, "float") == 0){
                                strcpy($<t.type>$, "float");
                                $<t.v.fval>$ = $<t.v.fval>1;
                                $<t.code>$ = $<t.code>1;
                            } 
                            else if(strcmp($<t.type>1, "boolean") == 0){
                                strcpy($<t.type>$, "boolean");
                                $<t.v.bval>$ = $<t.v.bval>1;
                                $<t.code>$ = $<t.code>1;
                            }                             
                        }
       ;

Operand : NUM       { 
                        strcpy($<t.type>$, "int");
                        $<t.v.ival>$ = $<t.v.ival>1; 
                        int num = $<t.v.ival>1;                                               
                        $<t.code>1 = (char *)malloc(20 * sizeof(char)); // Allocate memory for the string.
                        sprintf($<t.code>1, "%d", num);
                        $<t.code>$ = $<t.code>1;
                        //printf("\nNUM: $<t.code>$ = %s", $<t.code>$);
                        //printf("\nNUM: $<t.code>1 = %s", $<t.code>1);
                    }
        | CHAR      {
                        strcpy($<t.type>$, "char");
                        $<t.v.cval>$ = $<t.v.cval>1;
                        $<t.code>$ = $<t.v.cval>1;
                    }
        | FLOAT     {
                        strcpy($<t.type>$, "float");
                        $<t.v.fval>$ = $<t.v.fval>1;
                        double numf = $<t.v.fval>1;                                               
                        $<t.code>1 = (char *)malloc(20 * sizeof(char)); // Allocate memory for the string.
                        sprintf($<t.code>1, "%f", numf);
                        $<t.code>$ = $<t.code>1;
                    }
        | Content   {
                        Symbol* sym = lookupSymbol($<t.v.string>1);
                        
                        if(!sym) {
                            printf("\n Undeclared Identifier: %s", $<t.v.string>1);
                            char *name = extractArrayName($<t.v.string>1);
                            Symbol *sym1 = lookupSymbol(name);
                            //printf("\n is it an array = %d", sym1->isArray); 
                            if(sym1->isArray == 1)                           
                                printf("\nUninitialised Array Element = %s", $<t.v.string>1 );
                            else
                                exit(1);
                        } 
                        else if(!sym->initialized && sym->isArray == 0) {
                            printf("\nUninitialized Identifier: %s", $<t.v.string>1);
                            strcpy($<t.type>$, "string");
                            strcpy($<t.v.string>$, $<t.v.string>1);                            
                            exit(1);
                        }
                        else {
                            // type of the content is type of the ID
                            strcpy($<t.type>$, sym->type);
                            // Retrieve and set the value based on the type
                            if(strcmp(sym->type, "int") == 0) 
                            {
                                $<t.v.ival>$ = sym->value.ival;
                                $<t.code>$ = $<t.code>1;
                            } 
                            else if(strcmp(sym->type, "float") == 0)
                            {
                                $<t.v.fval>$ = sym->value.fval;
                                $<t.code>$ = $<t.code>1;
                            } 
                            else if(strcmp(sym->type, "char") == 0)
                            {
                                $<t.v.cval>$ = sym->value.cval;
                                $<t.code>$ = $<t.code>1;
                            }
                            else if(strcmp(sym->type, "boolean") == 0)
                            {
                                $<t.v.bval>$ = sym->value.bval;
                                $<t.code>$ = $<t.code>1;
                            } 
                        }
                    }
        ;

Type : T_INTEGER    { strcpy($<t.type>$, "int"); }       
     | T_REAL       { strcpy($<t.type>$, "float"); }        
     | T_CHAR       { strcpy($<t.type>$, "char"); }         
     | T_BOOLEAN    { strcpy($<t.type>$, "boolean"); }         
     ;

Content : ID {
                updateSymbolTable();
                //printf("\n1.Here");
                //printSymbolTable();
                $<t.v.string>$ = $<t.v.string>1;
                Symbol* sym = lookupSymbol($<t.v.string>1);
                if(!sym) {
                    printf("\nUndeclared Identifier: %s", $<t.v.string>1);
                    exit(1);
                } 
                else {
                    strcpy($<t.type>$, sym->type);
                    $<t.code>$ = $<t.v.string>1;
                }
            }
        | ArrElement    {
                            //printf("\n2.Here");
                            Symbol* sym = lookupSymbol(extractArrayName($<t.v.string>1));
                            if(!sym){
                                printf("\nUndeclared Array Element: %s", $<t.v.string>1);
                                //exit(1);
                            }
                            else{
                                strcpy($<t.type>$, sym->type);
                                $<t.code>$ = $<t.v.string>1;
                                if (sym->initialized) {
                                    if (strcmp(sym->type, "int") == 0) {
                                        $<t.v.ival>$ = sym->value.ival;
                                    } else if (strcmp(sym->type, "float") == 0) {
                                        $<t.v.fval>$ = sym->value.fval;
                                    } else if (strcmp(sym->type, "char") == 0) {
                                        $<t.v.cval>$ = sym->value.cval;
                                    } else if (strcmp(sym->type, "boolean") == 0) {
                                        $<t.v.bval>$ = sym->value.bval;
                                    }
                                }
                            }
                        }
        ;
        ;


RelOp : EQUAL    { $<t.v.op>$ = "=";  strcpy($<t.type>$, "op"); $<t.code>$ = $<t.v.op>$; }
       | NEQ     { $<t.v.op>$ = "!="; strcpy($<t.type>$, "op"); $<t.code>$ = $<t.v.op>$; }
       | LT      { $<t.v.op>$ = "<";  strcpy($<t.type>$, "op"); $<t.code>$ = $<t.v.op>$; }
       | GT      { $<t.v.op>$ = ">";  strcpy($<t.type>$, "op"); $<t.code>$ = $<t.v.op>$; }
       | LE      { $<t.v.op>$ = "<="; strcpy($<t.type>$, "op"); $<t.code>$ = $<t.v.op>$; }
       | GE      { $<t.v.op>$ = ">="; strcpy($<t.type>$, "op"); $<t.code>$ = $<t.v.op>$; }
       | EQUAL T_NOT    { $<t.v.op>$ = "= not"; strcpy($<t.type>$, "op"); $<t.code>$ = $<t.v.op>$; }
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
