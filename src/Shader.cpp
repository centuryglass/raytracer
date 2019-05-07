#include "Shader.h"

Vector3D Shader::calculateShadowMult
    (HitStruct& hit,Light * light,Vector3D lightDir,Scene * scene) {

    Vector3D shadowMult(1, 1, 1);
    Ray shadow = hit.getViewingRay();
    Vector3D r = hit.getIntersect();
    r = r + (hit.getSurfaceNormal() *.001);
    float tMax = lightDir.length();
    HitStruct shadowHit;
    lightDir.normalize();
    shadow.setOrigin(r);
    shadow.setDirection(lightDir);
    bool shadowed = true;
    double tMin = 0.0001;
    while (shadowed && (tMin < tMax)) {
        shadowed = scene->intersect(shadow, tMin, tMax, shadowHit);
        if (shadowed) {
            tMin = shadowHit.getT() + 0.001;
            shadowMult = shadowMult *
                    shadowHit.getShape()->getShader()->
                    getShadow(hit, light, scene);
        }
    }
    return shadowMult;

}

bool Shader::calculateReflection(HitStruct& hit, Scene * scene){
    Vector3D v = hit.getViewingRay().getDirection()*-1;
            v.normalize();
            Vector3D r = (v*-1)
                    + 2 * (v.dot(hit.getSurfaceNormal()))
                    * hit.getSurfaceNormal();
            if (roughness > 0) {
                r[0] += ((hit.getViewingRay().getRand()*2 - 1) * roughness);
                r[1] += ((hit.getViewingRay().getRand()*2 - 1) * roughness);
                r[2] += ((hit.getViewingRay().getRand()*2 - 1) * roughness);
            }
            Vector3D rCol;
            r.normalize();
            Ray reflect=hit.getViewingRay();
            reflect.setOrigin(hit.getIntersect());
            reflect.setDirection(r);
            return (scene->intersect(reflect, 0.001, 99999.0, hit)); 
}