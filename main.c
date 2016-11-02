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
#define max 10000
#define mAx 1000
#define pi 3.14159265
#define PI 3.142857142857
#define E 2.71828182845
#define bufSize 10240
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include <limits.h>
#include <time.h>
#include "stack.h"
#include "function.h"
#include "token.h"
#include "header.h"

int errorno = 1;
int check = 0;
int check2 = 0;
 //global variable required for real division
int  z = 0; //global variable required for real division
int base = 0;	
int ff = 0,fi = 0;
int main (int argc, char *argv[]) {
	////////only one file argunment is handled ....pls....
	
	char str[MAX], fac[MAX], *ps1, *ps2, pc, *buff[6000];
	char *cc, *tmp, *pow, *d;
	int x, ans, cke = 0;
	int i = 0, tt = 0, w = 0;
	token *t;
	stringstack s;
	charstack c;
	sinit (&s);
	cinit (&c);
	infinity :
	if(argc > 1){
		if(strcmp( argv[1], "-h") == 0){
			FILE* fp;
			char buf[bufSize];
			if (argc != 2){
				fprintf(stderr,"Usage: %s <soure-file>\n", argv[0]);
				return 1;
			}
			if ((fp = fopen("help.txt", "r")) == NULL) {
				 /* Open source file. */
		//		perror("fopen source-file");
		//		return 1;
			}
			while (fgets(buf, sizeof(buf), fp) != NULL) {
				buf[strlen(buf) - 1] = '\0'; // eat the newline fgets() stores
				printf("%s\n", buf);
			}
			fclose(fp);
			exit(1);
		}
	}
	printf("\n\t\t\t\t\t\t\t\t\tBC 0.00.01\n\t\t\t\t\t\t\t\t\t  POSTFIX\n\t\t\t\t\t\tCopyright 2016 - 2019 MUKT COEP Software Foundation, Inc.\n\t\t\t\t\t\tThis is free software with ABSOLUTELY NO WARRANTY.......\n");
	date();
	FILE* fp;
	char buf[bufSize];
	if ((fp = fopen(argv[1], "r")) == NULL) {
		//perror("fopen source-file");
		goto End;
	}
	x = 0;
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		buf[strlen(buf) - 1] = '\0'; // eat the newline fgets() stores
		buff[x] = (char *)malloc(mAx);
		strcpy( buff[x] , buf );
		x++;
	}
	ff = x - 1;
	i = 0;
	fi = 0;
	//take tokens for the math.h
	End:
	if(fi < ff ){
		cke = 1;
		strcpy(str ,buff[fi] );
		fi++;
		goto file;
		
	}
	x = 1;
	while (1) {
		x = readline(str, 8192);
		cke = 0;
		file:
		if(cke == 1)
			printf("%s\n",str);
		i = checkexpression(str);
		if ( i == 0 )
			goto End;
		if(x == 0)
			goto End;
		postfix:
		i = 0;
		while(1){
			t = getnext( str, &i);
			if(t->type == ERROR){
				printf("(standard_in) %d: syntax error\n",errorno);
				errorno++;
				goto End;
			}
			if(t->type == OPERAND){				// sin
				if(( t->val[0] == 's' || t->val[0] == 'S') && (t->val[1] == 'i' || t->val[1] == 'I') &&( t->val[2] == 'n' || t->val[2] == 'N') && (t->val[3] != 'h' && t->val[3] != 'H') || (t->val[3] == 'e' || t->val[3] == 'E')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", sin((g * PI / 180)));
							goto End;
						}
					}	
				}								//cos
				else if( (t->val[0] == 'c' || t->val[0] == 'C') && (t->val[1] == 'o' || t->val[1] == 'O') && ( t->val[2] == 's' || t->val[2] == 'S') && ( t->val[3] != 'h' && t->val[3] != 'H') || (t->val[3] == 'i' || t->val[3] == 'I') || (t->val[4] == 'n' || t->val[4] == 'N') || (t->val[5] == 'E' || t->val[5] == 'e')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", cos((g * PI / 180)));
							goto End;
						}
					}
				}			//tan
				else if( (t->val[0] == 't'|| t->val[0] == 'T') && (t->val[1] == 'a' || t->val[1] == 'A') && ( t->val[2] == 'n'|| t->val[2] == 'N') && ( t->val[3] != 'h' && t->val[3] != 'H') || t->val[3] == 'g' || t->val[3] == 'G' || t->val[4] == 'e' || t->val[4] == 'E' || t->val[5] == 'n' || t->val[5] == 'N'|| t->val[6] == 't' || t->val[6] == 'T'){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							if( g % 90 == 0 && g% 180 != 0){
								printf("NOT DEFINED\n");
								goto End;
							}
							printf("%lf\n", tan((g * PI / 180)));
							goto End;
						}
					}
				}			//sec
				else if( (t->val[0] == 's' || t->val[0] == 'S' ) && (t->val[1] == 'e' || t->val[1] == 'E') && (t->val[2] == 'c' || t->val[2] == 'C') && ( t->val[3] != 'h' && t->val[3] != 'H') || (t->val[3] == 'a' || t->val[3] == 'A') || (t->val[4] == 'n' || t->val[4] == 'N') || (t->val[5] == 't' || t->val[5] == 'T')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if( g % 90 == 0 && g % 180 != 0){
								printf("NOT DEFINED\n");
								goto End;
							}
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", 1 / cos(g * PI / 180));
							goto End;
						}
					}

				}			//cosec
				else if( (t->val[0] == 'c' || t->val[0] == 'C') && (t->val[1] == 'o' || t->val[1] == 'O') && (t->val[2] == 's' || t->val[2] == 'S') && (t->val[3] == 'e' || t->val[3] == 'E') && (t->val[4] == 'c' || t->val[4] == 'C') && ( t->val[5] != 'h' && t->val[5] != 'H') || ( t->val[5] == 'a' || t->val[5] == 'A' ) || (t->val[6] == 'n' || t->val[6] == 'N') ){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							
							if( g % 180 == 0 ){
								printf("NOT DEFINED\n");
								goto End;
							}
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", 1 / sin((g * PI / 180)));
							goto End;
						}
					}
				}			//cot
				else if( ( t->val[0] == 'c' || t->val[0] == 'C' ) && ( t->val[1] == 'o' || t->val[1] == 'O' ) && (t->val[2] == 't' || t->val[2] == 'T') && ( t->val[3] != 'h' && t->val[3] != 'H') || ( t->val[3] == 'a' || t->val[3] == 'A') || t->val[4] == 'n' || t->val[4] == 'N' || t->val[5] == 'g' || t->val[5] == 'G' || t->val[6] == 'e' || t->val[6] == 'E' ||t->val[7] == 'n' || t->val[7] == 'N' || t->val[8] == 'T' || t->val[8] == 't'){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if ( g % 180 == 0){
								printf("NOT DEFINED\n");
								goto End;
							}
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", 1 / tan((g * PI / 180)));
							goto End;
						}
					}
				}		//log
				else if( (t->val[0] == 'l' || t->val[0] == 'L') && (t->val[1] == 'o' || t->val[1] == 'O') && (t->val[2] == 'g' || t->val[2] == 'G')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", log10(g));
							goto End;
						}
					}
				}			//ln
				else if( (t->val[0] == 'l' || t->val[0] == 'L') && (t->val[1] == 'n' || t->val [1] == 'N')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", log(g));
							goto End;
						}
					}
				}		//exp
				else if ((t->val[0] == 'e' || t->val[0] == 'E')|| (t->val[1] == 'x' || t->val[1] == 'X')|| t->val[2] == 'p' || t->val[2] == 'P'){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", exp(g));
							goto End;
						}
					}
				}			//arccos
				else if( (t->val[0] == 'a' || t->val [0] == 'A') && (t->val[1] == 'r' || t->val[1] == 'R') && (t->val[2] == 'c' || t->val[2] == 'C') || (t->val[3] == 'c' || t->val[3] == 'C') && (t->val[4] == 'o' || t->val[4] == 'O') && ( t->val[5] == 's' || t->val[5] == 'S') || (t->val[6] == 'i' || t->val[6] == 'I') || (t->val[7] == 'n' || t->val[7] == 'N') || (t->val[8] == 'E' || t->val[8] == 'e')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", acos(g)*180/PI);
							goto End;
						}
					}
				}			//sinh
				else if(( t->val[0] == 's' || t->val[0] == 'S') && (t->val[1] == 'i' || t->val[1] == 'I') &&( t->val[2] == 'n' || t->val[2] == 'N') && (t->val[3] == 'h' || t->val[3] == 'H')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", sinh(g));
							goto End;
						}
					}
					goto End;	

				}			//tanh
				else if((t->val[0] == 't'|| t->val[0] == 'T') && (t->val[1] == 'a' || t->val[1] == 'A') && ( t->val[2] == 'n'|| t->val[2] == 'N') && (t->val[3] == 'h' || t->val[3] == 'H')){
				x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", tanh(g));
							goto End;
						}
					}
				}		//cosh
				else if((t->val[0] == 'c' || t->val[0] == 'C') && (t->val[1] == 'o' || t->val[1] == 'O') && ( t->val[2] == 's' || t->val[2] == 'S') && (t->val[3] == 'h' || t->val[2] == 'H')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", cosh(g));
							goto End;
						}
					}
				}			//sech
				else if((t->val[0] == 's' || t->val[0] == 'S' ) && (t->val[1] == 'e' || t->val[1] == 'E') && (t->val[2] == 'c' || t->val[2] == 'C') && (t->val[3] == 'h' || t->val[3] == 'H')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", 1 / cosh( g ));
							goto End;
						}
					}
				}			//cosech
				else if((t->val[0] == 'c' || t->val[0] == 'C') && (t->val[1] == 'o' || t->val[1] == 'O') && (t->val[2] == 's' || t->val[2] == 'S') && (t->val[3] == 'e' || t->val[3] == 'E') && (t->val[4] == 'c' || t->val[4] == 'C') &&(t->val[5] == 'h' || t->val[5] == 'H')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", 1 / sinh( g ));
							goto End;
						}
					}
				}			//coth
				else if(( t->val[0] == 'c' || t->val[0] == 'C' ) && ( t->val[1] == 'o' || t->val[1] == 'O' ) && (t->val[2] == 't' || t->val[2] == 'T') &&(t->val[3] == 'h' || t->val[3] == 'H')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", 1 / tanh(  g ));
							goto End;
						}
					}
				}		//arcsin
				else if((t->val[0] == 'a' || t->val [0] == 'A') && (t->val[1] == 'r' || t->val[1] == 'R') && (t->val[2] == 'c' || t->val[2] == 'C') && ( t->val[3] == 's' || t->val[3] == 'S') && (t->val[4] == 'i' || t->val[4] == 'I') || ( t->val[5] == 'n' || t->val[5] == 'N')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", asin(g)*180 / PI);
							goto End;
						}
					}
				}
				//arctan
				else if((t->val[0] == 'a' || t->val [0] == 'A') && (t->val[1] == 'r' || t->val[1] == 'R') && (t->val[2] == 'c' || t->val[2] == 'C') && (t->val[3] == 't'|| t->val[3] == 'T') && (t->val[4] == 'a' || t->val[4] == 'A') && ( t->val[5] == 'n'|| t->val[5] == 'N') || t->val[6] == 'g' || t->val[6] == 'G' || t->val[7] == 'e' || t->val[7] == 'E' || t->val[8] == 'n' || t->val[8] == 'N'|| t->val[9] == 't' || t->val[9] == 'T'){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", (atan(g)) * 180 / PI);
							goto End;
						}
					}
				}			//arccosec
				else if((t->val[0] == 'a' || t->val [0] == 'A') && (t->val[1] == 'r' || t->val[1] == 'R') && (t->val[2] == 'c' || t->val[2] == 'C') && (t->val[3] == 'c' || t->val[3] == 'C') && (t->val[4] == 'o' || t->val[4] == 'O') && (t->val[5] == 's' || t->val[5] == 'S') && (t->val[6] == 'e' || t->val[6] == 'E') && (t->val[7] == 'c' || t->val[7] == 'C')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", (asin(1 / g) * 180 / PI));
							goto End;
						}
					}
				}			//arcsec
				else if((t->val[0] == 'a' || t->val [0] == 'A') && (t->val[1] == 'r' || t->val[1] == 'R') && (t->val[2] == 'c' || t->val[2] == 'C') && (t->val[3] == 's' || t->val[3] == 'S' ) && (t->val[4] == 'e' || t->val[4] == 'E') && (t->val[5] == 'c' || t->val[5] == 'C')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", acos(1 / g)* 180 /PI);
							goto End;
						}
					}
				}			//arccot
				else if((t->val[0] == 'a' || t->val [0] == 'A') && (t->val[1] == 'r' || t->val[1] == 'R') && (t->val[2] == 'c' || t->val[2] == 'C') &&( t->val[0] == 'c' || t->val[0] == 'C' ) && ( t->val[1] == 'o' || t->val[1] == 'O' ) && (t->val[2] == 't' || t->val[2] == 'T')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", atan(1 / g)* 182 / PI );
							goto End;
						}
					}
				}					//sqrt babylaon method ..function defined
				else if((t->val[0] == 's' || t->val[0] == 'S') && (t->val[1] == 'q' || t->val[1] == 'Q') && 
				(t->val[2] == 'r' || t->val[2] == 'R') && (t->val[3] == 't' || t->val[3] == 'T')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							long  g = atol(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", squareroot( g ));
							goto End;
						}
					}
				}			//ceil
				else if(( t->val[0] == 'c' || t->val[0] == 'C') && ( t->val[1] == 'e' || t->val[1] == 'E' ) && (t->val[2] == 'i' || t->val[2] == 'I') && ( t->val[3] == 'l' || t->val[3] == 'L')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							float g = atof(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", ceil( g ));
							goto End;
						}
					}
				}		//fabs
				else if((t->val[0] == 'f' || t->val[0] == 'F') && (t->val[1] == 'a' || t->val[1] == 'A') && ( t->val[2] == 'b' || t->val[2] == 'B') && ( t->val[3] == 's' || t->val[3] == 'S')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							float g = atof(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", fabs( g ));
							goto End;
						}
					}
				}			//floor
				else if((t->val[0] == 'f' || t->val[0] == 'F') && (t->val[1] == 'l' || t->val[1] == 'L') && (t->val[2] == 'o' || t->val[2] == 'O') && (t->val[3] == 'o' || t->val[3] == 'O') && ( t->val[4] == 'r' || t->val[4] == 'R')){
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							float g = atof(t->val);
							if(x == 1)
								g = g * ( - 1 );
							printf("%lf\n", fabs( g ));
							goto End;
						}
					}
				}		//matrix
				else if(( t->val[0] == 'm' || t->val[0] == 'M') && (t->val[1] == 'a' || t->val[1] == 'A' ) && (t->val[2] == 't' || t->val[2] == 'T') && (t->val[3] == 'r' || t->val[3] == 'R' ) && (t->val[4] == 'i' || t->val[4] == 'I') && (t->val[5] == 'x' || t->val[5] == 'X')){
					matrix();
					goto End;
				}			//c          clear the function
				else if( (t->val[0] == 'c' || t->val[0] == 'C') ){
					x = 50;
					while(x != 0){
						printf("\n");
						x--;
					}
					goto End;
				}			// scale..........
				else if((t->val[0] == 't' || t->val[0] == 'T') || ( t->val[1] == 'i' || t->val[1] == 'I' ) || (t->val[2] == 'm' || t->val[2] == 'M') || (t->val[3] == 'e' || t->val[3] == 'E')){
					date();
					goto End;
				}
				if((t->val[0] == 's' || t->val[0] == 'S') ){
					x = 0;
					while(1){
						t = getnext(str, &i);
						
						if(t->type == END)
							goto End;
						if( t->op == '-')
						 	x = 1;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							int g = atof(t->val);
							if(x == 1)
								printf("scale cannot be minus so it will be converted to positive value\n");
								
							scaleseter(g);
							sinit( &s );
							goto End;
						}
					}
				}
				else if((t->val[0] == 'b' || t->val[0] == 'B') || (t->val[1] == 'a' || t->val[1] == 'A') || (t->val[2] == 's' || t->val[2] == 'S') || (t->val[3] == 'e' || t->val[3] == 'E')){
					
					x = 0;
					while(1){
						t = getnext(str, &i);
						if(t->type == END)
							goto End;
						if(t->val[0] >= '0' && t->val[0] <= '9' ){
							int g = atoi(t->val);
							x = g;
							break;
						}
					}					
					if(x == 2){
						printf("DECIMAL TO BINARY enter the decimal no\n");
						ps1 = (char *) malloc(max);
						scanf("%s",ps1);
						DtoB(ps1);
						goto End;
					}
					else if(x == 10){
						printf("BINARY TO DECIMAL enter the binary number\n");
						ps1 = (char *)malloc(max);
						scanf("%s",ps1);
						BtoD(ps1);
						goto End;
					}
					goto End;
				}
					spush( &s, t->val);
			}
			if(t->type == OPERATOR){
				ps1 = spop (&s);
				if(t->op == '!'){
					strcpy( fac, ps1);
					factorial( fac );
					spush( &s, fac);
					goto infinity2;
				}
				ps2 = spop (&s);
				switch( t->op ){
					case '+':
						ps2 = adddecimal( ps2, ps1);
						spush ( &s, ps2);
						//addition performed
						break;
					case '-':
						if(strlen( ps1 ) > strlen(ps2) ){
							cc = (char *)malloc(MAX);
						}
						else {
							cc = (char *)malloc( MAX );
						}
						subtractiondecimal( ps1, ps2, cc);
						spush( &s, cc);
						//subtraction
						break;
					case '*':
						cc = (char *)malloc(MAX);
						mul( ps1, ps2, cc);
						if(cc[0] == '.'){
							strcat("0",cc);
						}
						tmp = (char *)malloc(strlen(cc) +3);
						strcpy(tmp , cc);
						free( cc );
						spush ( &s,tmp);
						//multiplication......
						break;
					case '%':
						cc = (char *)malloc( MAX / 1000);
						d = (char *)malloc(strlen( ps1 ) + strlen( ps2 ));
						actualdivisioninterface( ps2, ps1, cc, d);
						spush( &s, d);
						free (cc);
						break;
					case '/':
						cc = (char *)malloc( MAX );
						d = (char *)malloc( strlen( ps1 ) + strlen( ps2 ));
						actualdivisioninterface( ps2, ps1, cc, d);
				
						spush( &s, cc);
						
						break;
					case '!':
						//factorial..........
						infinity2:
						break;
					case '^':
						pow = (char *)malloc(MAX);
						d = (char *)malloc(MAX);
						strcpy( d, ps2);
						//strcpy( pow, ps2);
						power( d, ps1, pow);
						cc = (char *)malloc( strlen(pow) + 3 );
						strcpy( cc, pow);
						free( pow );
						free( d );
						spush( &s, cc);
						break;
					case 'd': case 'D':
						exit(1);
				}
			}
			if(t->type == END){
				ps2 = spop(&s);
				ans = strlen (ps2);
				if( s.u >= 1){
					printf("(standard_in) %d: syntax error\n", errorno);
					errorno++;
					sinit(&s);
					break;///use goto for the next input.........
				}
				if(strlen(ps2) != 1)
				removezero(ps2);
				printf("%s\n",ps2);
				goto End;
			}
			///now just display that its works .......
		}
	}
}
