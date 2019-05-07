/*Shape.h
 *Author: Anthony Brown
 *An abstract base class for all rendered geometric shapes within the scene
 */

#ifndef __SHAPE__
#define __SHAPE__

#include <string>
#include <iostream>
using namespace std;
#include "Vector3D.h"
#include "Ray.h"
#include "HitStruct.h"
#include "Shader.h"
#include "BoundingBox.h"
using namespace sivelab;
#include "Matrix4x4.h"
using namespace ablib;

class HitStruct;
class Shader;
class Shape {
protected:
    Vector3D position;
    Shader * shader;
    string name;
    BoundingBox bbox;
public:
    /**
     * Determine whether Ray r intersects with this Shape.
     * @param r The viewing ray.
     * @param tmin Minimum acceptable t-value.
     * @param tmax Maximum acceptable t-value.
     * @param hit is used to store hit information if r intersects with t.
     * @return true if r intersects with this Shape
     */
    Vector3D getCenter(){return bbox.center();}
    virtual bool intersect(Ray &r, float tmin, float tmax, HitStruct &hit) = 0;
        /**
     * Sets s and t to the texture coordinates at a certain point on the 
     * shape's surface.
     * @param hit The hitStruct storing collision info.
     * @param s first texture coordinate, 0<=s<=1
     * @param t second texture coordinate, 0<=t<=1
     */
    virtual void getTextureCoordinates(HitStruct& hit, double& s, double& t)= 0;

    void setShader(Shader * shade) {
        shader = shade;
    }
    
    double getThickness(HitStruct &hit, Ray &r);

    Shader * getShader() {
        if (shader == NULL)return shader;
    }

    string getName() 
    {
        return name;
    }
    
    virtual int shapeCount() = 0;

    void setName(string newName) 
    {
        name = newName;
    }

    void setBoundingBox(BoundingBox b)
    {
        bbox = b;
    }

    BoundingBox getBoundingBox()
    {
        return bbox;
    }
    
    Shape() { }
    
    ~Shape() { }
    

};
#endif	
