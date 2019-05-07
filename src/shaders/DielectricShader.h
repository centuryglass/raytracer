/* 
 * File:   DielectricShader.h
 * Author: Anthony
 *
 * Created on May 8, 2013, 4:14 PM
 */

#ifndef DIELECTRICSHADER_H
#define	DIELECTRICSHADER_H

#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"
#include "Ray.h"
#include "TextureMap.h"
#include "Random.h"

using namespace sivelab;

class DielectricShader : public Shader {
private:
    float refractiveIndex;
    Vector3D attenuationCoef;
    bool colored;
public:

    /**
     * Instantiates a new Dielectric Mirrored shader.
     * @param diffusion Diffuse texture
     * @param refractiveInd refractive index value
     * @param mirrorCoef the mirror coefficient
     * @param useShadows set to true to enable shadows.
     */
    DielectricShader(float refractiveInd) {
        refractiveIndex = refractiveInd;
        colored = false;
        type = "Dielectric";
    }

    /**
     * Sets the amount of light energy absorbed by the object over one unit
     * @param a the attenuation coefficient
     */
    void setAttenuation(Vector3D a){
        attenuationCoef = a;
        colored = true;
    }
    /**
     * Calculate the hit color at a single intersect point.
     * @param scene The scene where the intersect occurs
     * @param hit The structure containing hit data.
     * @return 
     */
    Vector3D getHitColor(Scene* scene, HitStruct& hit);
    ~DielectricShader() {
    }
    Vector3D mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth);
        /**
     * Gets the shadow cast by an object with this shader
     * @param hit where the shadow ray hits the object
     * @param l the light the object is blocking
     * @param scene
     * @return a Vector3D indicating what percent of the light source passes
     * through the object 
     */
    Vector3D getShadow(HitStruct &hit, Light * l, Scene * scene);
};
#endif	/* DIELECTRICSHADER_H */

