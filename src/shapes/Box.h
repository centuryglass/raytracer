/*Box.h
 *Author: Anthony Brown
 *Implements the Shape class to represent boxes.
 */

#ifndef __BOX__
#define __BOX__

#include "Vector3D.h"
#include "Triangle.h"
#include "HitStruct.h"
#include "Shape.h"

class Box : public Shape {
private:
    Triangle * tri[12];
    Vector3D min, max;
public:
    /**
     * Determine whether Ray r intersects with this Box.
     * @param r The viewing ray.
     * @param tmin Minimum acceptable t-value.
     * @param tmax Maximum acceptable t-value.
     * @param hit is used to store hit information if r intersects with t.
     * @return true if r intersects with this Box
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
    /**
     * Instantiates a new Box
     * @param minPt The smallest box corner vector
     * @param maxPt The largest box corner vector
     */
    int shapeCount(){return 1;}
    Box(const Vector3D& minPt, const Vector3D& maxPt);
    ~Box();

};

#endif	
