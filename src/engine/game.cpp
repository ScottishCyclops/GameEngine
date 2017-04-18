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
    m_mouse = new Mouse(display->getWidth(),display->getHeight());
    m_camera = new Camera(glm::vec3(0,0,-10),55.f,display->getWidth(),display->getHeight(),0.01f,300);
    m_scene = new Scene();
}


void Game::initScene(float* timeDelta)
{
    m_i = 0;
    m_timeDelta = timeDelta;
    m_speed = 0.005f * (*m_timeDelta);
    m_camSensitivity = .04f * (*m_timeDelta);
    m_isMouseLocked = true;

    uint sphere = m_scene->addObject(SPHERE_M);
    m_scene->getObject(sphere)->scale(1);
    m_scene->getObject(sphere)->rotateY(0);

    uint pistol = m_scene->addObject(PISTOL_M);
    m_scene->getObject(pistol)->translate(0,0,-5);



    m_light = new SunLight;
    m_light->base.color = glm::vec3(1.f,1.f,1.f);
    m_light->base.intensity = 1.f;
    m_light->direction = glm::normalize(glm::vec3(0.f,0.f,1.f));
}


void Game::update()
{
    m_kb->update();

    while(SDL_PollEvent(&m_e) != 0)
    {
        if(m_e.type == SDL_QUIT)
        {
            isRunning = false;
        }
        else
        {
            m_kb->event(&m_e);
        }
    }

    if(m_isMouseLocked)
    {
        display->setCursorVisibility(false);
        mouseLook();
    }
    else
    {
        display->setCursorVisibility(true);
    }

    //keys
    if(m_kb->isKeyReleased(SDL_SCANCODE_ESCAPE))
    {
        isRunning = false;
    }
    if(m_kb->isKeyPressed(SDL_SCANCODE_TAB))
    {
        m_isMouseLocked = !m_isMouseLocked;
    }

    //keyboard motion
    if(m_kb->isKeyDown(SDL_SCANCODE_A))
    {
        m_camera->translate(X_AXIS,-m_speed);
    }
    if(m_kb->isKeyDown(SDL_SCANCODE_D))
    {
        m_camera->translate(X_AXIS,m_speed);
    }
    if(m_kb->isKeyDown(SDL_SCANCODE_W))
    {
        m_camera->translate(Z_AXIS,m_speed);
    }
    if(m_kb->isKeyDown(SDL_SCANCODE_S))
    {
        m_camera->translate(Z_AXIS,-m_speed);
    }
    if(m_kb->isKeyDown(SDL_SCANCODE_Q))
    {
        m_camera->translate(Y_AXIS,m_speed);
    }
    if(m_kb->isKeyDown(SDL_SCANCODE_E))
    {
        m_camera->translate(Y_AXIS,-m_speed);
    }

    if(m_kb->isKeyDown(SDL_SCANCODE_F))
    {
        m_light->base.intensity-=m_speed;
    }
    if(m_kb->isKeyDown(SDL_SCANCODE_G))
    {
        m_light->base.intensity+=m_speed;
    }
    if(m_kb->isKeyDown(SDL_SCANCODE_C))
    {
        m_scene->getObject(0)->rotateY(-m_speed);
    }
    if(m_kb->isKeyDown(SDL_SCANCODE_V))
    {
        m_scene->getObject(0)->rotateY(m_speed);
    }

}

void Game::mouseLook()
{
    //update mouse pos and acceleration
    glm::vec2 acc = Utils::getAcceleration(m_mouse->getLastPos(),m_mouse->getCurrentPos(),*m_timeDelta);

    m_camera->rotate(Y_AXIS,acc.x*m_camSensitivity);
    m_camera->rotate(X_AXIS,-acc.y*m_camSensitivity);


    m_mouse->resetPosition();
}

void Game::render()
{
    m_i+=.02f;

    //m_scene->getObject(0)->rotateY(.01);
    for(uint i  = 0; i < m_scene->getObjects()->size(); i++)
    {
        m_scene->getObject(i)->draw(m_camera,m_light);
    }
}

void Game::quit()
{
    display->close();
}
