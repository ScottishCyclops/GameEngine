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

/*
Mesh* MeshLoader::LoadObjMesh(const string &file)
{
    ifstream objFile(file.c_str());

    //the data we are going to get
    vector<glm::vec3> importedV;
    vector<glm::vec2> importedVt;
    vector<glm::vec3> importedVn;
    vector<ushort> importedVIndicies;
    vector<ushort> importedVtIndicies;
    vector<ushort> importedVnIndicies;

    bool hasNormals = false;
    bool hasUvs = false;

    if(objFile.is_open())
    {

        for(string line; getline(objFile, line);)
        {
            //transforming to QString to have better comparaison fonctions
            const char* cLine = line.c_str();

            //if we found a vertex
            if(cLine[0] == 'v' && cLine[1] == ' ')
            {
                importedV.push_back(parseLineAsVec3(line,2));
            }
            //we found a texture coord
            else if(cLine[0] == 'v' && cLine[1] == 't')
            {
                hasUvs = true;
                importedVt.push_back(parseLineAsVec2(line,3));
            }
            //we found a normal
            else if(cLine[0] == 'v' && cLine[1] == 'n')
            {
                hasNormals = true;
                importedVn.push_back(parseLineAsVec3(line,3));
            }
            //we found a face
            else if(cLine[0] == 'f' && cLine[1] == ' ')
            {
                vector<string> values = Utils::splitStr(line,' ');
                //we skip the "f " we start at 1
                for(uint j = 1; j < values.size(); j++)
                {
                    vector<string> separatedValues = Utils::splitStr(values[j],'/');

                    importedVIndicies.push_back(  (ushort) Utils::strToInt(separatedValues[0]) -1 );
                    if(hasUvs)
                    {
                        importedVtIndicies.push_back( (ushort) Utils::strToInt(separatedValues[1]) -1 );
                        if(hasNormals)
                        {
                            importedVnIndicies.push_back( (ushort) Utils::strToInt(separatedValues[2]) -1 );
                        }
                    }
                    else if(hasNormals)
                    {
                        //if we don't have uvs but normals, they will be at index 1
                        importedVnIndicies.push_back( (ushort) Utils::strToInt(separatedValues[1]) -1 );
                    }
                }
            }
        }
    }
    else
    {
        cout << "E: File opening failure: " << file << endl;
        exit(-1);
    }

    //we compute the vertex normals for now
    vector<glm::vec3> normals = computeNormals(importedVIndicies,importedV);



    return new Mesh(importedV,normals,importedVt,importedVIndicies);
}
*/


Mesh* MeshLoader::LoadMesh(const string &file)
{
    ifstream objFile(file.c_str());

    vector<glm::vec3> v;
    vector<glm::vec3> n;
    vector<glm::vec2> t;
    vector<ushort>    f;

    bool hasNormals = false;
    bool hasUvs = false;

    if(objFile.is_open())
    {

        for(string line; getline(objFile, line);)
        {
            const char* cLine = line.c_str();
            int lenght = line.length();

            if(cLine[0] == 'o')
            {
                //the comment, we ignore it
            }
            else if(cLine[0] == 'v')
            {
                //the locations array
                parseLineAsVec3(line.substr(2,lenght),&v);
            }
            else if(cLine[0] == 'n')
            {
                //the normals array
                hasNormals = true;
                parseLineAsVec3(line.substr(2,lenght),&n);
            }
            else if(cLine[0] == 't')
            {
                //the uvs array
                hasUvs = true;
                parseLineAsVec2(line.substr(2,lenght),&t);
            }
            else if(cLine[0] == 'f')
            {
                //the faces array
                parseLineAsShorts(line.substr(2,lenght),&f);
            }
        }
    }
    else
    {
        cout << "E: file opening failure: " << file << endl;
        exit(1);
    }

    if(!hasNormals)
    {
        n = computeNormals(f,v);
    }

    if(!hasUvs)
    {
        t = genFakeUvs(f.size());
    }

    return new Mesh(v,n,t,f);
}

void MeshLoader::parseLineAsVec3(const string &line, vector<glm::vec3>* vec)
{
    vector<string> data = Utils::splitStr(line,' ');
    for(uint i = 0; i < data.size(); i+=3)
    {
        vec->push_back(glm::vec3(Utils::strToFloat(data[i]),Utils::strToFloat(data[i+1]),Utils::strToFloat(data[i+2])));
    }
}
void MeshLoader::parseLineAsVec2(const string &line, vector<glm::vec2>* vec)
{
    vector<string> data = Utils::splitStr(line,' ');
    for(uint i = 0; i < data.size(); i+=2)
    {
        vec->push_back(glm::vec2(Utils::strToFloat(data[i]),Utils::strToFloat(data[i+1])));
    }
}
void MeshLoader::parseLineAsShorts(const string &line, vector<ushort>* vec)
{
    vector<string> data = Utils::splitStr(line,' ');
    for(uint i = 0; i < data.size(); i++)
    {
        vec->push_back(Utils::strToUshort(data[i]));
    }
}

vector<glm::vec3> MeshLoader::computeNormals(vector<ushort> vIndices, vector<glm::vec3> v)
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

vector<glm::vec2> MeshLoader::genFakeUvs(uint amount)
{
    vector<glm::vec2> fakeUvs;

    for(uint i = 0; i < amount; i++)
    {
        fakeUvs.push_back(glm::vec2(0,0));
    }

    return fakeUvs;
}

/*
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

*/
