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

#ifndef MESHLOADER_H
#define MESHLOADER_H

#include "libs.h"

#include "engine/utils/utils.h"
#include "engine/mesh/mesh.h"

class MeshLoader
{
public:
    static MeshData* LoadMesh(const string &file);
private:
    static glm::vec2 parseLineAsVec2(const string &line, uint start);
    static glm::vec3 parseLineAsVec3(const string &line, uint start);
    static float parseFloat(const string &chars, uint start, uint end);
    static vector<glm::vec3> computePerVertexNormals(vector<glm::vec3>vn, vector<uint>vIndicies, vector<uint>vnIndicies);
};

#endif // MESHLOADER_H
