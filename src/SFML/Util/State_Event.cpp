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

std::vector<State*> State_Event::registered_states;

State_Event::State_Event(int id)
{
    event_id = id;
}

State_Event::~State_Event()
{
    if(State_Event::registered_states.size() > 0){
        it = State_Event::registered_states.begin();
        (*it)->unRegisterEvent(this);
    }
}


bool State_Event::trigger()
{
    if(State_Event::registered_states.size() > 0)
    {
        for ( it = State_Event::registered_states.begin(); it != State_Event::registered_states.end() ; it++ )
        {
            (*it)->trigger(event_id);
        }
        return true;
    }
    return false;
}


int State_Event::getId()
{
    return event_id;
}


void State_Event::setId(int id)
{
    event_id = id;
}


void State_Event::registerState(State* s)
{
    unRegisterState(s);
    State_Event::registered_states.push_back(s);
}


void State_Event::unRegisterState(State* s)
{
    int count = 0;

    if(State_Event::registered_states.size() > 0)
    {
        for ( it = State_Event::registered_states.begin(); it != State_Event::registered_states.end() ; it++ )
        {
            if((*it)->getName() == s->getName())
            {
                State_Event::registered_states.erase(State_Event::registered_states.begin() + count);
                break;
            }
            else
                count++;
        }
    }

}




} // namespace sf
