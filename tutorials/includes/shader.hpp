#ifndef CE87DBEC_44A6_4B97_9B99_A09C8CDBAE27
#define CE87DBEC_44A6_4B97_9B99_A09C8CDBAE27

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include "shader_type.hpp"

class Shader {
    private:
        unsigned int id {0};
        GLint checkShaderProcessingStatus(GLuint shaderId, GLenum statusType);
        GLuint convertShaderType(ShaderType type);
    public:
        Shader();
        virtual ~Shader();
        void loadShader(const char* shaderFileName, ShaderType shaderType);
        const int getShaderID();
        const bool isReady();
        void useShader();
};

#endif /* CE87DBEC_44A6_4B97_9B99_A09C8CDBAE27 */
