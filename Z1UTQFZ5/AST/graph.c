#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <stdbool.h>
#include "y.tab.h"
FILE *outputFile;
char *valu[100];
int ind = 0;
int del = 1; /* distance of graph columns */
int eps = 3; /* distance of graph lines */
int flag = 0; // flag to print main initially
/* interface for drawing (can be replaced by "real" graphic using GD or other) */
void graphInit (void);
void graphFinish();
void graphBox (char *s, int *w, int *h);
void graphDrawBox (char *s, int c, int l);
void graphDrawArrow (int c1, int l1, int c2, int l2);


typedef struct id_sym{
    char *type;
    char *name;
    char *val;
	char *val2[100];
	int row_n;
	int col_n;
}id_sym;

typedef struct func_sym{
	char *type;
	char *name;
	char *val;
	// char *arg[100];
	// int arg_count;
	int fun_id_cnt;
	id_sym fun_id[1000];
	nodeType *body;
	
}func_sym;
int fun_IND = 0;
id_sym func_temp_table[100];
int id_count = 0;
id_sym id_table[1000];
func_sym func_table[1000];
int cnt = 0;
int func_count = 0;
char *paraV[100];
int paraV_ind = 0;
/* recursive drawing of the syntax tree */
void exNode (nodeType *p, int c, int l, int *ce, int *cm);
/***********************************************************/
/* main entry point of the manipulation of the syntax tree */
int ex (nodeType *p, int f)
{
	flag = f;
	int rte, rtm;
    printf("\n1.");
	graphInit ();
    printf("\n2.");
	exNode (p, 0, 0, &rte, &rtm);
    printf("\n3.");
	//evaluate(p,0);
	graphFinish();
    printf("\n4.");
	// print_Id_Table();
	printFuncs();
    printf("\n5.");
	//printFuncTable();
	return 0;
}


void exNode( nodeType *p,  int c, int l, /* start column and line of node */  int *ce, int *cm /* resulting end column and mid of node */)
{
	int w, h; /* node width and height */
	char *s; /* node text */
	int cbar; /* "real" start column of node (centred above subnodes)
	*/
	int k; /* child number */
	int che, chm; /* end column and mid of children */
	int cs; /* start column of children */
	char word[20]; /* extended node text */
	if (!p) return;
	strcpy (word, "???"); /* should never appear */
	s = word;
	switch(p->type) 
	{
		case typeCon: sprintf (word, "c[%s]", p->con.value); break;
		case typeId: sprintf (word, "id[%s]", p->id.name); break;
		case typeOpr:
		switch(p->opr.oper)
		{
			case FOR: s = "for"; break;
			case WHILE: s = "while"; break;
			case IF: s = "if"; break;
			case READ: s = "read"; break;
            case WRITE: s="write";break;
			case ';': s = "[;]"; break;
			case '=': s = "[=]"; break;
			case ',' : s = "[,]"; break;
		//	case UMINUS: s = "[_]"; break;
			case '+': s = "[+]"; break;
			case '-': s = "[-]"; break;
			case '*': s = "[*]"; break;
			case '/': s = "[/]"; break;
			case '<': s = "[<]"; break;
			case '>': s = "[>]"; break;
			case ':': s = "[:]"; break;
			case '?': s = "[?]"; break;
			case '%': s = "[%]"; break;
			case GE: s = "[>=]"; break;
			case LE: s = "[<=]"; break;
			case NEQ: s = "[!=]"; break;
			case EQUAL: s = "[==]"; break;
			case AND: s = "[&&]"; break;
			case OR: s = "[||]"; break;
            case PRO: s= 'Program';break;
            case GT: s = "[>]"; break;
            case LT: s = "[<]"; break;
            case NOT: s = "[!]"; break;
		}
	break;
	}
 	/* construct node text box */
	graphBox (s, &w, &h);
	cbar = c;
	*ce = c + w;
	*cm = c + w / 2;
	/* node is leaf */
	if (p->type == typeCon || p->type == typeId || p->opr.nops == 0) 
	{
		graphDrawBox (s, cbar, l);
		return;
	}

 	/* node has children */
 	cs = c;
	for (k = 0; k < p->opr.nops; k++) 
	{
		exNode (p->opr.op[k], cs, l+h+eps, &che, &chm);
		cs = che;
	}
	/* total node width */
	if (w < che - c) 
	{
		cbar += (che - c - w) / 2;
		*ce = che;
		*cm = (c + che) / 2;
	}
	/* draw node */
	graphDrawBox (s, cbar, l);
	/* draw arrows (not optimal: children are drawn a second time) */
	cs = c;
	for (k = 0; k < p->opr.nops; k++)
	{
		exNode (p->opr.op[k], cs, l+h+eps, &che, &chm);
		graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
		cs = che;
	}
	// if(s == "[=]")evaluate_assgn_3(p);
}

/* interface for drawing */
#define lmax 500
#define cmax 500
char graph[lmax][cmax]; /* array for ASCII-Graphic */
int graphNumber = 0;

void graphTest (int l, int c)
{ 
	int ok;
	ok = 1;
	if (l < 0) ok = 0;
	if (l >= lmax) ok = 0;
	if (c < 0) ok = 0;
	if (c >= cmax) ok = 0;
	if (ok) return;
	fprintf(outputFile, "\n+++error: l=%d, c=%d not in drawing rectangle 0, 0 ... %d, %d", l, c, lmax, cmax);
	exit (1);
}

void graphInit (void) {
    int i, j;
    for (i = 0; i < lmax; i++) {
        for (j = 0; j < cmax; j++) {
            graph[i][j] = ' ';
            
        }
    }
    return;
}

void graphFinish()
{
	int i, j;
	for (i = 0; i < lmax; i++)
	{
		for (j = cmax-1; j > 0 && graph[i][j] == ' '; j--);
		graph[i][cmax-1] = 0;
		if (j < cmax-1) 
			graph[i][j+1] = 0;
		if (graph[i][j] == ' ') 
			graph[i][j] = 0;
	}
	for (i = lmax-1; i > 0 && graph[i][0] == 0; i--);
	 graphNumber++;
	for (j = 0; j <= i; j++) fprintf(outputFile, "\n%s", graph[j]);
    fclose(outputFile);
    printf("Syntax tree saved to syntaxtree.txt\n");
}

void graphBox (char *s, int *w, int *h)
{
	*w = strlen (s) + del;
	*h = 1;
}
void graphDrawBox (char *s, int c, int l)
{
	int i;
	graphTest (l, c+strlen(s)-1+del);
	for (i = 0; i < strlen (s); i++) {
	graph[l][c+i+del] = s[i];
	}
}

void graphDrawArrow (int c1, int l1, int c2, int l2)
{
	int m;
	graphTest (l1, c1);
	graphTest (l2, c2);
	m = (l1 + l2) / 2;
	while (l1 != m)
	{
		graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--;
	}
	while (c1 != c2)
	{
		graph[l1][c1] = '-'; if (c1 < c2) c1++; else c1--;
	}
	while (l1 != l2)
	{
		graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--;
	}
	graph[l1][c1] = '|';
}

void printFuncs() {
    for (int i = 0; i < func_count; i++) {
        fprintf(outputFile, "%s\n", func_table[i].name);
    }
}