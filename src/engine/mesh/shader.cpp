/*
    Miden Engine, the real one. Built with OpenGL and SDL
    Copyright (C) 2017 Scott Winkelmann <scottlandart@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "shader.h"

Shader::Shader(const string &shaderName)
{
    m_glProgram = glCreateProgram();
    if(m_glProgram == 0)
    {
        cout << "E: Program creation failure" << endl;
        return;
    }

    m_shaders[0] = createShader(loadShader(shaderName + vertexShaderExt), GL_VERTEX_SHADER);
    m_shaders[1] = createShader(loadShader(shaderName + fragmentShaderExt), GL_FRAGMENT_SHADER);

    for(uint i = 0; i < NUM_SHADERS; i++)
    {
        glAttachShader(m_glProgram, m_shaders[i]);
    }

    //bind shader variable name
    //glBindAttribLocation(m_glProgram, 0, "pos");
    //glBindAttribLocation(m_glProgram, 1, "normal");

    glLinkProgram(m_glProgram);
    checkShaderError(m_glProgram,GL_LINK_STATUS,true, "Program linking failure");

    glValidateProgram(m_glProgram);
    checkShaderError(m_glProgram,GL_VALIDATE_STATUS,true, "Program validation failure");

    //transform is the name used in GLSL. This gets us the location of that variable so
    //we can use it from the CPU
    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_glProgram,"transform");
    m_uniforms[LIGHT_DIR_U] = glGetUniformLocation(m_glProgram,"lightDir");
}

void Shader::use()
{
    glUseProgram(m_glProgram);
}

void Shader::update(Transform *transform, Camera* camera, glm::vec3* lightDir)
{
    //model view projection
    glm::mat4 mvp = camera->getViewProjection() * transform->getModel();
    //4D matrix with float values
    glUniformMatrix4fv(m_uniforms[TRANSFORM_U],1,GL_FALSE,&mvp[0][0]);
    glUniform3fv(m_uniforms[LIGHT_DIR_U],1,(float*)lightDir);
}

Shader::~Shader()
{
    for(uint i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_glProgram, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_glProgram);
}

// static fonctions

string Shader::loadShader(const string &fileName)
{
    ifstream shaderFile(fileName);
    string output;

    if(shaderFile.is_open())
    {

        for(string line; getline(shaderFile,line); output+="\n")
        {
            output+=line;
        }
    }
    else
    {
        cout << "E: File opening failure: " << fileName << endl;
    }

    return output;
}

void Shader::checkShaderError(GLuint check, GLuint flag, bool isProgram, const std::string &errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = {0};

    if(isProgram)
        glGetProgramiv(check, flag, &success);
    else
        glGetShaderiv(check, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(check, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(check, sizeof(error), NULL, error);

        cout << "E: " << errorMessage << ": " << error << endl;
    }
}

/**
 * @brief Compiles the shader code into a GLSL shader and returns it
 * @param code : to code to generate the shader from
 * @param type : t he type of shader
 * @return the compiled shader
 */
GLuint Shader::createShader(const string &code, GLenum type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0)
    {
        cout << "E: Shader creation failure" << endl;
    }

    //we can have multiple codes, so it's an array in case
    const GLchar* shaderCode[1];
    GLint codeSize[1];

    shaderCode[0] = code.c_str();
    codeSize[0] = code.length();

    glShaderSource(shader,1,shaderCode,codeSize);
    glCompileShader(shader);

    checkShaderError(shader,GL_COMPILE_STATUS,false,"Shader compilation failure");

    return shader;
}
