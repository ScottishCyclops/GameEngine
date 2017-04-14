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

#include "display.h"

Display::Display(int width, int height, const string &title)
{
    m_isOpen = false;
    m_width = width;
    m_height = height;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetSwapInterval(0);

    m_window = SDL_CreateWindow(title.c_str(),0,0,width,height,SDL_WINDOW_OPENGL);
    if(m_window == NULL)
    {
        cout << "E: Window creation failure" << endl;
    }

    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        cout << "E : GLEW initialization failure: " << glewGetErrorString(status) << endl;
    }

    //OpenGL options

    glClearColor(.1f,.1f,.1f,1);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //gamma correction
    //glEnable(GL_FRAMEBUFFER_SRGB);

    cout << "I: OpenGL " << glGetString(GL_VERSION) << endl;
    cout << "I: SDL " << +SDL_MAJOR_VERSION << "." << +SDL_MINOR_VERSION << "."  << +SDL_PATCHLEVEL << endl;
    m_isOpen = true;
}

void Display::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::swap()
{
    SDL_GL_SwapWindow(m_window);
}

void Display::close()
{
    m_isOpen = false;
}

void Display::setTitle(const string &thing)
{
    SDL_SetWindowTitle(m_window,thing.c_str());
}

Display::~Display()
{
    if(m_isOpen)
    {
        cout << "W: Destroying display while opened" << endl;
    }

    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
