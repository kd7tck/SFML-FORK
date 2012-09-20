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
    gravity = new b2Vec2(0,9.8f);
    worldAABB = new b2AABB;
}


b2d::~b2d()
{
    delete gravity;
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

void b2d::setScale(float Scale)
{
    scale = Scale;
}

float b2d::getScale()
{
    return scale;
}

void b2d::setTimeStep(float step)
{
    timeStep = step;
}

float b2d::getTimeStep()
{
    return timeStep;
}

void b2d::setIterations(int it)
{
    iterations = it;
}

int b2d::getIterations()
{
    return iterations;
}

void b2d::setGravity(sf::Vector2f grav)
{
    gravity->x = grav.x;
    gravity->y = grav.y;
}

sf::Vector2f b2d::getGravity()
{
    return sf::Vector2f(gravity->x, gravity->y);
}


} // namespace sf
