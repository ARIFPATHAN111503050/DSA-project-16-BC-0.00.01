/*Copyright (C) 2015  Arif Pathan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.*/




#include <stdio.h>
#include "function.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "token.h"
#include <time.h>
//#include "header.h"
int scale = 0, ii = 0,j = 0;
#define MAX 1000000
#define max 10000
void scaleseter(int g){
	scale = g;
	printf("Scale_set:: SUCESS\n");
}
int zerocompare(char a[]){
	int i = 0, l;
	int flag = 0;
	l = strlen(a);
	while(i < l){
		if(a[i] != '0'){
			flag = 1;
			return flag;
		}
		i++;
	}
	return flag;
}

int BtoD(char a[]){
	char  b[max],c[max],mul[max];
	char *p, *q;
	p = (char *)malloc(strlen(a) +4);
	p[0] = '0';
	p[1] = '\0';
	c[0] = '2';
	c[1] = '\0';
	int i = 0, j, l;
	i = strlen( a );
	l = i = i - 1;
	tostring( b, i);
	//considering base 10
	i = i + 1;
	j = 0;
	while(j < i){
		if(a[j] == '1'){
			power( c, b, mul);
			l--;
			tostring(b,l);
			q = add( p, mul);
			strcpy( p, q);
			j++;
		}
		else if(a[j] == '0'){
			strminusone(b);
			j++;
		}
		else {
			printf("ERROR IN EXPRESSION\n");
			return 1;
		}
	}
	printf("%s \n",q);
	return 1;
}
int DtoB(char a[]){
	char b[max], c[max], d[max], bi[max];
	char p[max], q[max];
	int i ;
	printf("COMPLEXICITY N^2 TAKES TIME for big numbers\n");
	bi[0] = '\0';
	i = 1;
	b[0] = '2';
	b[1] = '\0';
	while( i != 0){
		i = zerocompare(a);
		actualdivisioninterface( a, b, c, d);
		strcat( bi, d);
		strcpy( a, c);
	}
	rev( bi, c);
	printf("%s\n",c);
	return 1;
}
float det(float a[100][100], float k){
	float s = 1, dete = 0, r[100][100];
	int i, j, m, n, c;
	if(k == 1){
		return a[0][0];
	}
	else {
		dete = 0 ;
		for(c = 0; c < k; c++){
			m = 0;n = 0;
			for(i = 0;i < k; i++){
				for(j = 0; j < k; j++){
					r[i][j] = 0;
						if(i != 0 && j != c){
						r[m][n] = a[i][j];
						if(n < (k - 2))
							n++;
						else{
							n = 0;
							m++;
						}
					}
				}
			}
			dete = dete + s * (a[0][c] * det( r, k - 1));
			s = ( -1 ) * s;
		}
	}
	return (dete);
}
void transpose(float n[100][100], float fac[100][100], float k){
	int i , j;
	float b[100][100], inverse[100][100], d;
	for(i = 0; i < k; i++){
		for(j = 0; j < k; j++){
			b[i][j] = fac[j][i];
		}
	}
	d = det(n,k);
	for(i = 0; i < k; i++){
		for(j = 0; j < k; j++){
			inverse[i][j] = b[i][j] / d;
		}
	}
//	printf("the inverse of the matrix is\n");
	for(i = 0; i < k; i++){
		for(j = 0; j < k; j++){
			global[i][j] = inverse[i][j];
//			printf("%f  ",inverse[i][j]);
		}
//		printf("\n");
	}
}

