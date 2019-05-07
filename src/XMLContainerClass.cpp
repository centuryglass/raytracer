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

#include "XMLContainerClass.h"

#include "textures/ImageTexture.h"
#include "textures/FlatTexture.h"
#include "textures/PerlinNoiseTexture.h"
#include "textures/MarbleTexture.h"

#include "cameras/PerspectiveCamera.h"
#include "cameras/OrthographicCamera.h"
#include "cameras/SphereCamera.h"


#include "shapes/Triangle.h"
#include "shapes/Sphere.h"
#include "shapes/Box.h"
#include "shapes/InstancedObject.h"
#include "shapes/Mesh.h"
#include "BoundingBox.h"


#include "shaders/NormalMapShader.h"
#include "shaders/LambertianShader.h"
#include "shaders/PhongShader.h"
#include "shaders/BlinnPhongShader.h"
#include "shaders/FlatShader.h"
#include "shaders/DielectricShader.h"
#include "shaders/PortalShader.h"
#include "shaders/MultiReflectionShader.h"
#include "shaders/CombinationShader.h"
#include "Matrix4x4.h"
#include "Basis.h"
#include "AreaLight.h"
using namespace ablib;
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <limits>
#include <vector>
using namespace std;

void XMLContainerClass::instance(ptree::value_type const &v) {
    if (v.first == "camera") {
        parseCameraData(v);
    }
    if (v.first == "light") {
        parseLightData(v);
    }
    // Shader 
    if (v.first == "shader") {
        parseShaderData(v);
    }
    // Shape or Instance
    if (v.first == "shape" || v.first == "instance") {
        parseShapeData(v);
    }
    if (v.first == "texture") {
        parseTextureData(v);
    }
    if (v.first == "sceneParameters") {
        parseSceneData(v);
    }
}

void XMLContainerClass::parseCameraData(ptree::value_type const &v) {
    istringstream buf;

    string name, type;
    Vector3D position, viewDir, lookatPoint;
    bool lookatSet = false;
    float focalLength;
    float imagePlaneWidth;

    name = v.second.get<string>("<xmlattr>.name");
    type = v.second.get<string>("<xmlattr>.type");

    buf.str(v.second.get<string>("position"));
    buf >> position;
    buf.clear();

    // LookAtPoint and ViewDir are optional, but one should be specified.
    boost::optional<string> plookatPoint =
            v.second.get_optional<string>("lookatPoint");
    boost::optional<string > pviewDir =
            v.second.get_optional<string>("viewDir");

    if (plookatPoint) {
        lookatSet = true;
        buf.str(*plookatPoint);
        buf >> lookatPoint;
        buf.clear();
    } else if (pviewDir) {
        buf.str(*pviewDir);
        buf >> viewDir;
        buf.clear();
    }

    buf.str(v.second.get<string>("focalLength"));
    buf >> focalLength;
    buf.clear();

    buf.str(v.second.get<string>("imagePlaneWidth"));
    buf >> imagePlaneWidth;
    buf.clear();

    if (type == "perspective") {
        if (lookatSet) {
            camera = new PerspectiveCamera
                    (position, lookatPoint, focalLength, imagePlaneWidth);
            camera->setLookAtPoint(lookatPoint);
        } else {
            camera = new PerspectiveCamera
                    (position, viewDir, focalLength, imagePlaneWidth);
        }
    } else if (type == "orthographic") {
        if (lookatSet) {
            camera = new OrthographicCamera
                    (position, lookatPoint, focalLength, imagePlaneWidth);
            camera->setLookAtPoint(lookatPoint);
        } else {
            camera = new OrthographicCamera
                    (position, viewDir, focalLength, imagePlaneWidth);
        }
    } else if (type == "sphere") {
        if (lookatSet) {
            camera = new SphereCamera
                    (position, lookatPoint, focalLength, imagePlaneWidth);
            camera->setLookAtPoint(lookatPoint);
        } else {
            camera = new SphereCamera
                    (position, viewDir, focalLength, imagePlaneWidth);
        }
    } else {
        cout << "Warning, unrecognized camera type " << type
                << ". Using perspective camera.";
        if (lookatSet) {
            camera = new PerspectiveCamera
                    (position, lookatPoint, focalLength, imagePlaneWidth);
            camera->setLookAtPoint(lookatPoint);
        } else {
            camera = new PerspectiveCamera
                    (position, viewDir, focalLength, imagePlaneWidth);
        }
    }
    boost::optional<float> depth =
            v.second.get_optional<float>("depthOfField");
    if(depth){
        camera->setDepthOfField(*depth);
        float lensRadius = v.second.get<float>("lensRadius");
        camera->setLensRadius(lensRadius);
    }
    camera->setName(name);
}

