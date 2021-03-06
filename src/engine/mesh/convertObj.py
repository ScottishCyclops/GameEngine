#!/usr/bin/python3
# -*- coding: UTF-8 -*-
'''
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
'''
import sys
import os

OUT_EXT = ".obgl"

# data
comment = ""
v = []
vt = []
vn = []

# indicies
vi = []
vti = []
vni = []

hasNormals = False
hasUvs = False

#TODO: transform class to a dict
class Vertex:
    def __init__(self, loc, norm, uv):
        self.loc = loc
        self.norm = norm
        self.uv = uv

def parseLine(string, separator, start = None, end = None):
    """returns a list of elements from a string, with a separator, from a given index"""
    if start == None:
        start = 0
    if end == None:
        end = len(string)
    return string[start:end].split(separator)


def importObj(file):
    """Imports all the data from an Obj file"""
    global comment
    global v
    global vt
    global vn
    global vi
    global vti
    global vni
    global hasNormals
    global hasUvs

    #TODO: handle triangulation
    #TODO: hangle multi-object files

    # r -> read mode
    with open(file, "r") as f:
        content = f.read()
    f.close()
    lines = content.splitlines()

    for line in lines:
        if line.startswith("v "):
            #3ds max exporter uses 2 spaces
            if("  " in line):
                data = parseLine(line," ",3)
            else:
                data = parseLine(line," ",2)
            v.append((float(data[0]), float(data[1]), float(data[2])))

        elif line.startswith("vt "):
            hasUvs = True
            data = parseLine(line," ",3)
            vt.append((float(data[0]), float(data[1])))

        elif line.startswith("vn "):
            hasNormals = True
            data = parseLine(line," ",3)
            vn.append((float(data[0]), float(data[1]), float(data[2])))

        elif line.startswith("f "):
            #3ds max exporter ends lines with space
            if line.endswith(" "):
                data = parseLine(line," ",2,-1)
            else:
                data = parseLine(line," ",2)
            #some exporters use 2 slashes
            separator = "/"
            if "//" in line:
                separator = "//"
            for d in data:
                x = parseLine(d,separator)
                vi.append(int(x[0]) - 1)
                if hasUvs:
                    vti.append(int(x[1]) - 1)
                    if hasNormals:
                        vni.append(int(x[2]) - 1)
                elif hasNormals:
                    vni.append(int(x[1]) - 1)

        elif line.startswith("o "):
            comment = line


def convertObj():
    """returns a tuple of 2 lists with the vertex data and the faces from the converted Obj data"""

    outV = []
    outVi = []

    if not hasNormals and not hasUvs:
        for i in range(0, len(vi)):
            outV.append(Vertex(v[vi[i]], None, None))
            outVi.append(i)

    else:
        for i in range(0, len(vi)):
            # creates a new vertex from the face list
            if hasNormals and hasUvs:
                newVert = Vertex(v[vi[i]], vn[vni[i]], vt[vti[i]])
            elif hasNormals:
                newVert = Vertex(v[vi[i]], vn[vni[i]], None)
            elif hasUvs:
                newVert = Vertex(v[vi[i]], None, vt[vti[i]])

            #test if the new vertex already exists
            if newVert in outV:
                #if it exists, we use it
                outVi.append(outV.index(newVert))
            else:
                #otherwise, we append it and use it
                outVi.append(len(outV))
                outV.append(newVert)

    return (outV, outVi)


def toString(dataTuple):
    """Converts the informations to a string and returns it"""
    output = str(comment) + "\n"
    verticies = dataTuple[0]
    faces = dataTuple[1]

    """Structure :
    comment
    v x y z x y z ...
    n x y z x y z ...
    t x y x y ...
    f x x ...
    """

    # location output
    output += "v "
    for vert in verticies:
        data = str(vert.loc[0]) + " " + str(vert.loc[1]) + \
            " " + str(vert.loc[2]) + " "
        output += data
    # remove last unwanted space
    output = output[0:-1]
    output += "\n"

    # normal output
    if hasNormals:
        output += "n "
        for vert in verticies:
            data = str(vert.norm[0]) + " " + str(vert.norm[1]
                                                 ) + " " + str(vert.norm[2]) + " "
            output += data
        # remove last unwanted space
        output = output[0:-1]
        output += "\n"

     # uvs output
    if hasUvs:
        output += "t "
        for vert in verticies:
            data = str(vert.uv[0]) + " " + str(vert.uv[1]) + " "
            output += data
        # remove last unwanted space
        output = output[0:-1]
        output += "\n"

    # face output
    output += "f "
    for face in faces:
        data = str(face) + " "
        output += data
    # remove last unwanted space
    output = output[0:-1]
    output += "\n"

    return output


def writeOutput(file, string):
    """writes the string to the file"""

    with open(file, "w+") as f:
        f.write(string)


def main():
    #checking parameters
    if len(sys.argv) == 1:
        print("Usage: ./convertObj.py ./file.obj\nAdd any second argument to overwrite existing output.")
        sys.exit(0)
    inFile = sys.argv[1]

    overwrite = False
    if len(sys.argv) > 2:
        overwrite = True

    if not inFile.endswith(".obj"):
        print("Incompatible file")
        sys.exit(1)
    if not os.path.isfile(inFile):
        print("File does not exist")
        sys.exit(1)

    #checking output file
    outFile = inFile[0:-4] + OUT_EXT
    if os.path.isfile(outFile) and not overwrite:
        print("Output already exists, aborting")
        sys.exit(0)

    importObj(inFile)

    print("loc:  ", len(v))
    print("uvs:  ", len(vt))
    print("norm: ", len(vn))

    print("faces:", len(vi))

    print("starting conversion...")
    writeOutput(outFile, toString(convertObj()))
    print("all done!")


if __name__ == "__main__":
    main()
