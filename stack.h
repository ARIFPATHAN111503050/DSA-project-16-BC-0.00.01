/*Copyright (C) 2015  Arif Pathan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.*/



/*******************************************************************************************************/
typedef struct stringstack {
	char *a[1000];
	int u;
}stringstack;

void spush(stringstack *s, char val[]);
char *spop(stringstack *s);
int sempty(stringstack *s);
int sfull(stringstack *s);
void sinit(stringstack *s);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct charstack {
	char a[1000];
	int i;
}charstack;

void cpush(charstack *s, char num);
int cpop(charstack *s);
int cempty(charstack *s);
int cfull(charstack *s);
void cinit(charstack *s);
void rev( char *, char *);

/*********************************************************************************************************/
