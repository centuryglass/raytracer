//Author: Anthony Brown

#include "Sphere.h"
using namespace sivelab;
#include <cmath>
#include <iostream>
using namespace std;
#define PI 3.14159

Sphere::Sphere(Vector3D& c, float r) {
    center = c;
    radius = r;
    bbox.update(c[0] - r, c[1] - r, c[2] - r);
    bbox.update(c[0] + r, c[1] + r, c[2] + r);
}

bool Sphere::intersect(Ray &r, float tmin, float tmax, HitStruct &hit) {
    if (!bbox.intersect(r))return false;

    //d=ray direction vector
    //o=ray origin vector
    //t=0 at point of intersection
    //c=sphere center vector
    //r=radius
    Vector3D d = r.getDirection();
    Vector3D o = r.getOrigin();
    //(d*d)t^2 + 2d*(o-c)t + (o-c) * (o-c) - r^2 = 0


    float a = d.dot(d);
    float b = (2 * d).dot(o - center);
    float c = ((o - center).dot(o - center)) - (radius * radius);

    float disc = (b * b) - (4 * a * c);
    //if disc < tmin, no solutions.
    if (disc < tmin) {
        return false;
    }

    //otherwise, calculate t
    float t1 = (-b + sqrt(disc)) / (2 * a);
    float t2 = (-b - sqrt(disc)) / (2 * a);
    float t;

    //select the closest intersect point
    if (t1 < t2) {
        t = t1;
        if (t < tmin) t = t2;
    } else {
        t = t2;
        if (t < tmin) t = t1;
    }

    if ((t > tmax) || (t < tmin)) {
        return false;
    } else {
        Vector3D normal, inter;
        inter = t * d + o;

        normal = inter - center;
        normal.normalize();
//        if(((o+(d*tmin))-center).length() < radius)//hit is coming from inside,
//            normal = normal *-1; //so reverse normal

        hit.add(this, t, normal, inter, r);
        return true;
    }
}

void Sphere::getTextureCoordinates(HitStruct & hit, double& s, double& t) {
    double theta = acos((center[1] - hit.getIntersect()[1]) / radius);
    double phi = atan2(hit.getIntersect()[0] - center[0],
            hit.getIntersect()[2] - center[2]);
    s = phi / (2 * PI);
    s += .5;
    t = theta / PI;
    if (s > 1) s = 1;
    if (s < 0) s = 0;
    if (t > 1) t = 1;
    if (t < 0) t = 0;
}