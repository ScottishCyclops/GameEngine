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

#include "mesh.h"

//MeshData

MeshData::MeshData(vector<glm::vec3> positions, vector<glm::vec3> normals, vector<uint> indicies)
{
    m_positions = positions;
    m_normals = normals;
    m_indicies = indicies;

    glGenVertexArrays(1, &m_vao);
    //setting which array we are going to affect with the following code
    glBindVertexArray(m_vao);

    //allocate memory on the gpu for our vertices location
    glGenBuffers(NUM_BUFFERS, m_vbo);

    //Position buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_positions.size() * sizeof(m_positions[0]),&m_positions[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_VB);
    glVertexAttribPointer(POSITION_VB,3,GL_FLOAT,GL_FALSE,0,0);

    //Normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(m_normals[0]),&m_normals[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_VB);
    glVertexAttribPointer(NORMAL_VB,3,GL_FLOAT,GL_FALSE,0,0);

    //Indicies buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(m_indicies[0]),&m_indicies[0],GL_STATIC_DRAW);

    //stop affecting our vertex array
    glBindVertexArray(0);
}

GLuint* MeshData::getVao()
{
    return &m_vao;
}

uint MeshData::getDrawCount()
{
    return (uint)m_indicies.size();
}

MeshData::~MeshData()
{
    glDeleteVertexArrays(1, &m_vao);
}

//Mesh

Mesh::Mesh(MeshData* data, Transform *transform, Shader* shader)
{
    m_data = data;
    m_transform = transform;
    m_shader = shader;
}

Mesh::Mesh(MeshData* data, Shader* shader)
{
    m_data = data;
    m_transform = new Transform;
    m_shader = shader;
}


void Mesh::draw(Camera* camera)
{
    m_shader->use();
    m_shader->update(m_transform,camera);

    glBindVertexArray(*m_data->getVao());

    glDrawElements(GL_TRIANGLES,m_data->getDrawCount(),GL_UNSIGNED_INT,0);

    glBindVertexArray(0);
}
