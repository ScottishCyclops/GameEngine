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

#ifndef DISPLAY_H
#define DISPLAY_H

#include "libs.h"

class Display
{
private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    int m_width;
    int m_height;
    bool m_isOpen;
    bool m_cursorVisibility;
public:
    Display(int width, int height, const string &title);
    void clear();
    void swap();
    void close();

    void setTitle(const string &thing);
    void setClearColor(glm::vec3 color);
    bool getCursorVisibility(){return m_cursorVisibility;}
    void setCursorVisibility(bool visible);

    bool isOpen(){return m_isOpen;}
    int getWidth(){return m_width;}
    int getHeight(){return m_height;}

    ~Display();
};

#endif // DISPLAY_H
