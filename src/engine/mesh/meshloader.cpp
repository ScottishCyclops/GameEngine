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

#include "meshloader.h"

Mesh* MeshLoader::LoadMesh(const string &file)
{
    ifstream objFile(file.c_str());

    //the data we are going to get
    vector<glm::vec3> v;
    vector<glm::vec2> vt;
    vector<glm::vec3> vn;
    vector<uint> vIndicies;
    vector<uint> vtIndicies;
    vector<uint> vnIndicies;

    bool hasNormals = false;
    bool hasUVs = false;

    for(string line; getline(objFile, line);)
    {
        //transforming to QString to have better comparaison fonctions
        const char* cLine = line.c_str();

        //if we found a vertex
        if(cLine[0] == 'v' && cLine[1] == ' ')
        {
            v.push_back(parseLineAsVec3(line,2));
        }
        //we found a texture coord
        else if(cLine[0] == 'v' && cLine[1] == 't')
        {
            hasUVs = true;
            vt.push_back(parseLineAsVec2(line,3));
        }
        //we found a normal
        else if(cLine[0] == 'v' && cLine[1] == 'n')
        {
            hasNormals = true;
            vn.push_back(parseLineAsVec3(line,3));
        }
        //we found a face
        else if(cLine[0] == 'f' && cLine[1] == ' ')
        {
            vector<string> values = Utils::splitStr(line,' ');
            //we skip the "f " we start at 1
            for(uint j = 1; j < values.size(); j++)
            {
                vector<string> separatedValues = Utils::splitStr(values[j],'/');

                vIndicies.push_back(  (uint) Utils::strToInt(separatedValues[0]) -1 );
                if(hasUVs)
                {
                    vtIndicies.push_back( (uint) Utils::strToInt(separatedValues[1]) -1 );
                    if(hasNormals)
                    {
                        vnIndicies.push_back( (uint) Utils::strToInt(separatedValues[2]) -1 );
                    }
                }
                else if(hasNormals)
                {
                    //if we don't have uvs but normals, they will be at index 1
                    vnIndicies.push_back( (uint) Utils::strToInt(separatedValues[1]) -1 );
                }
            }
        }
    }

    //we compute the vertex normals for now
    vector<glm::vec3> normals = computeNormals(vIndicies,v);

    return new Mesh(v,normals,vIndicies);
}

glm::vec2 MeshLoader::parseLineAsVec2(const string &line, uint start)
{
    uint lineLenght = line.length();
    const char* cLine = line.c_str();

    uint spaceIndex = 0;
    uint valuesStartIndex = start;

    for(uint i = valuesStartIndex; i < lineLenght; i++)
    {
        if(cLine[i] == ' ')
        {
            spaceIndex = i;
            break;
        }
    }

    float x = parseFloat(line,valuesStartIndex,spaceIndex);
    float y = parseFloat(line,spaceIndex+1,lineLenght);

    return glm::vec2(x,y);
}

glm::vec3 MeshLoader::parseLineAsVec3(const string &line, uint start)
{
    uint lineLenght = line.length();
    const char* cLine = line.c_str();

    vector<uint> spaceIndices;
    uint valuesStartIndex = start;

    for(uint i = valuesStartIndex; i < lineLenght; i++)
    {
        if(cLine[i] == ' ')
            spaceIndices.push_back(i);
    }

    float x = parseFloat(line,valuesStartIndex,spaceIndices[0]);
    float y = parseFloat(line,spaceIndices[0]+1,spaceIndices[1]);
    float z = parseFloat(line,spaceIndices[1]+1,lineLenght);

    return glm::vec3(x,y,z);
}

float MeshLoader::parseFloat(const string &chars, uint start, uint end)
{
    return (float)atof(chars.substr(start,end-start).c_str());
}

vector<glm::vec3> MeshLoader::computeNormals(vector<uint> vIndices, vector<glm::vec3> v)
{
    vector<glm::vec3> normals(v.size());

    for(uint i = 0; i < vIndices.size(); i+=3)
    {
        int i0 = vIndices[i  ];
        int i1 = vIndices[i+1];
        int i2 = vIndices[i+2];

        glm::vec3 v1 = v[i1] - v[i0];
        glm::vec3 v2 = v[i2] - v[i0];

        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

        normals[i0] += normal;
        normals[i1] += normal;
        normals[i2] += normal;
    }

    for(uint i = 0; i < v.size(); i++)
        normals[i] = glm::normalize(normals[i]);

    return normals;
}
