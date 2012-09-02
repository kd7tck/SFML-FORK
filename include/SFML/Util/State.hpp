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














////////////////////////////////////////////////////////////
/// \brief STATE_DATA_CACHE type. Used for animation tracking between cycles.
///
////////////////////////////////////////////////////////////
typedef struct STATE_DATA
{//holds data for state between cycles
    double time[2];
    std::vector <sf::Image*> image_buffers;
    std::vector <sf::Image*>::iterator image_it;



    ////////////////////////////////////////////////////////////
    /// \brief creates new Image object, and pushes it onto back of image_buffer
    ///
    /// \param int x
    ///
    /// \param int y
    ///
    ////////////////////////////////////////////////////////////
    void pushNewImage(int x, int y)
    {
        sf::Image* i = new sf::Image();
        (*i).create(x,y);
        image_buffers.push_back(i);
    }



    ////////////////////////////////////////////////////////////
    /// \brief pops last element in image_buffer
    ///
    ////////////////////////////////////////////////////////////
    void popImage()
    {
        delete image_buffers.back();
        image_buffers.pop_back();
    }



    ////////////////////////////////////////////////////////////
    /// \brief peeks at last image in buffer
    ///
    /// \return Image* last image in vector
    ///
    ////////////////////////////////////////////////////////////
    sf::Image* peekImage()
    {
        return image_buffers.back();
    }
}
STATE_DATA_CACHE;











namespace sf
{

class SFML_UTIL_API State_Event;
class SFML_UTIL_API State_Manager;

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
        if(registered_events.size() > 0)
            registered_events[0]->unRegisterState(this);

        if(manager != 0)
            manager->unRegisterState(this);

        //clear out cache
        if(cache != 0)
        {
            if((*cache).image_buffers.size() > 0)
            {
                for ( (*cache).image_it = (*cache).image_buffers.begin() ; (*cache).image_it < (*cache).image_buffers.end(); (*cache).image_it++ ){
                    delete *(*cache).image_it;
                }
                (*cache).image_buffers.clear();
            }

            delete cache;
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
    virtual bool trigger(int event_id)
    {
        if(isActive && eventIdStateTrigger[event_id].size() > 0)
        {
            next_state_name = eventIdStateTrigger[event_id];
            triggered = true;
            return true;
        }
        return false;
    }












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
    std::string state_name;//state identifier
    static std::vector <State_Event*> registered_events;
    std::vector <State_Event*>::iterator it;

    std::map <int, std::string> eventIdStateTrigger;//state to state mappings based on event_id
    std::string next_state_name;//the next state to run after this state ends
    std::string default_next_state_name;//if next_state_name is no longer valid
    bool triggered;//if triggered then state manager will transition to next state, can only be triggered if state is active
    bool isActive;//if this state is currently cycling with state manager
    State_Manager* manager;
    STATE_DATA_CACHE *cache;//holds animation data for state between cycles
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
