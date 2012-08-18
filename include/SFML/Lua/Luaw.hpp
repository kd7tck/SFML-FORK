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

#ifndef SFML_LUAW_HPP
#define SFML_LUAW_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Lua/Export.hpp>
#include <iostream>
#include <string>
#include <stack>

#ifndef lua_h
typedef struct lua_State lua_State;
typedef int (*lua_CFunction) (lua_State *L);
#endif

namespace sf
{

////////////////////////////////////////////////////////////
/// \brief The lua runtime wrapper class, allows for seamless
/// integration of lua scripts into game.
///
////////////////////////////////////////////////////////////
class SFML_LUA_API Luaw
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    Luaw();

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Luaw();

    ////////////////////////////////////////////////////////////
    /// \brief Load a lua script and run it
    ///
    /// This function allows the program to load and run any lua script.
    ///
    /// \param file The file to load, full path is needed.
    ///
    /// \return A zero is returned if successfull, non zero on error.
    ////////////////////////////////////////////////////////////
    int runLuaScript(const char* file);

    ////////////////////////////////////////////////////////////
    /// \brief registers a lua C function to a lua global called name
    ///
    /// This function allows the lua script to call C functions.
    ///
    /// \param name global lua name
    /// \param f C function pointer
    ///
    /// Example:
    /// \code
    ///
    ///     static int foo (lua_State *L) {
    ///       int n = getLuaStackSize();    /* number of arguments */
    ///       lua_Number sum = 0;
    ///       int i;
    ///       for (i = 1; i <= n; i++) {
    ///         if (!isLuaStackIndexANumber(i)) {
    ///           pushStringOntoLuaStack("incorrect argument");
    ///           luaError();
    ///         }
    ///         sum += returnLuaStackIndexAsNumber(i);
    ///       }
    ///       pushNumberOntoLuaStack(sum/n);        /* first result */
    ///       pushNumberOntoLuaStack(sum);         /* second result */
    ///       return 2;                   /* number of results */
    ///     }
    ///
    ///     registerLuaCFunction("foo", foo);
    ///
    /// \endcode
    ///
    ////////////////////////////////////////////////////////////
    void registerLuaCFunction(const char *name, lua_CFunction f);

    ////////////////////////////////////////////////////////////
    /// \brief return number of elements in lua stack
    ///
    /// This function returns int number of elements in lua stack.
    ///
    /// \return number of stack elements
    ////////////////////////////////////////////////////////////
    int getLuaStackSize();

    ////////////////////////////////////////////////////////////
    /// \brief check if index of stack is number
    ///
    /// \param index position in stack
    ///
    /// \return true if index of stack is a number
    ////////////////////////////////////////////////////////////
    bool isLuaStackIndexANumber(int index);

    ////////////////////////////////////////////////////////////
    /// \brief check if index of stack is string
    ///
    /// \param index position in stack
    ///
    /// \return true if index of stack is a string
    ////////////////////////////////////////////////////////////
    bool isLuaStackIndexAString(int index);

    ////////////////////////////////////////////////////////////
    /// \brief check if index of stack is C pointer
    ///
    /// \param index position in stack
    ///
    /// \return true if index of stack is a void pointer
    ////////////////////////////////////////////////////////////
    bool isLuaStackIndexACPointer(int index);

    ////////////////////////////////////////////////////////////
    /// \brief return index in stack as double
    ///
    /// \param index position in stack
    ///
    /// \return 0 if not number, otherwise the double is returned
    ////////////////////////////////////////////////////////////
    double returnLuaStackIndexAsNumber(int index);

    ////////////////////////////////////////////////////////////
    /// \brief return index in stack as string
    ///
    /// \param index position in stack
    ///
    /// \return string of index, otherwise empty string
    ////////////////////////////////////////////////////////////
    std::string returnLuaStackIndexAsString(int index);

    ////////////////////////////////////////////////////////////
    /// \brief return C pointer
    ///
    /// \param index position in stack
    ///
    /// \return void C pointer, NULL on error
    ////////////////////////////////////////////////////////////
    void * returnLuaStackIndexAsCPointer(int index);

    ////////////////////////////////////////////////////////////
    /// \brief pushes string literal onto lua stack
    ///
    /// \param s string literal
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void pushStringOntoLuaStack(std::string s);

    ////////////////////////////////////////////////////////////
    /// \brief pushes number onto lua stack
    ///
    /// \param n double number
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void pushNumberOntoLuaStack(double n);

    ////////////////////////////////////////////////////////////
    /// \brief pushes c Pointer of void type onto lua stack
    ///
    /// \param p void type pointer
    ///
    /// \return void
    ////////////////////////////////////////////////////////////
    void pushCPointerOntoLuaStack(void *p);

    ////////////////////////////////////////////////////////////
    /// \brief generate a lua error
    ///
    /// \param
    ///
    /// \return int that is never returned
    ////////////////////////////////////////////////////////////
    int luaError();

protected :

    std::stack<std::string> buffer;

    /* the Lua interpreter */
    lua_State* L;
};

} // namespace sf


#endif // SFML_LUAW_HPP


////////////////////////////////////////////////////////////
/// \class sf::Lua
/// \ingroup lua
///
/// sf::Lua is a very simple class that allows the wrapping of
/// the Lua runtime directly into an application.
///
/// Example:
/// \code
///
///     virtual void lua_routine(sf::Lua lua_runtime)
///     {
///         ;
///     }
///
/// \endcode
///
/// \see sf::Luaw
///
////////////////////////////////////////////////////////////
