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

#include "scene.h"

Scene::Scene() : m_meshes(NUM_MESHES)
{
    //initialize all mesh data that is going to be necessary later

    m_meshes[SMALL_ROCK_01_M] =
    {
        SMALL_ROCK_01_M,
        "rock.obgl",
        0,
        NULL
    };

    m_meshes[BIG_M] =
    {
        BIG_M,
        "big.obgl",
        0,
        NULL
    };

    m_meshes[TEST_M] =
    {
        TEST_M,
        "test.obgl",
        0,
        NULL
    };

    m_meshes[PISTOL_M] =
    {
        PISTOL_M,
        "pistol.obgl",
        0,
        NULL
    };

    m_meshes[ANO_M] =
    {
        ANO_M,
        "ano.obgl",
        0,
        NULL
    };
}

/**
 * @brief Loads the actual mesh data from disk onto the GPU
 * @param id : id of the meshdata we want to load
 */
void Scene::loadMesh(uint id)
{
    m_meshes[id].mesh = MeshLoader::LoadMesh(meshFolder+m_meshes[id].fileName);
}

/**
 * @brief Removes the mesh data from the GPU. Sets the pointer of the meshdata to NULL
 * @param id : id of the meshdata we want to remove
 */
void Scene::unloadMesh(uint id)
{
    m_meshes[id].mesh->destroy();
    m_meshes[id].mesh = NULL;
}

void Scene::addObject(uint id, Shader* shader)
{
    return addObject(id,shader,new Texture("dummy"),new Transform);
}

void Scene::addObject(uint id, Shader* shader, Texture* texture)
{
    return addObject(id,shader,texture,new Transform);
}

void Scene::addObject(uint id, Shader* shader, Texture* texture, Transform *transform)
{
    //if the mesh isn't loaded, we load it
    if(m_meshes[id].usage == 0)
    {
        loadMesh(id);
    }
    m_meshes[id].usage++;

    m_objects.push_back(new Object(id, m_objects.size(), m_meshes[id].mesh,shader,texture,transform));
}

void Scene::removeObject(Object* object)
{
    m_meshes[object->getType()].usage--;
    m_objects.erase(m_objects.begin()+object->getIndex());

    //remove the mesh data because it is no longer beeing used
    if(m_meshes[object->getType()].usage == 0)
    {
        unloadMesh(object->getType());
    }
}
