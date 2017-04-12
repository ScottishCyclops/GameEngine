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

#include "engine/mesh/mesh.h"
#include "engine/utils/input.h"
#include "engine/utils/transform.h"
#include "engine/camera.h"
#include "engine/mesh/shader.h"
#include "engine/mesh/meshloader.h"

#include <QList>

class Game
{
private:
    SDL_Event m_e;
    Mouse* m_mouse;
    Keyboard* m_kb;
    Camera* m_camera;
    QList<MeshData*> m_meshData;
    vector<Mesh> m_meshes;

public:
    bool isRunning;

    Game();
    void loadMeshes();
    void update();
    void render();
};

#endif // GAME_H
