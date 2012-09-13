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
    numberOfFrames = 1;
    unsigned char* output;


    int	i, j, Size, Row, Col, Width, Height, ExtCode, Count;
    GifRecordType RecordType;
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
        //allocate SHeight number of row arrays
        if ((ScreenBuffer = (GifRowType *) malloc(GifFile->SHeight * sizeof(GifRowType))) == NULL)
            exit(1);

        //determin size of row
        Size = GifFile->SWidth * sizeof(GifPixelType);

        //allocate for row
        if ((ScreenBuffer[0] = (GifRowType) malloc(Size)) == NULL)
            exit(1);

        //set to black
        for (i = 0; i < GifFile->SWidth; i++)
            ScreenBuffer[0][i] = GifFile->SBackGroundColor;

        // Allocate the other rows, and set their color to background too
        for (i = 1; i < GifFile->SHeight; i++)
        {
            if ((ScreenBuffer[i] = (GifRowType) malloc(Size)) == NULL)
                exit(1);

            memcpy(ScreenBuffer[i], ScreenBuffer[0], Size);
        }









        /* Scan the content of the GIF file and load the image(s) in: */
        do
        {
            if (DGifGetRecordType(GifFile, &RecordType) == GIF_ERROR)
            {
                exit(3);
            }
            switch (RecordType)
            {
                case IMAGE_DESC_RECORD_TYPE:
                    if (DGifGetImageDesc(GifFile) == GIF_ERROR)
                    {
                        exit(3);
                    }
                    Row = GifFile->Image.Top; /* Image Position relative to Screen. */
                    Col = GifFile->Image.Left;
                    Width = GifFile->Image.Width;
                    Height = GifFile->Image.Height;
                    if (GifFile->Image.Left + GifFile->Image.Width > GifFile->SWidth || GifFile->Image.Top + GifFile->Image.Height > GifFile->SHeight)
                    {
                        exit(3);
                    }
                    if (GifFile->Image.Interlace)
                    {
                        /* Need to perform 4 passes on the images: */
                        for (Count = i = 0; i < 4; i++)
                            for (j = Row + InterlacedOffset[i]; j < Row + Height; j += InterlacedJumps[i])
                            {
                                if (DGifGetLine(GifFile, &ScreenBuffer[j][Col], Width) == GIF_ERROR)
                                {
                                    exit(3);
                                }
                            }
                    }
                    else
                    {
                        for (i = 0; i < Height; i++)
                        {
                            if (DGifGetLine(GifFile, &ScreenBuffer[Row++][Col],Width) == GIF_ERROR)
                            {
                                exit(3);
                            }
                        }
                    }
                    break;
                case EXTENSION_RECORD_TYPE:
                    /* Skip any extension blocks in file: */
                    if (DGifGetExtension(GifFile, &ExtCode, &Extension) == GIF_ERROR)
                    {
                        exit(3);
                    }
                    while (Extension != NULL)
                    {
                        if (DGifGetExtensionNext(GifFile, &Extension) == GIF_ERROR)
                        {
                            exit(3);
                        }
                    }
                    break;
                case TERMINATE_RECORD_TYPE:
                    break;
                default:		    /* Should be trapped by DGifGetRecordType. */
                    break;
            }//end of switch
        } while (RecordType != TERMINATE_RECORD_TYPE);








        //output data to char stream
        width = GifFile->SWidth;
        height = GifFile->SHeight;
        if ((output = (unsigned char *) malloc(width * height * numberOfFrames * 3)) == NULL)
            exit(4);

        ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap : GifFile->SColorMap);
        if (ColorMap == NULL)
        {
            exit(4);
        }

        for (i = 0; i < height; i++)
        {
            GifRow = ScreenBuffer[i];
            for (j = 0; j < width; j++)
            {
                ColorMapEntry = &ColorMap->Colors[GifRow[j]];
                *output++ = ColorMapEntry->Red;
                *output++ = ColorMapEntry->Green;
                *output++ = ColorMapEntry->Blue;
            }
        }








        //close file and clean up
        if (DGifCloseFile(GifFile) == GIF_ERROR)
            exit(2);

        (void)free(ScreenBuffer);

        return output;
    }



    return 0;
}




} // namespace sf
