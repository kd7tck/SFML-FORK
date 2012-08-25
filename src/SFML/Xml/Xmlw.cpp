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
#include "pugixml.hpp"

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


namespace sf
{

Xmlw::Xmlw(std::string xmlstring)
{
    result = doc.load_buffer(xmlstring.c_str(), sizeof(xmlstring.c_str()));
}

Xmlw::Xmlw()
{
    ;
}

Xmlw::~Xmlw()
{
    doc.reset();
}


bool Xmlw::loadXmlFile(std::string xmlpath)
{
    result = doc.load_file(xmlpath.c_str());
    if(result)
        return true;

    return false;
}


bool Xmlw::loadXmlString(std::string xmlstring)
{
    result = doc.load_buffer(xmlstring.c_str(), xmlstring.size());
    if(result)
        return true;

    return false;
}


std::string Xmlw::saveXmlToString()
{
    std::stringstream s;
    doc.save(s);

    return s.str();
}


bool Xmlw::saveXmlToFile(std::string path)
{
    return doc.save_file(path.c_str());
}


bool Xmlw::goToRootNode()
{
    node = doc.first_child();
    if(node){
        attr = node.first_attribute();
        return true;
    }

    return false;
}


bool Xmlw::goToFirstChildNode()
{
    node = node.first_child();
    if(node){
        attr = node.first_attribute();
        return true;
    }

    return false;
}


bool Xmlw::goToNextSiblingNode()
{
    node = node.next_sibling();
    if(node){
        attr = node.first_attribute();
        return true;
    }

    return false;
}


bool Xmlw::goToParentNode()
{
    node = node.parent();
    if(node){
        attr = node.first_attribute();
        return true;
    }

    return false;
}


bool Xmlw::goToNextAttribute()
{
    attr = attr.next_attribute();
    if(attr){
        return true;
    }
    return false;
}


std::string Xmlw::getCurrentNodeValue()
{
    if(node){
        std::stringstream s;
        s << node.value();
        return s.str();
    }
    return "";
}


std::string Xmlw::getCurrentNodeName()
{
    if(node){
        std::stringstream s;
        s << node.name();
        return s.str();
    }
    return "";
}


std::string Xmlw::getCurrentAttributeValue()
{
    if(attr){
        std::stringstream s;
        s << attr.value();
        return s.str();
    }
    return "";
}


std::string Xmlw::getCurrentAttributeName()
{
    if(attr){
        std::stringstream s;
        s << attr.name();
        return s.str();
    }
    return "";
}


bool Xmlw::createNewNodeForCurrentNode(std::string name, std::string value)
{
    if(node){
        pugi::xml_node n = node.append_child(name.c_str());
        n.set_value(value.c_str());
        return true;
    }
    return false;
}


bool Xmlw::createNewNodeForRootNode(std::string name, std::string value)
{
    if(doc){
        pugi::xml_node n = doc.append_child(name.c_str());
        n.set_value(value.c_str());
        return true;
    }
    return false;
}


bool Xmlw::createNewAttributeForCurrentNode(std::string name, std::string value)
{
    if(node){
        node.append_attribute(name.c_str()) = value.c_str();
        return true;
    }
    return false;
}


bool Xmlw::removeChildNodeByIndexForCurrentNode(int index)
{
    if(node){
        int count = index;

        if(index < 0)
            count = 0;

        pugi::xml_node n = node.first_child();


        while(n && count){
            n = n.next_sibling();
            count--;
        }

        if(n){
            node.remove_child(n.name());
            return true;
        }
    }
    return false;
}


bool Xmlw::removeChildNodeByStringForCurrentNode(std::string name)
{
    if(node){
        return node.remove_child(name.c_str());
    }
    return false;
}


bool Xmlw::removeCurrentNode()
{
    pugi::xml_node n;

    if(node.next_sibling()){
        n = node.next_sibling();
    }
    else if(node.parent()){
        n = node.parent();
    }

    pugi::xml_node p = node.parent();
    if(p){
        p.remove_child(node.name());
        node = n;
    }
    else{
        doc.remove_child(node.name());
        node = n;
        return false;
    }

    return true;
}


} // namespace sf
