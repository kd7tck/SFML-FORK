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

#ifndef SFML_B2D_HPP
#define SFML_B2D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Export.hpp"
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <cmath>





namespace sf
{

////////////////////////////////////////////////////////////
/// \brief A Generic body definition.
///
////////////////////////////////////////////////////////////
class b2dGenericBodyDefinition : public b2BodyDef
{
    ;
};



////////////////////////////////////////////////////////////
/// \brief A generic AABB Querry callback.
///
////////////////////////////////////////////////////////////
class b2dGenericQueryCallback : public b2QueryCallback
{
public:
    std::vector<b2Body*> foundBodies;
    bool ReportFixture(b2Fixture* fixture)
    {
        foundBodies.push_back( fixture->GetBody() );
        return true;//keep going to find all fixtures in the query area
    }
};



////////////////////////////////////////////////////////////
/// \brief The BOX2D wrapper class.
///
////////////////////////////////////////////////////////////
class SFML_BOX2D_API b2d
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    b2d();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~b2d();

    ////////////////////////////////////////////////////////////
    /// \brief toggle sleep, if true then b2d will process sleeping objects
    ///
    /// \return bool current sleep state
    ///
    ////////////////////////////////////////////////////////////
    bool toggleSleepState();

    ////////////////////////////////////////////////////////////
    /// \brief get current sleep state
    ///
    /// \return bool current sleep state
    ///
    ////////////////////////////////////////////////////////////
    bool getSleepState();

    ////////////////////////////////////////////////////////////
    /// \brief set the float scale
    ///
    /// \param float Scale, number of pixels per meter
    ///
    ////////////////////////////////////////////////////////////
    void setScale(float Scale);

    ////////////////////////////////////////////////////////////
    /// \brief get current scale
    ///
    /// \return float current Scale
    ///
    ////////////////////////////////////////////////////////////
    float getScale();

    ////////////////////////////////////////////////////////////
    /// \brief set the float time step
    ///
    /// \param float step
    ///
    ////////////////////////////////////////////////////////////
    void setTimeStep(float step);

    ////////////////////////////////////////////////////////////
    /// \brief get current time step
    ///
    /// \return float step
    ///
    ////////////////////////////////////////////////////////////
    float getTimeStep();

    ////////////////////////////////////////////////////////////
    /// \brief set the number of iterations
    ///
    /// \param int number of iterations
    ///
    ////////////////////////////////////////////////////////////
    void setIterations(int it);

    ////////////////////////////////////////////////////////////
    /// \brief get the number of iterations
    ///
    /// \return int iterations
    ///
    ////////////////////////////////////////////////////////////
    int getIterations();

    ////////////////////////////////////////////////////////////
    /// \brief set the gravity vector
    ///
    /// \param sf::Vector2f new gravity vector
    ///
    ////////////////////////////////////////////////////////////
    void setGravity(sf::Vector2f grav);

    ////////////////////////////////////////////////////////////
    /// \brief get the gravity vector
    ///
    /// \return sf::Vector2f gravity vector
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f getGravity();

    ////////////////////////////////////////////////////////////
    /// \brief resize world based on scale
    ///
    ////////////////////////////////////////////////////////////
    void resizeWorld();

    ////////////////////////////////////////////////////////////
    /// \brief Query for any fixtures intersecting worldAABB
    /// Uses Generic Query call back class named gcallback, located inside this class
    /// Uses default worldAABB
    ///
    ////////////////////////////////////////////////////////////
    void queryAABB();

    ////////////////////////////////////////////////////////////
    /// \brief Query for any fixtures intersecting worldAABB
    /// Uses default worldAABB
    ///
    /// \param b2QueryCallback* callback
    ///
    ////////////////////////////////////////////////////////////
    void queryAABB(b2QueryCallback* callback);

    ////////////////////////////////////////////////////////////
    /// \brief Query for any fixtures intersecting
    /// Uses outside worldAABB
    ///
    /// \param b2QueryCallback* callback
    ///
    /// \param b2AABB& aabb box
    ///
    ////////////////////////////////////////////////////////////
    void queryAABB(b2QueryCallback* callback, const b2AABB& aabb);

    ////////////////////////////////////////////////////////////
    /// \brief set the x and y size of the box2d world
    ///
    /// \param vector2i size
    ///
    ////////////////////////////////////////////////////////////
    void setWorldSize(const sf::Vector2i size);

    ////////////////////////////////////////////////////////////
    /// \brief get the x and y size of the box2d world
    ///
    /// \return vector2i size
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2i getWorldSize();

    ////////////////////////////////////////////////////////////
    /// \brief create a new body from a generic body definition
    ///
    /// \param b2BodyDef* bodyDefinition
    ///
    /// \return index of new body, save this for later deletion, returns -1 if error
    ///
    ////////////////////////////////////////////////////////////
    int createBody(const b2dGenericBodyDefinition* def);

    ////////////////////////////////////////////////////////////
    /// \brief destroy body from worldBodies Vector List
    ///
    /// \param int body index
    ///
    ////////////////////////////////////////////////////////////
    void destroyBody(const int index);

    ////////////////////////////////////////////////////////////
    /// \brief destroy body from worldBodies Vector List
    ///
    /// \param int body index
    /// \param int b2Shape*
    /// \param float friction
    /// \param float density
    ///
    ////////////////////////////////////////////////////////////
    void generateFixtureForBodyIndex(const int index, b2Shape* shape, const float friction, const float density);

    ////////////////////////////////////////////////////////////
    /// \brief generate generic polygon shape
    /// \return b2PolygonShape*
    ///
    ////////////////////////////////////////////////////////////
    b2PolygonShape* generatePolygonShape(const float hx, const float hy);


protected :
    bool doSleep;//process sleeping objects
    int iterations;
    float scale;//number of pixels per meter
    float timeStep;
    int worldHeight;
    int worldWidth;
    b2AABB worldAABB;//query Box
    b2Vec2 gravity;
    b2World* world;
    b2dGenericQueryCallback gcallback;

    std::vector <b2Body*> worldBodies;
    std::vector <b2Body*>::iterator worldBodiesIT;
};

} // namespace sf


#endif // SFML_B2D_HPP

////////////////////////////////////////////////////////////
/// \class sf::b2dGenericBodyDefinition
/// \ingroup box2d
///
/// sf::b2dGenericBodyDefinition is used for creating new world bodies
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::b2dGenericBodyDefinition
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \class sf::b2dGenericQueryCallback
/// \ingroup box2d
///
/// sf::b2dGenericQueryCallback is used to act as a template for all AABB Query callbacks
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::b2dGenericQueryCallback
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \class sf::b2d
/// \ingroup box2d
///
/// sf::b2d is used to simulate physics on 2d geometry
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::b2d
///
////////////////////////////////////////////////////////////
