/* 
 * File:   FlatShader.h
 * Author: Anthony
 *
 * Created on April 8, 2013, 10:58 AM
 */

#ifndef FLATSHADER_H
#define	FLATSHADER_H

#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"
#include "TextureMap.h"

using namespace sivelab;
#include <iostream>
using namespace std;

class FlatShader : public Shader {
private:
    TextureMap * color;
public:

    /**
     * instantiates a new FlatShader
     * @param sceneColor the color to always use to represent this object
     */
    FlatShader(TextureMap * sceneColor) {
        color = sceneColor;
        type = "Flat";
    }

    ~FlatShader() {
    }

    /**
     * Given a hitpoint, return the color data for that hit
     * In a FlatShader, the same value is returned in all circumstances.
     * @param scene The scene in which the hit occured.
     * @param hit The hitStructure containing data about the hit
     * @return The calculated color value.
     */
    Vector3D getHitColor(Scene* scene, HitStruct& hit) {
        Vector3D hitCol = color->getTexel(hit);
        return hitCol;
    }

    Vector3D mapLightRay(Scene* scene, HitStruct& hit, Vector3D light, int depth) {
        if (hit.getViewingRay().getRand() > 0.5 && depth != 0) {
            return color->getTexel(hit)*light;
        } else {
            HitStruct subHit = hit;
            if (calculateReflection(subHit, scene)) {
                hit = subHit;
                return subHit.getShape()->getShader()->mapLightRay
                        (scene, hit, color->getTexel(hit)*light,depth+1);
            } else {
                Vector3D miss(-1, -1, -1);
                return miss;
            }
        }
    }

    /**
     * Gets the shadow cast by an object with this shader
     * @param hit where the shadow ray hits the object
     * @param l the light the object is blocking
     * @param scene
     * @return a Vector3D indicating what percent of the light source passes
     * through the object (always <0,0,0> here)
     */
    Vector3D getShadow(HitStruct &hit, Light * l, Scene * scene) {
        Vector3D s;
        return s;
    }
};


#endif	/* FLATSHADER_H */

