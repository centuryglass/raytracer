/* 
 * File:   textureMap.h
 * Author: Anthony
 *
 * Created on April 5, 2013, 8:44 PM
 */
#include "Vector3D.h"
#include "HitStruct.h"
using namespace sivelab;
#include <string>
using namespace std;

#ifndef TEXTUREMAP_H
#define	TEXTUREMAP_H

class TextureMap {
protected:
    float tileRate;
    string name;
    Vector3D col;
public:

    TextureMap() {
    }

    ~TextureMap() {
    }
    std::string getName() {
        return name;
    }

    void setName(string newName) {
        name = newName;
    }

    void setColor(Vector3D& color) {
        col = color;
    }
/**
 * setTileRate specifies the number of times the texture is repeated over the
 * shape surface.
 * @param rate The number of times the texture is to be repeated over the
 * shape surface.
 */
    void setTileRate(float rate) {
        tileRate = rate;
    }
    /**
     * virtual function for getting the color data of a color at a single
     * point.
     * @param hit Contains information about the intersect point.
     * @return Texture color data at the intersect point
     */
    virtual Vector3D getTexel(HitStruct& hit) = 0;

};

#endif	/* TEXTUREMAP_H */

