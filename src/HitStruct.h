/*HitStruct.h
 *Author: Anthony Brown
 *Contains information for a collisions with a single viewing ray.
 */
#ifndef __HITSTRUCT__
#define __HITSTRUCT__

#include "Vector3D.h"
#include "Shape.h"
#include "Scene.h"
#include "Shader.h"
#include "Ray.h"
using namespace sivelab;

#include <iostream>
using namespace std;

class Scene;
class Shader;
class Shape;

class HitStruct {
private:
    Shape * shape;
    float t;
    Vector3D sNormal, in;
    Ray viewingRay;
    int depth;

public:

    HitStruct() {
        t = -1;
        depth = 10;
    }

    ~HitStruct() {
    }
    /**
     * Stores data about a single intersection between a ray and a shape
     * @param s pointer to the intersected shape
     * @param tVal amount the viewing ray is scaled to intersect with the shape
     * @param surfaceNormal the shape's surface normal at the intersect point
     * @param intersect the point of intersect
     * @param r the viewing ray
     */
    void add(Shape * s, float tVal, const Vector3D& surfaceNormal,
            const Vector3D& intersect, Ray& r);

    /**
     * Find the color value associated with a particular intersection
     * @param scene the scene in which the color value is found
     * @return the color value.
     */
    Vector3D getHitColor(Scene* scene);

    /**
     * Resets collision data.
     */
    void reset();

    float getT() {
        return t;
    }

    Shape * getShape() {
        return shape;
    }

    Ray getViewingRay() {
        return viewingRay;
    }

    void setPhoton(const Vector3D& photon) {
        viewingRay.setPhoton(photon);
    }

    void setShape(Shape * s) {
        shape = s;
    }

    void setSurfaceNormal(Vector3D n) {
        sNormal = n;
    }

    Vector3D getSurfaceNormal() {
        return sNormal;
    }

    Vector3D getIntersect() {
        return in;
    }

    int getDepth() {
        return depth;
    }

    int setDepth(int d) {
        depth = d;
    }

};
#endif	