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

#ifndef SFML_LUAC_HPP
#define SFML_LUAC_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include <SFML/Lua/*.hpp>
#include <iostream>
#include <stack>
#include <string>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
}


namespace sf
{

////////////////////////////////////////////////////////////
/// \brief The lua runtime wrapper class, allows for seamless
/// integration of lua scripts into game.
///
////////////////////////////////////////////////////////////
class Luac
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    Luac() {}

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Luac() {}

    ////////////////////////////////////////////////////////////
    /// \brief Load a lua script and run it
    ///
    /// This function allows the program to load and run any lua script
    /// A zero is returned if successfull, non zero on error.
    ///
    /// \param file The file to load, full path is needed.
    ///
    ////////////////////////////////////////////////////////////
    int runScript(char* file);

protected :
    std::stack<std::string> buffer;
};

} // namespace sf


#endif // SFML_LUAC_HPP


////////////////////////////////////////////////////////////
/// \class sf::Lua
/// \ingroup lua
///
/// sf::Lua is a very simple class that allows the wrapping of
/// the Lua runtime directly into an application.
///
/// Example:
/// \code
///
///     virtual void lua_routine(sf::Lua lua_runtime)
///     {
///         ;
///     }
///
/// \endcode
///
/// \see sf::RenderTarget
///
////////////////////////////////////////////////////////////
