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
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


namespace sf
{

State::State()
{
    ;
}

State::~State()
{
    for ( it = registered_events.begin() ; it < registered_events.end(); it++ ){
        (**it).unRegisterState(this);
    }
    registered_events.clear();
}


bool State::setName(std::string name)
{
    if(name.size() < 2)
        return false;

    state_name = name;
    return true;
}

//this is called only by events
void State::trigger(int event_id)
{
    if(eventIdStateTrigger[event_id].size() > 0)
    {
        next_state_name = eventIdStateTrigger[event_id];
    }
}


std::string State::getName()
{
    return state_name;
}



void State::registerEvent(State_Event* e)
{
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
            e->unRegisterState(this);
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




} // namespace sf
