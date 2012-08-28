
set(INCROOT ${PROJECT_SOURCE_DIR}/include/SFML/Util)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/SFML/Util)

FILE(GLOB SRC *.c)
FILE(GLOB SRCPP *.cpp)

# define the sfml-util target
sfml_add_library(sfml-util
                 SOURCES ${SRCPP} ${SRC}
                 DEPENDS sfml-window sfml-system
                 EXTERNAL_LIBS m)
