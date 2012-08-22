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

#ifndef SFML_SQLITE_HPP
#define SFML_SQLITE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Sqlite3/Export.hpp>
#include "sqlite3.h"
#include <iostream>
#include <string>

typedef int (*sq3_callback)(void*, int, char**, char**);

namespace sf
{

////////////////////////////////////////////////////////////
/// \brief The Sqlite3 runtime wrapper class.
///
////////////////////////////////////////////////////////////
class SFML_SQLITE3_API Sqlite
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    ////////////////////////////////////////////////////////////
    Sqlite(std::string Database_Name);

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Sqlite();

    ////////////////////////////////////////////////////////////
    /// \brief query the database
    ///
    /// \param string query in sql, this is for insert and creation only
    ///
    /// Example:
    /// \code
    /// sqlQuery("CREATE TABLE t_type...");
    /// sqlQuery("INSERT INTO t_type('PARENT_ID','TITLE') VALUES (0,'VEHICLES');");
    /// \endcode
    ///
    /// \return true if successful
    ////////////////////////////////////////////////////////////
    bool sqlQuery(std::string);

    ////////////////////////////////////////////////////////////
    /// \brief query the database
    ///
    /// \param string query in sql
    /// \param string passed by reference, returns any query results
    ///
    /// Example:
    /// \code
    /// sqlQuery("CREATE TABLE t_type...");
    /// sqlQuery("INSERT INTO t_type('PARENT_ID','TITLE') VALUES (0,'VEHICLES');");
    /// sqlQuery_ref("SELECT * FROM t_assets WHERE TYPE_ID=1;", stringVariable);
    /// \endcode
    ///
    /// \return true if successful
    ////////////////////////////////////////////////////////////
    bool sqlQuery_ref(std::string, std::string&);

    ////////////////////////////////////////////////////////////
    /// \brief query the database, with a callback
    ///
    /// \param string query in sql, this is for any type of query
    /// \param sq3_callback, pointer to callback function
    ///
    /// Example:
    /// \code
    /// static int call(void *NotUsed, int argc, char **argv, char **Col){
    /// int i;
    /// for(i=0; i<argc; i++){
    /// printf("%s | %s\n", Col[i], argv[i] ? argv[i] : "NULL");
    /// }
    /// printf("\n");
    /// return 0;
    /// }
    ///
    /// sqlQuery("SELECT * FROM t_assets WHERE TYPE_ID=1;", call);
    /// \endcode
    ///
    /// \return true if successful
    ////////////////////////////////////////////////////////////
    bool sqlQuery(std::string, sq3_callback);


protected :
    sqlite3 *db;
    char *zErrMsg;
    std::string dbName;
    int rc;

};

} // namespace sf


#endif // SFML_SQLITE_HPP


////////////////////////////////////////////////////////////
/// \class sf::Sqlite
/// \ingroup sqlite3
///
/// sf::Sqlite is a very simple class that allows the wrapping of
/// the sqlite3 runtime directly into an application.
///
/// Example:
/// \code
/// std::string out("");
/// db.sqlQuery("CREATE TABLE customer (First_Name char(50), Last_Name char(50), Address char(50), City char(50), Country char(25));");
/// db.sqlQuery("INSERT INTO customer VALUES ('joshua', 'reisenauer', '11111', '22222', '33333');");
/// db.sqlQuery_ref("SELECT * FROM customer;", out);
/// std::ofstream myfile;
/// myfile.open ("out.txt");
/// myfile << out;
/// myfile.close();
///
/// \endcode
///
/// \see sf::Sqlite
///
////////////////////////////////////////////////////////////