void cofact( float num[100][100], float k){
	float b[100][100], fac[100][100];
	int p, q, m, n, i, j;
	for(q = 0; q < k; q++){
		for(p = 0;p < k; p++){
			m = 0;
			n = 0;
			for(i = 0;i < k; i++){
				for(j = 0; j < k; j++){
					if(i != q && j != p){
						b[m][n] = num[i][j];
						if(n < (k - 2))
							n++;
						else {
							n = 0;
							m++;
						}
					}
				}
			}
			fac[q][p] = pow((-1), q+p) * det(b, k - 1);//pow of real bc clashes handle these cases
		}
	}
	transpose( num, fac, k);
}
void inverse(int k){
	float a[100][100], result;
	int i, j;
	printf(" N  = \n");
	global[100][100] = k;
	for(i = 0; i < k; i++){
			for(j = 0; j < k; j++){
				printf("Enter B [%d] [%d] =", i, j);
				scanf("%f", &a[i][j]);
			}
		}
	
	result = det(a,k);
	if(result == 0){
		printf("the inverse of the given matrix is not possible\n");
		return;
	}
	else
		cofact( a, k);
}
int matrix() {
	char *a[100][100], *b[100][100], *c[100][100];
	float x[100][100];
	int r, c2, r1, c1, i, j, k, n = 0, sum = 0, ii, m = 0;
	char aa, *p, *q;
	p = (char *)malloc(3);
	p[0] = '-';
	p[1] = '\0';
	printf("OPERATOR ie( + - * / ) ~[ a (OPERATOR) b ] = ");
	scanf("%c", &aa);
	if( aa == '*')
		goto infinity3;
	printf("(M X N) = ");
	scanf("%d%d", &m, &n);
	//chose the mode....
	char aaa[MAX];
	if(aa == '+'){
		for(i = 0;i < m; i++){
			for(j = 0;j < n; j++){
				printf("Enter A [%d] [%d] = ", i, j);
				scanf("%s",aaa);
				a[i][j] = (char*)malloc(strlen(aaa) + 1);
				strcpy(a[i][j], aaa);
			}
		}
		for(i = 0; i < m; i++){
			for(j = 0; j < n; j++){
				printf("Enter B [%d] [%d] = ", i, j);
				scanf("%s", aaa );
				b[i][j] = (char *)malloc(strlen(aaa) +1);
				strcpy(b[i][j], aaa);
			}
		}
		////now call the addition function recursively
		for(i = 0;i < m; i++){
			for(j = 0;j < n; j++){
				//play it here 
				if ( strlen(a[i][j]) >= strlen(b[i][j])){
					adddecimal(a[i][j] , b[i][j]);
					c[i][j] = (char *)malloc(strlen(a[i][j]) + 1);
					strcpy( c[i][j], a[i][j]);
				}
				else{
					adddecimal(b[i][j], a[i][j]);
					c[i][j] = (char *)malloc(strlen(b[i][j]) + 1);
					strcpy( c[i][j], b[i][j]);
				}
			}
			
		}
		for(i = 0; i < m; i++){
			for(j = 0;j < n;j++){
				printf(" %s\t",c[i][j]);
			}
			printf("\n\n");
		}///no limitations for addition for 2 matrices 
		
	}
	//only simple cases handled
	if(aa == '-'){
		for(i = 0; i < m; i++){
			for(j = 0; j < n; j++){
				printf("Enter A [%d] [%d] = ", i, j);
				scanf("%s",aaa);
				a[i][j] = (char*)malloc(strlen(aaa) + 1);
				strcpy(a[i][j], aaa);
			}
		}
		for(i = 0; i < m; i++){
			for(j = 0; j < n; j++){
				printf("Enter B [%d] [%d] = ", i, j);
				scanf("%s", aaa);
				b[i][j] = (char *)malloc(strlen(aaa) +1);
				strcpy(b[i][j], aaa);
			}
		}
		for(i = 0; i < m; i++){
			for(j = 0;j < n; j++){
				if(strlen( a[i][j] ) >= strlen(b[i][j] ) ){
					c[i][j] = (char *)malloc(strlen( a[i][j] ) + 1 );
					ii = subtractiondecimal( a[i][j] , b[i][j], c[i][j]);
					p[0] = '-';
					p[1] = '\0';
					if(ii == 1){
						strcat( p, c[i][j]);
						strcpy( c[i][j], p);//insert '-' in begining.....
						
					}
				}
				else {
					c[i][j] = (char *)malloc(strlen( b[i][j] ) + 1 );
					ii = subtractiondecimal ( a[i][j] , b[i][j], c[i][j]); 
					p[0] = '-';
					p[1] = '\0';
					if(ii == 1){
						strcat( p, c[i][j]);
						strcpy( c[i][j], p);
						//insert '-' in begining.......
					}
				}
			}
		}
		printf("\n");
		for(i = 0;i < m; i++){
			for(j = 0;j < n; j++){
				printf("  %s\t\t",c[i][j]);
			}
			printf("\n");
		}
	}
	if(aa == '*'){
		infinity3:
		//in multiplication of matrix rows and column may differ...
		printf("( M1 X N1) = ");
		scanf("%d%d", &r, &c2);
		printf("( M2 X N2 ) = ");
		scanf("%d%d", &r1, &c1);
		if( c2 != r1 ){
			printf("Multiplication not possible as N1 and M2 differs\nPROPERTIES OF MATRIX\n");
			return 0;
		}
		for(i = 0; i < r; i++){
			for(j = 0; j < c2; j++){
				printf("Enter A [%d] [%d] = ", i, j);
				scanf("%s",aaa);
				a[i][j] = (char*)malloc(strlen(aaa) + 1);
				strcpy(a[i][j], aaa);
			}
		}
	
		for(i = 0;i < r1; i++){
			for(j = 0;j < c1; j++){
				printf("Enter B [%d] [%d] = ", i, j);
				scanf("%s", aaa);
				b[i][j] = (char *)malloc(strlen(aaa) +1);
				strcpy(b[i][j], aaa);
			}
		}
		for(i = 0; i < r; i++){
			for(j = 0; j < c1; j++){
				sum = 0;
				for(k = 0; k < r1; k++){
					//sum = sum + a[i][k] * b[k][j];
					c[i][j] = (char *)malloc(1024);
					if(sum < 1){
						c[i][j][0] = '0';
						c[i][j][1] = '\0';
						sum++;
					}
					mul( a[i][k], b[k][j], aaa);
					add( c[i][j] , aaa);
				}
			}
		}
		for(i = 0;i < r; i++){
			for(j = 0; j < c1; j++){
				printf("  %s  \t ", c[i][j]);
			}
			printf("\n");
		}
	return 0;
	}//decimal cant be performed right now...
	if(aa == '/'){
		//fing the inverse of b and multiply by b;
		for(i = 0; i < m; i++){
			for(j = 0;j < n; j++){
				printf("enter A [%d] [%d] = ", i, j);
				scanf("%f",&x[i][j]);
			}
		}
		inverse( n );
		//multiply global  with a;
		sum = 0;
		r = c2 = n;
		r1 = c1 = global[100][100];
		for(i = 0; i < r; i++){
			for(j = 0; j < c1; j++){
				for(k = 0; k < r1; k++){
					sum = sum + x[i][k] * global[k][j];
				}
			x[i][j] = sum;
			sum = 0;
			}
		}
		printf("Division of matrix A to matrix B.\n\n");
		for(i = 0;i < r; i++){
			for(j = 0; j < c2; j++){
				printf("%lf ", x[i][j]);
			}
			printf("\n");
		}
	}//the code of division is the worst didnt had time.......every thing is worst...that'ss done in integer!
}
float squareroot(int n){
	float x = n;
	float y = 1;
	float e = 0.000001;
	while(x - y > e){
		x = (x + y) / 2;
		y = n / x;
	}
	return x;
}
int subtractiondecimal(char fir[], char sec[], char res[]){
	char  *p;
	int flag = 0, flag1 = 0;
	int a, b, c, d, e, f, sign = 0;
	a = strlen(fir);
	b = strlen(sec);
	while(c < a){
		if( fir[c] == '.' ){
			flag = 1;
			break;
		}
		c++;
	}
	while(d < b){
		if(sec[d] == '.'){
			flag1 = 1;
			break;
		}
		d++;
	}
	if(flag == 0 && flag1 == 0 ) {
		 sign = sub(fir, sec, res) ;
		if(sign != 1)	
			printf("-");
		int len = strlen(res);
		return sign;
	}//works fine
	if(flag == 1 && flag1 == 0) {
		a = strlen( fir ) - c - 1;
		while(a != 0){
			strcat( sec, "0");
			a--;
		}
		//remove the dot from fir.....
		a = c;
		b = strlen ( fir );
		c = b - c -1;
		while(a < b) {
			fir[a] = fir[a + 1];
			a++;
		}
		if(sign = sub( fir, sec, res) == 1)
			printf("-");
			//insert the dot.
			b = strlen ( res );
			while(c != 0){
				res[b] = res[ b - 1];
				c--;
				b--;
			}
			res[b] = '.';
			p = (char *)malloc(strlen (res) + 4);
			p[0] = '0';
			p[1] = '\0';
			if(res[0] == '.'){
				strcat( p, res);
				strcpy( res, p);
			}
			free ( p );
			return sign;	
		
	}//works fine
	if( flag == 0 && flag1 == 1){
		a = strlen ( sec ) - d - 1;
		while( a != 0 ){
			strcat ( fir, "0");
			a--;
		}
		//remove the dot......
		a = d;
		b = strlen(sec);
		d = b - d -1;
		while(a < b){
			sec[a] = sec[ a + 1];
			a++;
		}
		if(sign = sub( fir, sec, res) == 1)
			printf("-");
		//insert dot.....
		b = strlen ( res );
		while( d != 0){
			res[b] = res[b - 1];
			d--;
			b--;
		}
		res[b] = '.';
		p = (char *)malloc(strlen (res) + 4);
		p[0] = '0';
		p[1] = '\0';	
		if(res [0] == '.'){
			strcat ( p, res);
			strcpy( res, p);
		}
		free ( p );
		return sign;
	}
	if ( flag == 1 && flag1 == 1){
		a = strlen ( fir );
		b = strlen ( sec );
		c = a - c - 1;
		d = b - d - 1;
		if( c > d){
			e = c;
			f = c - d;
			c = a - c - 1;
			d = b - d - 1;
			//remove the dots....
			while(c < a){
			}
				fir[c] = fir[c + 1];
				c++;
			while(d < b){
				sec[d] = sec[d + 1];
				d++;
			}//dots removed
			//add zero to lesser number forr equidecimal
			while(f != 0){
				strcat( sec, "0");
				f--;
			}//now call subtraction
			if(sign = sub( fir, sec, res) == 1)
				printf("-");
				//insert the dot in res of max 
			b = strlen ( res );
			if( strlen(res) < e){
				a = strlen( res );
				b = e - a;
				p = (char *)malloc( strlen ( fir ) + strlen ( sec ) );
				while(b != 0){
					p[0] = '0';
					p[1] = '\0';
					strcat( p, res);
					strcpy( res, p);
					b--;
				}
				p[0] = '0';
				p[1] = '.';
				p[2] = '\0';
				strcat( p, res);
				strcpy( res, p);
				free ( p );
				return sign;
			}
			while(e != 0){
				res[b] = res[b - 1];
				b--;
				e--;
			}
			res[b] = '.';
			p = (char *)malloc(strlen ( res ) + 4);
			p[0] = '0';
			p[1] = '\0';
			if( res [0] == '.'){
				strcat( p, res);
				strcpy( res, p);
			}
			free ( p );
			return sign;
		}//works perfectly......
		else if (c < d){
			e = d;
			f = d - c;
			//remove decimal dots
			c = a - c - 1;
			d = b - d - 1;
			while( c < a ){
				fir[c] = fir[c + 1];
				c++;
			}
			while( d < b ){
				sec[d] = sec[ d + 1 ];
				d++;
			}
			//make equal decimals
			while(f != 0){
				strcat( fir, "0");
				f--;
			}
			if(sign = sub( fir, sec, res))
				printf("-");
			b = strlen( res );
			if (b < e){
				a = strlen( res );
				b = e - a;
				p = (char *)malloc( strlen ( fir ) + strlen ( sec ) );
				while(b != 0){
					p[0] = '0';
					p[1] = '\0';
					strcat( p, res);
					strcpy( res, p);
					b--;
				}
				p[0] = '0';
				p[1] = '.';
				p[2] = '\0';
				strcat( p, res);
				strcpy( res, p);
				free ( p );
				return sign;
			}
			while(e != 0){
				res[b] = res[b - 1];
				b--;
				e--;
			}
			res[b] = '.';
			p = (char *)malloc(strlen ( res ) + 4);
			p[0] = '0';
			p[1] = '\0';
			if( res [0] == '.'){
				strcat( p, res);
				strcpy( res, p);
			}
			free ( p );
			return sign;

		}//works fine...
		else if ( c == d ){
			//just remove the dots.......
			e = c;
			c = a - c - 1;
			d = b - d - 1;
			while(c < a){
				fir[c] = fir[c + 1];
				c++;
			}
			while(d < b){
				sec[d] = sec[d + 1];
				d++;
			}
			if(sub( fir, sec, res) == 1)
				printf("-");
			b = strlen( res );
			if( b < e ){
				a = strlen( res );
				b = e - a;
				p = (char *)malloc( strlen ( fir ) + strlen ( sec ) );
				while(b != 0){
					p[0] = '0';
					p[1] = '\0';
					strcat( p, res);
					strcpy( res, p);
					b--;
				}
				p[0] = '0';
				p[1] = '.';
				p[2] = '\0';
				strcat( p, res);
				strcpy( res, p);
				free ( p );
				return 1;
			}
			while(e != 0){
				res[b] = res[b - 1];
				b--;
				e--;
			}
			res[b] = '.';
			p = (char *)malloc(strlen ( res ) + 4);
			p[0] = '0';
			p[1] = '\0';
			if( res [0] == '.'){
				strcat( p, res);
				strcpy( res, p);
			}
			free ( p );
			return 1;
		}
	}
}
void actualdivisioninterface(char a[], char b[], char c[], char d[]){
	char *p;
	int i, ii, j, flag = 0, flag1 = 0;
	//check string compare..compare the value of the given two string and 	
	//note while using the above function 
	////value of *a changes in addition......
	//value of *a changes in subtraction
	////here a and b both changes in multiplication.../././././
	//build first an n^2 complexicity function where it will run only 20 times which is negligile
	//lets go
	//yup done the code of division of n^2 complexicity will be used to calculate to divide and rule application
	//to make it just k*n where its is almost negligible compare to n^2 and k is no of digits +- some numbers 
	//depending upon the case.. 
	//now using the above multiplying code to reach the real unlimited division......
	//take the argunemnt as -l for decimal   mode   .....................
	removezero(a);
	removezero(b);
	if( strcmp(a,b) == 0 ){
		c[0] = '1';
		c[1] = '\0';
		d[0] = '0';
		d[1] = '\0';
		return;
	}
	infinity:
	i = 0;
	j = strlen(a);
	while(i < j){
		if(a[i] == '.'){
			flag = 1;
			ii = i;
			break;
		}
		i++;
	}
	i = 0;
	j = strlen(b);
	while(i < j){
		if(b[i] == '.'){
			flag1 = 1;
			break;
		}
		i++;
	}
	if(flag == 0 && flag1 == 0){
		int c1;
		c1 = 0;
	 	if(scale != 0){
			while( c1 <= scale ){
			strcat( a, "0");
			c1++;
			}
		}
		realdivision( a, b, c, d);
		int j = 0;
		int iii = strlen(c);
		if( scale != 0 ){
			while( j <= scale ){
				c[iii] = c[iii - 1];
				iii--;
				j++;
			}
			c[ iii ] = '.';
		}
		return;
	}
	else if(flag == 1 && flag1 == 0){
		//remove the dot and divide
		// ii has the dot position.
		flag = strlen(a);
		flag1 = ii; 
		while(ii < flag) {
			a[ii] = a[ii + 1];
			ii++;
		}
		int c1;
		c1 = 0;
		if(scale != 0){
			while( c1 < scale ){
				strcat( a, "0");
				c1++;
			}
		}
		realdivision( a, b, c, d);
		int j = 0;
		int iii = strlen(c);
		if( scale != 0 ){
			while( j <= scale ){
				c[iii] = c[iii - 1];
				iii--;
				j++;
			}
			c[ iii ] = '.';
			return ;
		}
		ii = strlen (c);
		flag1 = flag - flag1 - 1;
		c[ii + 1] = '\0';
		while(flag1 != 0){
			c[ii] = c[ii - 1];
			ii--;
			flag1--;
		}
		c[ii] = '.';
		///for the case of the decimal solid calculate later the value
		return;
	}
	else if(flag == 0 && flag1 == 1){
		//i has the dot position.....
		flag = strlen (b);
		flag1 = 0;
		while(i < flag){
			b[i] = b[i + 1];
			flag1++;
			i++;
		}
		//check
		while(flag1 != 1){
			strcat( a, "0");
			flag1--;
		}
		int c1;
		c1 = 0;
		if(scale != 0){
				while( c1 <= scale ){
				strcat( a, "0");
				c1++;
			}
		}
		realdivision( a, b, c, d);
		int j = 0;
		int iii = strlen(c);
		if( scale != 0 ){
			while( j <= scale ){
				c[iii] = c[iii - 1];
				iii--;
				j++;
			}
			c[ iii ] = '.';
			return ;
		}
		removezero(c);
		return;
	}
	else if(flag == 1 && flag1 == 1){
		//again more three cases arries headache .comparing bot the dots of the a and b
		 ii = strlen(a) - ii -1;
		 i = strlen (b) - i - 1;
		 if(ii == i){
		 	//remove the dots from both the strings and multiply
		 	ii = strlen(a) - ii - 1;
		 	i = strlen(b) - i -1;
		 	flag = strlen(a) ;
		 	flag1 = strlen(b);
		 	while( ii < flag ){
		 		a[ii] = a[ii + 1];
		 		ii++;
		 	}
		 	while( i < flag1 ){
		 		b[i] = b[i + 1];
		 		i++;
		 	}
		 	int c1;
			c1 = 0;
			if(scale != 0){
					while( c1 <= scale ){
					strcat( a, "0");
					c1++;
				}
			}
		 	realdivision( a, b, c, d);
		 	int j = 0;
			int iii = strlen(c);
			if( scale != 0 ){
				while( j <= scale ){
					c[iii] = c[iii - 1];
					iii--;
					j++;
				}
				c[ iii ] = '.';
				return ;
			}
			removezero(c);
		 	///decimal cases will be handled later......
		 	return;
		 }
		 else if( ii > i ){
		 	//shift the dot in a;
		 	ii = strlen(a) - ii -1;
			flag = i;
			while( i != 0 ){
				a[ii] = a[ii + 1];
				ii++;
				i--;
			}
			a[ii] = '.';
			//remove the dot from b
			flag = strlen(b) - flag - 1;
			j = strlen(b);
			while(flag < j){
				b[flag] = b[flag + 1];
				flag++;
			}// dot removed
			flag = 0;
			flag1 = 0;
			goto infinity;
		}
		else if( ii < i){
			//remove the dot from a ||shift the dot in b
			flag = ii;
			ii = strlen(a) - ii -1;
			j = strlen(a); 
			while(ii < j) {
				a[ii] = a[ii + 1];
				ii++;
			}
			ii = flag;
			i = strlen(b) - i - 1;
			while(ii != 0){
				b[i] = b[i + 1];
				i++;
				ii--;
			}
			b[i] = '.';
			flag = 0;
			flag1 = 0;
			goto infinity;
		}
	}
}
void getnum(char a[], char e[]){
	int t;
	t = strlen (e);
	e[t] = a[ii];
	e[t + 1] = '\0';
	ii++;
	return;
}
void realdivision( char a[], char b[], char c[], char d[] ){
	//yes denotes decimal case on
	//remember dont change the value  of a and b in any cases
	//store the quotient in c and the remainder
	//bc gives the decimal accuracy of 20 after the deciml point at that number.
	//so lets go
	//take tha argunment as the fifth argunment in this function as sucess condition ..
	j = 0;
	int fb;
	int k, iii;
	int c1;
	/* c1 = 0;
	while( c1 <= 20 ){
		strcat( a, "0");
		c1++;
	}*/
	c1 = compare( a, b);
	if(c1 == 3){
		c[0] = '0';
		c[1] = '\0';
		strcpy( d, a);
		return;
	}
	k = strlen (a);
	c[0] = '\0';
	char f[MAX];
	char e[MAX];
	e[0] = '\0';
	ii = 0;
	while( ii < k ) {
		j = 0;
		while(1){
			fb = compare( b, e);
			if( fb == 3){
				break;
			}
			iii = ii;
			if( j > 0 && iii <= k ){
				strcat( c, "0");
				iii++;
			}
			if( iii == k + 1 ){
				return;
			}
			getnum( a, e);
			j++;
		}
		//e has the number...
		
		multiplythere( e, b, f, d);
		strcat( c, f);
		strcpy( e, d);
	}
	
	//insert the decimal point from behind at  the place of 20
	//then there will be no need of remainder
	//after two zero after the a variable gives wired results
	//saving space;
	//i hav a function which gives the remainder in the 3 and 4 argunment array.
}
void multiplythere(char a[], char b[], char c[],char d[]){
	char mul[MAX];
	int i;
	char *pp;
	if (strcmp( a, b) == 0 ){
		strcpy( c, a);
		d[0] = '0';
		d[1] = '\0';
		return;
	}
	c[0] = '1';
	c[1] = '\0';
	d[0] = '1';
	d[1] = '\0';
	while( 1 ){
		c[0] = '1';
		c[1] = '\0';
		multiply( b, d, mul);///HERE ALSO changes the value of a and b. so irretating
		////value of c gives segfaults......remember cant use c any further bro
		if(mul[0] == '0' && strlen ( mul ) != 1){
			int j = strlen (mul);
			i = 0;
			while(j != 0){
				mul[i] = mul[i + 1];
				i++;
				j--;
			}
		}
		i = compare ( mul, a);
		if( i == 1){
			strcpy( c, d);
			d[0] = '0';
			d[1] = '\0';
			return;
		}
		 if( i == 2){
			//multiplication gone far bring it 2 step back;
			c[0] = '1';
			c[1] = '\0';
			int j = sub( d, c, c);///MARK ,LINE OF MISTAKE
			// FOR REMAINDER
			multiply( c, b, mul);
			j = sub( a, mul, d);
			return;
		}
		if(i == 3){
			addition( d, c);
		}
	}
}
int compare(char a[],char b[]){//here a is to be compared....
	removezero (a);
	removezero (b);
	int i, j;
	i = strlen(a);
	j = strlen(b);
	if(i > j){
		return 2;
	}
	if(i < j){
		return 3;
	}
	if( i == j ){
		i = strcmp( a, b);
		if( i == 0)
			return 1;
		if( i < 0 )
			return 3;
		if( i > 0 )
			return 2;
	}
	
}

