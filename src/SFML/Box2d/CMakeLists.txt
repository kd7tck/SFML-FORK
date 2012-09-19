
set(INCROOT ${PROJECT_SOURCE_DIR}/include/SFML/Box2d)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/SFML/Box2d)

FILE(GLOB SRC *.c)
FILE(GLOB SRCPP *.cpp)

FILE(GLOB SRC Box2D/*.c)
FILE(GLOB SRCPP Box2D/*.cpp)

# define the sfml-box2d target
sfml_add_library(sfml-box2d
                 SOURCES ${SRCPP} ${SRC}
                 DEPENDS sfml-graphics sfml-window sfml-system
                 EXTERNAL_LIBS m)
