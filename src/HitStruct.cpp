//Author:Anthony Brown

#include "HitStruct.h"

void HitStruct::add(Shape * s, float tVal, const Vector3D& surfaceNormal,
        const Vector3D& intersect, Ray& r) {
    shape = s;
    t = tVal;
    sNormal = surfaceNormal;
    in = intersect;
    viewingRay = r;
}

void HitStruct::reset() {
    shape = NULL;
    t = -1;
    sNormal.set(0, 0, 0);
    in.set(0, 0, 0);
}

Vector3D HitStruct::getHitColor(Scene* scene) {
    Vector3D shade;
    if (shape == NULL) return shade;
    if (shape->getShader() == NULL) return shade;
    shade += shape->getShader()->getHitColor(scene, *this);
    shade.clamp(0, 1);
    return shade;
}