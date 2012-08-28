////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2012 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#define STB_DEFINE
#include <SFML/Util/stb_vec.h>



/////////////////////////////////////////////////////////////////////////
//C Definitions
/////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct fract{
    double whole;
    double top;
    double bottom;
    bool positive;
}fraction;

typedef long double (*func_x)(long double x);
static long double func_square(long double x);
static long double func_pow_neg1(long double x);
double gcd(double x, double y);
fraction convertDecToFraction(double d);
long double integrate(func_x fx, double a, double b, unsigned int div);
long double integrate_x(func_x fx, double x);
long double naturalLog(double a);
long double difference_eq(func_x fx, long double h, long double x);
char* convertFractionToChar(fraction f);
long double slope_fx(func_x fx);



static long double func_square(long double x){
	return x*x;
}

static long double func_pow_neg1(long double x){
	if(x==0)
		return 0;
	else
		return 1.0/x;
}

double gcd(double x, double y){
        if(y == 0)
        {
                return x;
        }
        else
        {
                return gcd(y, fmod(x,y));
        }
}

fraction convertDecToFraction(double d){
	fraction f;
	double temp;

	if(d < 0){
		f.top = modf(fabs(d), &f.whole);
		f.bottom = 1.0;
		f.positive = false;
	}
	else if(!d){
		return f;
	}
	else{
		f.top = modf(d, &f.whole);
		f.bottom = 1.0;
		f.positive = true;
	}

	while(modf(f.top, &temp) > 0){
		f.top *= 10.0;
		f.bottom *= 10.0;
	}

	temp = gcd(f.top, f.bottom);
	while (temp != 1){
		f.top /= temp;
		f.bottom /= temp;
		temp = gcd(f.top, f.bottom);
	}

	return f;
}

long double integrate(func_x fx, double a, double b, unsigned int div){
	if(div==0)
		return 0;

	int count = 0;
	long double piece = (b-a)/((long double) div);
	long double base = a + piece;
	long double total = 0.0;

	for(;count<div;count++){
		total += fx(base) * (base - (base - piece));
		base += piece;
	}
	return total;
}


long double integrate_x(func_x fx, double x){
	return (integrate(fx, 0.0, 1.0, 1000000) * fx(x)) + fx(x);
}

long double naturalLog(double a){
	return integrate(&func_pow_neg1, 1.0, a, 1000000);
}

long double difference_eq(func_x fx, long double h, long double x){
	return (fx(x + h)-fx(x)) / h;
}

char* convertFractionToChar(fraction f){
	char* p = malloc(64);//63 characters
	p[63]='\0';
	if(f.positive)
		sprintf(p,"%.0f %.0f/%.0f", f.whole, f.top, f.bottom);
	else
		sprintf(p,"-%.0f %.0f/%.0f", f.whole, f.top, f.bottom);

	return p;
}


long double slope_fx(func_x fx){
	return difference_eq(fx, 0.0000001, 1.0);
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
