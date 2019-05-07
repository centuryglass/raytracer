/* 
 * File:   InstancedObject.h
 * Author: Anthony
 *
 * Created on April 12, 2013, 5:56 PM
 */

#ifndef INSTANCEDOBJECT_H
#define	INSTANCEDOBJECT_H


#include "Vector3D.h"
using namespace sivelab;
#include "Ray.h"
#include "HitStruct.h"
#include "Shape.h"
#include "Matrix4x4.h"
using namespace ablib;

class InstancedObject : public Shape {
private:
    Matrix4x4 transform;
    Shape * baseObject;
public:
       /**
     * Determine whether Ray r intersects with this InstancedObject.
     * @param r The viewing ray.
     * @param tmin Minimum acceptable t-value.
     * @param tmax Maximum acceptable t-value.
     * @param hit is used to store hit information if r intersects with t.
     * @return true if r intersects with this InstancedObject
     */
    bool intersect(Ray &r, float tmin, float tmax, HitStruct &hit);
        /**
     * Sets s and t to the texture coordinates at a certain point on the 
     * shape's surface.
     * @param hit The hitStruct storing collision info.
     * @param s first texture coordinate, 0<=s<=1
     * @param t second texture coordinate, 0<=t<=1
     */
    void getTextureCoordinates(HitStruct & hit, double& s, double& t);
    /**
     * Instantiates a new InstancedObject object.
     */
    int shapeCount(){return 1;}
    InstancedObject(Shape * base, Matrix4x4 & t);

    ~InstancedObject() {
    }
};



#endif	/* INSTANCEDOBJECT_H */

