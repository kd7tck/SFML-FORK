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
    worldHeight = 600;
    worldWidth = 800;
    doSleep = true;
    velocityIterations = 8;
    positionIterations = 3;
    scale = 30.f;
    timeStep = 1/60;
    gravity.Set(0, -9.8f);
    resizeWorld();
    world = new b2World(gravity);
    world->SetAllowSleeping(doSleep);
}


b2d::~b2d()
{
    delete world;
}



bool b2d::toggleSleepState()
{
    doSleep = !doSleep;
    world->SetAllowSleeping(doSleep);
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



void b2d::setVelocityIterations(int it)
{
    velocityIterations = it;
}



int b2d::getVelocityIterations()
{
    return velocityIterations;
}


void b2d::setPositionIterations(int it)
{
    positionIterations = it;
}



int b2d::getPositionIterations()
{
    return positionIterations;
}



void b2d::setGravity(sf::Vector2f grav)
{
    gravity.x = grav.x;
    gravity.y = grav.y;
    world->SetGravity(gravity);
}



sf::Vector2f b2d::getGravity()
{
    return sf::Vector2f(gravity.x, gravity.y);
}



void b2d::resizeWorld()
{
    //upper left window corner
    worldAABB.lowerBound.Set(-1000/scale, -1000/scale);

    //lower right corner of window
    worldAABB.upperBound.Set(1000/scale, 1000/scale);
}




void b2d::queryAABB(b2QueryCallback* callback)
{
    world->QueryAABB(callback, worldAABB);
}




void b2d::queryAABB(b2QueryCallback* callback, const b2AABB& aabb)
{
    world->QueryAABB(callback, aabb);
}




void b2d::queryAABB()
{
    world->QueryAABB(&gcallback, worldAABB);
}





void b2d::setWorldSize(const sf::Vector2i size)
{
    worldHeight = size.y;
    worldWidth = size.x;
}





sf::Vector2i b2d::getWorldSize()
{
    return sf::Vector2i(worldWidth, worldHeight);
}





int b2d::createBody(const b2BodyDef* def)
{
    b2Body* ptr = 0;
    ptr = world->CreateBody(def);
    if(!ptr)
        return -1;

    worldBodies.push_back(ptr);
    return worldBodies.size()-1;
}




void b2d::destroyBody(const int index)
{
    b2Body* bod = 0;
    int x;

    if(worldBodies.size() > 0)
    {
        for( worldBodiesIT = worldBodies.begin(), x=0; worldBodiesIT != worldBodies.end(); worldBodiesIT++, x++)
        {
            if(x==index)
            {
                bod = (*worldBodiesIT);
                world->DestroyBody(bod);
                worldBodies.erase(worldBodies.begin() + x);
            }
        }
    }


}


bool b2d::generateFixtureForBodyIndex(const int bodyIndex, b2Shape* shape, const float friction=1, const float density=1, const float restitution=1)
{
    int x;
    b2FixtureDef* FixtureDef = new b2FixtureDef();
    FixtureDef->density = density;
    FixtureDef->friction = friction;
    FixtureDef->shape = shape;
    FixtureDef->restitution = restitution;


    if(worldBodies.size() > 0){
        for( worldBodiesIT = worldBodies.begin(), x=0; worldBodiesIT != worldBodies.end(); worldBodiesIT++, x++){
            if(x==bodyIndex)
            {
                (*worldBodiesIT)->CreateFixture(FixtureDef);
                return true;
            }
        }
    }

    delete (FixtureDef);
    return false;
}



b2PolygonShape* b2d::generatePolygonShape(const float hx, const float hy)
{
    b2PolygonShape* temp = new b2PolygonShape();
    temp->SetAsBox(hx,hx);
    return temp;
}


b2PolygonShape* b2d::generatePolygonShape(const b2Vec2 *vertices, int vertexCount)
{
    b2PolygonShape* temp = new b2PolygonShape();
    temp->Set(vertices,vertexCount);
    return temp;
}


b2BodyDef* b2d::generateDynamicBodyDefinition(const float x, const float y)
{
    b2BodyDef* temp = new b2BodyDef();
    temp->type = b2_dynamicBody;
    temp->position.x = x;
    temp->position.y = y;
    return temp;
}


b2BodyDef* b2d::generateStaticBodyDefinition(const float x, const float y)
{
    b2BodyDef* temp = new b2BodyDef();
    temp->type = b2_staticBody;
    temp->position.x = x;
    temp->position.y = y;
    return temp;
}


void b2d::worldStep()
{
    world->Step(timeStep,velocityIterations,positionIterations);
}


} // namespace sf