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
#include "pugixml.hpp"
#include <iostream>
#include <string>


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
    /// \brief build new xml doc from file
    ///
    /// \param string xml_document_string
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool loadXmlFile(std::string xmlpath);

    ////////////////////////////////////////////////////////////
    /// \brief build new xml doc from string
    ///
    /// \param string xml_document_string
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool loadXmlString(std::string xmlstring);

    ////////////////////////////////////////////////////////////
    /// \brief save xml doc to string and return it
    ///
    /// \return string xml
    ////////////////////////////////////////////////////////////
    std::string saveXmlToString();

    ////////////////////////////////////////////////////////////
    /// \brief save xml doc to file
    ///
    /// \param string file_path
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool saveXmlToFile(std::string path);

    ////////////////////////////////////////////////////////////
    /// \brief build new attribute and append it to the current node
    ///
    /// \param string name
    ///
    /// \param string value
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool createNewAttributeForCurrentNode(std::string name, std::string value);

    ////////////////////////////////////////////////////////////
    /// \brief build new node and append it to the current node
    ///
    /// \param string name
    ///
    /// \param string value
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool createNewNodeForCurrentNode(std::string name, std::string value);

    ////////////////////////////////////////////////////////////
    /// \brief build new node and append it to the root node
    ///
    /// \param string name
    ///
    /// \param string value
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool createNewNodeForRootNode(std::string name, std::string value);

    ////////////////////////////////////////////////////////////
    /// \brief remove nth child for current node
    ///
    /// \param int index
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool removeChildNodeByIndexForCurrentNode(int index);

    ////////////////////////////////////////////////////////////
    /// \brief remove child node for current node, by name
    ///
    /// \param string name
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool removeChildNodeByStringForCurrentNode(std::string name);

    ////////////////////////////////////////////////////////////
    /// \brief remove current node
    ///
    /// \param int index
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool removeCurrentNode();


    ////////////////////////////////////////////////////////////
    /// \brief transition to root, resets current position
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool goToRootNode();


    ////////////////////////////////////////////////////////////
    /// \brief transition to first child node, from current node position
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool goToFirstChildNode();


    ////////////////////////////////////////////////////////////
    /// \brief transition to parent node, from current node position
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool goToParentNode();


    ////////////////////////////////////////////////////////////
    /// \brief transition to next sibling node, from current node position
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool goToNextSiblingNode();

    ////////////////////////////////////////////////////////////
    /// \brief transition to next attribute, based on current node position, node position is left unaltered
    ///
    /// \return true on success
    ////////////////////////////////////////////////////////////
    bool goToNextAttribute();


    ////////////////////////////////////////////////////////////
    /// \brief read current node position value
    ///
    /// \return std::string
    ////////////////////////////////////////////////////////////
    std::string getCurrentNodeValue();


    ////////////////////////////////////////////////////////////
    /// \brief read current node position name
    ///
    /// \return std::string
    ////////////////////////////////////////////////////////////
    std::string getCurrentNodeName();


    ////////////////////////////////////////////////////////////
    /// \brief read current attribute position value
    ///
    /// \return std::string
    ////////////////////////////////////////////////////////////
    std::string getCurrentAttributeValue();


    ////////////////////////////////////////////////////////////
    /// \brief read current attribute position name
    ///
    /// \return std::string
    ////////////////////////////////////////////////////////////
    std::string getCurrentAttributeName();


protected :
    pugi::xml_document doc;
    pugi::xml_parse_result result;
    pugi::xml_node node;
    pugi::xml_attribute attr;
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
/// sf::Xmlw xml_reader;
/// std::string out("");
/// xml_reader.loadXmlString("<?xml version=\"1.0\"?><note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>");
/// out += xml_reader.getCurrentNodeName();
/// out += xml_reader.getCurrentNodeValue();
/// xml_reader.goToFirstChild();
/// out += xml_reader.getCurrentNodeName();
/// out += xml_reader.getCurrentNodeValue();
/// std::ofstream myfile;
/// myfile.open ("out.txt");
/// myfile << out;
/// myfile.close();
///
/// \endcode
///
/// \see sf::Xmlw
///
////////////////////////////////////////////////////////////
