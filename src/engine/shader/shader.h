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

#ifndef SHADER_H
#define SHADER_H

#include "libs.h"
#include "engine/utils/transform.h"
#include "engine/camera.h"

#define vertexShaderExt ".glvs"
#define fragmentShaderExt ".glfs"

class Shader
{
private:
    enum
    {
        PROJECTION_U,
        VIEW_U,
        MODEL_U,
        LIGHT_DIR_U,

        NUM_UNIFORMS,
    };
    static const uint NUM_SHADERS = 2;
    GLuint m_glProgram;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];

public:
    Shader(const string &shaderName);
    void use();
    void update(Transform* transform, Camera *camera, glm::vec3 *lightDir);
    void destroy();
    ~Shader();

    static string loadShader(const string &fileName);
    static void checkShaderError(GLuint check, GLuint flag, bool isProgram, const std::string &errorMessage);
    static GLuint createShader(const string &code, GLenum type);
};

#endif // SHADER_H
