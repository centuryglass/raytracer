/* 
 * File:   BlinnPhongShader.cpp
 * Author: Anthony
 * 
 * Created on March 31, 2013, 2:20 PM
 */
#include "BlinnPhongShader.h"
#include "AreaLight.h"
#include<cmath>
#include<iostream>
#include<set>
using namespace std;

Vector3D BlinnPhongShader::getHitColor(Scene* scene, HitStruct& hit) {

    //L = d*l*max(0,n.dot(l))+s*l*max(0,v.dot(r))^p
    Vector3D rCol(0, 0, 0);
    Vector3D shade(0, 0, 0);
    set<Light*> lights = scene->getLights();
    int lightcount = 0;
    for (set<Light*>::iterator it = lights.begin(); it != lights.end(); ++it) {
        Light * light = *it;

        Vector3D lightPos;
        if (light->getType() == 'a' && hit.getViewingRay().getMaxRayNum() > 1) {
            Ray ray = hit.getViewingRay();
            lightPos = ((AreaLight *) light)->getLightPt(ray);
        } else lightPos = light->getPosition();

        Vector3D l = lightPos - hit.getIntersect();
        Vector3D shadowMult(1, 1, 1);
        if (useShadow) {
            shadowMult = calculateShadowMult(hit, light, l, scene);
        }
        l.normalize();

        float m = l.dot(hit.getSurfaceNormal());
        if (m < 0) m = 0;
        shade += (((diffuse->getTexel(hit) * light->getIntensity()) * m)
                * shadowMult);
        //direction ray from intersect to camera
        Vector3D v = hit.getViewingRay().getDirection()*-1;
        v.normalize();
        Vector3D h;
        h[0] = (v[0] + l[0]) / 2;
        h[1] = (v[1] + l[1]) / 2;
        h[2] = (v[2] + l[2]) / 2;
        h.normalize();
        float sStrength = hit.getSurfaceNormal().dot(h);
        if (sStrength < 0)sStrength = 0;
        shade += (((specular->getTexel(hit) * light->getIntensity()) *
                pow(sStrength, phongExp)) * shadowMult);

    }
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

    if (scene->generatePhotonMap) {
        if (hit.getViewingRay().getRayNum() == 0) {
            Vector3D photon = scene->getLightMap()->getClosest(hit.getIntersect(),
                    scene->getPhotonRadius());
            hit.setPhoton(photon);
            shade += photon;
        } else shade += hit.getViewingRay().getPhoton();
    }
    shade.clamp(0, 1);
    return shade;
}

Vector3D BlinnPhongShader::mapLightRay(Scene* scene, HitStruct& hit, Vector3D light, int depth) {
    Ray ray = hit.getViewingRay();

    //calculate radiance
    Vector3D shade;
    float m = (ray.getDirection()).dot(hit.getSurfaceNormal());
    if (m < 0) m *= -1;
    shade += ((diffuse->getTexel(hit) * light) * m);

    Vector3D v = ray.getDirection()*-1;
    v.normalize();
    Vector3D h;
    h.normalize();
    float sStrength = hit.getSurfaceNormal().dot(h);
    if (sStrength < 0)sStrength = 0;
    shade += ((specular->getTexel(hit) * light) * pow(sStrength, phongExp));
    if (mirrorCoef > 0) {
        shade *= (1.0 - mirrorCoef);
        shade += (mirrorCoef * light);
    }
    shade.clamp(0, 1);
    if (ray.getRand() > 0.5 && depth != 0) {
        return shade;
    } else {

        HitStruct subHit = hit;
        if (calculateReflection(subHit, scene)) {
            hit = subHit;
            return hit.getShape()->getShader()->mapLightRay
                    (scene, hit, shade, depth + 1);
        } else {
            Vector3D miss(-1, -1, -1);
            return miss;
        }
    }
}