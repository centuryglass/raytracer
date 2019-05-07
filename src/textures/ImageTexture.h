/* 
 * File:   imageTexture.h
 * Author: Anthony
 *
 * Created on April 5, 2013, 9:15 PM
 */

#ifndef IMAGETEXTURE_H
#define	IMAGETEXTURE_H

#include "Vector3D.h"
#include "TextureMap.h"
#include "HitStruct.h"

#include "png++/png.hpp"
using namespace sivelab;
#include <string>
using namespace std;

class ImageTexture : public TextureMap {
public:
/**
 * Instantiate a new image texture.
 * @param fileName the filename of the .png image to use as a texture
 */
    ImageTexture(string fileName) {
        fName = fileName;
        imData = new png::image< png::rgb_pixel >(fName);
        tileRate = 1;
    }

    ~ImageTexture() {
        delete imData;
    }
    /**
     * Returns the appropriate pixel from the texture image when given texture
     * coordinates
     * @param s 1st texture coordinate
     * @param t 2nd texture coordinate
     * @return The color value calculated.
     */
    Vector3D getTexel(HitStruct& hit);
private:
    string fName;
    png::image< png::rgb_pixel > * imData;

};

#endif	/* IMAGETEXTURE_H */