void XMLContainerClass::parseShapeData(ptree::value_type const &v) {
    string type, name;
    type = v.second.get<string>("<xmlattr>.type");
    name = v.second.get<string>("<xmlattr>.name");
    Shape * shape;



    istringstream buf;
    if (type == "sphere") {
        float radius;
        sivelab::Vector3D center;

        buf.str(v.second.get<string>("center"));
        buf >> center;
        buf.clear();

        radius = v.second.get<float>("radius");
        shape = new Sphere(center, radius);
    }

    if (type == "box") {
        sivelab::Vector3D minPt, maxPt;

        buf.str(v.second.get<string>("minPt"));
        buf >> minPt;
        buf.clear();

        buf.str(v.second.get<string>("maxPt"));
        buf >> maxPt;

        buf.clear();
        shape = new Box(minPt, maxPt);
    }

    if (type == "triangle") {
        sivelab::Vector3D v0, v1, v2;

        buf.str(v.second.get<string>("v0"));
        buf >> v0;
        buf.clear();

        buf.str(v.second.get<string>("v1"));
        buf >> v1;
        buf.clear();

        buf.str(v.second.get<string>("v2"));
        buf >> v2;
        buf.clear();
        shape = new Triangle(v0, v1, v2);
    }
    if (type == "mesh") {
        string fName = v.second.get<string>("file");
        shape = meshFromObj(fName);
    }
    if (type == "instance") {
        Shape * s;
        string base = v.second.get<string>("<xmlattr>.id");
        for (set<Shape*>::iterator it = instances.begin();
                it != instances.end(); ++it) {
            if ((*it)->getName() == base) {
                s = *it;
            }
        }
        if (s == NULL)cout << "Error: base not found!\n";
        ptree::const_assoc_iterator it = v.second.find("transform");

        Matrix4x4 matrix;
        for (int i = 0; i < 4; i++) {
            matrix[i][i] = 1;
        }
        for (ptree::const_iterator it2 = it->second.begin();
                it2 != it->second.end(); ++it2) {
            string transform = it2->first;

            if (transform == "translate") {
                Matrix4x4 m;
                Vector3D trans;
                buf.str(it2->second.get_value<string>());
                buf >> trans;
                for (int i = 0; i < 4; i++) {
                    m[i][i] = 1;
                }
                m[3][0] = trans[0];
                m[3][1] = trans[1];
                m[3][2] = trans[2];
                m[3][3] = 1;
                buf.clear();
                matrix *= m;
            } else if (transform == "scale") {
                Matrix4x4 m;
                Vector3D scale;
                buf.str(it2->second.get_value<string>());
                buf >> scale;
                m[0][0] = scale[0];
                m[1][1] = scale[1];
                m[2][2] = scale[2];
                m[3][3] = 1;

                matrix *= m;
                buf.clear();
            } else if (transform == "rotate") {
                Matrix4x4 m;
                boost::optional<string> ax =
                        it2->second.get_optional<string>("<xmlattr>.axis");
                string axis;
                if (ax) axis = *ax;
                else {
                    axis = "X";
                    cout << "axis not found: assuming X axis\n";
                }
                double angle = it2->second.get_value<double>();
                angle /= 180;
                angle *= 3.14159;
                Basis b;
                Vector3D basisVector;
                if (axis == "X") {
                    basisVector.set(1, 0, 0);
                    //                    m[0][0] = 1;
                    //                    m[1][1] = cos(angle);
                    //                    m[2][1] = -1* sin(angle);
                    //                    m[1][2] = sin(angle);
                    //                    m[2][2] = cos(angle);
                    //                    m[3][3] = 1;
                } else if (axis == "Y") {
                    basisVector.set(0, 1, 0);
                    //                    m[0][0] = cos(angle);
                    //                    m[2][0] = sin(angle);
                    //                    m[1][1] = 1;
                    //                    m[0][2] = -1*sin(angle);
                    //                    m[2][2] = cos(angle);
                    //                    m[3][3] = 1;
                } else if (axis == "Z") {
                    basisVector.set(0, 0, 1);
                    //                    m[0][0] = cos(angle);
                    //                    m[1][0] = -1*sin(angle);
                    //                    m[0][1] = sin(angle);
                    //                    m[1][1] = cos(angle);
                    //                    m[2][2] = 1;
                    //                    m[3][3] = 1;
                }
                b.calculateBasis(basisVector);
                m[0][0] = b.getU()[0];
                m[1][0] = b.getV()[0];
                m[2][0] = b.getW()[0];

                m[0][1] = b.getU()[1];
                m[1][1] = b.getV()[1];
                m[2][1] = b.getW()[1];

                m[0][2] = b.getU()[2];
                m[1][2] = b.getV()[2];
                m[2][2] = b.getW()[2];
                m[3][3] = 1;

                Matrix4x4 inv = m.inverse();

                Matrix4x4 rot;
                rot[0][0] = cos(angle);
                rot[1][0] = -1 * sin(angle);
                rot[0][1] = sin(angle);
                rot[1][1] = cos(angle);
                rot[2][2] = 1;
                rot[3][3] = 1;

                m *= rot;
                m *= inv;

                matrix *= m;
            }
        }
        shape = new InstancedObject(s, matrix);
    }
    ptree::const_assoc_iterator it = v.second.find("shader");
    if (it != v.second.not_found()) {
        parseShaderData(*it);
        shape->setShader(selectedShader);
    }
    shape->setName(name);
    if (v.first == "instance")instances.insert(shape);
    else scene->insertShape(shape);
}

