/* 
 * File:   ShapeContainer.h
 * Author: Anthony
 *
 * Created on April 15, 2013, 12:08 PM
 */

#ifndef SHAPECONTAINER_H
#define	SHAPECONTAINER_H

#include <set>
#include <vector>
using namespace std;
#include "Vector3D.h"
#include "HitStruct.h"
#include "Shape.h"
#include "BoundingBox.h"
using namespace sivelab;

class ShapeContainer : public Shape {
private:
    set <Shape *> shapes;
    Shape * left;
    Shape * right;
    int axis;
    vector <double> sortGaps(int ax);
public:

    void addShape(Shape * t) {
        shapes.insert(t);
    }
    int shapeCount();
    /**
     * Determine whether Ray r intersects with this ShapeContainer.
     * @param r The viewing ray.
     * @param tmin Minimum acceptable t-value.
     * @param tmax Maximum acceptable t-value.
     * @param hit is used to store hit information if r intersects with t.
     * @return true if r intersects with this ShapeContainer
     */
    bool intersect(Ray& r, float tmin, float tmax, HitStruct &hit);
    /**
     * Sets s and t to the texture coordinates at a certain point on the 
     * shape's surface.
     * @param hit The hitStruct storing collision info.
     * @param s first texture coordinate, 0<=s<=1
     * @param t second texture coordinate, 0<=t<=1
     */
    void getTextureCoordinates(HitStruct& hit, double& s, double& t);

    void clear() {
        shapes.clear();
    }
    BoundingBox buildTree();

    ShapeContainer() {
        axis = -1;
        name = "shapeContainer";
    }

    ~ShapeContainer() {
        for (set<Shape*>::iterator it = shapes.begin();
                it != shapes.end(); ++it) {
            delete *it;
        }
    }
    

};

#endif	/* SHAPECONTAINER_H */

