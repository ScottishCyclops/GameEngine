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

#include "material.h"


Material::Material(Texture *diffuse, float specularIntensity)
{
    m_diffuse = diffuse;
    m_diffuseIntensity = 1.f;
    m_specular = glm::vec3(1.f,1.f,1.f);
    m_specularIntensity = specularIntensity;
    m_hardness = 20.f;
}

Material::Material(Texture *diffuse, float diffuseIntensity, glm::vec3 specular, float specularIntensity, float hardness)
{
    m_diffuse = diffuse;
    m_diffuseIntensity = diffuseIntensity;
    m_specular = specular;
    m_specularIntensity = specularIntensity;
    m_hardness = hardness;
}

void Material::destroy()
{
    m_diffuse->destroy();
}

Material::~Material()
{
    destroy();
}
