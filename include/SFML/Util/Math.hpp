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

#ifndef SFML_MATH_HPP
#define SFML_MATH_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Export.hpp"
#include "stb_vec.h"
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>






namespace sf
{

const double C_PI_180 = 1.7453292519943295769236907684886127e-2L;
const double C_180_PI = 57.295779513082320876798154814105170L;

////////////////////////////////////////////////////////////
/// \brief The Fraction class.
///
////////////////////////////////////////////////////////////
class SFML_UTIL_API Fraction
{//Fraction class written by Naraku9333
	public:
		Fraction();
		Fraction(int numer);
		Fraction(int numer, int denom);
		Fraction(char* frac);

		Fraction operator+(const Fraction& op2) const;
		friend Fraction operator+(const int op1, const Fraction& op2);
		Fraction operator-(const Fraction& op2) const;
		friend Fraction operator-(const int op1, const Fraction& op2);
		Fraction operator*(const Fraction& op2) const;
		friend Fraction operator*(const int op1, const Fraction& op2);
		Fraction operator/(const Fraction& op2) const;
		friend Fraction operator/(const int op1, const Fraction& op2);


		bool operator<(const Fraction& op2) const;
		friend bool operator<(const int op1, const Fraction& op2);
		bool operator>(const Fraction& op2) const;
		friend bool operator>(const int op1, const Fraction& op2);
		bool operator<=(const Fraction& op2) const;
		friend bool operator<=(const int op1, const Fraction& op2);
		bool operator>=(const Fraction& op2) const;
		friend bool operator>=(const int op1, const Fraction& op2);
		bool operator==(const Fraction& op2) const;
		friend bool operator==(const int op1, const Fraction& op2);
		bool operator!=(const Fraction& op2) const;
		friend bool operator!=(const int op1, const Fraction& op2);


		Fraction operator-() const;


		friend std::ostream& operator<<(std::ostream& ostr, const Fraction& frac);

		friend std::istream& operator>>(std::istream& istr, Fraction& frac);

		class Undefined{};
		class Invalid{};

	private:
		int numer, denom, whole;
		void reduce();
		Fraction reduce(Fraction& frac) const;
		bool isNum(char* n);
};



////////////////////////////////////////////////////////////
/// \brief The Util State Abstract class.
///
////////////////////////////////////////////////////////////
class SFML_UTIL_API Math
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    /// \param string name
    ///
    ////////////////////////////////////////////////////////////
    Math();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Math();

    ////////////////////////////////////////////////////////////
    /// \brief obtain greatest common denomenator
    ///
    /// \param type x
    ///
    /// \param type y
    ///
    /// \return type gcd result
    ///
    ////////////////////////////////////////////////////////////
    template <class T>
    T gcd(T x, T y);

    ////////////////////////////////////////////////////////////
    /// \brief using function f(x), compute the difference eq. of x, all over h
    ///
    /// Example:
    /// \code
    /// static long double func_square(long double x){
    /// return x*x;
    /// }
    /// difference_eq<long double>(&func_square, 0.0000001, 1.0);
    /// \endcode
    ///
    /// \param MATH_FUNCTION<type>::func_x f
    ///
    /// \param type h
    ///
    /// \param type x
    ///
    /// \return type result
    ///
    ////////////////////////////////////////////////////////////
    template <class T>
    T difference_eq(T (*func_x)(T x), T h, T x);


    ////////////////////////////////////////////////////////////
    /// \brief obtain prime factors of number
    ///
    /// \param type x
    /// \return type vector of factors
    ///
    ////////////////////////////////////////////////////////////
    template <class T>
    std::vector<T> getFactors(T x);



protected :

};

} // namespace sf


#endif // SFML_MATH_HPP

////////////////////////////////////////////////////////////
/// \class sf::Fraction
/// \ingroup util
///
/// sf::Fraction is a object type used to store fractional numbers
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::Fraction
///
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// \class sf::Math
/// \ingroup util
///
/// sf::Math contains static functions for mathematical computation
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::Math
///
////////////////////////////////////////////////////////////
