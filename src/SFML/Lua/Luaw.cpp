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
#include "lua.hpp"
#include <SFML/Lua.hpp>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>


namespace sf
{


////////////////////////////////////////////////////////////
Luaw::Luaw()
{
    L = luaL_newstate();
    luaL_openlibs(L);
}


////////////////////////////////////////////////////////////
Luaw::~Luaw()
{
    lua_close(L);
}


////////////////////////////////////////////////////////////
int Luaw::runLuaScript(const char* file)
{
    return luaL_dofile(L, file);
}


///////////////////////////////////////////////////////////
void Luaw::registerLuaCFunction(const char *name, lua_CFunction f)
{
    lua_register(L, name, f);
}


///////////////////////////////////////////////////////////
int Luaw::getLuaStackSize()
{
    return lua_gettop(L);
}


///////////////////////////////////////////////////////////
bool Luaw::isLuaStackIndexANumber(int index)
{
    return lua_isnumber(L, index);
}


///////////////////////////////////////////////////////////
bool Luaw::isLuaStackIndexAString(int index)
{
    return lua_isstring(L, index);
}


///////////////////////////////////////////////////////////
bool Luaw::isLuaStackIndexACPointer(int index)
{
    return lua_isuserdata(L, index);
}


///////////////////////////////////////////////////////////
double Luaw::returnLuaStackIndexAsNumber(int index)
{
    if(this->isLuaStackIndexANumber(index)){
        return lua_tonumber(L, index);
    }
    else
        return 0;
}


///////////////////////////////////////////////////////////
std::string Luaw::returnLuaStackIndexAsString(int index)
{
    if(this->isLuaStackIndexAString(index)){
        const char* d = lua_tolstring(L, index, NULL);
        std::string out(d);
        return out;
    }
    else
        return "";
}


///////////////////////////////////////////////////////////
void * Luaw::returnLuaStackIndexAsCPointer(int index)
{
    return lua_touserdata(L, index);
}


///////////////////////////////////////////////////////////
void Luaw::pushStringOntoLuaStack(std::string s)
{
    lua_pushliteral(L, s.c_str());
}


///////////////////////////////////////////////////////////
void Luaw::pushNumberOntoLuaStack(double n)
{
    lua_pushnumber(L, n);
}


///////////////////////////////////////////////////////////
void Luaw::pushCPointerOntoLuaStack(void *p)
{
    lua_pushlightuserdata(L, p);
}


///////////////////////////////////////////////////////////
int Luaw::luaError()
{
    return lua_error(L);
}






} // namespace sf
