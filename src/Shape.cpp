#include "Shape.h"

double Shape::getThickness(HitStruct &hit, Ray &r) {
    HitStruct subHit;
    Ray nRay;
    Vector3D origin = r.getOrigin() + (r.getDirection() * 100);
    Vector3D direction = r.getDirection()*-1;
    nRay.setOrigin(origin);
    nRay.setDirection(direction);
    if (intersect(nRay, 0.001, 99999.0, subHit)) {
        return (subHit.getIntersect() - hit.getIntersect()).length();
    } else {
        return 0.001;
    }
}
