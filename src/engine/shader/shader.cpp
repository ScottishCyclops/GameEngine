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
        exit(1);
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

    m_uniforms[PROJECTION_U] = glGetUniformLocation(m_glProgram,"projection");
    m_uniforms[VIEW_U] = glGetUniformLocation(m_glProgram,"view");
    m_uniforms[MODEL_U] = glGetUniformLocation(m_glProgram,"model");

    m_uniforms[AMBIANT_LIGHT_U] = glGetUniformLocation(m_glProgram,"ambiantLight");

    m_uniforms[CAM_POS_U] = glGetUniformLocation(m_glProgram,"camPos");
    m_uniforms[SPEC_COLOR_U] = glGetUniformLocation(m_glProgram,"specColor");
    m_uniforms[SPEC_INTENSITY_U] = glGetUniformLocation(m_glProgram,"specIntensity");
    m_uniforms[SPEC_HARDNESS_U] = glGetUniformLocation(m_glProgram,"hardness");

    m_uniforms[SUN_LIGHT_COLOR_U] = glGetUniformLocation(m_glProgram,"sun.base.color");
    m_uniforms[SUN_LIGHT_INTENSITY_U] = glGetUniformLocation(m_glProgram,"sun.base.intensity");
    m_uniforms[SUN_LIGHT_DIRECTION_U] = glGetUniformLocation(m_glProgram,"sun.direction");

    for(uint i = 0; i < MAX_POINTS_LIGHT; i++)
    {
        m_uniforms[POINT_LIGHT_0_COLOR_U+(i*POINT_LIGHT_COMPONANTS)] =
                glGetUniformLocation(m_glProgram, ("pointLights["+to_string(i)+"].base.color").c_str());
        m_uniforms[POINT_LIGHT_0_INTENSITY_U+(i*POINT_LIGHT_COMPONANTS)] =
                glGetUniformLocation(m_glProgram, ("pointLights["+to_string(i)+"].base.intensity").c_str());
        m_uniforms[POINT_LIGHT_0_CONSTANT_U+(i*POINT_LIGHT_COMPONANTS)] =
                glGetUniformLocation(m_glProgram, ("pointLights["+to_string(i)+"].attenuation.constant").c_str());
        m_uniforms[POINT_LIGHT_0_LINEAR_U+(i*POINT_LIGHT_COMPONANTS)] =
                glGetUniformLocation(m_glProgram, ("pointLights["+to_string(i)+"].attenuation.linear").c_str());
        m_uniforms[POINT_LIGHT_0_EXPONENT_U+(i*POINT_LIGHT_COMPONANTS)] =
                glGetUniformLocation(m_glProgram, ("pointLights["+to_string(i)+"].attenuation.exponent").c_str());
        m_uniforms[POINT_LIGHT_0_POSITION_U+(i*POINT_LIGHT_COMPONANTS)] =
                glGetUniformLocation(m_glProgram, ("pointLights["+to_string(i)+"].position").c_str());
    }
}

void Shader::update(Transform *transform, Camera* camera, SunLight* light, Material* mat)
{
    //model view projection, inversed for calculation !

    glm::mat4 projection = camera->getProjection();
    glm::mat4 view = camera->getView();
    glm::mat4 model = transform->getModel();

    //4D matrix with float values
    glUniformMatrix4fv(m_uniforms[PROJECTION_U],1,GL_FALSE,&projection[0][0]);
    glUniformMatrix4fv(m_uniforms[VIEW_U],1,GL_FALSE,&view[0][0]);
    glUniformMatrix4fv(m_uniforms[MODEL_U],1,GL_FALSE,&model[0][0]);

    glUniform3fv(m_uniforms[AMBIANT_LIGHT_U],1,(float*)m_ambiantLight);

    glUniform3fv(m_uniforms[CAM_POS_U],1,(float*)camera->getPos());
    glUniform3fv(m_uniforms[SPEC_COLOR_U],1,(float*)mat->getSpecular());
    glUniform1f(m_uniforms[SPEC_INTENSITY_U],mat->getSpecularIntensity());
    glUniform1f(m_uniforms[SPEC_HARDNESS_U],mat->getHardness());

    glUniform3fv(m_uniforms[SUN_LIGHT_COLOR_U],1,(float*)&light->base.color);
    glUniform1f(m_uniforms[SUN_LIGHT_INTENSITY_U],light->base.intensity);
    glUniform3fv(m_uniforms[SUN_LIGHT_DIRECTION_U],1,(float*)&light->direction);

    for(uint i = 0; i < MAX_POINTS_LIGHT; i++)
    {
        glUniform3fv(m_uniforms[POINT_LIGHT_0_COLOR_U+(i*POINT_LIGHT_COMPONANTS)],1,(float*)&m_pointLights[i]->base.color);
        glUniform1f(m_uniforms[POINT_LIGHT_0_INTENSITY_U+(i*POINT_LIGHT_COMPONANTS)],m_pointLights[i]->base.intensity);
        glUniform1f(m_uniforms[POINT_LIGHT_0_CONSTANT_U+(i*POINT_LIGHT_COMPONANTS)], m_pointLights[i]->attenuation.constant);
        glUniform1f(m_uniforms[POINT_LIGHT_0_LINEAR_U+(i*POINT_LIGHT_COMPONANTS)],   m_pointLights[i]->attenuation.linear);
        glUniform1f(m_uniforms[POINT_LIGHT_0_EXPONENT_U+(i*POINT_LIGHT_COMPONANTS)], m_pointLights[i]->attenuation.exponent);
        glUniform3fv(m_uniforms[POINT_LIGHT_0_POSITION_U+(i*POINT_LIGHT_COMPONANTS)],1,(float*)&m_pointLights[i]->position);
    }

}

void Shader::use()
{
    glUseProgram(m_glProgram);
}

void Shader::destroy()
{
    for(uint i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_glProgram, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_glProgram);
}

Shader::~Shader()
{
    destroy();
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
        exit(1);
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
        exit(1);
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
