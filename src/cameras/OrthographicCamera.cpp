//Author: Anthony Brown
#include "OrthographicCamera.h"
using namespace sivelab;

void OrthographicCamera::computeRay(int i, int j, Ray& ray) {
    double u;
    double v;
    Random r;
    int rayNum = ray.getRayNum();
    int dimension = sqrt(ray.getMaxRayNum());
    //u = (-imagePlaneWidth / 2) + imagePlaneWidth * (i + 0.5) / resX;
    //u = l + (r − l )(i + 0.5)/nx
    //u = left boundary + (width)(i+.5)/nX
    //now:
    //left pixel boundary + rayXcoord*(pixel size/numXRays)+
    //((uniform*2)-1)*(pixel size/numXRays)   
    u = (-imagePlaneWidth / 2) + imagePlaneWidth * i / resX;
    if (ray.getMaxRayNum() > 1)
        u = u + ((rayNum % dimension) + r.uniform())
        *(imagePlaneWidth / resX / dimension);
    //v = b + (t − b)(j + 0.5)/ny
    //v = top boundary - (height)(j+.5)/nY
    v = (imagePlaneWidth / 2 / resX * resY)
            - (imagePlaneWidth / resX * resY)*(j) / resY;
    if (ray.getMaxRayNum() > 1)
        v = v + ((rayNum / dimension) + r.uniform())
        *(imagePlaneWidth / resX / dimension);
    Vector3D pos = ray.getDirection();
    pos = (basis.getW())+
            ((basis.getU()) * u) +
            ((basis.getV()) * v) + position;
    Vector3D dir = -1 * basis.getW();
    //dir.normalize();
    if (depthOfField > 0) {
        applyDepthOfField(ray, dir);
    } else {
        ray.setOrigin(pos);
        ray.setDirection(dir);
    }

}