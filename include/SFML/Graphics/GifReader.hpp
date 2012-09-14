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

////////////////////////////////////////////////////////////
/// \brief The GifReader class.
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API GifReader
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
    /// \brief convert entire gif, including animations into char array, free array when done with it
    ///
    /// \param int width of frame
    ///
    /// \param int height of frame
    ///
    /// \param int number of frames in animation
    ///
    /// \return unsigned char* the pointer to the pixel array
    ///
    ////////////////////////////////////////////////////////////
    unsigned char* Gif2RGB(std::string filename, int& framewidth, int& frameheight, int& numberOfFrames);

    ////////////////////////////////////////////////////////////
    /// \brief convert gif frame number into array of pixels, free array when done
    ///
    /// \param int width of frame
    ///
    /// \param int height of frame
    ///
    /// \param int the frame to retrieve
    ///
    /// \return unsigned char* the pointer to the pixel array
    ///
    ////////////////////////////////////////////////////////////
    unsigned char* GetImageByIndex(std::string filename, int& framewidth, int& frameheight, int frameNumber);



protected :

};

} // namespace sf


#endif // SFML_GIFREADER_HPP


////////////////////////////////////////////////////////////
/// \class sf::GifReader
/// \ingroup graphics
///
/// sf::GifReader contains static functions for reading from gif files
///
/// Example:
/// \code
///
/// \endcode
///
/// \see sf::GifReader
///
////////////////////////////////////////////////////////////
