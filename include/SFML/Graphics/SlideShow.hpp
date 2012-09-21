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
/// Be very careful with SlideShow class, they are heavy weight objects and take up vast amount of computer memory.
/// SlideShow is also very slow and the image should not be changed more than once every second.
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API SlideShow : public Image
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    SlideShow() : sf::Image()
    {
        sdisposal = 0;
    }

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~SlideShow();

    ////////////////////////////////////////////////////////////
    /// \brief clear out all slides from memory
    ///
    ////////////////////////////////////////////////////////////
    void deleteSlides();

    ////////////////////////////////////////////////////////////
    /// \brief get the number of slides
    ///
    /// \return int number of slides
    ///
    ////////////////////////////////////////////////////////////
    int getSlideCount();

    ////////////////////////////////////////////////////////////
    /// \brief get array of frame disposal modes, these are equal to number of frames
    ///
    /// \param int index of image
    ///
    /// \return int array of frame disposal modes, 0=unspecified, 1=do_not_dispose, 2=clear_to_color, 3=restore_previous_content, it's size is equal to number of frames
    ///
    ////////////////////////////////////////////////////////////
    bool setCurrentSlide(unsigned int index);

    ////////////////////////////////////////////////////////////
    /// \brief Load the image from a file on disk
    ///
    /// The supported image formats are bmp, png, tga, jpg, gif,
    /// psd, hdr and pic. Some format options are not supported,
    /// like progressive jpeg.
    /// If this function fails, the image is left unchanged.
    ///
    /// \param filename Path of the image file to load
    ///
    /// \return True if loading was successful
    ///
    /// \see loadFromMemory, loadFromStream, saveToFile
    ///
    ////////////////////////////////////////////////////////////
    bool loadSlideFromFile(const std::string& filename);

    ////////////////////////////////////////////////////////////
    /// \brief Load the image from a file in memory
    ///
    /// The supported image formats are bmp, png, tga, jpg, gif,
    /// psd, hdr and pic. Some format options are not supported,
    /// like progressive jpeg.
    /// If this function fails, the image is left unchanged.
    ///
    /// \param data Pointer to the file data in memory
    /// \param size Size of the data to load, in bytes
    ///
    /// \return True if loading was successful
    ///
    /// \see loadFromFile, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadSlideFromMemory(const void* data, std::size_t size);

    ////////////////////////////////////////////////////////////
    /// \brief Load the image from a custom stream
    ///
    /// The supported image formats are bmp, png, tga, jpg, gif,
    /// psd, hdr and pic. Some format options are not supported,
    /// like progressive jpeg.
    /// If this function fails, the image is left unchanged.
    ///
    /// \param stream Source stream to read from
    ///
    /// \return True if loading was successful
    ///
    /// \see loadFromFile, loadFromMemory
    ///
    ////////////////////////////////////////////////////////////
    bool loadSlideFromStream(InputStream& stream);

    ////////////////////////////////////////////////////////////
    /// \brief Load the image from a dynamic image pointer
    ///
    ///
    /// \param Image* dynamic image pointer
    ///
    /// \return True if loading was successful
    ///
    ////////////////////////////////////////////////////////////
    bool loadSlideFromImage(sf::Image* image);

    ////////////////////////////////////////////////////////////
    /// \brief Load gif animation file into series of slides
    ///
    ///
    /// \param const std::string& gifFilename
    ///
    /// \return True if loading was successful
    ///
    ////////////////////////////////////////////////////////////
    bool loadSlidesFromGifFile(const std::string& filename);



protected :
    int totalSlides;

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
///    sf::SlideShow s;
///    s.loadSlideFromFile("1.jpg");
///    s.loadSlideFromFile("2.jpg");
///    s.loadSlideFromFile("3.jpg");
///    sf::Texture t;
///    sf::Time sleeptime = sf::seconds(1.0f);
///    int counter=0;
///    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
///
///    // run the program as long as the window is open
///    while (window.isOpen())
///    {
///        if(!s.getSlideCount())
///            window.close();
///
///        // check all the window's events that were triggered since the last iteration of the loop
///        sf::Event event;
///        while (window.pollEvent(event))
///        {
///            // "close requested" event: we close the window
///            if (event.type == sf::Event::Closed)
///                window.close();
///        }
///
///        if(!s.setCurrentSlide(counter))
///            window.close();
///
///        t.loadFromImage(s);
///        sf::Sprite spr(t);
///        window.draw(spr);
///        window.display();
///        sf::sleep(sleeptime);
///        counter++;
///        counter=counter % s.getSlideCount();
///    }
///
///    s.deleteSlides();
///
/// \endcode
///
/// \see sf::SlideShow
///
////////////////////////////////////////////////////////////
