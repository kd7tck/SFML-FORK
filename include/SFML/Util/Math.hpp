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








extern "C" {
    typedef struct fract{
        double whole;
        double top;
        double bottom;
        bool positive;
    }fraction;

    typedef long double (*func_x)(long double x);
    extern long double func_square(long double x);
    extern long double func_pow_neg1(long double x);
    extern double gcd(double x, double y);
    extern fraction convertDecToFraction(double d);
    extern long double integrate(func_x fx, double a, double b, unsigned int div);
    extern long double integrate_x(func_x fx, double x);
    extern long double naturalLog(double a);
    extern long double difference_eq(func_x fx, long double h, long double x);
    extern char* convertFractionToChar(fraction f);
    extern long double slope_fx(func_x fx);
}




namespace sf
{

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



protected :

};

} // namespace sf


#endif // SFML_MATH_HPP


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
