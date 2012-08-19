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

#ifndef SFML_SQLITE_HPP
#define SFML_SQLITE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Sqlite3/Export.hpp>
#include "sqlite3.h"
#include <iostream>
#include <string>

namespace sf
{

////////////////////////////////////////////////////////////
/// \brief The Sqlite3 runtime wrapper class.
///
////////////////////////////////////////////////////////////
class SFML_SQLITE3_API Sqlite
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    Sqlite();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Sqlite();

    

protected :

    
};

} // namespace sf


#endif // SFML_SQLITE_HPP


////////////////////////////////////////////////////////////
/// \class sf::Sqlite
/// \ingroup Sqlite3
///
/// sf::Sqlite is a very simple class that allows the wrapping of
/// the sqlite3 runtime directly into an application.
///
/// Example:
/// \code
///
///
/// \endcode
///
/// \see sf::Luaw
///
////////////////////////////////////////////////////////////
