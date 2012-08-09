
set(INCROOT ${PROJECT_SOURCE_DIR}/include/SFML/Lua)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/SFML/Lua)

FILE(GLOB SRC *.c)
FILE(GLOB SRCPP *.cpp)

# define the sfml-graphics target
sfml_add_library(sfml-lua
                 SOURCES ${SRCPP} ${SRC}
                 DEPENDS sfml-window sfml-system
                 EXTERNAL_LIBS pthread m dl)
