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

#ifndef MATERIAL_H
#define MATERIAL_H

#include "libs.h"
#include "engine/material/texture.h"


class Material
{
private:
    Texture* m_diffuse;
    float m_diffuseIntensity;
    glm::vec3 m_specular;
    float m_specularIntensity;
    float m_hardness;
public:
    Material(Texture* diffuse, float specularIntensity);
    Material(Texture* diffuse, float diffuseIntensity, glm::vec3 specular, float specularIntensity, float hardness);

    Texture* getDiffuse(){return m_diffuse;}
    float getDiffuseIntensity(){return m_diffuseIntensity;}
    glm::vec3* getSpecular(){return &m_specular;}
    float getSpecularIntensity(){return m_specularIntensity;}
    float getHardness(){return m_hardness;}

    void destroy();
    ~Material();
};

#endif // MATERIAL_H
