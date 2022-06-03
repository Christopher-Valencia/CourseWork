project(list C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

SET(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES main.c list.c)

add_executable(list ${SOURCE_FILES})


