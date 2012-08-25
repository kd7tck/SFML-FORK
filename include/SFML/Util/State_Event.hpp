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

#ifndef SFML_STATE_EVENT_HPP
#define SFML_STATE_EVENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Export.hpp"
#include <iostream>
#include <string>
#include <vector>



namespace sf
{

class SFML_UTIL_API State;

////////////////////////////////////////////////////////////
/// \brief The Util State_Event class.
///
////////////////////////////////////////////////////////////
class SFML_UTIL_API State_Event
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    State_Event();


    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~State_Event();


    ////////////////////////////////////////////////////////////
    /// \brief trigger this event, and trigger all registered states
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void trigger();


    ////////////////////////////////////////////////////////////
    /// \brief obtain this event's ID
    ///
    /// \return int Event ID
    ////////////////////////////////////////////////////////////
    int getId();


    ////////////////////////////////////////////////////////////
    /// \brief register a state with this event
    ///
    /// \param State*
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void registerState(State*);


    ////////////////////////////////////////////////////////////
    /// \brief unregister a state from this event
    ///
    /// \param State*
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void unRegisterState(State*);



protected :
    static int event_count;
    int event_id;
    std::vector<State*> registered_states;
    std::vector<State*>::iterator it;
};

} // namespace sf


#endif // SFML_STATE_EVENT_HPP


////////////////////////////////////////////////////////////
/// \class sf::State_Event
/// \ingroup util
///
/// sf::State represents an event that can register with multiple states.
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::State_Event
///
////////////////////////////////////////////////////////////
