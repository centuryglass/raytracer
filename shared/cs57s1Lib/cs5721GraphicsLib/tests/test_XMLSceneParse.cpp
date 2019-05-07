/*
 *  test_XMLSceneParse.cpp
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
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
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cassert>

#include "Vector3D.h"
#include "XMLSceneParser.h"
#include "handleGraphicsArgs.h"

using namespace sivelab;

// Here's an example

class CameraCreator : public SceneElementCreator
{
public:
  CameraCreator() {}
  ~CameraCreator() {}

  void instance( ptree::value_type const &v )
  {
    std::istringstream buf;

    std::string name, type;
    Vector3D position, viewDir, lookatPoint;
    bool lookatSet = false;
    float focalLength;
    float imagePlaneWidth;

    name = v.second.get<std::string>("<xmlattr>.name");
    type = v.second.get<std::string>("<xmlattr>.type");

    buf.str( v.second.get<std::string>("position") );
    buf >> position;
    buf.clear();

    // LookAtPoint and ViewDir are optional, but one should be specified.
    boost::optional<std::string> plookatPoint = v.second.get_optional<std::string>("lookatPoint");
    boost::optional<std::string > pviewDir = v.second.get_optional<std::string>("viewDir");

    if (plookatPoint) {
      lookatSet = true;
      buf.str( *plookatPoint );
      buf >> lookatPoint; 
      buf.clear();
    } else if (pviewDir) {
      buf.str( *pviewDir );
      buf >> viewDir; 
      buf.clear();
    }

    buf.str( v.second.get<std::string>("focalLength") );
    buf >> focalLength;
    buf.clear();

    buf.str( v.second.get<std::string>("imagePlaneWidth") );
    buf >> imagePlaneWidth;
    buf.clear();

    std::cout << "Camera: name=" << name << ", type=" << type << std::endl;
    std::cout << "\tposition: " << position << std::endl;
    if (lookatSet)
      std::cout << "\tlook at point: " << lookatPoint << std::endl;
    else 
      std::cout << "\tview direction: " << viewDir << std::endl;
    std::cout << "\tfocal length: " << focalLength << std::endl;
    std::cout << "\timage plane width: " << imagePlaneWidth << std::endl;
  }

private:
};

class ContainerClass : public SceneElementCreator
{
public:
  ContainerClass() {}
  ~XMLContainerClass() {}

  void instance( ptree::value_type const &v )
  {
    //
    // Light
    //
    if (v.first == "light") {
      // Do what is necessary to pull out the light...
    }


    // 
    // Shader
    // 
    if (v.first == "shader") {
      parseShaderData(v);
    }

    // 
    // Shape or Instance
    // 
    if (v.first == "shape") {
      parseShapeData(v);
    }
  }

  void parseShapeData( ptree::value_type const &v )
  {
    std::string type, name;
    type = v.second.get<std::string>("<xmlattr>.type");
    name = v.second.get<std::string>("<xmlattr>.name");

    // Make sure to find the shader data objects; HAVE to include a
    // shader in this version; Need to find the shader in the second part
    // of the shape pair
    ptree::const_assoc_iterator it = v.second.find("shader");
    if( it != v.second.not_found() )
      {
	parseShaderData( *it );
      }
    
    std::istringstream buf;

    if (type == "sphere") {
      float radius;
      sivelab::Vector3D center;

      buf.str( v.second.get<std::string>("center") );
      buf >> center;
      buf.clear();

      radius = v.second.get<float>("radius");
    }

    if (type == "box") {
      sivelab::Vector3D minPt, maxPt;

      buf.str( v.second.get<std::string>("minPt") );
      buf >> minPt;
      buf.clear();

      buf.str( v.second.get<std::string>("maxPt") );
      buf >> maxPt;
      buf.clear();
    }

    if (type == "triangle") {
      sivelab::Vector3D v0, v1, v2;
      
      buf.str( v.second.get<std::string>("v0") );
      buf >> v0;
      buf.clear();
      
      buf.str( v.second.get<std::string>("v1") );
      buf >> v1;
      buf.clear();

      buf.str( v.second.get<std::string>("v2") );
      buf >> v2;
      buf.clear();
    }
  }

  void parseShaderData( ptree::value_type const &v )
  {
    std::istringstream buf;

    std::string type, name;
    boost::optional<std::string> optShaderRef = v.second.get_optional<std::string>("<xmlattr>.ref");

    if (!optShaderRef) {
      type = v.second.get<std::string>("<xmlattr>.type");
      name = v.second.get<std::string>("<xmlattr>.name");
    }
    // else 
    // std::cout << "Found optional shader ref: " << *optShaderRef << std::endl;

    // if name exists in the shader map and this is a ref, return the shader pointer
    // otherwise, add the shader if it NOT a ref and the name doesn't exist
    // final is to throw error
    if (!optShaderRef) {

      // Did not find the shader and it was not a reference, so create and return
      
      if (type == "Lambertian") {
	sivelab::Vector3D kd;
	buf.str( v.second.get<std::string>("diffuse") );
	buf >> kd;
	buf.clear();
      }
      else if (type == "BlinnPhong" || type == "Phong") {
	sivelab::Vector3D kd;
	sivelab::Vector3D ks;
	float phongExp;

	buf.str( v.second.get<std::string>("diffuse") );
	buf >> kd;
	buf.clear();

	buf.str( v.second.get<std::string>("specular") );
	buf >> ks;
	buf.clear();

	phongExp = v.second.get<float>("phongExp");
      }
    }
  }

private:

};


int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);

  XMLSceneParser xmlScene;

  // register object creation function with xmlScene
  xmlScene.registerCallback("camera", new CameraCreator);

  xmlScene.registerCallback("light", new ContainerClass);
  xmlScene.registerCallback("shader", new ContainerClass);
  xmlScene.registerCallback("shape", new ContainerClass);

  if (args.inputFileName != "")
    xmlScene.parseFile( args.inputFileName );
  else
    {
      std::cerr << "Need input file!" << std::endl;
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}


