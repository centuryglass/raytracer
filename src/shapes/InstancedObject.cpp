/* 
 * File:   InstancedObject.cpp
 * Author: Anthony
 * 
 * Created on April 12, 2013, 5:56 PM
 */

#include "InstancedObject.h"
#include <iostream>
using namespace std;

InstancedObject::InstancedObject(Shape * base, Matrix4x4 & t) {
    baseObject = base;
    transform = t;
    shader = baseObject->getShader();
    BoundingBox box = base->getBoundingBox();
    Vector3D min(box.bboxMin[0], box.bboxMin[1], box.bboxMin[2]);
    Vector3D max(box.bboxMax[0], box.bboxMax[1], box.bboxMax[2]);
    max = transform.multByVector(max, 1);
    min = transform.multByVector(min, 1);

    bbox = box;
    bbox.update(max[0], max[0], max[0]);
    bbox.update(min[0], min[0], min[0]);
    bbox.update(max[1], max[1], max[1]);
    bbox.update(min[1], min[1], min[1]);
    bbox.update(max[2], max[2], max[2]);
    bbox.update(min[2], min[2], min[2]);
    //I suspect the bounding box produced here is a lot less tight than it could
    //be, but it works for now.
}

bool InstancedObject::intersect
        (Ray &r, float tmin, float tmax, HitStruct &hit) {
    Matrix4x4 inv = transform.inverse();
    Vector3D o = r.getOrigin();
    Vector3D d = r.getDirection();
    Ray nRay;
    o = inv.multByVector(o, 1);
    d = inv.multByVector(d, 0);


    nRay.setOrigin(o);
    nRay.setDirection(d);
    if (baseObject->intersect(nRay, tmin, tmax, hit)) {

        //transpose inv to get the appropriate matrix for transforming
        //the surface normal
        Vector3D norm = hit.getSurfaceNormal();
        Matrix4x4 N;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                N[y][x] = inv[x][y];
            }
        }
        norm = N.multByVector(norm, 1);
        norm.normalize();
        Vector3D inter = (r.getDirection() * hit.getT()) + r.getOrigin();
        hit.add(this, hit.getT(), norm, inter, r);
        return true;
    } else return false;
}

void InstancedObject::getTextureCoordinates
        (HitStruct & hit, double& s, double& t) {
    Matrix4x4 inv = transform.inverse();
    Ray r = hit.getViewingRay();
    Vector3D o = r.getOrigin();
    Vector3D d = r.getDirection();
    o = inv.multByVector(o, 1);
    d = inv.multByVector(d, 0);
    r.setOrigin(o);
    r.setDirection(d);
    Vector3D inter = (r.getDirection() * hit.getT()) + r.getOrigin();
    HitStruct subHit;
    subHit.add(this, hit.getT(), hit.getSurfaceNormal(), inter, r);
    baseObject->getTextureCoordinates(subHit, s, t);
}
