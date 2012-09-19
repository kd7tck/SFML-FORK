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

#ifndef SFML_B2D_HPP
#define SFML_B2D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Export.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <cmath>



class b2AABB;


namespace sf
{

////////////////////////////////////////////////////////////
/// \brief The BOX2D wrapper class.
///
////////////////////////////////////////////////////////////
class SFML_BOX2D_API b2d
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    b2d();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~b2d();

    ////////////////////////////////////////////////////////////
    /// \brief toggle sleep
    ///
    /// \return bool current sleep state
    ///
    ////////////////////////////////////////////////////////////
    bool toggleSleepState();

    ////////////////////////////////////////////////////////////
    /// \brief get current sleep state
    ///
    /// \return bool current sleep state
    ///
    ////////////////////////////////////////////////////////////
    bool getSleepState();


protected :
    bool doSleep;
    int iterations;
    float scale;
    float timeStep;
    sf::Vector2f gravity;
    b2AABB* worldAABB;

};

} // namespace sf


#endif // SFML_B2D_HPP

////////////////////////////////////////////////////////////
/// \class sf::b2d
/// \ingroup box2d
///
/// sf::b2d is used to simulate physics on 2d geometry
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::b2d
///
////////////////////////////////////////////////////////////
