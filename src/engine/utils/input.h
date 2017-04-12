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

#ifndef INPUT_H
#define INPUT_H

#include "libs.h"

class Mouse
{
public:
    static glm::vec2 getPos()
    {
        int x;
        int y;
        SDL_GetMouseState(&x,&y);
        return glm::vec2(x,y);
    }
    static void setMousePos(int x, int y)
    {
        SDL_WarpMouseInWindow(NULL,x,y);
    }
    static glm::vec2 toScreenSpace(glm::vec2 coord, int width, int height)
    {
        glm::vec2 space(0,0);
        space.x = -((coord.x/width*2)-1);
        space.y = -((coord.y/height*2)-1);

        return space;
    }
};

class Keyboard
{
private:
    static const int m_numKeys = 256;
    static const int m_numButtons = 3;
    vector<bool> m_keyState;
    vector<bool> m_mouseState;
public:
    Keyboard();
    void update(SDL_Event* e);

    bool isKeyDown(int keyCode)
    {
        return m_keyState[keyCode];
    }
    bool isKeyUp(int keyCode)
    {
        return !m_keyState[keyCode];
    }
    bool isMouseDown(int buttonCode)
    {
        return m_mouseState[buttonCode];
    }
    bool isMouseUp(int buttonCode)
    {
        return m_mouseState[buttonCode];
    }
};

#endif // INPUT_H
