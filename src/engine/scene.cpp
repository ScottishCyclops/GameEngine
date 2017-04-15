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

Scene::Scene() :
    m_meshes(NUM_MESHES),
    m_textures(NUM_TEXTURES),
    m_shaders(NUM_SHADERS)
{
    //initialize all mesh data that is going to be necessary later

    //meshes
    m_meshes[SMALL_ROCK_01_M] =
    {
        SMALL_ROCK_01_M,
        "rock.obgl",
        RUSSIAN_T,
        BASIC_S,
        0,
        NULL,
    };
    m_meshes[BIG_M] =
    {
        BIG_M,
        "big.obgl",
        SIMPLE_T,
        BASIC_S,
        0,
        NULL
    };
    m_meshes[PISTOL_M] =
    {
        PISTOL_M,
        "pistol.obgl",
        PISTOL_T,
        BASIC_S,
        0,
        NULL
    };
    m_meshes[ANO_M] =
    {
        ANO_M,
        "ano.obgl",
        ANO_T,
        BASIC_S,
        0,
        NULL
    };
    m_meshes[GROUND_M] =
    {
        GROUND_M,
        "ground.obgl",
        RUSSIAN_T,
        BASIC_S,
        0,
        NULL
    };

    //textures
    m_textures[PISTOL_T] =
    {
        PISTOL_T,
        "pistol.png",
        0,
        NULL
    };
    m_textures[RUSSIAN_T] =
    {
        RUSSIAN_T,
        "img.bmp",
        0,
        NULL
    };
    m_textures[ANO_T] =
    {
        ANO_T,
        "ano.png",
        0,
        NULL
    };
    m_textures[SIMPLE_T] =
    {
        SIMPLE_T,
        "simple.png",
        0,
        NULL
    };

    //shaders
    m_shaders[BASIC_S] =
    {
        BASIC_S,
        "basicShader",
        0,
        NULL,
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

void Scene::loadTex(uint id)
{
    m_textures[id].texture = new Texture(textureFolder+m_textures[id].fileName,id);
}

void Scene::unloadTex(uint id)
{
    m_textures[id].texture->destroy();
    m_textures[id].texture = NULL;
}

void Scene::loadShader(uint id)
{
    m_shaders[id].shader = new Shader(shaderFolder+m_shaders[id].fileName);
}

void Scene::unloadShader(uint id)
{
    m_shaders[id].shader->destroy();
    m_shaders[id].shader = NULL;
}

uint Scene::addObject(uint mesh)
{
    return addObject(mesh,-1,-1,new Transform);
}

uint Scene::addObject(uint mesh, int texture)
{
    return addObject(mesh,-1,texture,new Transform);
}

uint Scene::addObject(uint mesh, int shader, int texture)
{
    return addObject(mesh,shader,texture,new Transform);
}

uint Scene::addObject(uint mesh, int shader, int texture, Transform *transform)
{
    //undefined
    if(shader == -1)
    {
        shader = m_meshes[mesh].defaultShader;
    }
    if(texture == -1)
    {
        texture = m_meshes[mesh].defaultTex;
    }

    //if the mesh isn't loaded, we load it
    if(m_meshes[mesh].usage == 0)
    {
        loadMesh(mesh);
    }

    //same for the shader
    if(m_shaders[shader].usage == 0)
    {
        loadShader(shader);
    }

    //same for the tex
    if(m_textures[texture].usage == 0)
    {
        loadTex(texture);
    }

    m_meshes[mesh].usage++;
    m_shaders[shader].usage++;
    m_textures[texture].usage++;

    uint index = m_objects.size();

    m_objects.push_back(new Object(mesh,shader,texture,index,
                                   m_meshes[mesh].mesh,
                                   m_shaders[shader].shader,
                                   m_textures[texture].texture,
                                   transform));

    return index;
}

void Scene::removeObject(uint id)
{
    uint type = m_objects[id]->getMeshId();

    m_meshes[type].usage--;
    m_objects.erase(m_objects.begin()+id);

    //remove the mesh data because it is no longer beeing used
    if(m_meshes[type].usage == 0)
    {
        unloadMesh(type);
    }

    //TODO: remove tex and shader
}
