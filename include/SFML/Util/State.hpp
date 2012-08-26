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

#ifndef SFML_STATE_HPP
#define SFML_STATE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "Export.hpp"
#include "State_Event.hpp"
#include <iostream>
#include <string>


namespace sf
{


class SFML_UTIL_API State_Event;

////////////////////////////////////////////////////////////
/// \brief The Util State class.
///
////////////////////////////////////////////////////////////
class SFML_UTIL_API State
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    State();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~State();


    ////////////////////////////////////////////////////////////
    /// \brief change state name
    ///
    /// \param string new name
    ///
    /// \return true if successful
    ////////////////////////////////////////////////////////////
    bool setName(std::string name);


    ////////////////////////////////////////////////////////////
    /// \brief get state name
    ///
    /// \return string
    ////////////////////////////////////////////////////////////
    std::string getName();


    ////////////////////////////////////////////////////////////
    /// \brief an event was triggered
    ///
    /// \param int ID of event
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void trigger(int event_id);


    ////////////////////////////////////////////////////////////
    /// \brief register a state_event with this state
    ///
    /// \param State_Event*
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void registerEvent(State_Event*);


    ////////////////////////////////////////////////////////////
    /// \brief unregister a state_event from this state
    ///
    /// \param State_Event*
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void unRegisterEvent(State_Event*);


protected :
    std::string state_name;
    std::vector<State_Event*> registered_events;
    std::vector<State_Event*>::iterator it;

};

} // namespace sf


#endif // SFML_STATE_HPP


////////////////////////////////////////////////////////////
/// \class sf::State
/// \ingroup util
///
/// sf::State represents a single state within a finite state machine.
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::State
///
////////////////////////////////////////////////////////////
