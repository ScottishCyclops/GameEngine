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

#include "game.h"

Game::Game()
{
    isRunning = false;
    m_kb = new Keyboard();
    m_mouse = new Mouse();
    m_camera = new Camera(glm::vec3(0,0,-5),70,800.f/600.f,0.01f,1000);
}

void Game::loadMeshes()
{
    //Shader shader("../resources/shaders/basicShader");
    Shader* shader = new Shader("../resources/shaders/basicShader");

    vector<glm::vec3> pos =
    {
        glm::vec3(1,-1,0),
        glm::vec3(0,1,0),
        glm::vec3(-1,-1,0)
    };
    vector<glm::vec3> norm =
    {
        glm::vec3(0,0,-1),
        glm::vec3(0,0,-1),
        glm::vec3(0,0,-1)
    };
    vector<uint> i = {0,1,2};

    MeshData* md = new MeshData(pos,norm,i);
    m_meshData.append(md);
    m_meshData.append(MeshLoader::LoadMesh("../resources/meshes/cube.obj"));


    Mesh mesh(m_meshData[0],shader);
    Mesh mesh2(m_meshData[1],shader);
    mesh.getTransform()->scale = glm::vec3(.3,.3,.3);
    mesh2.getTransform()->loc.x+=1;

    m_meshes.push_back(mesh);
    m_meshes.push_back(mesh2);

}

void Game::update()
{
    while(SDL_PollEvent(&m_e) != 0)
    {
        if(m_e.type == SDL_QUIT)
        {
            isRunning = false;
        }
        else
        {
            m_kb->update(&m_e);
        }
    }

    if(m_kb->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        isRunning = false;
    }

}

void Game::render()
{
    m_meshes[0].getTransform()->rot.y+=.05;
    m_meshes[0].draw(m_camera);
    m_meshes[1].draw(m_camera);
}
