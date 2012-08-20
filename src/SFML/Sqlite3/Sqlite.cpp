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
#include <SFML/Sqlite3.hpp>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <stdio.h>

static std::string TMP__STORAGE;

static int SQ_cback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        char buffer [100] = {'\0'};
        sprintf(buffer, "%s\n%s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        std::string s(buffer);
        TMP__STORAGE.append(s);
    }
    printf("\n");
    return 0;
}

namespace sf
{

//////////////////////////////////////////////////
Sqlite::Sqlite(std::string Name)
{
    dbName = Name;
    rc = sqlite3_open(dbName.c_str(), &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
}


/////////////////////////////////////////////////
Sqlite::~Sqlite()
{
    sqlite3_close(db);
}


/////////////////////////////////////////////////
bool Sqlite::sqlQuery(std::string query)
{
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}


/////////////////////////////////////////////////
bool Sqlite::sqlQuery_ref(std::string query, std::string& str_ref)
{
    rc = sqlite3_exec(db, query.c_str(), SQ_cback, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    str_ref.append(TMP__STORAGE);
    return true;
}


/////////////////////////////////////////////////
bool Sqlite::sqlQuery(std::string query, sq3_callback call)
{
    rc = sqlite3_exec(db, query.c_str(), call, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}




} // namespace sf
