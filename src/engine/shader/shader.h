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
#include "engine/light/light.h"
#include "engine/material/material.h"

#define vertexShaderExt ".glvs"
#define fragmentShaderExt ".glfs"

const uint MAX_POINTS_LIGHT = 4;

class Shader
{
private:
    const glm::vec3* m_ambiantLight = new glm::vec3(0.1f,0.1f,0.1f);
    static const uint NUM_SHADERS = 2;
    static const uint POINT_LIGHT_COMPONANTS = 6;
    enum
    {
        PROJECTION_U,
        VIEW_U,
        MODEL_U,
        AMBIANT_LIGHT_U,
        CAM_POS_U,

        SPEC_COLOR_U,
        SPEC_INTENSITY_U,
        SPEC_HARDNESS_U,

        SUN_LIGHT_COLOR_U,
        SUN_LIGHT_INTENSITY_U,
        SUN_LIGHT_DIRECTION_U,

        POINT_LIGHT_0_COLOR_U,
        POINT_LIGHT_0_INTENSITY_U,
        POINT_LIGHT_0_CONSTANT_U,
        POINT_LIGHT_0_LINEAR_U,
        POINT_LIGHT_0_EXPONENT_U,
        POINT_LIGHT_0_POSITION_U,

        POINT_LIGHT_1_COLOR_U,
        POINT_LIGHT_1_INTENSITY_U,
        POINT_LIGHT_1_CONSTANT_U,
        POINT_LIGHT_1_LINEAR_U,
        POINT_LIGHT_1_EXPONENT_U,
        POINT_LIGHT_1_POSITION_U,

        POINT_LIGHT_2_COLOR_U,
        POINT_LIGHT_2_INTENSITY_U,
        POINT_LIGHT_2_CONSTANT_U,
        POINT_LIGHT_2_LINEAR_U,
        POINT_LIGHT_2_EXPONENT_U,
        POINT_LIGHT_2_POSITION_U,

        POINT_LIGHT_3_COLOR_U,
        POINT_LIGHT_3_INTENSITY_U,
        POINT_LIGHT_3_CONSTANT_U,
        POINT_LIGHT_3_LINEAR_U,
        POINT_LIGHT_3_EXPONENT_U,
        POINT_LIGHT_3_POSITION_U,

        NUM_UNIFORMS,
    };

    GLuint m_glProgram;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
    PointLight* m_pointLights[MAX_POINTS_LIGHT];

public:
    Shader(const string &shaderName);
    void use();
    void setPointLight(uint index, PointLight* light){m_pointLights[index] = light;}
    void update(Transform* transform, Camera *camera, SunLight *light, Material* mat);
    void destroy();
    ~Shader();

    static string loadShader(const string &fileName);
    static void checkShaderError(GLuint check, GLuint flag, bool isProgram, const std::string &errorMessage);
    static GLuint createShader(const string &code, GLenum type);
};

#endif // SHADER_H
