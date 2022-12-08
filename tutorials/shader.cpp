#include "includes/shader.hpp"


Shader::Shader() {
};

Shader::~Shader() {
};


void Shader::loadShader(const char* shaderFileName, ShaderType shaderType) {
    //load shader file from path
    std::ifstream fShaderFile {};
    fShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    const char* shaderCode {};
    
    try {
        fShaderFile.open(shaderFileName);
        std::stringstream shaderStream;
        shaderStream << fShaderFile.rdbuf();
        fShaderFile.close();

        shaderCode = shaderStream.str().c_str();

    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER cannot load shader from file " << shaderFileName << "(" << shaderType << ")" << std::endl;
        return;
    }

    //compile shader
    GLuint shaderId { glCreateShader(convertShaderType(shaderType)) };
    glShaderSource(shaderId, 1, &shaderCode, nullptr);
    glCompileShader(shaderId);
    if (checkShaderProcessingStatus(shaderId, GL_COMPILE_STATUS) == GL_FALSE) {
        return;
    }

    
    id = glCreateProgram();
    glAttachShader(id, shaderId);
    glLinkProgram(id);
    if (checkShaderProcessingStatus(shaderId, GL_LINK_STATUS) == GL_FALSE) {
        return;
    }

    glDeleteShader(shaderId);

}

const int Shader::getShaderID() {
    return id;
}

const bool Shader::isReady() {
    return id != 0;
}

void Shader::useShader() {
    if (isReady()) {
        glUseProgram(id);
    }
}


GLint Shader::checkShaderProcessingStatus(GLuint shaderId, GLenum statusType) {
    GLint status {};
    glGetShaderiv(shaderId, statusType, &status);
    if (status != GL_TRUE) {
     	GLchar errorMsg {};
        glGetShaderInfoLog(shaderId, 512, nullptr, &errorMsg);
        std::cout << "ERROR::SHADER error processing shader " << shaderId << ", error is " << errorMsg << std::endl;
    }
    return status;
}


GLuint Shader::convertShaderType(ShaderType type) {
    switch (type) {
        case ShaderType::vertex:
            return GL_VERTEX_SHADER;
        case ShaderType::fragment:
            return GL_FRAGMENT_SHADER;
        default:
            std::cout << "ERROR::SHADER unsupported shader type requested" << std::endl;
            return -1;
    }
};