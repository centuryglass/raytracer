/*  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, 
 * University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of CS5721 Computer Graphics library (cs5721Graphics).
 *
 * cs5721Graphics is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cs5721Graphics is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with cs5721Graphics.  If not, see <http://www.gnu.org/licenses/>.
 * Modified by: Anthony Brown
 */


#ifndef __XMLCONTAINERCLASS__
#define __XMLCONTAINERCLASS__

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <set>
#include <string>
using namespace std;

#include "Vector3D.h"
#include "XMLSceneParser.h"
#include "TextureMap.h"
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "Shape.h"
#include "Shader.h"
using namespace sivelab;

class XMLContainerClass : public SceneElementCreator {
public:

    XMLContainerClass() {
        scene = new Scene();
    }

    ~XMLContainerClass() {
    }

    void instance(ptree::value_type const &v);
    void parseCameraData(ptree::value_type const &v);
    void parseShaderData(ptree::value_type const &v);
    void parseShapeData(ptree::value_type const &v);
    void parseLightData(ptree::value_type const &v);
    void parseTextureData(ptree::value_type const &v);
    void parseSceneData(ptree::value_type const &v);

    Scene * getScene() {
        return scene;
    }

    Camera * getCamera() {
        return camera;
    }

private:
    Camera * camera;
    Scene * scene;
    set<Shader*> shaders;
    set<TextureMap*> textureMaps;
    set<Shape*> instances;
    Shader * selectedShader;
    TextureMap * selectedTexture;
    Shape * meshFromObj(string fname);
    
};
#endif