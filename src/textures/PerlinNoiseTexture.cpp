/* 
 * File:   PerlinNoiseTexture.cpp
 * Author: Anthony
 * 
 * Created on April 14, 2013, 8:43 AM
 */

#include "PerlinNoiseTexture.h"

Vector3D PerlinNoiseTexture::getTexel(HitStruct& hit) {
    double s, t;
    hit.getShape()->getTextureCoordinates(hit, s, t);
    double x = s * tileRate * 10;
    double y = t * tileRate * 10;
    return calc.perlinNoiseFunction(x, y);
}


