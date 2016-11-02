/*Copyright (C) 2015  Arif Pathan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.*/
	


#define MAX 1000000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define OPERAND 10 
#define OPERATOR 20
#define	END	30
#define ERROR	40
#define BSTART	50
#define BEND	60
typedef struct token {
	int type; // type takes values OPERAND/OPERATOR/END/ERROR/BSTART/BEND
	int number;
	char *val;
	char op;
}token;
token *getnext(char *, int *);
enum states { SPC, DIG, OPR, STOP, ERR , BS , BE};
token *getnext(char *arr, int *i) {
	char p[MAX];
	static int currstate = SPC;
	if (*i == 0)
		currstate = SPC;
	int nextstate;
	int num;
	token *t = (token *)malloc(sizeof(token));
	t->val = (char *) malloc(512);
	while (1) {
		strcpy( p, arr);
		switch(arr[*i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.': case 's':
			case '=': case 'c': case 'a': case 'l':
			case 'e': case 'i': case 'n': case 'o':
			case 't': case 'q': case 'u': case 'r':
			case 'g': case 'C': case 'A': case 'L':
			case 'E': case 'I': case 'N': case 'O':
			case 'T': case 'Q': case 'U': case 'R':
			case 'G': case 'x': case 'X': case 'p':
			case 'P': case 'S': case 'f': case 'F':
			case 'b': case 'B': case 'M': case 'm':
			case 'h': case 'H': 
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '!': case '^': case 'd':
			case 'D':
				nextstate = OPR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			case '(':
				nextstate = BS;
				break;
			case ')':
				nextstate = BE;
				break;
			default:
				nextstate = ERR;
				break;
		}
		switch (currstate) {
			case SPC:
				if(nextstate == DIG){
					num = arr[*i] - '0';
					p[0] = arr[*i];
					p[1] = '\0';
					strcpy( t->val, p);
				}
				else if(nextstate == BS) {
					currstate = SPC;
					t->type = BSTART;
					(*i)++;
					return t;
				}
				else if(nextstate == BE) {
					currstate = SPC;
					t->type = BEND;
					(*i)++;
					return t;
				}

				break;
			case DIG:
				if(nextstate == DIG){
					p[0] = arr[*i];
					p[1] = '\0';
					strcat( t->val, p);
					num = num * 10 + arr[*i] - '0';}
				else if(nextstate == OPR) {
					currstate = SPC;
					t->type = OPERAND;
					t->number = num;
					return t;
				}
				else  {
					t->type = OPERAND;
					t->number = num;
					currstate = nextstate;
					return t;
				}
				break;
			case OPR:
				t->type = OPERATOR;
				t->op = arr[*i - 1];	
				currstate = SPC;
				return t;
				break;
			case STOP:
				t->type = END;
				currstate = SPC;
				(*i)++;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				return t;
				break;
			case BE:
				t->type = BEND;
				currstate = SPC;
				(*i)++;
				return t;
				break;
		}
		currstate = nextstate;
		(*i)++;
	}
}

