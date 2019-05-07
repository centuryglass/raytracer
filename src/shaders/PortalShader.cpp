/* 
 * File:   PortalShader.cpp
 * Author: Anthony
 * When light hits an object with this shader, just send it somewhere else
 * Created on May 11, 2013, 11:51 AM
 */

#include "PortalShader.h"
#include<cmath>
#include<iostream>
#include<set>
using namespace std;

Vector3D PortalShader::getHitColor(Scene* scene, HitStruct& hit) {
    if (hit.getDepth() > 0) {
        hit.setDepth(hit.getDepth() - 1);
        Ray pR = hit.getViewingRay();
        HitStruct pHit;
        pR.setOrigin
                (transformation.multByVector(hit.getIntersect(), 1));
        Vector3D dir = hit.getViewingRay().getDirection();
        dir = transformation.multByVector(dir, 0);
        dir.normalize();
        pR.setDirection(dir);
        if (scene->intersect(pR, 0.001, 99999, pHit)) {
            return pHit.getHitColor(scene);
        } else return scene->getSceneColor();
    }
}

Vector3D PortalShader::mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth) {
    if (hit.getDepth() > 0) {
        hit.setDepth(hit.getDepth() - 1);
        Ray pR = hit.getViewingRay();
        HitStruct pHit;
        pR.setOrigin
                (transformation.multByVector(hit.getIntersect(), 1));
        Vector3D dir = hit.getViewingRay().getDirection();
        dir = transformation.multByVector(dir, 0);
        dir.normalize();
        pR.setDirection(dir);
        if (scene->intersect(pR, 0.001, 99999, pHit)) {
            hit = pHit;
            return hit.getShape()->getShader()->mapLightRay
                    (scene, hit, light,depth+1);
        }
    }
    Vector3D miss(-1, -1, -1);
    return miss;
}