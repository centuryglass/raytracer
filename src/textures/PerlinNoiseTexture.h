/* 
 * File:   PerlinNoiseTexture.h
 * Author: Anthony
 *
 * Created on April 14, 2013, 8:43 AM
 * 
 * Thanks are due to 
 * http://webstaff.itn.liu.se/~stegu/TNM022-2005
 * /perlinnoiselinks/perlin-noise-math-faq.html
 * for clarifying the algorithm for perlin noise significantly
 */

#ifndef PERLINNOISETEXTURE_H
#define	PERLINNOISETEXTURE_H


#include "Vector3D.h"
#include "TextureMap.h"
#include "HitStruct.h"
#include "TextureCalculator.h"
using namespace sivelab;

class PerlinNoiseTexture : public TextureMap {
public:
/**
 * Instantiate a new perlin noise texture.
 */
    PerlinNoiseTexture(){tileRate = 10;} 

    ~PerlinNoiseTexture() {
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
#endif	/* PERLINNOISETEXTURE_H */

