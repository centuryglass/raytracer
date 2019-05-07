/* 
 * File:   MarbleTexture.cpp
 * Author: Anthony
 * 
 * Created on April 14, 2013, 11:37 AM
 */

#include "MarbleTexture.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Random.h"
using namespace sivelab;


Vector3D MarbleTexture::getTexel(HitStruct& hit) {
    double s, t;
    double width = 1;
    hit.getShape()->getTextureCoordinates(hit, s, t);
    double x = s * tileRate*30;
    double y = t * tileRate*30;
    
    double tval = (1 + sin(y+calc.turbulenceFunction(x,y,5)[0])/width)/2;
    Vector3D a (1,0,0);
    Vector3D b (1,1,1);
    return (tval*a) + ((1-tval)*b);
}

