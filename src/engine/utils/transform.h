/*
    NinjaGame based on SDL2 GLEW and GL
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

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "libs.h"

class Transform
{
public:
    glm::vec3 loc;
    glm::vec3 rot;
    glm::vec3 scale;

    Transform(glm::vec3 loc = glm::vec3(0,0,0), glm::vec3 rot = glm::vec3(0,0,0), glm::vec3 scale = glm::vec3(1,1,1));

    glm::mat4 getModel();

    ~Transform();

};

#endif // TRANSFORM_H
