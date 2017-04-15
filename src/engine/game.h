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

#ifndef GAME_H
#define GAME_H

#include "libs.h"

#include "engine/utils/input.h"
#include "engine/camera.h"
#include "engine/display.h"
#include "engine/scene.h"

class Game
{
private:
    Shader* m_shader;
    Texture* m_tex;
    SDL_Event m_e;
    Mouse* m_mouse;
    Keyboard* m_kb;
    Camera* m_camera;
    Scene* m_scene;

    float m_i;
    float m_speed;
    float m_camSensitivity;
    float* m_timeDelta;
    bool m_isMouseLocked;

public:
    Display* display;
    bool isRunning;

    Game(Display *display);
    void initScene(float* timeDelta);
    void update();
    void mouseLook();
    void render();
    void quit();
};

#endif // GAME_H
