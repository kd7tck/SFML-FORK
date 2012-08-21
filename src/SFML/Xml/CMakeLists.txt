
set(INCROOT ${PROJECT_SOURCE_DIR}/include/SFML/Xml)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/SFML/Xml)

FILE(GLOB SRC *.c)
FILE(GLOB SRCPP *.cpp)

# define the sfml-xml target
sfml_add_library(sfml-xml
                 SOURCES ${SRCPP} ${SRC}
                 DEPENDS sfml-window sfml-system
                 EXTERNAL_LIBS)
