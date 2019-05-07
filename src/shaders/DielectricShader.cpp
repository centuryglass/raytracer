/* 
 * File:   DielectricShader.cpp
 * Author: Anthony
 * 
 * Created on May 8, 2013, 4:14 PM
 */

#include "DielectricShader.h"
#include "AreaLight.h"
#include<cmath>
#include<iostream>
#include<set>
using namespace std;

Vector3D DielectricShader::getHitColor(Scene* scene, HitStruct& hit) {

    //L = d*l*max(0,n.dot(l))+s*l*max(0,v.dot(r))^p
    Vector3D rCol(0, 0, 0);
    Vector3D shade(0, 0, 0);
    //calculate refracted light
    //nsinθ = nt sinφ
    //1*sin theta/nt = sin phi
    //asin (sin theta/nt) = phi
    if (hit.getDepth() > 0) {

        Vector3D v = hit.getViewingRay().getDirection();
        v.normalize();
        double theta = acos((v * -1).dot(hit.getSurfaceNormal()));

        double phi = asin(sin(theta) / refractiveIndex);
        //above the critical angle, there is no refracted ray.
        if (phi <= asin(sin(3.14159 / 2) / refractiveIndex)) {//if we're below the critical angle
            //I was getting this math all wrong, thankfully the correct
            //equations were on Wikipedia
            Vector3D r;

            if (cos(theta) > 0) {
                r = (refractiveIndex * v)
                        +((refractiveIndex * cos(theta) - cos(phi)) * hit.getSurfaceNormal());
            } else {
                r = (refractiveIndex * v)
                        +((refractiveIndex * cos(theta) + cos(phi)) * hit.getSurfaceNormal());
            }
            r.normalize();
            Ray refract = hit.getViewingRay();
            refract.setOrigin(hit.getIntersect());
            refract.setDirection(r);

            double s = hit.getShape()->getThickness(hit, refract);
            double tMin = s + 0.001;
            HitStruct subHit;
            subHit.setDepth(hit.getDepth() - 1);
            bool intersect = scene->intersect(refract, tMin, 99999.0, subHit);
            while (hit.getShape() == subHit.getShape() && intersect) {
                tMin = subHit.getT() + 0.001;
                intersect = scene->intersect(refract, tMin, 99999.0, subHit);
            }
            if (intersect) {
                rCol = (subHit.getHitColor(scene));
            } else {
                rCol = (scene->getSceneColor());
            }
            //I(s) = I(0)e^−ln(a)s
            Vector3D shadowMult;
            double e = 2.71828l;

            for (int i = 0; i < 3; i++) {
                shadowMult[i] = pow(e, -1 * log(attenuationCoef[i]) * s);
            }
            rCol = rCol * shadowMult;

            rCol.clamp(0, 1);
            shade += rCol;
            rCol.set(0, 0, 0);
        }
        //find reflection coefficient using Schlick's approximation
        double r0 = pow((refractiveIndex - 1) / (refractiveIndex + 1), 2);
        double mirrorCoef = r0 + ((1 - r0) * pow((1 - cos(theta)), 5));
        if (mirrorCoef > 0) {
            if (hit.getDepth() > 0) {
                hit.setDepth(hit.getDepth() - 1);
                Vector3D rCol;
                if (calculateReflection(hit, scene)) {
                    rCol = (hit.getHitColor(scene));
                } else {
                    rCol = (scene->getSceneColor());
                }
                rCol *= mirrorCoef;
                shade *= (1.0 - mirrorCoef);
                shade += rCol;
            }
        }
    } else {
        shade = (scene->getSceneColor());
    }
    shade.clamp(0, 1);

    return shade;
}

Vector3D DielectricShader::getShadow(HitStruct &hit, Light * l, Scene * scene) {
//    if(scene->generatePhotonMap){
//        //we shouldn't render light that passes through
//        //the object twice
//        Vector3D shadow;
//        return shadow;
//    }
    Vector3D shadowMult(1, 1, 1);

    Vector3D v = hit.getViewingRay().getDirection();
    v.normalize();
    double theta = acos((v * -1).dot(hit.getSurfaceNormal()));
    double phi = asin(sin(theta) / refractiveIndex);
    Vector3D r;
    if (cos(theta) > 0) {
        r = (refractiveIndex * v)
                +(refractiveIndex * cos(theta) - cos(phi)) * hit.getSurfaceNormal();
    } else {
        r = (refractiveIndex * v)
                +(refractiveIndex * cos(theta) + cos(phi)) * hit.getSurfaceNormal();
    }
    r.normalize();
    Ray refract = hit.getViewingRay();
    refract.setOrigin(hit.getIntersect());
    refract.setDirection(r);
    //I(s) = I(0)e^−ln(a)s
    double e = 2.71828l;
    double s = hit.getShape()->getThickness(hit, refract);
    for (int i = 0; i < 3; i++) {
        shadowMult[i] = pow(e, -1 * log(attenuationCoef[i]) * s);
    }
    return shadowMult;
}

Vector3D DielectricShader::mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth) {
    if (hit.getDepth() > 0) {
        hit.setDepth(hit.getDepth() - 1);
        //calculate mirror coefficient
        Vector3D v = hit.getViewingRay().getDirection();
        v.normalize();
        double theta = acos((v * -1).dot(hit.getSurfaceNormal()));
        double r0 = pow((refractiveIndex - 1) / (refractiveIndex + 1), 2);
        double mirrorCoef = r0 + ((1 - r0) * pow((1 - cos(theta)), 5));
        if (hit.getViewingRay().getRand() <= mirrorCoef) {//follow the reflected ray
            if (calculateReflection(hit, scene)) {
                return hit.getShape()->getShader()->mapLightRay
                        (scene, hit, light,depth+1);
            }
        } else {//follow the refracted ray
            double phi = asin(sin(theta) / refractiveIndex);
            if (phi <= asin(sin(3.14159 / 2) / refractiveIndex)) {
                Vector3D r;
                if (cos(theta) > 0) {
                    r = (refractiveIndex * v)
                            +((refractiveIndex * cos(theta) - cos(phi)) * hit.getSurfaceNormal());
                } else {
                    r = (refractiveIndex * v)
                            +((refractiveIndex * cos(theta) + cos(phi)) * hit.getSurfaceNormal());
                }
                r.normalize();
                Ray refract = hit.getViewingRay();
                refract.setOrigin(hit.getIntersect());
                refract.setDirection(r);

                double s = hit.getShape()->getThickness(hit, refract);
                double tMin = s + 0.001;
                HitStruct subHit;
                subHit.setDepth(hit.getDepth() - 1);
                bool intersect = scene->intersect(refract, tMin, 99999.0, subHit);
                while (hit.getShape() == subHit.getShape() && intersect) {
                    tMin = subHit.getT() + 0.001;
                    intersect = scene->intersect(refract, tMin, 99999.0, subHit);
                }
                if (intersect) {
                    Vector3D shadowMult;
                    double e = 2.71828l;

                    for (int i = 0; i < 3; i++) {
                        shadowMult[i] = pow(e, -1 * log(attenuationCoef[i]) * s);
                    }
                    hit = subHit;
                    return hit.getShape()->getShader()->mapLightRay
                            (scene, hit, light * shadowMult,depth+1);
                }
            }
        }
        Vector3D miss(-1, -1, -1);
        return miss;

    }

}