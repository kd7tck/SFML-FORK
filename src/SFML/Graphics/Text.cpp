////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
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
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>


namespace sf
{
////////////////////////////////////////////////////////////
Text::Text() :
m_string       (),
m_font         (NULL),
m_characterSize(30),
m_style        (Regular),
m_color        (255, 255, 255),
m_vertices     (Quads),
m_bounds       ()
{
    m_boundBox.left=0;
    m_boundBox.top=0;
    m_boundBox.height=600;
    m_boundBox.width=800;
    m_numBoundChars=0;
    m_boundMargin=0;
    m_isBounded=false;
}



////////////////////////////////////////////////////////////
Text::Text(const String& string, const Font& font, unsigned int characterSize) :
m_string       (string),
m_font         (&font),
m_characterSize(characterSize),
m_style        (Regular),
m_color        (255, 255, 255),
m_vertices     (Quads),
m_bounds       ()
{
    m_boundBox.left=0;
    m_boundBox.top=0;
    m_boundBox.height=600;
    m_boundBox.width=800;
    m_numBoundChars=0;
    m_boundMargin=0;
    m_isBounded=false;
    updateGeometry();
}



////////////////////////////////////////////////////////////
void Text::setString(const String& string)
{
    m_string = string;
    if(m_isBounded)
        updateGeometryBounding();
    else
    	updateGeometry();
}


////////////////////////////////////////////////////////////
void Text::setBoundingMargin(int margin)
{
	m_boundMargin = margin;
    if(m_isBounded)
        updateGeometryBounding();
    else
    	updateGeometry();
}


////////////////////////////////////////////////////////////
void Text::setBounding(bool bounding)
{
	m_isBounded = bounding;
}


////////////////////////////////////////////////////////////
void Text::setFont(const Font& font)
{
    if (m_font != &font)
    {
        m_font = &font;
        if(m_isBounded)
            updateGeometryBounding();
        else
        	updateGeometry();
    }
}


////////////////////////////////////////////////////////////
void Text::setCharacterSize(unsigned int size)
{
    if (m_characterSize != size)
    {
        m_characterSize = size;
        if(m_isBounded)
            updateGeometryBounding();
        else
            updateGeometry();
    }
}


////////////////////////////////////////////////////////////
void Text::setStyle(Uint32 style)
{
    if (m_style != style)
    {
        m_style = style;
        if(m_isBounded)
            updateGeometryBounding();
        else
            updateGeometry();
    }
}


////////////////////////////////////////////////////////////
void Text::setColor(const Color& color)
{
    if (color != m_color)
    {
        m_color = color;
        for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i)
            m_vertices[i].color = m_color;
    }
}


////////////////////////////////////////////////////////////
void Text::setBoundingBox(const FloatRect rect){
    m_boundBox = rect;
    if(m_isBounded)
        updateGeometryBounding();
}


////////////////////////////////////////////////////////////
const String& Text::getString() const
{
    return m_string;
}


////////////////////////////////////////////////////////////
const Font* Text::getFont() const
{
    return m_font;
}


////////////////////////////////////////////////////////////
unsigned int Text::getCharacterSize() const
{
    return m_characterSize;
}


////////////////////////////////////////////////////////////
unsigned int Text::getNumberBoundedCharacters() const
{
	return m_numBoundChars;
}


////////////////////////////////////////////////////////////
Uint32 Text::getStyle() const
{
    return m_style;
}


////////////////////////////////////////////////////////////
const Color& Text::getColor() const
{
    return m_color;
}


////////////////////////////////////////////////////////////
Vector2f Text::findCharacterPos(std::size_t index) const
{
    // Make sure that we have a valid font
    if (!m_font)
        return Vector2f();

    // Adjust the index if it's out of range
    if (index > m_string.getSize())
        index = m_string.getSize();

    // Precompute the variables needed by the algorithm
    bool  bold   = (m_style & Bold) != 0;
    float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
    float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));

    // Compute the position
    Vector2f position;
    Uint32 prevChar = 0;
    for (std::size_t i = 0; i < index; ++i)
    {
        Uint32 curChar = m_string[i];

        // Apply the kerning offset
        position.x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
        prevChar = curChar;

        // Handle special characters
        switch (curChar)
        {
            case ' ' :  position.x += hspace;                 continue;
            case '\t' : position.x += hspace * 4;             continue;
            case '\n' : position.y += vspace; position.x = 0; continue;
            case '\v' : position.y += vspace * 4;             continue;
        }

        // For regular characters, add the advance offset of the glyph
        position.x += static_cast<float>(m_font->getGlyph(curChar, m_characterSize, bold).advance);
    }

    // Transform the position to global coordinates
    position = getTransform().transformPoint(position);

    return position;
}


////////////////////////////////////////////////////////////
FloatRect Text::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////
FloatRect Text::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


///////////////////////////////////////////////////////////
FloatRect Text::getBoundingBox() const
{
    return m_boundBox;
}


