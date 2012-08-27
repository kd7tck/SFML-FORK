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

State_Event::State_Event()
{
    event_id = event_count;
    event_count++;
}

State_Event::~State_Event()
{
    ;
}


bool State_Event::trigger()
{
    for ( it = registered_states.begin() ; it < registered_states.end(); it++ ){
        return (**it).trigger(event_id);
    }
}


int State_Event::getId()
{
    return event_id;
}


void State_Event::registerState(State* s)
{
    registered_states.push_back(s);
}


void State_Event::unRegisterState(State* s)
{
    int count = 0;
    for ( it = registered_states.begin() ; it < registered_states.end(); it++ ){
        if((**it).getName() == s->getName())
        {
            registered_states.erase(registered_states.begin() + count);
        }
        else
            count++;
    }
}




} // namespace sf
