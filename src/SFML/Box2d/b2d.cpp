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

#include <SFML/Box2d.hpp>
#include "Box2D/Box2D.h"
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>


namespace sf
{


b2d::b2d()
{
    doSleep = true;
    iterations = 10;
    scale = 30.f;
    timeStep = 1/60;
    gravity.y = 9.8f;
    worldAABB = new b2AABB;
}


b2d::~b2d()
{
    delete worldAABB;
}


bool b2d::toggleSleepState()
{
    doSleep = !doSleep;
    return doSleep;
}

bool b2d::getSleepState()
{
    return doSleep;
}


} // namespace sf
