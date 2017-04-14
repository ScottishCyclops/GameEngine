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
    //static Mesh* LoadObjMesh(const string &file);
    static Mesh* LoadMesh(const string &file);
private:
    static void parseLineAsVec2(const string &line, vector<glm::vec2>* vec);
    static void parseLineAsVec3(const string &line, vector<glm::vec3>* vec);
    static void parseLineAsShorts(const string &line, vector<ushort>* vec);
    //static float parseFloat(const string &chars, uint start, uint end);
    static vector<glm::vec3> computeNormals(vector<ushort> vIndices, vector<glm::vec3> v);
    static vector<glm::vec2> genFakeUvs(uint amount);
    /*
    static void reIndexUvsAndNormals(bool hasUvs,
                                     bool hasNormals,
                                     vector<glm::vec3> v,
                                     vector<glm::vec2> vt,
                                     vector<glm::vec3> vn,
                                     vector<ushort> vIndicies,
                                     vector<ushort> vtIndicies,
                                     vector<ushort> vnIndicies,
                                     vector<glm::vec3>* outLocations,
                                     vector<glm::vec3>* outNormals,
                                     vector<glm::vec2>* outUVs);

    static bool compareVerticies(bool hasUvs, bool hasNormals, glm::vec3* loc1, glm::vec3* norm1, glm::vec2* uv1, glm::vec3* loc2, glm::vec3* norm2, glm::vec2* uv2);
    */
};

#endif // MESHLOADER_H
