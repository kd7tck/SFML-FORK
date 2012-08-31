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

State_Manager::State_Manager()
{
    currentState = "";
    nextState = "";
    previousState = "";
}

State_Manager::~State_Manager()
{
    if(states.size() > 0)
        for ( it = states.begin() ; it < states.end(); it++ ){
            (**it).setStateManager(0);
        }
}


void State_Manager::registerState(State* s)
{
    unRegisterState(s);
    states.push_back(s);
    (*s).setStateManager(this);
}


void State_Manager::unRegisterState(State* s)
{
    int count = 0;
    for ( it = states.begin() ; it < states.end(); it++ ){
        if((**it).getName() == s->getName())
        {
            states.erase(states.begin() + count);
        }
        else
            count++;
    }
}


void State_Manager::Cycle()
{
    State* cptr = 0;

    if(currentState != "")
    {
        for ( it = states.begin() ; it < states.end(); it++ )
        {//find current state
            if((**it).getName() == currentState)
                cptr = *it;
        }

        if(cptr != 0 && (*cptr).stateDone())
        {//if current state is done

            if((*cptr).nextState() != "")
            {//first phase of state shift
                (*cptr).setActiveStatus(false);
                (*cptr).resetTrigger();
                nextState = (*cptr).nextState();
                previousState = currentState;
                currentState = "";
                Cycle();//start second phase of state shift
            }

            cptr = 0;
        }
    }
    else
    {
        if(nextState != "")
        {//second phase of state shift
            for ( it = states.begin() ; it < states.end(); it++ )
            {
                if((**it).getName() == nextState)
                    cptr = *it;
            }

            if(cptr != 0)
            {
                currentState = nextState;
                nextState = "";
            }
        }
    }


    //////////////////////////////////////
    //process current cycle, if no state shift
    //////////////////////////////////////
    if(cptr != 0)
    {
        ;
    }
}

void State_Manager::setCurrentState(State* s)
{
    if(s != 0)
        currentState = (*s).getName();
}



} // namespace sf
