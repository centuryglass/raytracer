//Author: Anthony Brown
#include "NormalMapShader.h"
using namespace sivelab;

Vector3D NormalMapShader::getHitColor(Scene* scene, HitStruct& hit) {
    /*Vector3D hitCol(255, 255, 255);  
    double s, t;
    hit.getShape()->getTextureCoordinates(hit, s, t);
    hitCol[0] *= s;
    hitCol[1] *= t;
     */
    Vector3D hitCol = hit.getSurfaceNormal();
    hitCol *= .5;
    hitCol[0] += .5;
    hitCol[1] += .5;
    hitCol[2] += .5;
    Ray r = hit.getViewingRay();// view thickness
    double s = hit.getShape()->getThickness(hit, r);
    hitCol[0] = s/3;
    hitCol[1] = s/3;
    hitCol[2] = s/3;
    return hitCol; 
}