void XMLContainerClass::parseShaderData(ptree::value_type const &v) {
    istringstream buf;
    string type, name;
    Vector3D kd;
    Vector3D ks;
    TextureMap * tSpec;
    TextureMap * tDif;
    float phongExp;
    Shader * s;

    boost::optional<string> optShaderRef =
            v.second.get_optional<string>("<xmlattr>.ref");

    if (!optShaderRef) {
        type = v.second.get<string>("<xmlattr>.type");
        name = v.second.get<string>("<xmlattr>.name");
    } else {
        for (set<Shader*>::iterator it = shaders.begin();
                it != shaders.end(); ++it) {
            if ((*it)->getName() == *optShaderRef) {
                selectedShader = *it;
            }
        }
    }
    if (!optShaderRef) {
        // Did not find the shader and it was not a reference, 
        //so create and return
        if (type == "Lambertian" || type == "Glaze" || type == "MultiReflect") {
            buf.str(v.second.get<string>("diffuse"));
            buf >> kd;
            selectedTexture = new FlatTexture(kd);

            ptree::const_assoc_iterator it = v.second.find("diffuse");
            if (it != v.second.not_found()) {
                boost::optional<string> optTextureRef =
                        it->second.get_optional<string>("<xmlattr>.tex");
                if (optTextureRef) {
                    parseTextureData(*it);
                    selectedTexture->setColor(kd);
                }
            }
            if (type == "Glaze" || type == "MultiReflect") {
                double mirrorCoef;
                mirrorCoef = v.second.get<float>("mirrorCoef");
                if (type == "MultiReflect") {
                    int count = v.second.get<int>("reflectionCount");
                    s = new MultiReflectionShader
                            (selectedTexture, mirrorCoef, count, scene->useShadow);

                } else
                    s = new LambertianShader
                        (selectedTexture, mirrorCoef, scene->useShadow);


            } else s = new LambertianShader(selectedTexture, scene->useShadow);
            buf.clear();

        } else if (type == "Combination") {
            s = new CombinationShader();
            ptree::const_assoc_iterator it = v.second.find("shaders");

            for (ptree::const_iterator it2 = it->second.begin();
                    it2 != it->second.end(); ++it2) {
                string shader = it2->second.get<string>("<xmlattr>.ref");
                for (set<Shader*>::iterator it3 = shaders.begin();
                        it3 != shaders.end(); ++it3) {
                    if ((*it3)->getName() == shader) {
                        selectedShader = *it3;
                    }
                }
                double strength = it2->second.get_value<double>();
                pair<Shader *, double> p;
                p.first = selectedShader;
                p.second = strength;
                ((CombinationShader *) s)->addShader(p);
            }
        } else if (type == "Dielectric") {
            double refractiveIndex = v.second.get<float>("refractiveIndex");
            Vector3D attenuationCoef(1, 1, 1);
            ptree::const_assoc_iterator it = v.second.find("attenuationCoef");
            if (it != v.second.not_found()) {
                buf.str(v.second.get<string>("attenuationCoef"));
                buf >> attenuationCoef;
            }
            s = new DielectricShader(refractiveIndex);
            ((DielectricShader *) s)->setAttenuation(attenuationCoef);
        } else if (type == "BlinnPhong" || type == "Phong"
                || type == "BlinnPhongMirrored") {
            buf.str(v.second.get<string>("diffuse"));
            buf >> kd;
            tDif = new FlatTexture(kd);
            ptree::const_assoc_iterator it = v.second.find("diffuse");
            if (it != v.second.not_found()) {
                boost::optional<string> optTextureRef =
                        it->second.get_optional<string>("<xmlattr>.tex");
                if (optTextureRef) {

                    parseTextureData(*it);
                    selectedTexture->setColor(kd);
                    tDif = selectedTexture;
                }
            }

            buf.clear();

            buf.str(v.second.get<string>("specular"));
            buf >> ks;
            tSpec = new FlatTexture(ks);
            ptree::const_assoc_iterator it2 = v.second.find("specular");
            if (it2 != v.second.not_found()) {
                boost::optional<string> optTextureRef =
                        it2->second.get_optional<string>("<xmlattr>.tex");
                if (optTextureRef) {
                    parseTextureData(*it2);
                    selectedTexture->setColor(ks);
                    tSpec = selectedTexture;
                }
            }
            buf.clear();

            phongExp = v.second.get<float>("phongExp");

            if (type == "Phong") {
                s = new PhongShader(tDif, tSpec, phongExp, scene->useShadow);
            } else if (type == "BlinnPhong" || type == "BlinnPhongMirrored") {

                it = v.second.find("mirrorCoef");
                if (it != v.second.not_found()) {
                    double mirrorCoef;
                    mirrorCoef = v.second.get<float>("mirrorCoef");
                    s = new BlinnPhongShader
                            (tDif, tSpec, phongExp, mirrorCoef, scene->useShadow);
                } else s = new BlinnPhongShader
                        (tDif, tSpec, phongExp, scene->useShadow);
            } else s = new NormalMapShader();

            it = v.second.find("roughness");
            if (it != v.second.not_found()) {
                double roughness = v.second.get<double>("roughness");
                ((BlinnPhongShader *) s)->setRoughness(roughness);
            }

        } else if (type == "Mirror") {
            Vector3D bl(1, 1, 1);
            TextureMap * blank = new FlatTexture(bl);
            TextureMap * blank2 = new FlatTexture(bl);
            s = new BlinnPhongShader(blank, blank2, 1, 1, scene->useShadow);
        } else if (type == "Flat") {
            buf.str(v.second.get<string>("color"));
            buf >> kd;
            selectedTexture = new FlatTexture(kd);

            ptree::const_assoc_iterator it = v.second.find("color");
            if (it != v.second.not_found()) {
                boost::optional<string> optTextureRef =
                        it->second.get_optional<string>("<xmlattr>.tex");
                if (optTextureRef) {
                    parseTextureData(*it);
                    selectedTexture->setColor(kd);
                }
            }
            s = new FlatShader(selectedTexture);
            buf.clear();
        } else if (type == "Portal") {
            ptree::const_assoc_iterator it = v.second.find("transform");

            Matrix4x4 matrix;
            for (int i = 0; i < 4; i++) {
                matrix[i][i] = 1;
            }
            for (ptree::const_iterator it2 = it->second.begin();
                    it2 != it->second.end(); ++it2) {
                string transform = it2->first;

                if (transform == "translate") {
                    Matrix4x4 m;
                    Vector3D trans;
                    buf.str(it2->second.get_value<string>());
                    buf >> trans;
                    for (int i = 0; i < 4; i++) {
                        m[i][i] = 1;
                    }
                    m[3][0] = trans[0];
                    m[3][1] = trans[1];
                    m[3][2] = trans[2];
                    m[3][3] = 1;
                    buf.clear();
                    matrix *= m;
                } else if (transform == "scale") {
                    Matrix4x4 m;
                    Vector3D scale;
                    buf.str(it2->second.get_value<string>());
                    buf >> scale;
                    m[0][0] = scale[0];
                    m[1][1] = scale[1];
                    m[2][2] = scale[2];
                    m[3][3] = 1;

                    matrix *= m;
                    buf.clear();
                } else if (transform == "rotate") {
                    Matrix4x4 m;
                    boost::optional<string> ax =
                            it2->second.get_optional<string>("<xmlattr>.axis");
                    string axis;
                    if (ax) axis = *ax;
                    else {
                        axis = "X";
                        cout << "axis not found: assuming X axis\n";
                    }
                    double angle = it2->second.get_value<double>();
                    angle /= 180;
                    angle *= 3.14159;
                    Basis b;
                    Vector3D basisVector;
                    if (axis == "X") {
                        basisVector.set(1, 0, 0);
                        //                    m[0][0] = 1;
                        //                    m[1][1] = cos(angle);
                        //                    m[2][1] = -1* sin(angle);
                        //                    m[1][2] = sin(angle);
                        //                    m[2][2] = cos(angle);
                        //                    m[3][3] = 1;
                    } else if (axis == "Y") {
                        basisVector.set(0, 1, 0);
                        //                    m[0][0] = cos(angle);
                        //                    m[2][0] = sin(angle);
                        //                    m[1][1] = 1;
                        //                    m[0][2] = -1*sin(angle);
                        //                    m[2][2] = cos(angle);
                        //                    m[3][3] = 1;
                    } else if (axis == "Z") {
                        basisVector.set(0, 0, 1);
                        //                    m[0][0] = cos(angle);
                        //                    m[1][0] = -1*sin(angle);
                        //                    m[0][1] = sin(angle);
                        //                    m[1][1] = cos(angle);
                        //                    m[2][2] = 1;
                        //                    m[3][3] = 1;
                    }
                    b.calculateBasis(basisVector);
                    m[0][0] = b.getU()[0];
                    m[1][0] = b.getV()[0];
                    m[2][0] = b.getW()[0];

                    m[0][1] = b.getU()[1];
                    m[1][1] = b.getV()[1];
                    m[2][1] = b.getW()[1];

                    m[0][2] = b.getU()[2];
                    m[1][2] = b.getV()[2];
                    m[2][2] = b.getW()[2];
                    m[3][3] = 1;

                    Matrix4x4 inv = m.inverse();

                    Matrix4x4 rot;
                    rot[0][0] = cos(angle);
                    rot[1][0] = -1 * sin(angle);
                    rot[0][1] = sin(angle);
                    rot[1][1] = cos(angle);
                    rot[2][2] = 1;
                    rot[3][3] = 1;

                    m *= rot;
                    m *= inv;

                    matrix *= m;
                }
            }
            s = new PortalShader(matrix);
        } else {
            s = new NormalMapShader();
        }
        s->setName(name);
        shaders.insert(s);
        selectedShader = s;
    }
}

