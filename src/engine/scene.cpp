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
    m_materials(NUM_MATERIALS),
    m_shaders(NUM_SHADERS),
    m_pointLights(MAX_POINTS_LIGHT)
{
    //initialize all mesh data that is going to be necessary later

    //meshes
    m_meshes[SMALL_ROCK_01_M] =
    {
        SMALL_ROCK_01_M,
        "rock.obgl",
        RUSSIAN_ML,
        ADVANCED_S,
        0,
        NULL,
    };
    m_meshes[BIG_M] =
    {
        BIG_M,
        "big.obgl",
        RUSSIAN_ML,
        ADVANCED_S,
        0,
        NULL
    };
    m_meshes[PISTOL_M] =
    {
        PISTOL_M,
        "pistol.obgl",
        PISTOL_ML,
        ADVANCED_S,
        0,
        NULL
    };
    m_meshes[ANO_M] =
    {
        ANO_M,
        "ano.obgl",
        ANO_ML,
        ADVANCED_S,
        0,
        NULL
    };
    m_meshes[GROUND_M] =
    {
        GROUND_M,
        "ground.obgl",
        RUSSIAN_ML,
        ADVANCED_S,
        0,
        NULL
    };
    m_meshes[SPHERE_M] =
    {
        SPHERE_M,
        "sphere.obgl",
        RUSSIAN_ML,
        ADVANCED_S,
        0,
        NULL
    }; 

    m_meshes[GUN_M] =
    {
        GUN_M,
        "gun.obgl",
        GUN_ML,
        ADVANCED_S,
        0,
        NULL
    };

    //textures
    m_materials[PISTOL_ML] =
    {
        PISTOL_ML,
        "pistol.png",
        0,
        NULL
    };
    m_materials[RUSSIAN_ML] =
    {
        RUSSIAN_ML,
        "img.bmp",
        0,
        NULL
    };
    m_materials[ANO_ML] =
    {
        ANO_ML,
        "ano.png",
        0,
        NULL
    };
    m_materials[SIMPLE_ML] =
    {
        SIMPLE_ML,
        "simple.png",
        0,
        NULL
    };
    m_materials[GUN_ML] =
    {
        GUN_ML,
        "gun.png",
        0,
        NULL
    };

    //shaders
    m_shaders[BASIC_S] =
    {
        BASIC_S,
        "basic",
        0,
        NULL,
    };
    m_shaders[ADVANCED_S] =
    {
        ADVANCED_S,
        "advanced",
        0,
        NULL,
    };

    //lights
    PointLight* p1 = new PointLight;
    p1->base.color = glm::vec3(1.f,1.f,1.f);
    p1->base.intensity = 0.;
    p1->attenuation.constant = 1;
    p1->attenuation.exponent = 0;
    p1->attenuation.linear = 0;
    p1->position = glm::vec3(-1.f,2.f,10.f);
    m_pointLights[0] = p1;

    PointLight* p2 = new PointLight;
    p2->base.color = glm::vec3(1.f,0.f,0.f);
    p2->base.intensity = 1.;
    p2->attenuation.constant = 1;
    p2->attenuation.exponent = 0;
    p2->attenuation.linear = 0;
    p2->position = glm::vec3(0.f,0.f,0.f);
    m_pointLights[1] = p2;

    m_pointLights[2] = p1;
    m_pointLights[3] = p1;

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

void Scene::loadMaterial(uint id)
{
    m_materials[id].material = new Material(new Texture(textureFolder+m_materials[id].fileName,id),2.f);
}

void Scene::unloadMaterial(uint id)
{
    m_materials[id].material->destroy();
    m_materials[id].material = NULL;
}

void Scene::loadShader(uint id)
{
    m_shaders[id].shader = new Shader(shaderFolder+m_shaders[id].fileName);
    //TODO: choose the 4 closest lights
    //TODO: do a loop
    m_shaders[id].shader->setPointLight(0,m_pointLights[0]);
    m_shaders[id].shader->setPointLight(1,m_pointLights[1]);
    m_shaders[id].shader->setPointLight(2,m_pointLights[2]);
    m_shaders[id].shader->setPointLight(3,m_pointLights[3]);
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

uint Scene::addObject(uint mesh, int material)
{
    return addObject(mesh,-1,material,new Transform);
}

uint Scene::addObject(uint mesh, int shader, int material)
{
    return addObject(mesh,shader,material,new Transform);
}

uint Scene::addObject(uint mesh, int shader, int material, Transform *transform)
{
    //undefined
    if(shader == -1)
    {
        shader = m_meshes[mesh].defaultShader;
    }
    if(material == -1)
    {
        material = m_meshes[mesh].defaultMat;
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
    if(m_materials[material].usage == 0)
    {
        loadMaterial(material);
    }

    m_meshes[mesh].usage++;
    m_shaders[shader].usage++;
    m_materials[material].usage++;

    uint index = m_objects.size();

    m_objects.push_back(new Object(mesh,shader,material,index,
                                   m_meshes[mesh].mesh,
                                   m_shaders[shader].shader,
                                   m_materials[material].material,
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
