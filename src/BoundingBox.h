/* 
 * File:   BoundingBox.h
 * Created on April 14, 2013, 5:13 PM
 */

#ifndef BOUNDINGBOX_H
#define	BOUNDINGBOX_H

#include <limits>
#include "Vector3D.h"
#include "Ray.h"

using namespace sivelab;

class BoundingBox {
private:
    double e;
public:

    Vector3D bboxMin;
    Vector3D bboxMax;

    BoundingBox();
    ~BoundingBox(){}
    /**
     * Finds the center of the bounding box
     */
    Vector3D center();
    /**
     * Check to see if a ray hits the box
     */
    bool intersect(Ray& r);

    /**
     * Given three coordinates, expand the bounding box if necessary
     */
    void update(float x, float y, float z);
    /**
     * given bounding box b2, expand this box to contain b2
     */
    void combine(BoundingBox b2);
    /**
     * reset values to default.
     */
    void reset();
};


#endif	/* BOUNDINGBOX_H */