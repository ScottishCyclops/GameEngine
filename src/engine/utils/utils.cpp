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

#include "utils.h"

vector<string> Utils::splitStr(const string &str, const char &delim)
{
    vector<string> elements;

    uint nextStart = 0;

    const char* cStr = str.c_str();
    uint strLenght = str.length();

    for(uint i = 0; i < strLenght; i++)
    {
        if(cStr[i] == delim)
        {
            elements.push_back(str.substr(nextStart,i-nextStart));
            //+1 to not take the space
            nextStart = i+1;
        }
        else if(i == strLenght-1)
        {
            elements.push_back(str.substr(nextStart,strLenght));
        }
    }

    return elements;
}

int Utils::strToInt(string str)
{
    return (int)atof(str.c_str());
}