int sub(char *a,char *b,char *ans) {
	char *aa, *bb;
	if( strlen(a) > strlen(b) ){
		aa = (char *)malloc(strlen ( a ) + 4);
		bb = (char *)malloc(strlen (b) + 4);
	}
	else {
		aa = (char *)malloc(strlen (b) + 4);
		bb = (char *)malloc(strlen (b) + 4);
	}
	int l, s, tmp;
	int n = 0, h = 0, anss;
	l = strlen(a);
	s = strlen(b);
	int sign = 0;
	if(l < s){
		strcpy(ans, a);
		strcpy(a, b);
		strcpy(b, ans);
		//exchange the length also yaar
		tmp = l;
		l = s;
		s = tmp;
		sign = 1;
	}
	if(l == s){
		if(strcmp( a, b) < 0){
			strcpy( ans, a);
			strcpy( a, b);
			strcpy( b, ans);
			sign = 1;
			tmp = l;
			l = s;
			s = tmp;
		}
	}
	rev( a,aa);
	rev( b,bb);
	for( ; s < l; s++)
		bb[s] = '0';
	bb[s] = '\0';
	for( ; n < l;n++){
		anss = aa[n] - (bb[n] +h);
		if(anss < 0){
			h = 1;//bring to exact ascii
			ans[n] = 10 + anss + '0';
		}
		else{
			ans[n] = anss + '0';
			h = 0;
		}
	}
	for(n = l - 1;n > 0; n--){
		if (ans[n] != '0')
			break;
	}
	ans[n+1] = '\0';
	rev( ans, a);
	strcpy( ans, a);
	return sign;
}

