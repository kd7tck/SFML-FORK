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

#ifndef SFML_STATE_MANAGER_HPP
#define SFML_STATE_MANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Export.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>


namespace sf
{


class SFML_UTIL_API State;

class SFML_UTIL_API NULLState;

////////////////////////////////////////////////////////////
/// \brief The Util State_Manager class.
///
////////////////////////////////////////////////////////////
class SFML_UTIL_API State_Manager
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    State_Manager();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~State_Manager();

    ////////////////////////////////////////////////////////////
    /// \brief register a state with this state manager
    ///
    /// \param State*
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void registerState(State*);

    ////////////////////////////////////////////////////////////
    /// \brief unregister a state with this state manager
    ///
    /// \param State*
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void unRegisterState(State*);

    ////////////////////////////////////////////////////////////
    /// \brief cycle one itteration, checks all states and runs them for one pass
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void Cycle();

    ////////////////////////////////////////////////////////////
    /// \brief set current state
    ///
    /// \param State*
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void setCurrentState(State*);


protected :
    std::vector<State*> states;
    std::string currentState;
    std::string nextState;
    std::string previousState;
    std::vector<State*>::iterator it;
    State* baseState;
    Image backBuffer;
    Clock clock;
    Time time;
};

} // namespace sf


#endif // SFML_STATE_MANAGER_HPP


////////////////////////////////////////////////////////////
/// \class sf::State_Manager
/// \ingroup util
///
/// sf::State_Manager manages a collection of states
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::State_Manager
///
////////////////////////////////////////////////////////////
