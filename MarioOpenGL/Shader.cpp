#include "Shader.h"
#include <iostream>

Shader &Shader::Use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource)
{
    unsigned int sVertex, sFragment, sGeometry;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, alse compile geometry shader
    if (geometrySource != nullptr)
    {
        sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(sGeometry, 1, &geometrySource, NULL);
        glCompileShader(sGeometry);
        checkCompileErrors(sGeometry, "GEOMETRY");
    }

    // shader program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
    {
        glAttachShader(this->ID, sGeometry);
    }

    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // Delete the shaders as they're linked into our program and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
    {
        glDeleteShader(sGeometry);
    }
}

