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

//Mesh

Mesh::Mesh(vector<glm::vec3> positions, vector<glm::vec3> normals, vector<glm::vec2> uvs, vector<ushort> indicies)
{
    m_positions = positions;
    m_normals = normals;
    m_uvs = uvs;
    m_ibo = indicies;

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

    //UV buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[UV_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(m_uvs[0]),&m_uvs[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(UV_VB);
    glVertexAttribPointer(UV_VB,2,GL_FLOAT,GL_FALSE,0,0);

    //Indicies buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_ibo.size() * sizeof(m_ibo[0]),&m_ibo[0],GL_STATIC_DRAW);

    //stop affecting our vertex array
    glBindVertexArray(0);
}

GLuint* Mesh::getVao()
{
    return &m_vao;
}

uint Mesh::getDrawCount()
{
    return (ushort)m_ibo.size();
}

void Mesh::destroy()
{
    glDeleteVertexArrays(1, &m_vao);
}

Mesh::~Mesh()
{
    destroy();
}

//Object

Object::Object(uint meshId, uint shaderId, uint matId, uint index, Mesh* mesh, Shader* shader, Material* material, Transform* transform)
{
    m_meshId = meshId;
    m_shaderId = shaderId;
    m_matId = matId;
    m_index = index;

    m_mesh = mesh;
    m_shader = shader;
    m_mat = material;
    m_transform = transform;
}

void Object::draw(Camera* camera, SunLight* light)
{
    Texture::unBind();

    m_shader->use();
    m_shader->update(m_transform,camera,light,m_mat);

    //if we have specified a texture
    if(m_mat->getDiffuse() != NULL)
    {
        m_mat->getDiffuse()->use();
    }

    glBindVertexArray(*m_mesh->getVao());

    //UNSIGNED SHORT takes less memory than unsigned int
    glDrawElements(GL_TRIANGLES,m_mesh->getDrawCount(),GL_UNSIGNED_SHORT,0);

    glBindVertexArray(0);
}

//transformation methods

void Object::translate(float x, float y, float z)
{
    m_transform->loc.x+=x;
    m_transform->loc.y+=y;
    m_transform->loc.z+=z;
}

void Object::translate(glm::vec3 translation)
{
    m_transform->loc+=translation;
}

void Object::rotateX(float angle)
{
    m_transform->rot.x+=angle;
}

void Object::rotateY(float angle)
{
    m_transform->rot.y+=angle;
}

void Object::rotateZ(float angle)
{
    m_transform->rot.z+=angle;
}

void Object::scale(float x, float y, float z)
{
    m_transform->scale.x*=x;
    m_transform->scale.y*=y;
    m_transform->scale.z*=z;
}

void Object::scale(float w)
{
    m_transform->scale*= w;
}
/*
void Object::rotate(float angle, glm::vec3 axis)
{
    m_transform->getModel()
}
*/
