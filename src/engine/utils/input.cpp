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

#include "input.h"

Keyboard::Keyboard()
{
    m_keyState.reserve(m_numKeys);
    m_mouseState.reserve(m_numButtons);

    for(int i = 0; i < m_numKeys; i++)
    {
        m_keyState[i] = false;
    }

    for(int i = 0; i < m_numButtons; i++)
    {
        m_mouseState[i] = false;
    }
}

void Keyboard::update(SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN)
    {
        m_keyState[e->key.keysym.scancode] = true;
    }
    else if(e->type == SDL_KEYUP)
    {
        m_keyState[e->key.keysym.scancode] = false;
    }
    else if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        m_mouseState[e->button.button] = true;
    }
    else if(e->type == SDL_MOUSEBUTTONUP)
    {
        m_mouseState[e->button.button] = false;
    }
}
