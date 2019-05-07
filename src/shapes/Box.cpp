//Author: Anthony Brown
#include "Box.h"
#include <iostream>
using namespace std;

Box::Box(const Vector3D& minPt, const Vector3D& maxPt) {
    //Calculate remaining 6 cube points
    //t=top b=bottom l=left r=right F=front B=back
    //minPt = lbF, maxPt = rtB
    min = minPt;
    max = maxPt;
    bbox.update(min[0],min[1],min[2]);
    bbox.update(max[0],max[1],max[2]);

    Vector3D lbF = minPt;
    Vector3D ltF(minPt[0], maxPt[1], minPt[2]);
    Vector3D rbF(maxPt[0], minPt[1], minPt[2]);
    Vector3D rtF(maxPt[0], maxPt[1], minPt[2]);

    Vector3D rtB = maxPt;
    Vector3D rbB(maxPt[0], minPt[1], maxPt[2]);
    Vector3D lbB(minPt[0], minPt[1], maxPt[2]);
    Vector3D ltB(minPt[0], maxPt[1], maxPt[2]);

    //add front face
    tri[0] = new Triangle(lbF, ltF, rbF);
    tri[1] = new Triangle(rbF, rtF, ltF);
    //add back face
    tri[2] = new Triangle(lbB, ltB, rbB);
    tri[3] = new Triangle(rbB, rtB, ltB);
    //add left face
    tri[4] = new Triangle(lbF, ltF, ltB);
    tri[5] = new Triangle(lbB, ltB, lbF);
    //add right face
    tri[6] = new Triangle(rbF, rtF, rtB);
    tri[7] = new Triangle(rbB, rtB, rbF);
    //add top face
    tri[8] = new Triangle(ltF, rtF, rtB);
    tri[9] = new Triangle(ltB, rtB, ltF);
    //add bottom face
    tri[10] = new Triangle(lbF, rbF, rbB);
    tri[11] = new Triangle(lbB, rbB, lbF);
}

Box::~Box() {
    for (int i = 0; i <= 11; i++) {
        if (tri[i] != NULL) delete tri[i];
    }
    delete [] tri;
}

bool Box::intersect(Ray& r, float tmin, float tmax, HitStruct &hit) {
    if(!bbox.intersect(r))return false;
    float max = tmax;
    HitStruct subHit;
    for (int i = 11; i >= 0; i--) {
        if (tri[i]->intersect(r, tmin, max, subHit)) {
            max = subHit.getT();
        }
    }
    if (subHit.getT() == -1) return false;
    else {
        hit.add(this, subHit.getT(),
                (subHit.getSurfaceNormal()),
                subHit.getIntersect(),
                r);
        return true;
    }
}

void Box::getTextureCoordinates(HitStruct & hit, double& s, double& t) {
    //figure out which triangle is being hit
    float max = 99999;
    HitStruct subHit;
    bool foundHit = false;
    for (int i = 11; i >= 0; i--) {
        Ray r = hit.getViewingRay();
        if (tri[i]->intersect(r, (float) 0.001, max, subHit)) {
            max = subHit.getT();
            foundHit = true;
        }
    }
    if (foundHit) {
        subHit.getShape()->getTextureCoordinates(subHit, s, t);
    }
    else{
        s=0;
        t=0;
    }
    if (s > 1) s = 1;
    if (s < 0) s = 0;
    if (t > 1) t = 1;
    if (t < 0) t = 0;
}

