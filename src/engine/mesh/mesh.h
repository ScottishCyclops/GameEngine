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

#ifndef MESH_H
#define MESH_H

#include "libs.h"

#include "engine/utils/transform.h"
#include "engine/mesh/shader.h"

class MeshData
{
private:
    vector<glm::vec3> m_positions;
    vector<glm::vec3> m_normals;
    vector<uint> m_indicies;
    enum
    {
        POSITION_VB,
        NORMAL_VB,
        INDEX_VB,
        NUM_BUFFERS,
    };
    GLuint m_vao;
    GLuint m_vbo[NUM_BUFFERS];
public:
    MeshData(vector<glm::vec3> positions, vector<glm::vec3> normals, vector<uint> indicies);
    MeshData(const string &file);
    GLuint* getVao();
    uint getDrawCount();
    ~MeshData();
};

class Mesh
{
private:
    Transform* m_transform;
    MeshData* m_data;
    Shader* m_shader;
public:
    Mesh(MeshData* data, Transform* transform, Shader* shader);
    Mesh(MeshData* data, Shader* shader);
    void draw(Camera *camera);
    Transform* getTransform(){return m_transform;}
};

#endif // MESH_H
