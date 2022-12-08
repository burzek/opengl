cmake_minimum_required(VERSION 3.0.0)
project(arkanoid VERSION 0.1.0)

file(GLOB PROJECT_HEADERS includes/*.hpp includes/*.h)
file(GLOB PROJECT_SOURCES *.cpp *.c)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})


find_package(glfw3 3.3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(Boost 1.73 COMPONENTS thread log log_setup)
include_directories(${BOOST_INCLUDE_DIRS})
add_definitions(-DBOOST_LOG_DYN_LINK)

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)

#find_package(X11 REQUIRED)
#include_directories(${X11_INCLUDE_DIR})


#executable    
add_executable(${PROJECT_NAME} 
    main.cpp
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${PROJECT_CONFIGS}
)

#linker
target_link_libraries(
    ${PROJECT_NAME} 
    glfw3
    X11
    ${Boost_LIBRARIES}
    ${GLFW_LIBRARIES} 
    ${GLAD_LIBRARIES}
    ${X11_LIBRARIES}

    ${OPENGL_gl_LIBRARY}
    #${OPENGL_LIBRARIES}
    #OpenGL::GL
    #glfw3
    #X11
)

