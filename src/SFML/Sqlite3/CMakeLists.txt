
set(INCROOT ${PROJECT_SOURCE_DIR}/include/SFML/Sqlite3)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/SFML/Sqlite3)

FILE(GLOB SRC *.c)
FILE(GLOB SRCPP *.cpp)

# define the sfml-sqlite3 target
sfml_add_library(sfml-sqlite3
                 SOURCES ${SRCPP} ${SRC}
                 DEPENDS sfml-window sfml-system
                 EXTERNAL_LIBS pthread m dl)
