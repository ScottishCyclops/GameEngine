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

class Mesh
{
private:
    vector<glm::vec3> m_positions;
    vector<glm::vec3> m_normals;
    vector<uint> m_ibo;
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
    Mesh(vector<glm::vec3> positions, vector<glm::vec3> normals, vector<uint> indicies);
    GLuint* getVao();
    uint getDrawCount();
    void destroy();
    ~Mesh();
};

class Object
{
private:
    uint m_typeId;
    uint m_index;
    Mesh* m_mesh;
    Shader* m_shader;
    Transform* m_transform;
public:
    Object(uint typeId, uint index, Mesh* mesh, Shader* shader);
    Object(uint typeId, uint index, Mesh* mesh, Shader* shader, Transform* transform);
    void draw(Camera *camera, glm::vec3 *lightDir);
    Transform* getTransform(){return m_transform;}

    void translate(float x, float y, float z);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void scale(float x, float y, float z);
    void scale(float w);

    glm::vec3* getLoc(){return &m_transform->loc;}
    glm::vec3* getRot(){return &m_transform->rot;}
    glm::vec3* getScale(){return &m_transform->scale;}
    uint getType(){return m_typeId;}
    uint getIndex(){return m_index;}

    void setLoc(glm::vec3 loc){m_transform->loc = loc;}
    void setRot(glm::vec3 rot){m_transform->rot = rot;}
    void setScale(glm::vec3 scale){m_transform->scale = scale;}

};

#endif // MESH_H