////////////////////////////////////////////////////////////
void Text::draw(RenderTarget& target, RenderStates states) const
{
    if (m_font)
    {
        states.transform *= getTransform();
        states.texture = &m_font->getTexture(m_characterSize);
        target.draw(m_vertices, states);
    }
}


////////////////////////////////////////////////////////////
void Text::updateGeometry()
{
    // Clear the previous geometry
    m_vertices.clear();
    m_bounds = FloatRect();

    // No font: nothing to draw
    if (!m_font)
        return;

    // No text: nothing to draw
    if (m_string.isEmpty())
        return;

    // Compute values related to the text style
    bool  bold               = (m_style & Bold) != 0;
    bool  underlined         = (m_style & Underlined) != 0;
    float italic             = (m_style & Italic) ? 0.208f : 0.f; // 12 degrees
    float underlineOffset    = m_characterSize * 0.1f;
    float underlineThickness = m_characterSize * (bold ? 0.1f : 0.07f);

    // Precompute the variables needed by the algorithm
    float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
    float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));
    float x      = 0.f;
    float y      = static_cast<float>(m_characterSize);

    // Create one quad for each character
    float minX = static_cast<float>(m_characterSize);
    float minY = static_cast<float>(m_characterSize);
    float maxX = 0.f;
    float maxY = 0.f;
    Uint32 prevChar = 0;
    for (std::size_t i = 0; i < m_string.getSize(); ++i)
    {
        Uint32 curChar = m_string[i];

        // Apply the kerning offset
        x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
        prevChar = curChar;

        // If we're using the underlined style and there's a new line, draw a line
        if (underlined && (curChar == L'\n'))
        {
            float top = y + underlineOffset;
            float bottom = top + underlineThickness;

            m_vertices.append(Vertex(Vector2f(0, top),    m_color, Vector2f(1, 1)));
            m_vertices.append(Vertex(Vector2f(x, top),    m_color, Vector2f(1, 1)));
            m_vertices.append(Vertex(Vector2f(x, bottom), m_color, Vector2f(1, 1)));
            m_vertices.append(Vertex(Vector2f(0, bottom), m_color, Vector2f(1, 1)));
        }

        // Handle special characters
        if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n') || (curChar == '\v'))
        {
            // Update the current bounds (min coordinates)
            minX = std::min(minX, x);
            minY = std::min(minY, y);

            switch (curChar)
            {
                case ' ' :  x += hspace;        break;
                case '\t' : x += hspace * 4;    break;
                case '\n' : y += vspace; x = 0; break;
                case '\v' : y += vspace * 4;    break;
            }

            // Update the current bounds (max coordinates)
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);

            // Next glyph, no need to create a quad for whitespace
            continue;
        }

        // Extract the current glyph's description
        const Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, bold);

        int left   = glyph.bounds.left;
        int top    = glyph.bounds.top;
        int right  = glyph.bounds.left + glyph.bounds.width;
        int bottom = glyph.bounds.top  + glyph.bounds.height;

        float u1 = static_cast<float>(glyph.textureRect.left);
        float v1 = static_cast<float>(glyph.textureRect.top);
        float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width);
        float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height);

        // Add a quad for the current character
        m_vertices.append(Vertex(Vector2f(x + left  - italic * top,    y + top),    m_color, Vector2f(u1, v1)));
        m_vertices.append(Vertex(Vector2f(x + right - italic * top,    y + top),    m_color, Vector2f(u2, v1)));
        m_vertices.append(Vertex(Vector2f(x + right - italic * bottom, y + bottom), m_color, Vector2f(u2, v2)));
        m_vertices.append(Vertex(Vector2f(x + left  - italic * bottom, y + bottom), m_color, Vector2f(u1, v2)));

        // Update the current bounds
        minX = std::min(minX, x + left - italic * bottom);
        maxX = std::max(maxX, x + right - italic * top);
        minY = std::min(minY, y + top);
        maxY = std::max(maxY, y + bottom);

        // Advance to the next character
        x += glyph.advance;
    }

    // If we're using the underlined style, add the last line
    if (underlined)
    {
        float top = y + underlineOffset;
        float bottom = top + underlineThickness;

        m_vertices.append(Vertex(Vector2f(0, top),    m_color, Vector2f(1, 1)));
        m_vertices.append(Vertex(Vector2f(x, top),    m_color, Vector2f(1, 1)));
        m_vertices.append(Vertex(Vector2f(x, bottom), m_color, Vector2f(1, 1)));
        m_vertices.append(Vertex(Vector2f(0, bottom), m_color, Vector2f(1, 1)));
    }

    // Update the bounding rectangle
    m_bounds.left = minX;
    m_bounds.top = minY;
    m_bounds.width = maxX - minX;
    m_bounds.height = maxY - minY;
}


