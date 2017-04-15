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
    //we invert x
    m_pos = glm::vec3((float)-pos.x,(float)pos.y,(float)pos.z);
    m_forward = forwardVector;
    m_up = upVector;
    m_left = glm::normalize(glm::cross(m_forward,m_up));

    m_fov = fov;
    m_width = width;
    m_height = height;

    m_perspective = glm::perspective(Utils::degreesToRad(fov),(float)width/height,minClip,maxClip);
    //m_rotation = glm::vec3(0,0,0);
}

glm::mat4 Camera::getView()
{
    //rotation order : y x z
    return glm::lookAt(m_pos,m_pos+(*getForward()),*getUp());
}

glm::mat4 Camera::getProjection()
{
    return m_perspective;
}

glm::mat4 Camera::getViewProjection()
{
    return getProjection()*getView();
}

void Camera::rotate(uint axis, float angle)
{
    glm::vec3 localAxis(0,0,0);

    if(axis == X_AXIS)
    {
        //it rotates on it's local x
        localAxis = -m_left;
    }
    else if(axis == Y_AXIS)
    {
        //the camera always rotates on the world y
        localAxis = upVector;
        //clockwise correction
        angle = -angle;
    }
    else if(axis == Z_AXIS)
    {
        //it rotates on i's local z
        localAxis = m_forward;
    }

    if(localAxis != m_up)
    {
        m_up = Utils::rotateAroundAxis(m_up, angle, localAxis);
    }
    if(localAxis != m_forward)
    {
        m_forward = Utils::rotateAroundAxis(m_forward, angle, localAxis);
    }
    if(localAxis != m_left)
    {
        //- because it is somehow inverted ? TODO: fix
        m_left = Utils::rotateAroundAxis(-m_left, angle, localAxis);
    }
}

void Camera::translate(uint axis, float amount)
{
    glm::vec3 direction(0,0,0);

    if(axis == LOCAL_X_AXIS)
    {
        direction = m_left;
    }
    else if(axis == LOCAL_Y_AXIS)
    {
        direction = m_up;
    }
    else if(axis == LOCAL_Z_AXIS)
    {
        direction = m_forward;
    }
    else if(axis == X_AXIS)
    {
        direction = glm::normalize(glm::cross(m_forward,upVector));
    }
    else if(axis == Y_AXIS)
    {
        direction = upVector;
    }
    else if(axis == Z_AXIS)
    {
        direction = glm::normalize(glm::cross(upVector,m_left));
    }

    //m_pos = Utils::scaleAdd(amount,direction,m_pos);
    m_pos = amount*direction+m_pos;

}
