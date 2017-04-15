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

Keyboard::Keyboard() :
    m_keyState(m_numKeys),
    m_lastKeyState(m_numKeys),
    m_buttonState(m_numButtons),
    m_lastButtonState(m_numButtons)
{

    for(uint i = 0; i < m_numKeys; i++)
    {
        m_keyState[i] = false;
        m_lastKeyState[i] = false;
    }

    for(uint i = 0; i < m_numButtons; i++)
    {
        m_buttonState[i] = false;
        m_lastButtonState[i] = false;
    }
}

void Keyboard::update()
{
    for(uint i = 0; i < m_numKeys; i++)
    {
        m_lastKeyState[i] = m_keyState[i];
    }
    for(uint i = 0; i < m_numButtons; i++)
    {
        m_lastButtonState[i] = m_buttonState[i];
    }
}

void Keyboard::event(SDL_Event *e)
{
    SDL_Scancode* keyCode = &e->key.keysym.scancode;
    unsigned char* buttonCode = &e->button.button;

    if(e->type == SDL_KEYDOWN)
    {
        m_keyState[*keyCode] = true;
    }
    else if(e->type == SDL_KEYUP)
    {
        m_keyState[*keyCode] = false;
    }
    else if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        m_buttonState[*buttonCode] = true;
    }
    else if(e->type == SDL_MOUSEBUTTONUP)
    {
        m_buttonState[*buttonCode] = false;
    }
}
