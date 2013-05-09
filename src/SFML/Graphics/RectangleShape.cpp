////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
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
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>


namespace sf
{

////////////////////////////////////////////////////////////
RectangleShape::RectangleShape(const Vector2f& size)
{
    setSize(size);
}


////////////////////////////////////////////////////////////
void RectangleShape::setSize(const Vector2f& size)
{
    m_size = size;
    coordinates[0] = Vector2f(0, 0);
    coordinates[1] = Vector2f(m_size.x, 0);
    coordinates[2] = Vector2f(m_size.x, m_size.y);
    coordinates[3] = Vector2f(0, m_size.y);
    update();
}


////////////////////////////////////////////////////////////
void RectangleShape::line(const Vector2f& p1, const Vector2f& p2, unsigned int thick)
{
    int thickness = thick;

    if(thickness == 0)
        thickness = 1;

    if(p1 == p2)//pixel
    {
        setSize(Vector2f(thickness, thickness));
        setPosition(p1.x-(thickness/2), p1.y-(thickness/2));
    }
    else//line
    {

        float dist = sqrt( pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) );
        setSize(Vector2f(thickness, dist));



        if(p1.x == p2.x)//vertical line
        {
            if(p1.y < p2.y)
                setPosition(p1.x, p1.y);
            else
                setPosition(p2.x, p2.y);
        }
        else if(p1.y == p2.y)//horizontal line
        {
            setRotation(-90.f);
            if(p1.x < p2.x)
                setPosition(p1.x, p1.y);
            else
                setPosition(p2.x, p2.y);
        }
        else if(p1.x < p2.x)
        {
            float deltaX = p2.x - p1.x;
            float deltaY = p2.y - p1.y;
            float angleInDegrees = atan2(deltaX, deltaY) * 57.295779513082320876798154814105170L;
            setRotation(-angleInDegrees);
            setPosition(p1.x, p1.y);
        }
        else if(p1.x > p2.x)
        {
            float deltaX = p1.x - p2.x;
            float deltaY = p1.y - p2.y;
            float angleInDegrees = atan2(deltaX, deltaY) * 57.295779513082320876798154814105170L;
            setRotation(-angleInDegrees);
            setPosition(p2.x, p2.y);
        }
    }


}


////////////////////////////////////////////////////////////
const Vector2f& RectangleShape::getSize() const
{
    return m_size;
}


////////////////////////////////////////////////////////////
unsigned int RectangleShape::getPointCount() const
{
    return 4;
}


////////////////////////////////////////////////////////////
Vector2f RectangleShape::getPoint(unsigned int index) const
{
    switch (index)
    {
        default:
        case 0: return coordinates[index];
        case 1: return coordinates[index];
        case 2: return coordinates[index];
        case 3: return coordinates[index];
    }

}

} // namespace sf
