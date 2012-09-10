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
#include <SFML/Audio.hpp>
#include "Export.hpp"
#include <iostream>
#include <string>
#include <map>



namespace sf
{

class State_Event;
class State_Manager;

////////////////////////////////////////////////////////////
/// \brief The Util State Abstract class.
///
////////////////////////////////////////////////////////////
class SFML_UTIL_API State
{
public :

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
        if(manager != 0)
            manager->unRegisterState(this);

        if(State::registered_events.size() > 0){
            it = State::registered_events.begin();
            (*it)->unRegisterState(this);
        }
    }











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
    /// \brief an event was triggered
    ///
    /// \param int ID of event
    ///
    /// \return bool true on success
    ////////////////////////////////////////////////////////////
    bool trigger(int event_id);

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
    /// \return string name
    ////////////////////////////////////////////////////////////
    std::string getName();

    ////////////////////////////////////////////////////////////
    /// \brief get next state name
    ///
    /// \return string name, "" if none
    ////////////////////////////////////////////////////////////
    std::string nextState();

    ////////////////////////////////////////////////////////////
    /// \brief change DefaultNextStateName
    ///
    /// \param string new name
    ///
    /// \return true if successful
    ////////////////////////////////////////////////////////////
    bool setDefaultNextStateName(std::string name);

    ////////////////////////////////////////////////////////////
    /// \brief check if state is done, then transition to next state
    ///
    /// \return bool ,this is the triggered variable
    ////////////////////////////////////////////////////////////
    bool stateDone();


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

    ////////////////////////////////////////////////////////////
    /// \brief set a manager for this state
    ///
    /// \param State_Manager*
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void setStateManager(State_Manager*);

    ////////////////////////////////////////////////////////////
    /// \brief Change Active status, active status meaning is this state running?
    ///
    /// \param bool, active status true or false, the isActive variable
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void setActiveStatus(bool);

    ////////////////////////////////////////////////////////////
    /// \brief Get the Active status, active status meaning is this state running?
    ///
    /// \return bool, the isActive variable
    ////////////////////////////////////////////////////////////
    bool getActiveStatus();

    ////////////////////////////////////////////////////////////
    /// \brief reset the trigger by setting it to false
    ////////////////////////////////////////////////////////////
    void resetTrigger();



protected :

    //state identifier
    std::string state_name;

    static std::vector <State_Event*> registered_events;
    std::vector <State_Event*>::iterator it;

    //state to state mappings based on event_id
    std::map <int, std::string> eventIdStateTrigger;

    //the next state to run after this state ends
    std::string next_state_name;

    //if next_state_name is no longer valid
    std::string default_next_state_name;

    //if triggered then state manager will transition to next state, can only be triggered if state is active
    bool triggered;

    //if this state is currently cycling with state manager
    bool isActive;

    //pointer to the state_manager for this state
    State_Manager* manager;
};









////////////////////////////////////////////////////////////
/// \brief A NULL State.
///
////////////////////////////////////////////////////////////
class SFML_UTIL_API NULLState : public State
{
public:

    NULLState() : State("")
    {
        ;
    }

    ~NULLState()
    {
        ;
    }

    int Update (const double time)
    {
        return 0;
    }
    int Events ()
    {
        return 0;
    }
    int Draw (Image& canvas)
    {
        return 0;
    }
    int CleanUp ()
    {
        return 0;
    }
    int Init ()
    {
        return 0;
    }

protected:
    ;
};

} // namespace sf


#endif // SFML_STATE_HPP


////////////////////////////////////////////////////////////
/// \class sf::State
/// \ingroup util
///
/// sf::State represents a single state within a finite state machine. This is an abstract class.
///
/// Example:
/// \code
///
///class IntroState : public sf::State
///{
///public:
///	   std::string name;
///
///	   IntroState(std::string n) : sf::State(n)
///    {
///        name = n;
///    }
///
///    ~IntroState()
///    {
///        ;
///    }
///
///    int Update (const double time)
///    {
///    	   std::cout << "Intro_Update_" << name << std::endl;
///        return 0;
///    }
///
///    int Events ()
///    {
///    	   std::cout << "Intro_Events_" << name << std::endl;
///        return 0;
///    }
///
///    int Draw (sf::Image& canvas)
///    {
///    	   std::cout << "Intro_Draw_" << name << std::endl;
///        return 0;
///    }
///
///    int CleanUp ()
///    {
///    	   std::cout << "Intro_Cleanup_" << name << std::endl;
///        return 0;
///    }
///
///    int Init ()
///    {
///    	   std::cout << "Intro_Init_" << name << std::endl;
///        return 0;
///    }
///};
///
/// \endcode
///
/// \see sf::State
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \class sf::NULLState
/// \ingroup util
///
/// sf::NULLState represents a single state within no real functionality.
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::NULLState
///
////////////////////////////////////////////////////////////
