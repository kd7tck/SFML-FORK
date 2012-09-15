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

        if ((output = (unsigned char *) malloc(width * height * numberOfFrames * 4)) == NULL)
            exit(4);

        op = output;

        ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap : GifFile->SColorMap);
        if (ColorMap == NULL)
        {
            exit(4);
        }

        for(int y=0; y < numberOfFrames; y++)
            for(int x=0; x < width*height; x++)
            {
                ColorMapEntry = &ColorMap->Colors[GifFile->SavedImages[y].RasterBits[x]];
                *op++ = 255;//alpha
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





unsigned char* GifReader::GetImageByIndex(std::string filename, int& framewidth, int& frameheight, int& frameNumber)
{
    int width, height;
    int nf;//returns the number of frames in gif
    sf::Color c;
    unsigned char* op;
    unsigned char* out;
    unsigned char* outp;
    GifFileType *GifFile;
    GifColorType *ColorMapEntry;
    ColorMapObject *ColorMap;
    int Error;
    SavedImage* sv;



    if ((GifFile = DGifOpenFileName(filename.c_str(), &Error)) != NULL)
    {
        if(DGifSlurp(GifFile) == GIF_ERROR)
            exit(1);

        nf = GifFile->ImageCount;
        width = GifFile->Image.Width;
        height = GifFile->Image.Height;

        if ((out = (unsigned char *) malloc(width * height * 4)) == NULL)
            exit(4);

        outp = out;

        ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap : GifFile->SColorMap);
        if (ColorMap == NULL)
        {
            exit(4);
        }

        frameNumber = frameNumber % nf;
        sv = &GifFile->SavedImages[frameNumber];
        op = sv->RasterBits;

        for(int y = 0; y < height; y++)
            for(int x = 0; x < width; x++)
            {
                ColorMapEntry = &ColorMap->Colors[*op++];
                *outp++ = 255;//alpha
                *outp++ = ColorMapEntry->Red;
                *outp++ = ColorMapEntry->Green;
                *outp++ = ColorMapEntry->Blue;
            }

        if (DGifCloseFile(GifFile) == GIF_ERROR)
            exit(2);

        return out;
    }

    return 0;
}




int GifReader::GetImageByIndex(Image& i, int& frameNumber, std::string filename)
{
    int width, height;
    int nf;//returns the number of frames in gif
    sf::Color c;
    unsigned char* op;
    GifFileType *GifFile;
    GifColorType *ColorMapEntry;
    ColorMapObject *ColorMap;
    int Error;
    SavedImage* sv;
    GraphicsControlBlock GCB;



    if ((GifFile = DGifOpenFileName(filename.c_str(), &Error)) != NULL)
    {
        if(DGifSlurp(GifFile) == GIF_ERROR)
            exit(1);

        nf = GifFile->ImageCount;
        width = GifFile->Image.Width;
        height = GifFile->Image.Height;

        ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap : GifFile->SColorMap);
        if (ColorMap == NULL)
        {
            exit(4);
        }

        sf::Vector2u s = i.getSize();
        if(s.x != width || s.y != height)
        {
            ColorMapEntry = &ColorMap->Colors[GifFile->SBackGroundColor];
            c.r = ColorMapEntry->Red;
            c.g = ColorMapEntry->Green;
            c.b = ColorMapEntry->Blue;
            i.create(width, height, c);
        }

        frameNumber = frameNumber % nf;
        sv = &GifFile->SavedImages[frameNumber];
        op = sv->RasterBits;
        DGifSavedExtensionToGCB(GifFile, frameNumber, &GCB);

        for(int y = 0; y < height; y++)
            for(int x = 0; x < width; x++)
            {
                if(*op == GCB.TransparentColor)
                    c.a = 0;
                else
                    c.a = 255;

                ColorMapEntry = &ColorMap->Colors[*op++];
                c.r = ColorMapEntry->Red;
                c.g = ColorMapEntry->Green;
                c.b = ColorMapEntry->Blue;
                i.setPixel(x,y,c);
            }

        if (DGifCloseFile(GifFile) == GIF_ERROR)
            exit(2);

        return GCB.DisposalMode;
    }

    return 0;
}






} // namespace sf
