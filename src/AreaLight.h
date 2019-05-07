/* 
 * File:   AreaLight.h
 * Author: Anthony
 *
 * Created on April 16, 2013, 7:22 PM
 */

#ifndef AREALIGHT_H
#define	AREALIGHT_H

#include "Vector3D.h"
#include "Light.h"
#include "Basis.h"
#include "Random.h"
#include "shapes/Triangle.h"
using namespace sivelab;
#include <set>
#include <cmath>
using namespace std;

class AreaLight : public Light {
protected:
    Vector3D normal;
    double width;
    double length;
    Basis basis;
    Triangle * t1;
    Triangle * t2;
public:
/**
 * Initialize a new area light
 * @param position
 * @param intensity
 * @param norm surface normal
 * @param w width
 * @param l length
 */
    AreaLight
    (const Vector3D& position,
            const Vector3D& intensity,
            Vector3D& norm, double w, double l);
/**
 * Check to see if a ray in a given scene intersects with the light
 * @param ray
 * @param scene
 * @param tMin
 */
    bool intersect(Ray& ray, Scene * scene, double tMin);

    ~AreaLight() {
    }

    Vector3D getPosition() {
        return pos;
    }

    Vector3D getIntensity() {
        return intens;
    }
/**
 * Given a ray, get a light point for the ray to try and hit.
 * @param ray
 */
    Vector3D getLightPt(Ray& ray);

};


#endif	/* AREALIGHT_H */

