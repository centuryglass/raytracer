//Author: Anthony Brown
#include "SphereCamera.h"
using namespace sivelab;
#include<cmath>
using namespace std;

void SphereCamera::computeRay(int i, int j, Ray & ray) {
    float u;
    float v;
    float w;

    double dx, dy, dist, angle;
    int rayNum = ray.getRayNum();
    int dimension = sqrt(ray.getMaxRayNum());
    dx = i - (resX / 2);
    dy = j - (resY / 2);
    dist = sqrt(pow(dx, 2) + pow(dy, 2))
            / sqrt(pow(resX / 2, 2) + pow(resY / 2, 2));
    //angle = atan(dy/dx);

    //u = l + (r − l )(i + 0.5)/nx
    //u = left boundary + (width)(i+.5)/nX
    //u = (-imagePlaneWidth / 2) + imagePlaneWidth * (i + 0.5) / resX;
    u = (dist * 2) - 1;


    //v = b + (t − b)(j + 0.5)/ny
    //v = top boundary - (height)(j+.5)/nY
    //v = (imagePlaneWidth / 2 / resX * resY)
    //      - (imagePlaneWidth / resX * resY)*(j + 0.5) / resY;
    v = dy / resY;
    if(ray.getMaxRayNum()>1)
    v = v + ((rayNum / dimension) + ray.getRand())
            *(imagePlaneWidth / resX / dimension);
    w = dx / resX;
    if(ray.getMaxRayNum()>1)
    w = w + ((rayNum % dimension) + ray.getRand())
            *(imagePlaneWidth / resX / dimension);
    //r.direction = −d W + u U + v V ;
    Vector3D dir = ray.getDirection();

    dir = (((basis.getW()) * w)+
            ((basis.getU()) * u * (-focalLength)) +
            ((basis.getV()) * v));
    dir.set(dx / resX, (dist * 2) - 1, dy / resY);
    dir.normalize();

    if (depthOfField > 0) {
        applyDepthOfField(ray,dir);
    } else {
        ray.setDirection(dir);
        ray.setOrigin(position);
    }
}