void XMLContainerClass::parseLightData(ptree::value_type const &v) {

    string type = v.second.get<string>("<xmlattr>.type");
    istringstream buf;
    Vector3D position, intensity;
    buf.str(v.second.get<string>("position"));
    buf >> position;
    buf.clear();


    buf.str(v.second.get<string>("intensity"));
    buf >> intensity;
    buf.clear();

    Light * l;

    if (type == "area") {
        Vector3D normal;
        buf.str(v.second.get<string>("normal"));
        buf >> normal;
        buf.clear();

        double width = v.second.get<double>("width");
        double length = v.second.get<double>("length");
        l = new AreaLight(position, intensity, normal, width, length);


    } else l = new Light(position, intensity);
    scene->insertLight(l);


}

void XMLContainerClass::parseTextureData(ptree::value_type const &v) {
    istringstream buf;

    string type, name;
    boost::optional<string> optTextureRef =
            v.second.get_optional<string>("<xmlattr>.tex");

    if (!optTextureRef) {
        type = v.second.get<string>("<xmlattr>.type");
        name = v.second.get<string>("<xmlattr>.name");
    } else {
        for (set<TextureMap*>::iterator it = textureMaps.begin();
                it != textureMaps.end(); ++it) {
            if ((*it)->getName() == *optTextureRef) {
                selectedTexture = *it;
            }
        }
    }
    if (!optTextureRef) {
        TextureMap * t;
        // Did not find the shader and it was not a reference, 
        //so create and return

        if (type == "image") {
            string sf;
            buf.str(v.second.get<string>("sourcefile"));
            buf >> sf;
            t = new ImageTexture(sf);
            buf.clear();

            boost::optional<float> tileRate =
                    v.second.get_optional<float>("tileRate");
            if (tileRate) {
                t->setTileRate(*tileRate);
            }

        } else if (type == "PerlinNoise") {
            t = new PerlinNoiseTexture();
        } else if (type == "Marble") {
            t = new MarbleTexture();
        } else {
            t = new FlatTexture();
        }
        t->setName(name);
        textureMaps.insert(t);
        selectedTexture = t;
    }
}

