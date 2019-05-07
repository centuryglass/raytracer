/* 
 * File:   MarbleTexture.h
 * Author: Anthony
 *
 * Created on April 14, 2013, 11:37 AM
 */

#ifndef MARBLETEXTURE_H
#define	MARBLETEXTURE_H

#include "Vector3D.h"
#include "TextureMap.h"
#include "HitStruct.h"
#include "TextureCalculator.h"
using namespace sivelab;
class MarbleTexture : public TextureMap {
public:
/**
 * Instantiate a new marble texture.
 */
    MarbleTexture(){tileRate = 1;}

    ~MarbleTexture() {
    }
    /**
     * Returns the appropriate pixel calculated using perlin noise
     * @param s 1st texture coordinate
     * @param t 2nd texture coordinate
     * @return The color value calculated.
     */
    Vector3D getTexel(HitStruct& hit);
private:
    TextureCalculator calc;

};

#endif	/* MARBLETEXTURE_H */

