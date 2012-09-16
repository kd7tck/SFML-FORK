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

#ifndef SFML_SLIDESHOW_HPP
#define SFML_SLIDESHOW_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Export.hpp"
#include <iostream>
#include <string>
#include <map>






namespace sf
{

class Image;

////////////////////////////////////////////////////////////
/// \brief The SlideShow class, designed to display series of images.
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API SlideShow : public Image
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    SlideShow();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~SlideShow();

    ////////////////////////////////////////////////////////////
    /// \brief get array of frame disposal modes, these are equal to number of frames
    ///
    /// \param int index of image
    ///
    /// \return int array of frame disposal modes, 0=unspecified, 1=do_not_dispose, 2=clear_to_color, 3=restore_previous_content, it's size is equal to number of frames
    ///
    ////////////////////////////////////////////////////////////
    bool setCurrentSlide(int index);



protected :
    int swidth, sheight, totalSlides;

    //int** slide disposal mode, 0=unspecified, 1=do_not_dispose, 2=clear_to_color, 3=restore_previous_content, it's size is equal to number of slides
    int* sdisposal;

    std::vector <Image*> slides;
    std::vector <Image*>::iterator it;

};

} // namespace sf


#endif // SFML_SLIDESHOW_HPP


////////////////////////////////////////////////////////////
/// \class sf::SlideShow
/// \ingroup graphics
///
/// sf::SlideShow is used to display a series of discrete images one after the other
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::SlideShow
///
////////////////////////////////////////////////////////////
