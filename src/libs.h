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

#ifndef LIBS_H
#define LIBS_H


// namespace
using namespace std;

// grahics libraries
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

//gl math
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// utilities
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <array>

const string resFolder = "../resources";

#endif // LIBS_H
