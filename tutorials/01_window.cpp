#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "includes/01_window.hpp"

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768

void glfwInitialize() {

    std::cout << "Initializing GLFW subsystem" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  

GLFWwindow* createWindow() {
    GLFWwindow* glwfWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tutorial 01 - create window", NULL, NULL);
    if (glwfWindow == nullptr) {
        std::cout << "Error initializing window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(glwfWindow);

    //needs to be called AFTER context is set
    std::cout << "Initializing GLAD subsystem" << std::endl;
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return nullptr;
    }
    glfwSetFramebufferSizeCallback(glwfWindow, framebuffer_size_callback);  

    return glwfWindow;
}



void glfwShutdown() {
    std::cout << "Shutting down application";
    glfwTerminate();
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
}


GLuint prepareShaders() {
    std::cout << "Preparing shaders" << std::endl;
    //vertex shader
    const GLchar* vertexShaderSource = "#version 330 core\n"
        "layout(location=0) in vec3 aPos;\n"
        "void main() {\n"
            "gl_Position=vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n\0";
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
	    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar errorLog(maxLength);
	    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << errorLog << std::endl;
        glDeleteShader(vertexShader);
        return 0;
    }

    //fragment shader
    const GLchar* fragmentShaderSource = "#version 330 core\n"
        "out vec4 outColor;\n"
        "void main() {\n"
            "outColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
	    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar errorLog(maxLength);
	    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << errorLog << std::endl;
        glDeleteShader(fragmentShader);
        return 0;
    }

    //shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
	    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar errorLog(maxLength);
	    glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &errorLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED" << std::endl << errorLog << std::endl;
        glDeleteProgram(shaderProgram);
        return 0;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
    
    return shaderProgram;


}


GLuint prepareTriangle() {
    std::cout << "Preparing vertex arrays" << std::endl;
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    GLuint vao, vbo;

    //vertex buffer object    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    
    return vao;
}

GLuint prepareTwoTrianglesEBO() {
    std::cout << "Preparing vertex arrays for two triangles" << std::endl;
    GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
    };
    GLuint indices[] = {
        0, 1, 3,   
        1, 2, 3    
    };  

    GLuint vao, vbo, ebo;
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    //vertex array
    glBindVertexArray(vao);

    //vertex buffer object    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //element buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    return vao;
}

GLuint prepareTwoTrianglesArrays() {
    std::cout << "Preparing vertex arrays for two triangles" << std::endl;
    GLfloat vertices[] = {
     -0.5f, -0.5f, 0.0f,
     -0.5f,  0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,

     -0.5f,  0.5f, 0.0f,
      0.5f,  0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
    
    };

    GLuint vao, vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    //vertex array
    glBindVertexArray(vao);

    //vertex buffer object    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    return vao;
}




void renderFrame(GLFWwindow* window, GLuint shaderProgram, GLuint vertexArrayObject) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    //glDrawArrays(GL_TRIANGLES, 0, 3);   //for triangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  //for EBO
    //glDrawArrays(GL_TRIANGLES, 0, 6);   //for arrays
    glBindVertexArray(0);

}

void window_01_run() {

    glfwInitialize();
    GLFWwindow* window = createWindow();

    GLuint shaderProgram = prepareShaders();
    if (shaderProgram == 0) {
        return;
    }
    GLuint vertexArrayObject = prepareTwoTrianglesEBO();

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        renderFrame(window, shaderProgram, vertexArrayObject);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwShutdown();

}
