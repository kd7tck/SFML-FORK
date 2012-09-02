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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Util.hpp>

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>


namespace sf
{

State::State(std::string n)
{
    next_state_name = "";
    default_next_state_name = "";
    triggered = false;
    isActive = false;
    state_name = n;
    manager = 0;
}

bool State::setName(std::string name)
{
    if(name.size() < 1)
        return false;

    state_name = name;
    return true;
}

std::string State::getName()
{
    return state_name;
}

std::string State::nextState()
{
    if(next_state_name.size() > 0)
        return next_state_name;
    else
        return default_next_state_name;
}


bool State::setDefaultNextStateName(std::string name)
{
    if(name.size() < 1)
        return false;

    default_next_state_name = name;
    return true;
}

bool State::stateDone()
{
    return triggered;
}



void State::registerEvent(State_Event* e)
{
    unRegisterEvent(e);
    registered_events.push_back(e);
    e->registerState(this);
}


void State::unRegisterEvent(State_Event* e)
{
    int count = 0;
    for ( it = registered_events.begin() ; it < registered_events.end(); it++ ){
        if((**it).getId() == e->getId())
        {
            registered_events.erase(registered_events.begin() + count);
        }
        else
            count++;
    }
}


void State::registerStateChange(int event_id, std::string next_state)
{
    eventIdStateTrigger[event_id] = next_state;
}


void State::unRegisterStateChange(int event_id)
{
    eventIdStateTrigger[event_id] = "";
}


void State::setStateManager(State_Manager* sm)
{
    manager = sm;
}


void State::setActiveStatus(bool b)
{
    isActive = b;
}

bool State::getActiveStatus()
{
    return isActive;
}


void State::resetTrigger()
{
    triggered = false;
}



} // namespace sf
