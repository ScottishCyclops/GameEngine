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
const string textureFolder = resFolder+"/textures/";
const string shaderFolder = resFolder+"/shaders/";

enum Meshes
{
    SMALL_ROCK_01_M,
    BIG_M,
    PISTOL_M,
    ANO_M,
    GROUND_M,

    NUM_MESHES
};

enum Shaders
{
    BASIC_S,

    NUM_SHADERS
};

enum Textures
{
    PISTOL_T,
    RUSSIAN_T,
    ANO_T,
    SIMPLE_T,

    NUM_TEXTURES
};

struct MeshInfo
{
    uint id;
    string fileName;
    uint defaultTex;
    uint defaultShader;
    uint usage;
    Mesh* mesh;
};

//can't have more than 32 textures !
struct TexInfo
{
    uint id;
    string fileName;
    uint usage;
    Texture* texture;
};

struct ShaderInfo
{
    uint id;
    string fileName;
    uint usage;
    Shader* shader;
};


class Scene
{
private:
    vector<MeshInfo> m_meshes;
    vector<TexInfo> m_textures;
    vector<ShaderInfo> m_shaders;
    vector<Object*> m_objects;

    void loadMesh(uint id);
    void unloadMesh(uint id);

    void loadTex(uint id);
    void unloadTex(uint id);

    void loadShader(uint id);
    void unloadShader(uint id);

public:
    Scene();
    void updateMeshCache();

    uint addObject(uint mesh);
    uint addObject(uint mesh, int texture);
    uint addObject(uint mesh, int shader, int texture);
    uint addObject(uint mesh, int shader, int texture, Transform* transform);
    void removeObject(uint id);
    vector<Object*>* getObjects(){return &m_objects;}
    Object* getObject(uint id){return m_objects[id];}

};

#endif // SCENE_H