void XMLContainerClass::parseSceneData(ptree::value_type const &v) {
    istringstream buf;
    Vector3D sceneColor;
    buf.str(v.second.get<string>("bgColor"));
    buf >> sceneColor;
    buf.clear();

    ptree::const_assoc_iterator it = v.second.find("bgColor");
    if (it != v.second.not_found()) {
        boost::optional<string> optTextureRef =
                it->second.get_optional<string>("<xmlattr>.tex");
        if (optTextureRef) {
            parseTextureData(*it);
            selectedTexture->setColor(sceneColor);
            Vector3D minPt(-9999, -9999, -9999);
            Vector3D maxPt(9999, 9999, 9999);
            Shape * skyBox = new Box(minPt, maxPt);
            skyBox->setName("skyBox");
            Shader * skyShade = new FlatShader(selectedTexture);
            skyShade->setName("skyShade");
            skyBox->setShader(skyShade);
            scene->insertShape(skyBox);
        }
    }
    it = v.second.find("envMapPrefix");
    if (it != v.second.not_found()) {
        string prefix = v.second.get<string>("envMapPrefix");
        Shape * nx, * ny, * nz, * px, * py, * pz;
        Shader * snx, * sny, * snz, * spx, * spy, * spz;
        TextureMap * tnx, * tny, * tnz, * tpx, * tpy, * tpz;

        Vector3D minPt(-9999, -9999, -9999);
        Vector3D maxPt(-9998, 9999, 9999);
        nx = new Box(minPt, maxPt);
        maxPt.set(9999, -9998, 9999);
        ny = new Box(minPt, maxPt);
        maxPt.set(9999, 9999, -9998);
        nz = new Box(minPt, maxPt);
        maxPt.set(9999, 9999, 9999);

        minPt.set(9998, -9999, -9999);
        px = new Box(minPt, maxPt);
        minPt.set(-9999, 9998, -9999);
        py = new Box(minPt, maxPt);
        minPt.set(-9999, -9999, 9998);
        pz = new Box(minPt, maxPt);

        Vector3D tCol(1, 1, 1);
        tnx = new ImageTexture(prefix + "negX.png");
        tnx->setColor(tCol);
        snx = new FlatShader(tnx);
        nx->setShader(snx);
        scene->insertShape(nx);
        tny = new ImageTexture(prefix + "negY.png");
        tny->setColor(tCol);
        sny = new FlatShader(tny);
        ny->setShader(sny);
        scene->insertShape(ny);
        tnz = new ImageTexture(prefix + "negZ.png");
        tnz->setColor(tCol);
        snz = new FlatShader(tnz);
        nz->setShader(snz);
        scene->insertShape(nz);

        tpx = new ImageTexture(prefix + "posX.png");
        tpx->setColor(tCol);
        spx = new FlatShader(tpx);
        px->setShader(spx);
        scene->insertShape(px);
        tpy = new ImageTexture(prefix + "posY.png");
        tpy->setColor(tCol);
        spy = new FlatShader(tpy);
        py->setShader(spy);
        scene->insertShape(py);
        tpz = new ImageTexture(prefix + "posZ.png");
        tpz->setColor(tCol);
        spz = new FlatShader(tpz);
        pz->setShader(spz);
        scene->insertShape(pz);


    }
    scene->setColor(sceneColor);
}

