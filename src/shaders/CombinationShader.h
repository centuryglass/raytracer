/* 
 * File:   CombinationShader.h
 * Author: Anthony
 *
 * Created on May 11, 2013, 6:55 PM
 */

#ifndef COMBINATIONSHADER_H
#define	COMBINATIONSHADER_H

#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"
#include "TextureMap.h"

using namespace sivelab;
#include <iostream>
using namespace std;

class CombinationShader : public Shader {
private:
    set<pair<Shader *,double> > shaders;
public:

    /**
     * instantiates a new FlatShader
     * @param sceneColor the color to always use to represent this object
     */
    CombinationShader() {
        type = "Combination";
    }

    ~CombinationShader() {
    }

    /**
     * Given a hitpoint, return the color data for that hit
     * In a FlatShader, the same value is returned in all circumstances.
     * @param scene The scene in which the hit occured.
     * @param hit The hitStructure containing data about the hit
     * @return The calculated color value.
     */
    Vector3D getHitColor(Scene* scene, HitStruct& hit);
    
    void addShader(pair <Shader *,double> p){
        shaders.insert(p);
    }
    
    Vector3D mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth);

    /**
     * Gets the shadow cast by an object with this shader
     * @param hit where the shadow ray hits the object
     * @param l the light the object is blocking
     * @param scene
     * @return a Vector3D indicating what percent of the light source passes
     * through the object (always <0,0,0> here)
     */
    Vector3D getShadow(HitStruct &hit, Light * l, Scene * scene);
};

#endif	/* COMBINATIONSHADER_H */

