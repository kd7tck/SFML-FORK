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
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/ImageLoader.hpp>
#include <SFML/System/Err.hpp>
#include <algorithm>
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

SlideShow::SlideShow()
{
    ;
}



SlideShow::~SlideShow()
{
    deleteSlides();
}


void SlideShow::deleteSlides()
{
    if(slides.size() > 0)
    {
        for ( it = slides.begin(); it != slides.end() ; it++ )
        {
                delete(*it);
        }
        slides.clear();
    }
}



bool SlideShow::setCurrentSlide(int index)
{
    int count = 0;

    if(slides.size() > index)
    {
        for ( it = slides.begin(); it != slides.end() ; it++ )
        {
            if(count == index)
            {
                copy((**it),0,0);
                break;
            }
            else
            {
                count++;
            }
        }
    }
}


////////////////////////////////////////////////////////////
bool SlideShow::loadSlideFromFile(const std::string& filename)
{
    sf::Image* i = new sf::Image();
    bool r = i->loadFromFile(filename);
    slides.push_back(i);
    return r;
}


////////////////////////////////////////////////////////////
bool SlideShow::loadSlideFromMemory(const void* data, std::size_t size)
{
    sf::Image* i = new sf::Image();
    bool r = i->loadFromMemory(data,size);
    slides.push_back(i);
    return r;
}


////////////////////////////////////////////////////////////
bool SlideShow::loadSlideFromStream(InputStream& stream)
{
    sf::Image* i = new sf::Image();
    bool r = i->loadFromStream(stream);
    slides.push_back(i);
    return r;
}





} // namespace sf
