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

#include <SFML/Util.hpp>

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>

#define STB_DEFINE
#include <SFML/Util/stb_vec.h>

template <class T>
bool isPrime(T num)
{
    if (num <=1)
        return false;
    else if (num == 2)
        return true;
    else if (num % 2 == 0)
        return false;
    else
    {
        bool prime = true;
        T divisor = 3;
        double num_d = static_cast<double>(num);
        T upperLimit = static_cast<T>(sqrt(num_d) +1);

        while (divisor <= upperLimit)
        {
            if (num % divisor == 0)
                prime = false;
            divisor +=2;
        }
        return prime;
    }
}


namespace sf
{


Fraction::Fraction()
{
	numer = 0;
	denom = 1;
}


Fraction::Fraction(int n)
{
	numer = n;
	denom = 1;
}


Fraction::Fraction(int n, int d)
{
	if(d != 0)
	{
		numer = n;
		denom = d;
		reduce();
	}
	else
		throw Undefined();
}


Fraction::Fraction(char* frac)
{
	char *w, *n, *d;
	whole = 0;

	int j = strcspn(frac, " ");
	int k = strcspn(frac, "/");


	if(j != strlen(frac))
	{
		w = new char[j];
		for(int i = 0; i < j; i++)
			w[i] = frac[i];
		whole = atoi(w);

		delete [] w;
	}

	if(k != strlen(frac))
	{	//if frac !mixed
		if(j == strlen(frac)){j = -1;}

		n = new char[k - (j+1)];
		for(int i = 0; i < k - (j+1); i++)
			n[i] = frac[i + (j+1)];

		d = new char[strlen(frac) - k+1];
		for(int l = 0; l < (strlen(frac) - (k+1)); l++)
			d[l] = frac[l + (k+1)];

		numer = atoi(n);
		denom = atoi(d);

		delete [] n;
		delete [] d;
	}

	else if(j == strlen(frac) && k == strlen(frac) && isNum(frac))
	{
		numer = atoi(frac);
		denom = 1;
	}
	else
	{
		std::cout << "INVALID Fraction"<<std::endl;
		numer = 0;
		denom = 1;

	}

	numer += whole*denom;
	reduce();
}


Fraction Fraction::operator+(const Fraction& op2) const
{
	Fraction answer;


	int n = numer,
		d = denom,
		op2n = op2.numer,
		op2d = op2.denom;


	d *= op2d;
	n *= op2d;
	op2n *= denom;
	op2d = d;

	answer.denom = d;
	answer.numer = n + op2n;

	return reduce(answer);
}


Fraction operator+(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return temp + op2;
}



Fraction Fraction::operator-(const Fraction& op2) const
{
	Fraction answer;


	int n = numer,
		d = denom,
		op2n = op2.numer,
		op2d = op2.denom;


	d *= op2d;
	n *= op2d;
	op2n *= denom;
	op2d = d;

	answer.denom = d;
	answer.numer = n - op2n;

	return reduce(answer);
}


Fraction operator-(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return temp - op2;
}

Fraction Fraction::operator*(const Fraction& op2) const
{
	Fraction answer;

	answer.numer = numer * op2.numer;
	answer.denom = denom * op2.denom;
	if(answer.denom < 0)
	{
		answer.numer *= -1;
		answer.denom *= -1;
	}
	return reduce(answer);
}


Fraction operator*(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return temp * op2;
}


Fraction Fraction::operator/(const Fraction& op2) const
{
	Fraction answer;

	answer.numer = numer * op2.denom;
	answer.denom = denom * op2.numer;
	if(answer.denom < 0)
	{
		answer.numer *= -1;
		answer.denom *= -1;
	}
	return reduce(answer);
}


Fraction operator/(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return (temp / op2);
}


bool Fraction::operator<(const Fraction& op2) const
{
	if((numer * op2.denom) < (op2.numer * denom))
		return true;
	else
		return false;
}


bool operator<(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return (temp < op2);
}


bool Fraction::operator>(const Fraction& op2) const
{
	if((numer * op2.denom) > (op2.numer * denom))
		return true;
	else
		return false;
}


bool operator>(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return (temp > op2);
}


bool Fraction::operator<=(const Fraction& op2) const
{
	if((numer * op2.denom) <= (op2.numer * denom))
		return true;
	else
		return false;
}


bool operator<=(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return (temp <= op2);
}


bool Fraction::operator>=(const Fraction& op2) const
{
	if((numer * op2.denom) >= (op2.numer * denom))
		return true;
	else
		return false;
}


bool operator>=(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return (temp >= op2);
}

bool Fraction::operator==(const Fraction& op2) const
{
	if((numer * op2.denom) == (op2.numer * denom))
		return true;
	else
		return false;
}


bool operator==(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return (temp == op2);
}

bool Fraction::operator!=(const Fraction& op2) const
{
	if((numer * op2.denom) != (op2.numer * denom))
		return true;
	else
		return false;
}


bool operator!=(const int op1, const Fraction& op2)
{
	Fraction temp(op1);
	return (temp != op2);
}

Fraction Fraction::operator-() const
{
	return -numer;
}


std::ostream& operator<<(std::ostream& ostr, const Fraction& frac)
{
	if(abs(frac.numer) > frac.denom)
	{
		int n = frac.numer,
			d = frac.denom,
			w = n/d;

		n = n % d;
		ostr << w;
		if(frac.denom != 1 || (frac.numer % frac.denom) != 0)
			ostr << ' ' << abs(n) << '/' << d;

	}
	else if(frac.numer == frac.denom)
		ostr << 1;
	else
		ostr << frac.numer << '/' << frac.denom;

	return ostr;
}


std::istream& operator>>(std::istream& istr, Fraction& frac)
{
	char temp[80];
	istr.getline(temp, 80);
	frac = temp;

	return istr;
}

void Fraction::reduce()
{
	int temp;

	int n = numer;
	int d = denom;

	while (d != 0)
	{
		temp = abs(n) % abs(d);
		n = d;
		d = temp;
	}
	numer /= n;
	denom /= n;
}


Fraction Fraction::reduce(Fraction& frac) const
{
	int temp;
	int n = frac.numer;
	int d = frac.denom;

	while (d != 0)
	{
		temp = abs(n) % abs(d);
		n = d;
		d = temp;
	}
	frac.numer /= n;
	frac.denom /= n;

	return frac;
}


bool Fraction::isNum(char* n)
{
	int val = 0;

	for(int i = 0; i < strlen(n); i++)
		val = isdigit(n[i]);

    if(val)
        return true;
    else
        return false;
}




















Math::Math()
{
    ;
}


Math::~Math()
{
    ;
}

template <class T>
T Math::gcd(T x, T y)
{
    if(y == 0)
    {
            return x;
    }
    else
    {
            return gcd(y, fmod(x,y));
    }
}

template <class T>
T Math::difference_eq(T (*fx)(T x), T h, T x)
{
    return (fx(x + h)-fx(x)) / h;
}


template <class T>
std::vector<T> Math::getFactors(T x)
{
    std::vector<T> vFactors;
    int d = 2;

    if(x <= 2 || isPrime(x))
    {
        vFactors.push_back(x);
        return vFactors;
    }

    while(d < x)
    {
        if(x % d == 0)
        {
            vFactors.push_back(d);
            x /= d;
        }
        else
        {
            if(d == 2)
                d = 3;
            else
                d += 2;
        }
    }

    vFactors.push_back(d);
    return vFactors;
}

} // namespace sf
