
set(INCROOT ${PROJECT_SOURCE_DIR}/include/SFML/Lua)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/SFML/Lua)

FILE(GLOB SRC *.c)

# define the sfml-graphics target
sfml_add_library(sfml-lua
                 SOURCES ${SRC}
                 DEPENDS sfml-window sfml-system
                 EXTERNAL_LIBS pthread m dl)
