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

#include "transform.h"

Transform::Transform(glm::vec3 loc, glm::vec3 rot, glm::vec3 scale)
{
    Transform::loc = loc;
    Transform::rot = rot;
    Transform::scale = scale;
}

glm::mat4 Transform::getModel()
{
    glm::mat4 posMatrix = glm::translate(loc);
    glm::mat4 scaleMatrix = glm::scale(scale);

    glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1,0,0));
    glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0,1,0));
    glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0,0,1));

    //order matters, and it is reversed
    glm::mat4 rotMatrix = rotZMatrix*rotYMatrix*rotXMatrix;

    //first we scale, then we rotate, en finally we move the matrix
    return posMatrix*rotMatrix*scaleMatrix;
}