////value of *x changes......
void addition(char *x, char *y){
		int i, j, k, sum, carry, l, a, b, c, d;
		char str3[MAX];
		a = strlen(x);
		b = strlen(y);
		k = 0;
		carry = 0;
		sum = 0;
		if(a == 1 && b == 1){
			sum = a + b;
			i = (x[0] - '0') + (y[0] - '0');
			if(i <= 9){
				x[0] = (x[0] - '0') + (y[0] - '0') + '0';
				x[1] = '\0';
				return;
			}
			else {
				j = i/10;
				x[0] = j + '0';
				j = i % 10;
				x[1] = j + '0';
				x[2] = '\0';
				return;
			}
		}
		else {
			for(i = a - 1, j = b - 1; ; i--, j--) {
				if(x[i] == '.'){
					i--;
				}
				if(y[j] == '.'){
					j--;
				}
				c = x[i] - '0';
				d = y[j] - '0';
				if(j < 0) {
					d = 0;
				}
				if(i < 0) {
					c = 0;
				}
				if(i < 0 && j < 0) {
					break;
				}
				sum = c + d + carry;
				str3[k] = sum % 10 + '0';
				carry = sum / 10;
				k++;
			}
			for(l = k - 1, i = 0; l >= 0, i <= k - 1; l--, i++) {
				x[i] = str3[l];
			}
			x[i] = '\0';
			if(carry == 1){
				int ii, iik;
				ii = strlen (x);
				iik = ii;
				while(ii != 0){
					x[ii] = x[ii - 1];
					ii--;
				}
				x[0] = carry + '0';;
				x[iik+1] = '\0';
			}
			return;
		}
}

