/*Copyright (C) 2015  Arif Pathan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.*/


#include "stack.h"
#include <stdlib.h>
#include<string.h>
#define MAX 1000000
/*********************************************************************************************************/
///                                       string's  stack
void spush(stringstack *s, char val[]) {
	s->a[s->u] = (char *)malloc(strlen( val ) +1);
	strcpy( s->a[s->u], val);
	(s->u)++;
}
char * spop(stringstack *s) {
	(s->u)--;
	return s->a[s->u];
}
int sempty(stringstack *s) {
	return s->u == 0;
}
int sfull(stringstack *s) {
	return s->u == MAX;
}
void sinit(stringstack *s) {
	s->u = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////



void cpush(charstack *s, char num) {
	s->a[s->i]= num;
	(s->i)++;
}
int cpop(charstack *s) {
	(s->i)--;
	return s->a[s->i];
}
int cempty(charstack *s) {
	return s->i == 0;
}
int cfull(charstack *s) {
	return s->i == MAX;
}
void cinit(charstack *s) {
	s->i = 0;
}

char ctop(charstack *cs) {
	char x = cpop(cs);
	cpush(cs, x);
	return x;
}


/***********************************************************************************************************/
