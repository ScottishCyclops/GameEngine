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

Game::Game(Display* display)
{
    Game::display = display;

    isRunning = false;
    m_kb = new Keyboard();
    m_mouse = new Mouse();
    m_camera = new Camera(glm::vec3(0,.5,-5),55.f,display->getWidth(),display->getHeight(),0.01f,300);
    m_scene = new Scene();
    m_i = 0;
}


void Game::initScene()
{
    m_shader = new Shader(resFolder+"/shaders/basicShader");

    m_scene->addObject(SMALL_ROCK_01_M,m_shader,new Transform);

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

    if(m_kb->isMouseDown(SDL_BUTTON_LEFT))
    {
        Transform* trans = new Transform(m_mouse->toWorldSpace(m_mouse->getPos(),m_camera));
        m_scene->addObject(SMALL_ROCK_01_M,m_shader,trans);
    }

}

void Game::render()
{
    glm::vec3* light = new glm::vec3(.5,-.8,.1);

     m_scene->getObjects()->at(0)->rotateY(.01f);
    for(uint i  = 0; i < m_scene->getObjects()->size(); i++)
    {
        m_scene->getObjects()->at(i)->draw(m_camera,light);
    }
    /*

    m_i+=.02f;
    //light->x = sin(m_i);
    //light->y = cos(m_i);

    m_meshes[1].translate(0,0,sin(m_i)/6.f);

    m_meshes[0].draw(m_camera,light);
    m_meshes[1].draw(m_camera,light);
    */
}

void Game::quit()
{
    display->close();
}