void rev(char *a, char *b){
	char *tmp;
	int l = strlen(a);
	int l1;
	for( l1 = 0; l1 < l; l1++)
		b[l1] = a[l - l1 -1];
	b[l] = '\0';
}
//value of *a changes


void removezero(char a[]){
	int ij = 0;
	int l;
	l = strlen(a);
	while(a[0] == '0'){
		l = strlen(a);
		while(ij < l){
			a[ij] = a[ij+1];
			ij++;
		}
		ij = 0;
	}
	return;
}

void power(char a[], char b[], char c[]) {
	if(strlen(b) == 1 && b[0] == '0'){
		c[0] = '1';
		c[1] ='\0';
		return;
	}
	removezero(b);
	if(strcmp(b,"1") == 0){
		strcpy( c, a);
		return;
	}
	if( strlen(b) == 1 && b[0] == '0'){
		c[1] = '\0';
		c[0] = '1';
		
		return;
	}
	int j = 0, flag = 0, i = 0, k = 0, l;
	l = i = strlen ( a );
	char *p, *q;
	q = (char *)malloc(strlen (b) + 3);
	p = (char *)malloc(strlen( a ) + 3 );
	strcpy( p, a);
	strcpy( q, b);
	while(i != 0 ) {
		if(a[j] == '.'){
			flag = 1;
			break;
		}
		j++;
		i--;
	}
	///j is the position of the decimal from front.....
	//now remove the dot.......
	if( flag == 1){
		i = j;
		j = l - j -1;
		k = strlen( a );
		while(i < k){
			a[i] = a[i + 1];
			i++;
		}
		a[i] = '\0';
	}
	k = 0;
	strminusone(b);
	while(b[0] != '0'){
		mul( a, p, c);
		strcpy( a, c);
		strminusone(b);
		k++;
	}
	k = k + 1;
	if(flag == 1){
		k = k * j;
		i = strlen (c);
		//remove the dot.
		flag = 0;
		while(flag < i){
			if(c[flag] == '.'){
				break;
			}
			flag++;
		}
		while(flag < i){
			c[flag] = c[flag + 1];
			flag++;
		}
		//put the dot
		j = i = strlen(c);
		while(k != 0){
			c[i] = c[i - 1];
			i--;
			k--;
		}
		c[j+1] = '\0';
		c[i] = '.';
	}
	strcpy( a, p);
	strcpy( b, q);
	free( q );
	free ( p );
	return;
}
void factorial(char a[]) {
	char  b[MAX];
	char c[MAX], *d;
	int i = 0, j, k;
	{
		d = (char *)malloc(strlen( b ) + 3 );
		if( a[0] == '0' && a[1] == '\0'){
			a[0] = '1';
			return;
			
		}
		if(a[0] == '1' && a[1] == '\0'){
			return;
		}
		else{
			strcpy( b, a);
			strminusone( b );
			strcpy( d, b);
			while(b[0] != '0'){
				multiply( a, b, c);
				i = 0;
				k = 0;
				strcpy( b, d);
				strcpy( a, c);
				strminusone( b );
				strcpy( d, b);
				//	removezero(c);
			}
		}
		strcpy( a, c);
		free ( d );
		return ;
	}
}
void tostring(char str[], int num) {
	int i, rem, len = 0, n;
	n = num;
	while (n != 0) {
		len++;
		n =n / 10;
	}
	for (i = 0; i < len; i++) {
		rem = num % 10;
		num = num / 10;
		str[ len - (i + 1) ] = rem + '0';
	}
	str[len] = '\0';
}
char * strminusone(char a[]){
 	int i, j, k=0;
	if(strlen(a) == 1 && a[0] == '0'){
		return a;
	}
	i = strlen(a)-1;
	j=0;
	int u=0;
		while(a[i-j] == '0') {
			k++;
			j++;
		}
		if (k>=1){
			while(k!=0) {
				a[i]='9';
				k--;
				i--;
			}
			a[i]=a[i]-1;
			if(a[0]=='0' && a[1]!='0'){
				u=strlen(a);
				k=0;
				while(k < u) {
					a[k]=a[k+1];
					k++;
				}
			}
		}
		else {
			i = strlen(a) -1;
			a[i]=a[i]-1;
		}
		u++;
	
}
void multiply(char a[],char b[], char mul[]){
	char *c = (char *)malloc( MAX );
	char *tmp = (char *)malloc( MAX );
	char * c1, *c2;
	c1 = (char *)malloc(strlen ( a ) + 2);
	c2 = (char *)malloc(strlen ( b ) + 2);
	strcpy( c1, a);
	strcpy(c2 , b);
	int l, l1;
	int i, j, k = 0, x = 0, y;
	long int r = 0;
	long sum = 0;
	l = strlen(a) - 1;
	l1 = strlen(b) - 1;
	for(i = 0; i <= l; i++){
		a[i] = a[i] - 48;
	}
	for(i = 0; i <= l1; i++) {
		b[i] = b[i] - 48;
	}
	for(i = l1; i >= 0; i--){
		r = 0;
		for(j = l; j >= 0; j--){
				tmp[k++] = (b[i] * a[j] + r) % 10;
				r = (b[i] * a[j] + r) / 10;
		}
		tmp[k++] = r;
		x++;
		for(y = 0; y < x; y++ ) {
			tmp[k++] = 0;
		}
	}
	k = 0;
	r = 0;
	for( i = 0 ; i < l + l1 + 2; i++){
		sum = 0;
		y = 0;
		for(j = 1; j <= l1 + 1; j++){
			if(i <= l + j){
				sum = sum + tmp[y + i];
			}
			y += j + l + 1;
		}
		c[k++] = (sum + r) % 10;
		r = (sum + r)/10;
	}
	c[k] = r;
	j = 0;
	for(i = k - 1; i >= 0; i--){
		mul[j++] = c[i] + 48;
	}
	mul[j] = '\0';
	
	strcpy( a, c1);
	strcpy( b, c2);
	free( c );
	free( tmp );
	free( c1 );
	free( c2 );
	removezero( mul );
	return;
}
void mul(char a[],char b[], char c[]) {
	int flag = 0, flag1 = 0, x, y;
	int i , j, j1;
	x = strlen(a);
	y = strlen(b);
	i = 0;
	while( i < x ) {
		if ( a[i] == '.') {
			flag = 1;
			break;
		}
		i++;
	}
	i = 0;
	while( i < y ){
		if ( b[i] == '.'){
			flag1 = 1;
			break;
		}
		i++;
	}
	if ( flag == 1 && flag1 == 0 ){
		i = 0;
		int k;
		//char tmp;
		x = strlen(a);
		while ( i < x ){
			if ( a[i] == '.' ){
				break;
			}
			i++;
		}
		j = ( strlen(a) - i )-1;//decimal point from back.......set three as a reference please
		while( i < x ){
			a[i] = a[i+1];
			i++;
		}
		multiply( a, b, c);
		if(j > strlen(c) ) {
			i = j - strlen(c);
			char *cat;
			cat = (char *)malloc(strlen(c) + i + 3);
			cat[0] = '0';
			cat[1] = '.';
			j = 2;
			while(i != 0){
				cat[j] = '0';
				i--;
				j++;
			}
			cat[j] = '\0';
			strcat ( cat, c);
			strcpy( c, cat);
			free ( cat );
			return;
		}
		j = (strlen(c)-j);
		//tmp=c[j];
		k = strlen(c);
		while ( k >= j ) {
			c[k+1] = c[k];
			k--;
		}
		c[j] = '.';
		return;
	}
	else if( flag==0 && flag1==1 ){
		i = 0;
		int k;
		//char tmp;
		x = strlen(b);
		while( i < x ){
			if ( b[i] == '.' ){
				break;
			}
			i++;
		}
		j = ( strlen(b) - i )-1;//decimal point from back.......set three as a reference please
		while( i < x ){
			b[i] = b[i+1];
			i++;
		}
		multiply( a, b, c);
		if(j > strlen(c) ) {
			i = j - strlen(c);
			char *cat;
			cat = (char *)malloc(strlen(c) + i + 3);
			cat[0] = '0';
			cat[1] = '.';
			j = 2;
			while(i != 0){
				cat[j] = '0';
				i--;
				j++;
			}
			cat[j] = '\0';
			strcat ( cat, c);
			strcpy( c, cat);
			free ( cat );
			return;
		}
		j = (strlen(c)-j);
		//tmp=c[j];
		k = strlen(c);
		while( k >= j){
			c[k+1] = c[k];
			k--;
		}
		c[j] = '.';
		return;
	}
	else if(flag == 0 && flag1 == 0){
		multiply( a, b, c);
		return;
	}
	else if( flag==1 && flag1==1 ) {
		
		//a part to calculate the position of the decimal point.
		i = 0;
		int k;
		//char tmp;
		x = strlen(a);
		while(i < x){
			if(a[i] == '.'){
				break;
			}
			i++;
		}
		j = ( strlen(a) - i )-1;//decimal point from back.......set three as a reference please
		while(i < x){
			
			a[i] = a[i+1];
			i++;
		}
		//b part to calculate the position of the decimal point.;.;;;...;..;...;.;.;.;;;
		i = 0;
		x = strlen(b);
		while( i < x ){
			if(b[i] == '.'){
				break;
			}
			i++;
		}
		j1 = ( strlen(b) - i )-1;//decimal point from back.......set three as a reference please
		while(i < x){
			b[i] = b[i+1];
			i++;
		}
		multiply( a, b, c); 
		j = j + j1;
		
		j1 = strlen (c);
		if ( j > j1 ){ //when the decimal number is out of the range of the original
			i = j - j1;
			char *cat;
			cat = (char *)malloc(strlen(c) + j + 3);
			x = 0;
			cat[0] = '0';
			cat[1] = '.';
			x = 2;
			while(i != 0) {
				///insert zeros in begining;
				cat[x] = '0';
				x++;
				i--;
			}
			cat[x] = '\0';
			strcat(cat,c);
			strcpy( c , cat);
			free (cat);
			return;
		}
		i = j1;
		while(j != 0){
			c[j1] = c[j1 -1];
			j1--;
			j--;
		}
		c[j1] = '.';
		c[i + 1] = '\0';
		return;
	}///the last case does not work;
	return;
}
char  *add( char *x, char *y){
		int i, j, k, sum, carry, l, a, b, c, d;
		char *str3;
		if(strlen ( x ) > strlen ( y ) ){
			str3 = (char *)malloc(strlen ( x ) + 2 );
		}
		else {
			str3 = (char *)malloc(strlen ( y ) + 2 );
		}
		a = strlen(x);
		b = strlen(y);
		k = 0;
		carry = 0;
		sum = 0;
		if(a == 1 && b == 1){
			sum = a + b;
			//printf("sum is %d",(x[0]-'0')+(y[0]-'0'));
			if((x[0] - '0') + (y[0] - '0') <= 9){
				str3[0] = (x[0] - '0') + (y[0] - '0') + '0';
				str3[1] = '\0';
			}
			else{
				i = (x[0]-'0')+(y[0]-'0');
				str3[0] = (i / 10) + '0';
				str3[1] = (i % 10) + '0';
				str3[2] = '\0';
			}
			return str3;
		}
		else {
			for(i = a-1, j = b - 1 ; ; i--, j--)
			{
				if(x[i] == '.'){
					i--;
				}
				if(y[j] == '.'){
					j--;
				}
				c = x[i] - '0';
				d = y[j] - '0';
				if(j < 0) {
					d = 0;
				}
				if(i < 0) {
					c = 0;
				}
				if(i < 0 && j < 0) {
					break;
				}
				sum = c + d + carry;
				str3[k] = sum % 10 + '0';
				carry = sum / 10;
				k++;
			}
			for(l = k - 1,i = 0;l >= 0,i <= k - 1; l--, i++) {
				x[i] = str3[l];
			}
			
			x[i] = '\0';
			if(carry == 1){
				int ii,iik;
				
				ii = strlen (x);
				iik = ii;
				while(ii != 0){
					x[ii] = x[ii-1];
					ii--;
				}
				x[0] = carry +'0';;
				x[iik+1] = '\0';
			}
			return x;
		}
	
}
char * adddecimal(char x[], char y[]) {
	char  *z, *w, *xx, *yy, *cc;
	z = (char *)malloc(strlen (x) );
	w = (char *)malloc(strlen (y) );
	int i, j, k, sum, carry, l = 0, a, b, c, d, flag = 0, flag1 = 0;
	k = 0;
	carry = 0;
	sum = 0;
	{
		a = strlen(x);
		l = a;
		b = strlen(y);
		
		while(a != 0){
			if(x[a] == '.'){
				flag = 1;
				break;
			}
			a--;
		}
		while(b != 0){
			if(y[b] == '.'){
				flag1 = 1;
				break;
			}
			b--;
		}
		if(flag == 1){
			i = 0;
			l = strlen(x);
			while(i < l){
				if(x[i] == '.'){
					break;
				}
				i++;
			}
			i = i + 1;
			l = 0;
			a = strlen(x);
			while(i < a){
				z[l] = x[i];///z stores the value of the after decimal value of x .....
				i++;
				l++;
			}
			z[l] = '\0';
			l = strlen(x);
			i = 0;
			while(i < l){
				if(x[i] == '.'){
					break;
				}
				i++;
			}
			
			x[i+1] = '\0';
		}
		if(flag1 == 1){
			i=0;
			l = strlen(y);
			while(i < l){
				if(y[i] == '.'){
					break;
				}
				i++;
			}
			i = i + 1;
			l = 0;
			a = strlen(y);
			while(i < a){
				w[l] = y[i];///w stores the value of the after decimal value of y .....
				i++;
				l++;
			}
			w[l] = '\0';
			l = strlen(y);
			i = 0;
			while(i < l){
				if(y[i] == '.'){
					break;
				}
				i++;
			}
			y[i+1] = '\0';
		}
		if(flag == 0 && flag1 == 0){
			{
				a = strlen(x);
				b = strlen(y);
				if(b > a){
					xx = add(y,x);
				}
				else{
					xx = add(x,y);
				}
				
				return xx;
			}
		}//works fine
		else if(flag == 1 && flag1 == 0){
			xx = add(x,y);
			a = strlen (xx);
			xx[a] = '.';
			xx[a+1] = '\0';
			strcat( xx, z);
			return xx;
		}//works fine.
		else if(flag == 0 && flag1 == 1){
			xx = add(x,y);
			a = strlen (xx);
			xx[a] = '.';
			xx[a+1] = '\0';
			strcat( xx , w);
			return xx;
		}//works fine.
		else if(flag == 1 && flag == 1) {
			xx = add(x,y);
			a = strlen(xx);
			xx[a] = '.';
			xx[a+1] = '\0';
			a = strlen(z);
			b = strlen(w);
			int ii;
			ii = a;
			if(a > b){
				a = a - b;
				while(a != 0){
					w[b] = '0';
					b++;
					a--;
				}
				w[b+1] = '\0';
				yy = add( z, w);
				a = strlen(yy);
				b = strlen(z);
				if(a > b){
					cc[0] = yy[0];
					cc[1] = '\0';
					xx = add(xx,cc);
				}
				i = strlen(yy);
				int iik;
				if(i > ii){
					iik = strlen(xx);
					xx[iik - 1] = '\0';
					strcpy( x, xx);
					char aa[2];
					aa[0] = yy[0];
					aa[1] = '\0';
					xx = add(x,aa);
					iik = strlen(xx);
					xx[iik] = '.';
					xx[iik+1] = '\0';
					i = 0;
					iik = strlen(yy);
					while(i < iik){
						yy[i] = yy[i + 1];
						i++;
					}
				}
				strcat( xx, yy);
				return xx;
			}//works fine...
			else if(b > a){
				i = strlen( z );
				ii = strlen( w );
				i = ii - i;
				while( i != 0 ){
					strcat(z,"0");
					i--;
				}
				xx = add( z, w);
				if(strlen( xx ) > ii){
				//there should be the left shift in w cause of carry
					i = strlen ( x );
					x[i - 1] = '\0';
					yy = add(x,"1");
					i = strlen ( yy );
					yy[i] = '.';
					yy[i + 1] = '\0';
				}
				i = strlen (xx);
				ii = 0;
				while(ii < i){
					xx[ii] = xx[ii + 1];
					ii++;
				}
				strcat(x,xx);
				return x;
			}//works fine perfectly carry condition handled
			else if(a == b){
				yy = add ( z, w);
				i = strlen ( w );
				if( strlen( yy ) > i){
					ii = strlen (xx);
					xx[ ii - 1] = '\0';
					xx = add( xx, "1");
					strcat( xx, ".");
					i = strlen (yy);
					ii = 0;
					while(ii < i){
						yy[ii] = yy[ii + 1];
						ii++;
					}
				}
				strcat(xx, yy);
				return xx;
			}////works perfectly!!!!!!!!!!
		}
	}
	//only remains( -123.456 )case whicch will be handled in the postfix
}
int readline(char *arr, int len) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n' && i < MAX - 1) {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}
int precedence(char op) {
	if(op == '%')
		return 3;
	if(op == '*' || op == '/')
		return 2;
	if(op == '+' || op == '-')
		return 1;
	if(op == '(' || op == ')')
		return 4;
	return 0;
}
int checkexpression(char str[]){
	int i = 0, j = 0;
	token *t;
	t = getnext( str, &i);
	if( t->type == OPERATOR){
		if(t->op == 'd' || t->op == 'D'){
			return 1;
		}
		printf("PREFIX expression attempt : STANDARD INPUT ::  POSTFIX default only\n");
		return 0;
	}
	if(t->val[0] >='0' && t->val[0] <= '9'){
		j = 1;
	}
	t = getnext( str, &i);
	if(t->type == OPERATOR ) {
		if( j == 1){
			if(t->op != '!'){
				printf("INFIX expression attempt : STANDARD INPUT ::  POSTFIX default only\n");
				return 0;
			}
			return 1;
		}
		return 1;
	}
	t = getnext( str, &i);
	if( t->type == OPERATOR){
		return 1;
	}
}
int date(){
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "\n\t\t\t\t\t\tCurrent local time and date: %s\n", asctime (timeinfo) );
  return 0;
}

