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

#include "engine/utils/utils.h"

class Camera
{
private:
    glm::mat4 m_perspective;
    glm::vec3 m_pos;
    glm::vec3 m_forward;
    glm::vec3 m_up;

    float m_fov;
    int m_width;
    int m_height;

public:
    Camera(glm::vec3 pos, float fov, int width, int height, float minClip, float maxClip);
    glm::mat4 getView();
    glm::mat4 getProjection();
    glm::mat4 getViewProjection();
    glm::vec3 getLeft();
    glm::vec3 getRight();

    float* getX(){return &m_pos.x;}
    float* getY(){return &m_pos.y;}
    float* getZ(){return &m_pos.z;}

    int getWidth(){return m_width;}
    int getHeight(){return m_height;}
    int getFov(){return m_fov;}

};

#endif // CAMERA_H
