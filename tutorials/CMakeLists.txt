cmake_minimum_required(VERSION 3.0.0)
project(opengl-tutorials VERSION 0.1.0)


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


#includes
find_path(GLFW3_INCLUDE_DIR "GLFW/glfw3.h")
include_directories(${GLFW_INCLUDE_DIRS})



#executable    
add_executable(${PROJECT_NAME} 
    runner.cpp
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${PROJECT_CONFIGS}
)

#linker
target_link_libraries(
    ${PROJECT_NAME} 
    glfw3
    X11
    GL
    ${GLFW_LIBRARIES} 
    ${GLAD_LIBRARIES}

)

