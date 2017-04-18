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

#ifndef UTILS_H
#define UTILS_H

#include "libs.h"

const float pi = 3.14159265359f;

enum Direction
{
    X_AXIS,
    Y_AXIS,
    Z_AXIS,
    LOCAL_X_AXIS,
    LOCAL_Y_AXIS,
    LOCAL_Z_AXIS
};


class Utils
{
public:
    static vector<string> splitStr(const string &str, const char &delim);
    static int strToInt(string str);
    static float strToFloat(string str);
    static ushort strToUshort(string str);
    static float degreesToRad(float angle);
    static float radToDegrees(float angle);

    static glm::vec3 rotateAroundAxis(glm::vec3 vec, float angle, glm::vec3 axis);
    static glm::vec3 scaleAdd(float factor, glm::vec3 u, glm::vec3 v);
    static glm::vec2 getAcceleration(glm::vec2 posT1, glm::vec2 posT2, float deltaT);

    static string toString(glm::vec2 vec){return to_string(vec.x)+" "+to_string(vec.y);}
    static string toString(glm::vec3 vec){return to_string(vec.x)+" "+to_string(vec.y)+" "+to_string(vec.z);}

    static float getAngleBetweenVectors(glm::vec3 vec1, glm::vec3 vec2);
};

#endif // UTILS_H
