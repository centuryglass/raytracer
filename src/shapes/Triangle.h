/*Triangle.h
 *Author: Anthony Brown
 *Implements the Shape class to represent triangles.
 */

#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "Vector3D.h"
#include "Ray.h"
#include "HitStruct.h"
#include "Shape.h"
using namespace sivelab;

class Triangle : public Shape {
private:
    Vector3D v0;
    Vector3D v1;
    Vector3D v2;
    Vector3D normal;
    Vector3D n2;
    float d;
    double u1[3];
    double u2[3];
    pair <double, double> t0, t1, t2;
public:
    /**
     * Determine whether Ray r intersects with this Triangle.
     * @param r The viewing ray.
     * @param tmin Minimum acceptable t-value.
     * @param tmax Maximum acceptable t-value.
     * @param hit is used to store hit information if r intersects with t.
     * @return true if r intersects with this Triangle
     */
    bool intersect(Ray &r, float tmin, float tmax, HitStruct &hit);
    /**
     * Instantiates a new triangle object.
     * @param a First triangle corner.
     * @param b Second triangle corner.
     * @param c Third triangle corner.
     */
    Triangle(const Vector3D& a, const Vector3D& b, const Vector3D& c);
    /**
     * Sets s and t to the texture coordinates at a certain point on the 
     * shape's surface.
     * @param hit The hitStruct storing collision info.
     * @param s first texture coordinate, 0<=s<=1
     * @param t second texture coordinate, 0<=t<=1
     */
    void getTextureCoordinates(HitStruct & hit, double& s, double& t);
    /**
     * Sets texture coordinates for more complex texture mapping, usually
     * imported from .obj files
     * @param p0 texture coordinates for v0
     * @param p1 texture coordinates for v1
     * @param p2 texture coordinates for v2
     */
    void setTextureMapping(pair<double, double> p0,
            pair<double, double> p1,
            pair<double, double> p2) {
        t0 = p0;
        t1 = p1;
        t2 = p2;
    }

    int shapeCount() {
        return 1;
    }

    ~Triangle() {
    }
};
#endif	
