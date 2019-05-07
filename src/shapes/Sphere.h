/*Sphere.h
 *Author: Anthony Brown
 *Implements the Shape class to represent spheres.
 */

#ifndef __SPHERE__
#define __SPHERE__


#include "Vector3D.h"
#include "Ray.h"
#include "HitStruct.h"
#include "Shape.h"

class Sphere : public Shape {
private:
    Vector3D center;
    float radius;
public:
       /**
     * Determine whether Ray r intersects with this Sphere.
     * @param r The viewing ray.
     * @param tmin Minimum acceptable t-value.
     * @param tmax Maximum acceptable t-value.
     * @param hit is used to store hit information if r intersects with t.
     * @return true if r intersects with this Sphere
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
     * Instantiates a new Sphere object.
     * @param c the sphere's center
     * @param r the sphere's radius
     */
    int shapeCount(){return 1;}
    Sphere(Vector3D& c, float r);

    ~Sphere() {
    }
};

#endif	
