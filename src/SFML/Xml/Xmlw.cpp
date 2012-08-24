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
#include <SFML/Xml.hpp>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>


namespace sf
{

Xmlw::Xmlw(std::string xmlstring)
{
    if(xmlstring.size() < 512000){
        xmlstring.copy(xmldocstring, xmlstring.size(), 0);
        xmldocstring[xmlstring.size()] = '\0';
    }
    else{
        xmlstring.copy(xmldocstring, 511999, 0);
        xmldocstring[511999] = '\0';
    }

    xmldoc.parse<0>(xmldocstring);

    if(xmldoc.first_node()){
        node = xmldoc.first_node();
        attr = node->first_attribute();
    }
}

Xmlw::Xmlw()
{
    std::string xmlstring("<?xml version=\"1.0\"?>\n");
    xmlstring.copy(xmldocstring, xmlstring.size(), 0);
    xmldocstring[xmlstring.size()] = '\0';
    xmldoc.parse<0>(xmldocstring);
}

Xmlw::~Xmlw()
{
    xmldoc.clear();
}


bool Xmlw::loadXml(std::string xmlstring)
{
    if(xmlstring.size() < 512000){
        xmlstring.copy(xmldocstring, xmlstring.size(), 0);
        xmldocstring[xmlstring.size()] = '\0';
    }
    else{
        xmlstring.copy(xmldocstring, 511999, 0);
        xmldocstring[511999] = '\0';
    }

    xmldoc.parse<0>(xmldocstring);

    if(xmldoc.first_node()){
        node = xmldoc.first_node();
        attr = node->first_attribute();
        return true;
    }
    return false;
}


sfml_xml_node Xmlw::getRootNode()
{
    return xmldoc.first_node();
}


bool Xmlw::goToRootNode()
{
    if(xmldoc.first_node()){
        node = xmldoc.first_node();
        attr = node->first_attribute();
        return true;
    }
    return false;
}


bool Xmlw::goToFirstChildNode()
{
    if(node->first_node() != NULL){
        node = node->first_node();
        attr = node->first_attribute();
        return true;
    }
    return false;
}


bool Xmlw::goToNextSibling()
{
    if(node->parent() && node->next_sibling()){
        node = node->next_sibling();
        attr = node->first_attribute();
        return true;
    }
    return false;
}


bool Xmlw::goToParentNode()
{
    if(node->parent())
    {
        node = node->parent();
        return true;
    }
    return false;
}


bool Xmlw::goToNextAttribute()
{
    if(attr->next_attribute()){
        attr = attr->next_attribute();
        return true;
    }
    return false;
}


std::string Xmlw::getCurrentNodeValue()
{
    std::ostringstream Convert;
    Convert << node->value();
    return Convert.str();
}


std::string Xmlw::getCurrentNodeName()
{
    std::ostringstream Convert;
    Convert << node->name();
    return Convert.str();
}


std::string Xmlw::getCurrentAttributeValue()
{
    std::ostringstream Convert;
    Convert << attr->value();
    return Convert.str();
}


std::string Xmlw::getCurrentAttributeName()
{
    std::ostringstream Convert;
    Convert << attr->name();
    return Convert.str();
}


bool Xmlw::createNewNodeForCurrentNode(std::string name, std::string value)
{
    sfml_xml_node n = xmldoc.allocate_node(rapidxml::node_element, name.c_str(), value.c_str());
    if(n){
        node->append_node(n);
        return true;
    }
    return false;
}


bool Xmlw::createNewNodeForRootNode(std::string name, std::string value)
{
    sfml_xml_node n = xmldoc.allocate_node(rapidxml::node_element, name.c_str(), value.c_str());
    if(n){
        xmldoc.append_node(n);
        return true;
    }
    return false;
}


bool Xmlw::createNewAttributeForCurrentNode(std::string name, std::string value)
{
    sfml_xml_attribute at = xmldoc.allocate_attribute(name.c_str(), value.c_str());
    if(at){
        node->append_attribute(at);
        return true;
    }
    return false;
}


bool Xmlw::removeChildNodeByIndexForCurrentNode(int index)
{
    int count = index;

    if(index < 0)
        count = 0;

    sfml_xml_node n = node->first_node();


    while(n && count){
        n = n->next_sibling();
        count--;
    }

    if(n){
        node->remove_node(n);
        return true;
    }
    return false;
}


} // namespace sf
