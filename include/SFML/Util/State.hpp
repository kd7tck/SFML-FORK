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
#include <SFML/Graphics.hpp>
#include "Export.hpp"
#include <iostream>
#include <string>
#include <map>


namespace sf
{


class SFML_UTIL_API State_Event;

////////////////////////////////////////////////////////////
/// \brief The Util State Abstract class.
///
////////////////////////////////////////////////////////////
class SFML_UTIL_API State
{
public :

    //Virtual functions for assigning user desired functionality
    ////////////////////////////////////////////////////////////
    /// \brief second thing to be called every game cycle
    ///
    /// \param double current time in milliseconds
    ///
    /// \return 0 if successfull
    ////////////////////////////////////////////////////////////
    virtual int Update (const double time) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief first thing to be called every game cycle
    ///
    /// \return 0 if successfull
    ////////////////////////////////////////////////////////////
    virtual int Events () = 0;

    ////////////////////////////////////////////////////////////
    /// \brief third thing to be called every game cycle
    ///
    /// \param Image, canvas to draw on
    ///
    /// \return 0 if successfull
    ////////////////////////////////////////////////////////////
    virtual int Draw (Image& canvas) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief called once when state is done
    ///
    /// \return 0 if successfull
    ////////////////////////////////////////////////////////////
    virtual int CleanUp () = 0;

    ////////////////////////////////////////////////////////////
    /// \brief called once when state is entered
    ///
    /// \return 0 if successfull
    ////////////////////////////////////////////////////////////
    virtual int Init () = 0;










    ////////////////////////////////////////////////////////////
    /// \brief change state name
    ///
    /// \param string new name
    ///
    /// \return true if successful
    ////////////////////////////////////////////////////////////
    virtual bool setName(std::string name)
    {
        if(name.size() < 1)
            return false;

        state_name = name;
        return true;
    }

    ////////////////////////////////////////////////////////////
    /// \brief get state name
    ///
    /// \return string
    ////////////////////////////////////////////////////////////
    virtual std::string getName()
    {
        return state_name;
    }

    ////////////////////////////////////////////////////////////
    /// \brief an event was triggered
    ///
    /// \param int ID of event
    ///
    /// \return bool true on success
    ////////////////////////////////////////////////////////////
    virtual bool trigger(int event_id)
    {
        if(eventIdStateTrigger[event_id].size() > 0)
        {
            next_state_name = eventIdStateTrigger[event_id];
            return true;
        }
        return false;
    }











    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    /// \param string name
    ///
    ////////////////////////////////////////////////////////////
    State(std::string name);

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~State(){
        if(registered_events.size() > 0)
            registered_events[0]->unRegisterState(this);
    }








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


    ////////////////////////////////////////////////////////////
    /// \brief register a state transition from this state node
    ///
    /// \param int event id
    ///
    /// \param string name of next state
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void registerStateChange(int event_id, std::string next_state_name);


    ////////////////////////////////////////////////////////////
    /// \brief unregister a state transition from this state node
    ///
    /// \param int event id
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void unRegisterStateChange(int event_id);


protected :
    std::string state_name;
    static std::vector <State_Event*> registered_events;
    std::vector <State_Event*>::iterator it;
    std::map <int, std::string> eventIdStateTrigger;//state to state mappings based on event_id
    std::string next_state_name;//the next state to run after this state ends
    std::string default_next_state_name;//if next_state_name is no longer valid

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
