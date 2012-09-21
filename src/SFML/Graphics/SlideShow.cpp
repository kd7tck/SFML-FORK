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



SlideShow::~SlideShow()
{
    ;
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



bool SlideShow::setCurrentSlide(unsigned int index)
{
    int count = 0;

    if(slides.size() > index)
    {
        for ( it = slides.begin(); it != slides.end(); it++ )
        {
            if(count == index)
            {
                sf::Vector2u vs = (*it)->getSize();
                create(vs.x, vs.y, sf::Color::Black);
                for(int y = 0; y < vs.y; y++)
                {
                    for(int x = 0; x < vs.x; x++)
                    {
                        setPixel(x,y,(*it)->getPixel(x,y));
                    }
                }
                break;
            }
            else
            {
                count++;
            }
        }
    }

    if(count == index)
        return true;

    return false;
}




int SlideShow::getSlideCount()
{
    return slides.size();
}




////////////////////////////////////////////////////////////
bool SlideShow::loadSlideFromFile(const std::string& filename)
{
    sf::Image* i = new sf::Image;
    bool r = i->loadFromFile(filename);
    slides.push_back(i);
    return r;
}


////////////////////////////////////////////////////////////
bool SlideShow::loadSlideFromMemory(const void* data, std::size_t size)
{
    sf::Image* i = new sf::Image;
    bool r = i->loadFromMemory(data,size);
    slides.push_back(i);
    return r;
}


////////////////////////////////////////////////////////////
bool SlideShow::loadSlideFromStream(InputStream& stream)
{
    sf::Image* i = new sf::Image;
    bool r = i->loadFromStream(stream);
    slides.push_back(i);
    return r;
}


bool SlideShow::loadSlideFromImage(sf::Image* image)
{
    int c = slides.size();
    slides.push_back(image);
    if(slides.size() > c)
        return true;

    return false;
}


bool SlideShow::loadSlidesFromGifFile(const std::string& filename)
{
    if(sdisposal){
        free(sdisposal);
        sdisposal = 0;
    }

    if(getSlideCount())
        deleteSlides();

    int tmp[1000];//sdisposal buffer
    sf::GifReader gr;
    int x=0;//return value from GetImageByIndex
    int counter=0;//current frame index


    do
    {
        sf::Image* i = new sf::Image;
        tmp[counter] = gr.GetImageByIndex(*i, x, filename);

        if(counter && !x)//only if x==0 and counter!=0
        {
            delete(i);
            tmp[counter] = -1;
            break;
        }

        loadSlideFromImage(i);

        x++;
        counter++;
    }while(true);


    if ((sdisposal = (int *) malloc((counter-1) * 4)) == NULL)
        exit(4);

    for(x=0; x<counter-1; x++)
    {
        sdisposal[x] = tmp[x];
    }

    return true;
}





} // namespace sf
