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

#ifndef SFML_GIFREADER_HPP
#define SFML_GIFREADER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Export.hpp"






namespace sf
{

class Image;

////////////////////////////////////////////////////////////
/// \brief The GifReader class, designed to read animated gif files.
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API GifReader : public Image
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    GifReader();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~GifReader();

    ////////////////////////////////////////////////////////////
    /// \brief convert entire gif, including animations into char array, make sure to free array when done
    ///
    /// \param int width of frame
    ///
    /// \param int height of frame
    ///
    /// \param int number of frames in animation
    ///
    /// \param int** frame disposal mode, 0=unspecified, 1=do_not_dispose, 2=clear_to_color, 3=restore_previous_content.
    /// passed by reference, returns pointer to integer array of size numberOfFrames, make sure to free when done with it.
    ///
    /// \return unsigned char* the pointer to the pixel array
    ///
    ////////////////////////////////////////////////////////////
    unsigned char* Gif2RGB(const std::string filename, int& framewidth, int& frameheight, int& numberOfFrames, int** frameDisposal);

    ////////////////////////////////////////////////////////////
    /// \brief convert gif frame number into array of pixels, make sure to free array when done
    ///
    /// \param int width of frame
    ///
    /// \param int height of frame
    ///
    /// \param int the frame to retrieve
    ///
    /// \param int** frame disposal mode, 0=unspecified, 1=do_not_dispose, 2=clear_to_color, 3=restore_previous_content
    ///
    /// \return unsigned char* the pointer to the pixel array
    ///
    ////////////////////////////////////////////////////////////
    unsigned char* GetImageByIndex(const std::string filename, int& framewidth, int& frameheight, int& frameNumber, int** frameDisposal);

    ////////////////////////////////////////////////////////////
    /// \brief load gif frame number into Image passed by reference
    ///
    /// \param Image file to load frame into
    ///
    /// \param int the frame to retrieve
    ///
    /// \param string filename
    ///
    /// \return int frame disposal mode, 0=unspecified, 1=do_not_dispose, 2=clear_to_color, 3=restore_previous_content
    ///
    ////////////////////////////////////////////////////////////
    int GetImageByIndex(Image& image, int& frameNumber, const std::string filename);

    ////////////////////////////////////////////////////////////
    /// \brief Load the animated image from a file on disk into this object, sf::GifReader is a child of sf::Image.
    ///
    /// The supported image formats are animated gif.
    /// If this function fails, the image is left unchanged.
    /// This image if fully draw onto a window, will be a series of frames from top to bottom.
    ///
    /// Example:
    /// \code
    ///    sf::GifReader gr;
    ///    sf::Texture t;
    ///    sf::Time sleeptime = sf::seconds(0.01f);
    ///    int counter=0;
    ///    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    ///    gr.loadGifAnimationFromFile("a.gif");
    ///    t.loadFromImage(gr);
    ///
    ///    // run the program as long as the window is open
    ///    while (window.isOpen())
    ///    {
    ///        // check all the window's events that were triggered since the last iteration of the loop
    ///        sf::Event event;
    ///        while (window.pollEvent(event))
    ///        {
    ///            // "close requested" event: we close the window
    ///            if (event.type == sf::Event::Closed)
    ///                window.close();
    ///        }
    ///
    ///        sf::Sprite s(t);
    ///        sf::Rect<int> r(0,(counter * gr.getFrameSize().y),gr.getFrameSize().x,gr.getFrameSize().y);
    ///        s.setTextureRect(r);
    ///        window.draw(s);
    ///        window.display();
    ///        sf::sleep(sleeptime);
    ///        counter++;
    ///        counter=counter % gr.getNumberFrames();
    ///    }
    /// \endcode
    ///
    /// \param filename Path of the image file to load
    ///
    /// \return True if loading was successful
    ///
    ////////////////////////////////////////////////////////////
    bool loadGifAnimationFromFile(const std::string& filename);

    ////////////////////////////////////////////////////////////
    /// \brief get width and height of frame
    ///
    /// \return Vector2<int>
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2<int> getFrameSize();

    ////////////////////////////////////////////////////////////
    /// \brief get number of frames
    ///
    /// \return int
    ///
    ////////////////////////////////////////////////////////////
    int getNumberFrames();

    ////////////////////////////////////////////////////////////
    /// \brief get array of frame disposal modes, these are equal to number of frames
    ///
    /// \return int array of frame disposal modes, 0=unspecified, 1=do_not_dispose, 2=clear_to_color, 3=restore_previous_content, it's size is equal to number of frames
    ///
    ////////////////////////////////////////////////////////////
    int* getFrameDisposalModes();



protected :
    int fwidth, fheight, totalFrames;

    //int** frame disposal mode, 0=unspecified, 1=do_not_dispose, 2=clear_to_color, 3=restore_previous_content, it's size is equal to number of frames
    int* fdisposal;

};

} // namespace sf


#endif // SFML_GIFREADER_HPP


////////////////////////////////////////////////////////////
/// \class sf::GifReader
/// \ingroup graphics
///
/// sf::GifReader contains static functions for reading from animated gif files
///
/// Example:
/// \code
///    sf::GifReader gr;
///    sf::Image i;
///    sf::Texture t;
///    sf::Time sleeptime = sf::seconds(0.01f);
///    int counter=0;
///
///    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
///
///    // run the program as long as the window is open
///    while (window.isOpen())
///    {
///        // check all the window's events that were triggered since the last iteration of the loop
///        sf::Event event;
///        while (window.pollEvent(event))
///        {
///            // "close requested" event: we close the window
///            if (event.type == sf::Event::Closed)
///                window.close();
///        }
///
///        if(gr.GetImageByIndex(i,counter,"a.gif") == 2)
///            window.clear();
///
///        t.loadFromImage(i);
///        sf::Sprite s(t);
///
///        window.draw(s);
///        window.display();
///
///        sf::sleep(sleeptime);
///        counter++;
///    }
/// \endcode
///
/// \see sf::GifReader
///
////////////////////////////////////////////////////////////
