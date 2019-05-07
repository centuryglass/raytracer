/* 
 * File:   FlatTexture.h
 * Author: Anthony
 *
 * Created on April 5, 2013, 8:50 PM
 */

#ifndef FLATTEXTURE_H
#define	FLATTEXTURE_H

#include "TextureMap.h"
#include "HitStruct.h"

class FlatTexture : public TextureMap {
public:
/**
 * instantiates a new flat texture
 * @param color the color value of the texture.
 */
    FlatTexture(Vector3D& color) {
        col = color;
    }

    FlatTexture() {
    }

    ~FlatTexture() {
    }
/**
 * Returns texture color data at a single point.
 * FlatTexture returns the same value at all coordinates
 * @param s first texture coordinate
 * @param t second texture coordinate
 * @return the texture's color
 */
    Vector3D getTexel(HitStruct& hit) {
        return col;
    }
private:

};

#endif	/* FLATTEXTURE_H */

