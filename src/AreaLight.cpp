#include "AreaLight.h"

AreaLight::AreaLight
(const Vector3D& position,
        const Vector3D& intensity,
        Vector3D& norm, double w, double l)
: Light(position, intensity) {
    normal = norm;
    width = w;
    length = l;
    basis.calculateBasis(normal);
    type = 'a';

    Vector3D tl, tr, bl, br;
    double lu, ru, bv, tv;
    lu = -1 * (width / 2);
    bv = -1 * (length / 2);
    ru = 1 * (width / 2);
    tv = 1 * (length / 2);

    tl = (basis.getW()+
            ((basis.getU()) * lu) +
            ((basis.getV()) * tv));

    tr = (basis.getW()+
            ((basis.getU()) * ru) +
            ((basis.getV()) * tv));

    bl = (basis.getW()+
            ((basis.getU()) * lu) +
            ((basis.getV()) * bv));

    br = (basis.getW()+
            ((basis.getU()) * ru) +
            ((basis.getV()) * bv));

    t1 = new Triangle(tl, tr, bl);
    t2 = new Triangle(bl, br, tr);

}

bool AreaLight::intersect(Ray& ray, Scene * scene, double tMin) {
    //temporarily construct two triangles covering the light
    HitStruct hit;
    if (t1->intersect(ray, tMin, 99999, hit) 
            || t2->intersect(ray, 0.01, 99999, hit)) {
        double tMax = hit.getT();
        if (scene->intersect(ray, 0.0001, tMax, hit)) return false;
        else return true;
    }
    return false;
}

Vector3D AreaLight::getLightPt(Ray& ray) {
    int rayNum = ray.getRayNum();
    int dimension = sqrt(ray.getMaxRayNum());
    double u, v;
    u = -1 * (width / 2);
    v = -1 * (length / 2);
    u = u + ((rayNum % dimension) + ray.getRand())*(width / dimension);
    v = v + ((rayNum / dimension) + ray.getRand())*(length / dimension);

    Vector3D lightPt = (basis.getW()+
            ((basis.getU()) * u) +
            ((basis.getV()) * v));
    lightPt += pos;
    return lightPt;

}