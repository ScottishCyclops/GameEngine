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

#ifndef CAMERA_H
#define CAMERA_H

#include "libs.h"

class Camera
{
private:
    glm::mat4 m_perspective;
    glm::vec3 m_pos;
    glm::vec3 m_forward;
    glm::vec3 m_up;

public:
    Camera(glm::vec3 pos, float fov, float aspect, float minClip, float maxClip);
    glm::mat4 getViewProjection();

    float* getX();
    float* getY();
    float* getZ();
};

#endif // CAMERA_H