////////////////////////////////////////////////////////////
void Text::updateGeometryBounding()
{
    assert(m_font != NULL);

    //realign position to bounding box
    setPosition(m_boundBox.left + m_boundMargin, m_boundBox.top + m_boundMargin);

    //reset number of bounded characters
    m_numBoundChars = 0;

    // Clear the previous geometry
    m_vertices.clear();
    m_bounds = sf::FloatRect();

    // No text: nothing to draw
    if (m_string.isEmpty())
        return;

    //correct margins
    if(m_boundMargin >= m_boundBox.width/2 || m_boundMargin >= m_boundBox.height/2)
    	m_boundMargin = 0;

    //Bounding Data
    float boundTop = m_boundBox.top;
    float boundLeft = m_boundBox.left;
    float boundHeight = m_boundBox.height;
    float boundWidth = m_boundBox.width;
    Vector2f position;
    Vector2f positionGlobal;
    unsigned int charCounter = 0;//current character in m_string

    // Compute values related to the text style
    bool  bold               = (m_style & Bold) != 0;
    bool  underlined         = (m_style & Underlined) != 0;
    float italic             = (m_style & Italic) ? 0.208f : 0.f; // 12 degrees
    float underlineOffset    = m_characterSize * 0.1f;
    float underlineThickness = m_characterSize * (bold ? 0.1f : 0.07f);

    // Precompute the variables needed by the algorithm
    float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
    float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));
    position.x      = 0.f;
    position.y      = static_cast<float>(m_characterSize);

    // Create one quad for each character
    Uint32 prevChar = 0;
    position.y += m_boundMargin;
    while (positionGlobal.y < boundHeight + boundTop + m_boundMargin && charCounter < m_string.getSize())
    {
        Uint32 curChar = m_string[charCounter];

        // Apply the kerning offset
        position.x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));

        // Transform the position to global coordinates
        positionGlobal = getTransform().transformPoint(position);

        //correct out of bounds
        if(curChar != L'\n' && positionGlobal.x >= boundWidth + boundLeft + m_boundMargin + hspace){//check width
        	position.x -= static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
        	curChar = L'\n';
        	position.x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
        }
        else if(curChar == L'\n'){//check height
        	position.y += vspace;
        	positionGlobal = getTransform().transformPoint(position);
        	if(positionGlobal.y >= boundHeight + boundTop + m_boundMargin){
        		break;
        	}
        	else{
        		position.y -= vspace;
                	charCounter++;
                	m_numBoundChars++;
        	}
        }
        else{
		charCounter++;
		m_numBoundChars++;
        }

        prevChar = curChar;

        // If we're using the underlined style and there's a new line, draw a line
        if (underlined && (curChar == L'\n'))
        {
            float top = position.y + underlineOffset;
            float bottom = top + underlineThickness;

            m_vertices.append(Vertex(Vector2f(0, top),    m_color, Vector2f(1, 1)));
            m_vertices.append(Vertex(Vector2f(position.x, top),    m_color, Vector2f(1, 1)));
            m_vertices.append(Vertex(Vector2f(position.x, bottom), m_color, Vector2f(1, 1)));
            m_vertices.append(Vertex(Vector2f(0, bottom), m_color, Vector2f(1, 1)));
        }

        // Handle special characters
        switch (curChar)
        {
            case L' ' :  position.x += hspace;        continue;
            case L'\t' : position.x += hspace * 4;    continue;
            case L'\n' : position.y += vspace; position.x = m_boundBox.left+m_boundMargin; continue;
            case L'\v' : position.y += vspace * 4;    continue;
        }


        // Extract the current glyph's description
        const Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, bold);

        int left   = glyph.bounds.left;
        int top    = glyph.bounds.top;
        int right  = glyph.bounds.left + glyph.bounds.width;
        int bottom = glyph.bounds.top  + glyph.bounds.height;

        float u1 = static_cast<float>(glyph.textureRect.left);
        float v1 = static_cast<float>(glyph.textureRect.top);
        float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width);
        float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height);

        // Add a quad for the current character
        m_vertices.append(Vertex(Vector2f(position.x + left  - italic * top,    position.y + top),    m_color, Vector2f(u1, v1)));
        m_vertices.append(Vertex(Vector2f(position.x + right - italic * top,    position.y + top),    m_color, Vector2f(u2, v1)));
        m_vertices.append(Vertex(Vector2f(position.x + right - italic * bottom, position.y + bottom), m_color, Vector2f(u2, v2)));
        m_vertices.append(Vertex(Vector2f(position.x + left  - italic * bottom, position.y + bottom), m_color, Vector2f(u1, v2)));

        // Advance to the next character
        position.x += glyph.advance;
        // Transform the position to global coordinates
        positionGlobal = getTransform().transformPoint(position);
    }

    // If we're using the underlined style, add the last line
    if (underlined)
    {
        float top = position.y + underlineOffset;
        float bottom = top + underlineThickness;

        m_vertices.append(Vertex(Vector2f(0, top),    m_color, Vector2f(1, 1)));
        m_vertices.append(Vertex(Vector2f(position.x, top),    m_color, Vector2f(1, 1)));
        m_vertices.append(Vertex(Vector2f(position.x, bottom), m_color, Vector2f(1, 1)));
        m_vertices.append(Vertex(Vector2f(0, bottom), m_color, Vector2f(1, 1)));
    }

    // Recompute the bounding rectangle
    m_bounds = m_vertices.getBounds();
}

} // namespace sf
