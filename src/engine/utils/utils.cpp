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

#include "utils.h"

vector<string> Utils::splitStr(const string &str, const char &delim)
{
    vector<string> elements;

    uint nextStart = 0;

    const char* cStr = str.c_str();
    uint strLenght = str.length();

    for(uint i = 0; i < strLenght; i++)
    {
        if(cStr[i] == delim)
        {
            elements.push_back(str.substr(nextStart,i-nextStart));
            //+1 to not take the space
            nextStart = i+1;
        }
        else if(i == strLenght-1)
        {
            elements.push_back(str.substr(nextStart,strLenght));
        }
    }

    return elements;
}

int Utils::strToInt(string str)
{
    return (int)atof(str.c_str());
}

float Utils::strToFloat(string str)
{
    return (float)atof(str.c_str());
}

ushort Utils::strToUshort(string str)
{
    return (ushort)atof(str.c_str());
}

float Utils::degreesToRad(float angle)
{
    return angle*(pi/180.f);
}

float Utils::radToDegrees(float angle)
{
    return angle*(180.f/pi);
}


glm::vec3 Utils::rotateAroundAxis(glm::vec3 vec, float angle, glm::vec3 axis)
{
    axis = glm::normalize(axis);
    float radAngle = Utils::degreesToRad(angle);
    float sinAngle = sin(radAngle);
    float cosAngle = cos(radAngle);
    glm::vec3 axisCrossVec = glm::cross(axis,vec);

    glm::vec3 ret = vec*cosAngle;

    ret = Utils::scaleAdd(sinAngle,axisCrossVec,ret);
    ret = Utils::scaleAdd(glm::dot(axis,vec)*(1-cosAngle),axis,ret);

    return ret;
}

glm::vec3 Utils::scaleAdd(float factor, glm::vec3 u, glm::vec3 v)
{
    return glm::vec3(factor*u.x+v.x,factor*u.y+v.y,factor*u.z+v.z);
}

glm::vec2 Utils::getAcceleration(glm::vec2 posT1, glm::vec2 posT2, float deltaT)
{
    float deltaX = posT2.x-posT1.x;
    float deltaY = posT2.y-posT1.y;

    glm::vec2 acceleration(0,0);
    acceleration.x = deltaX/deltaT;
    acceleration.y = deltaY/deltaT;

    return acceleration;
}

bool XOR(bool a, bool b)
{
    return (a + b) % 2;
}

float Utils::getAngleBetweenVectors(glm::vec3 vec1, glm::vec3 vec2)
{
    return radToDegrees( acos( glm::dot(glm::normalize(vec1),glm::normalize(vec2)) ) );
}
