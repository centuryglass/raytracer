/* 
 * File:   Mesh.h
 * Author: Anthony
 *
 * Created on April 14, 2013, 5:19 PM
 */

#ifndef MESH_H
#define	MESH_H

#include <set>
#include <vector>
using namespace std;
#include "Vector3D.h"
#include "Triangle.h"
#include "HitStruct.h"
#include "Shape.h"
using namespace sivelab;

class Mesh : public Shape {
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
     * Determine whether Ray r intersects with this Mesh.
     * @param r The viewing ray.
     * @param tmin Minimum acceptable t-value.
     * @param tmax Maximum acceptable t-value.
     * @param hit is used to store hit information if r intersects with t.
     * @return true if r intersects with this Mesh
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
    BoundingBox buildTree();

    Mesh() {
        axis = -1;
    }

    ~Mesh() {
        for (set<Shape*>::iterator it = shapes.begin(); 
                it != shapes.end(); ++it) {
            delete *it;
        }
    }

};


#endif	/* MESH_H */

