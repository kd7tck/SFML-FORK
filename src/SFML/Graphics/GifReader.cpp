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
    unsigned char* op;
    GifFileType *GifFile;
    GifColorType *ColorMapEntry;
    ColorMapObject *ColorMap;
    int Error;



    if ((GifFile = DGifOpenFileName(filename.c_str(), &Error)) != NULL)
    {
        if(DGifSlurp(GifFile) == GIF_ERROR)
            exit(1);

        numberOfFrames = GifFile->ImageCount;
        width = GifFile->Image.Width;
        height = GifFile->Image.Height;

        if ((output = (unsigned char *) malloc(width * height * numberOfFrames * 3)) == NULL)
            exit(4);

        op = output;

        ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap : GifFile->SColorMap);
        if (ColorMap == NULL)
        {
            exit(4);
        }

        for(int x=0; x < width*height*numberOfFrames; x++)
        {
            ColorMapEntry = &ColorMap->Colors[GifFile->SavedImages->RasterBits[x]];
            *op++ = ColorMapEntry->Red;
            *op++ = ColorMapEntry->Green;
            *op++ = ColorMapEntry->Blue;
        }


        if (DGifCloseFile(GifFile) == GIF_ERROR)
            exit(2);

        return output;
    }



    return 0;
}





unsigned char* GifReader::GetImageByIndex(std::string filename, int& framewidth, int& frameheight, int frameNumber)
{
    int position;//frame number, zero based
    int nf;//returns the number of frames in gif
    unsigned char* out = Gif2RGB(filename.c_str(),framewidth,frameheight,nf);
    unsigned char* outp = out;
    unsigned char* out2;//the pixel array for chosen frame number
    unsigned char* out2p;



    position = frameNumber % nf;


    outp+=position*framewidth*frameheight*3;



    if ((out2 = (unsigned char *) malloc(framewidth * frameheight * 3)) == NULL)
        exit(4);

    out2p = out2;

    for(int y = 0; y < framewidth*frameheight*3; y++)
        *out2p++ = *outp++;



    free(out);

    return out2;
}




void GifReader::GetImageByIndex(Image& i, int frameNumber, std::string filename)
{
    int width, height;
    int position;//frame number, zero based
    int nf;//returns the number of frames in gif
    unsigned char* out = Gif2RGB(filename.c_str(), width, height, nf);
    unsigned char* outp = out;
    sf::Color c;

    sf::Vector2u s = i.getSize();
    if(s.x != width || s.y != height)
        i.create(width, height, sf::Color::Black);

    position = frameNumber % nf;

    outp+=position*width*height*3;

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
        {
            c.r = *outp++;
            c.g = *outp++;
            c.b = *outp++;
            i.setPixel(x,y,c);
        }

    free(out);
}




} // namespace sf
