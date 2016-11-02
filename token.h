/*Copyright (C) 2015  Arif Pathan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.*/


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