Shape * XMLContainerClass::meshFromObj(string fname) {
    Mesh * m = new Mesh();
    //line number, <s,t>
    std::map <int, pair <double, double> > textureList;
    //3d coordinate index,texture index
    std::vector <set<pair<int, int > > > indexList;
    std::vector<Vector3D> vertexList;

    BoundingBox bBox;

    std::cerr << "Parsing render file: " << fname << "..." << std::endl;

    std::ifstream obj_file(fname.c_str());
    if (obj_file.is_open() == false) {
        std::cerr << "Error opening file \""
                << fname << "\".  Exiting." << std::endl;
        exit(1);
    }

    vertexList.push_back(sivelab::Vector3D(0, 0, 0));

    int linemax = 1024;
    char *linebuf = new char[ linemax ];
    int texnum = 1;
    while (obj_file.good() && !obj_file.eof()) {

        // read a line off the file and append to string list
        obj_file.getline(linebuf, linemax);

        std::istringstream is(linebuf);

        string keystring;
        is >> keystring;

        if (keystring == "v") {
            double x, y, z;
            is >> x >> y >> z;
            vertexList.push_back(sivelab::Vector3D(x, y, z));
        } else if (keystring == "f") {
            set <pair <int, int> > face;
            while (!(is.eof())) {
                pair<int, int> index;
                string s;
                is >> s;

                int divPos = s.find('/');
                if (divPos == s.npos) {
                    istringstream(s) >> index.first;
                    index.second = -1;
                } else {
                    istringstream(s.substr(0, divPos)) >> index.first;
                    istringstream(s.substr(divPos + 1)) >> index.second;
                }
                face.insert(index);
            }
            indexList.push_back(face);
        } else if (keystring == "vt") {
            pair <double, double> p;
            is >> p.first;
            is >> p.second;
            pair <int, pair <double, double> > p2;
            p2.first = texnum;
            p2.second = p;
            textureList.insert(p2);
            texnum++;
        }

    }
    obj_file.close();
    for (int i = 0; i < indexList.size(); i++) {
        set<pair<int, int> > face = indexList [i];
        int id [3];
        set<pair<int, int> >::iterator it = face.begin();
        pair <double, double> tNodes [4];
        for (int i = 0; i < 3; i++) {
            id[i] = (*it).first;

            if ((*it).second != -1) {
                pair <double, double> p = textureList[(*it).second];
                tNodes[i] = p;
            }
            it++;
        }


        Vector3D v0
                (vertexList[ id[0] ][0],
                vertexList[ id[0] ][1],
                vertexList[ id[0] ][2]);
        bBox.update
                (vertexList[ id[0] ][0],
                vertexList[ id[0] ][1],
                vertexList[ id[0] ][2]);

        Vector3D v1
                (vertexList[ id[1] ][0],
                vertexList[ id[1] ][1],
                vertexList[ id[1] ][2]);
        bBox.update
                (vertexList[ id[1] ][0],
                vertexList[ id[1] ][1],
                vertexList[ id[1] ][2]);

        Vector3D v2
                (vertexList[ id[2] ][0],
                vertexList[ id[2] ][1],
                vertexList[ id[2] ][2]);
        bBox.update
                (vertexList[ id[2] ][0],
                vertexList[ id[2] ][1],
                vertexList[ id[2] ][2]);

        if (it != face.end()) {//polygon is square
            int idx3 = (*it).first;
            Vector3D v3
                    (vertexList[ idx3 ][0],
                    vertexList[ idx3 ][1],
                    vertexList[ idx3 ][2]);
            bBox.update
                    (vertexList[ idx3 ][0],
                    vertexList[ idx3 ][1],
                    vertexList[ idx3 ][2]);

            if ((*it).second != -1) {
                pair <double, double> p = textureList[(*it).second];
                tNodes[3] = p;
            }

            Vector3D s1 = v1;
            pair <double, double> t1 = tNodes[1];
            Vector3D s2 = v2;
            pair <double, double> t2 = tNodes[2];
            if ((v0 - v3).length()<(s2 - v3).length()) {
                s2 = v0;
                t2 = tNodes[0];
                if ((v2 - v3).length()<(s1 - v3).length()) {
                    s1 = v2;
                    t1 = tNodes[2];
                }
            } else if ((v0 - v3).length()<(s1 - v3).length()) {
                s1 = v0;
                t1 = tNodes[0];
                if ((v1 - v3).length()<(s2 - v3).length()) {
                    s2 = v1;
                    t2 = tNodes[1];
                }
            }
            Shape * t = new Triangle(s1, s2, v3);
            ((Triangle *) t)->setTextureMapping(t1, t2, tNodes[3]);
            m->addShape(t);
        }
        Shape * t = new Triangle(v0, v1, v2);
        ((Triangle *) t)->setTextureMapping
                (tNodes[0], tNodes[1], tNodes[2]);
        m->addShape(t);

    }
    cout << "building tree acceleration structure for mesh:\n";
    m->buildTree();
    cout << "Mesh acceleration structure built!\n";
    m->setBoundingBox(bBox);
    return (Shape *) m;
}

