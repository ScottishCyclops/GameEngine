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

#include "texture.h"
#include <cassert>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

Texture::Texture(const string &path)
{
    m_path = path;
    if(m_path != "dummy")
    {
        int width, height, componants;
        unsigned char* data = stbi_load(path.c_str(),&width,&height,&componants,4);

        if(data == NULL)
        {
            cout << "E: Texture loading failure: " << path << endl;
            return;
        }

        Texture::width = width;
        Texture::height = height;

        glGenTextures(1,&m_glTexture);
        glBindTexture(GL_TEXTURE_2D,m_glTexture);

        //set the texture to repeating
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

        //filtering
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Texture::width,Texture::height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

        stbi_image_free(data);
    }
}

void Texture::use(uint unit)
{
    if(m_path != "dummy")
    {
        assert(unit <= 31);

        glActiveTexture(GL_TEXTURE0+unit);
        glBindTexture(GL_TEXTURE_2D,m_glTexture);
    }
}

Texture::~Texture()
{
    if(m_path != "dummy")
    {
        glDeleteTextures(1,&m_glTexture);
    }
}
