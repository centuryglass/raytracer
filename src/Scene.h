/*Scene.h
 *Author: Anthony Brown
 *A container//accessor for all objects within/representing the scene
 */


#ifndef __SCENE__
#define __SCENE__

#include "Vector3D.h"
#include "Light.h"
#include "Camera.h"
#include "Shader.h"
#include "Shape.h"
#include "HitStruct.h"
#include "LightMap.h"
using namespace sivelab;
#include <set>
#include<iostream>
using namespace std;
class Shape;
class HitStruct;
class ShapeContainer;
class LightMap;
class Scene {
private:
    Vector3D color;
    ShapeContainer * shapes;
    set<Light*> lights;
    LightMap * lightMap;
    Camera * cam;
    double photonRadius;
public:

    Scene();

    ~Scene();
    int shapeCount();
    void insertLight(Light * light) {
        lights.insert(light);
    }
    Camera* getCamera(){return cam;}
    void setCamera(Camera* c){cam = c;}
    void insertShape(Shape * shape);
    void buildShapeTree();
    void setColor(const Vector3D& sceneCol) {
        color = sceneCol;
    }
    
    double getPhotonRadius(){return photonRadius;}

    set<Light*> getLights() {
        return lights;
    }

    Vector3D getSceneColor() {
        return color;
    }
    
    LightMap * getLightMap(){return lightMap;}
    /**
     * Removes all stored scene objects.
     */
    void resetScene();

    /**
     * Determines if a ray intersects with any objects in the scene.
     * @param r the viewing ray.
     * @param tmin minimum accepted t-value
     * @param tmax maximum accepted t-value
     * @param hit the hit structure used to store any intersect data
     * @return true if ray r intersects with some shape in the scene.
     */
    bool intersect(Ray &r, float tmin, float tmax, HitStruct &hit);

    bool useShadow;
    bool generatePhotonMap;


};
#endif			
