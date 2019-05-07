/* 
 * File:   imageTexture.cpp
 * Author: Anthony
 * 
 * Created on April 5, 2013, 9:15 PM
 */

#include "ImageTexture.h"
using namespace sivelab;
#include <cstdlib>
using namespace std;

Vector3D ImageTexture::getTexel(HitStruct& hit) {
    double s, t;
    s = 0;
    t = 0;
    if (hit.getShape() == NULL)cout << "Null shape!\n";
    else {
        hit.getShape()->getTextureCoordinates(hit, s, t);
        if (tileRate != 1) {
            s *= tileRate;
            s -= (int) s;

            t *= tileRate;
            t -= (int) t;
        }
    }
    Vector3D color;
    int sCoord = s * (imData->get_width()-1);
    int tCoord = (imData->get_height()-1) - (t * (imData->get_height()-1));
    
    if(sCoord > (imData->get_width()-1)) sCoord = (imData->get_width()-1);
    if(tCoord > (imData->get_height()-1)) tCoord = (imData->get_height()-1);
    if(sCoord<0)sCoord=0;
    if(tCoord<0)tCoord=0;
    png::rgb_pixel p =imData->get_pixel(sCoord,tCoord);
    color.set(p.red, p.green, p.blue);
    color *= (double) 1 / 255;
    //color.set(s, t, 0);
    color = color * col;
    return color;
}
