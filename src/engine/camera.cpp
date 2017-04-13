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

#include "camera.h"

Camera::Camera(glm::vec3 pos, float fov, int width, int height, float minClip, float maxClip)
{
    m_pos = pos;
    m_fov = fov;
    m_width = width;
    m_height = height;

    m_perspective = glm::perspective(Utils::degreesToRad(fov),(float)width/height,minClip,maxClip);
    m_forward = glm::vec3(0,0,1);
    m_up = glm::vec3(0,1,0);
}

glm::mat4 Camera::getView()
{
    return glm::lookAt(m_pos,m_pos+m_forward,m_up);
}

glm::mat4 Camera::getProjection()
{
    return m_perspective;
}

glm::mat4 Camera::getViewProjection()
{
    return getProjection()*getView();
}

glm::vec3 Camera::getLeft()
{
    return glm::normalize(glm::cross(m_up,m_forward));
}

glm::vec3 Camera::getRight()
{
    return glm::normalize(glm::cross(m_forward,m_up));
}
