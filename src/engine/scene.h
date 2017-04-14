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

#ifndef SCENE_H
#define SCENE_H

#include "libs.h"
#include "engine/mesh/mesh.h"
#include "engine/mesh/meshloader.h"
#include "engine/texture/texture.h"

const string meshFolder = resFolder+"/meshes/";

enum
{
    SMALL_ROCK_01_M,
    TEXTURED_CUBE_M,
    BIG_M,
    SPHERE_M,

    NUM_MESHES
};

struct MeshInfo
{
    uint id;
    string fileName;
    uint usage;
    Mesh* mesh;
};


class Scene
{

public:
    Scene();
    void updateMeshCache();
    Object* addObject(uint id, Shader* shader, Texture* texture);
    Object* addObject(uint id, Shader* shader, Texture* texture, Transform* transform);
    void removeObject(Object *object);
    vector<Object*>* getObjects(){return &m_objects;}

private:
    vector<MeshInfo> m_meshes;
    vector<Object*> m_objects;

    void loadMesh(uint id);
    void unloadMesh(uint id);
};

#endif // SCENE_H
