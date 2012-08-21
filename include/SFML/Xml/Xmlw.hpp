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

#ifndef SFML_XMLW_HPP
#define SFML_XMLW_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Xml/Export.hpp>
#include "rapidxml.hpp"
#include <iostream>
#include <string>

typedef rapidxml::xml_node<> * sfml_xml_node;

namespace sf
{


////////////////////////////////////////////////////////////
/// \brief The Xml runtime wrapper class.
///
////////////////////////////////////////////////////////////
class SFML_XML_API Xmlw
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    /// \param string xml_document_string
    ////////////////////////////////////////////////////////////
    Xmlw(std::string xmlstring);

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    Xmlw();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Xmlw();


    ////////////////////////////////////////////////////////////
    /// \brief get the root node pointer
    ///
    /// \return typedef rapidxml::xml_node<> * sfml_xml_node;
    ////////////////////////////////////////////////////////////
    sfml_xml_node getRootNode();


    ////////////////////////////////////////////////////////////
    /// \brief transition to root, resets current position
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void goToRootNode();


    ////////////////////////////////////////////////////////////
    /// \brief transition to first child node, from current position
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void goToFirstChild();


    ////////////////////////////////////////////////////////////
    /// \brief transition to next sibling, from current position
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void goToNextSibling();


protected :
    rapidxml::xml_document<> xmldoc;
    char xmldocstring[512000];//buffer that holds xml string, holds a max of 0.5 megabytes
    sfml_xml_node node;//current node state position

};

} // namespace sf


#endif // SFML_XMLW_HPP


////////////////////////////////////////////////////////////
/// \class sf::Xmlw
/// \ingroup xml
///
/// sf::Xmlw is a very simple class that allows the wrapping of
/// the xml runtime directly into an application.
///
/// Example:
/// \code
///
///
/// \endcode
///
/// \see sf::Xmlw
///
////////////////////////////////////////////////////////////
