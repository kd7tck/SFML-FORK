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
#include "giflib/gif_lib.h"

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

GifReader::GifReader()
{
    ;
}

GifReader::~GifReader()
{
    ;
}

unsigned char* GifReader::Gif2RGB(std::string filename, int& width, int& height, int& numberOfFrames)
{
    unsigned char* output;
    GifByteType *Extension;
    GifRowType *ScreenBuffer;
    GifFileType *GifFile;
    GifColorType *ColorMapEntry;

    int
        InterlacedOffset[] = { 0, 4, 2, 1 }, /* The way Interlaced image should. */
        InterlacedJumps[] = { 8, 8, 4, 2 };    /* be read - offsets and jumps... */

    int ImageNum = 0;
    ColorMapObject *ColorMap;
    int Error;
    GifRowType GifRow;



    if ((GifFile = DGifOpenFileName(filename.c_str(), &Error)) != NULL)
    {
        if(DGifSlurp(GifFile) == GIF_ERROR)
            exit(1);

        numberOfFrames = GifFile->ImageCount;
        width = GifFile->Image.Width;
        height = GifFile->Image.Height;

        if ((output = (unsigned char *) malloc(width * height * numberOfFrames * 3)) == NULL)
            exit(4);

        ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap : GifFile->SColorMap);
        if (ColorMap == NULL)
        {
            exit(4);
        }

        for(int x=0; x < GifFile->SWidth * GifFile->SHeight; x++)
        {
            ColorMapEntry = &ColorMap->Colors[GifFile->SavedImages->RasterBits[x]];
            *output++ = ColorMapEntry->Red;
            *output++ = ColorMapEntry->Green;
            *output++ = ColorMapEntry->Blue;
        }


        if (DGifCloseFile(GifFile) == GIF_ERROR)
            exit(2);

        return output;
    }



    return 0;
}




} // namespace sf
