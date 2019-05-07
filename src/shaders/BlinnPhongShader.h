/* 
 * File:   BlinnPhongShader.h
 * Author: Anthony
 *
 * Created on March 31, 2013, 4:09 PM
 */

#ifndef BLINNPHONGSHADER_H
#define	BLINNPHONGSHADER_H

#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"
#include "Ray.h"
#include "TextureMap.h"
#include "Random.h"

using namespace sivelab;

class BlinnPhongShader : public Shader {
private:
    TextureMap * diffuse;
    TextureMap * specular;
    float phongExp, mirrorCoef;
    bool useShadow;
public:

    /**
     * Instantiates a new BlinnPhong Mirrored shader.
     * @param diffusion Diffuse texture
     * @param specularity Specular texture
     * @param phongExponent phong Exponent value
     * @param mirrorCoef the mirror coefficient
     * @param useShadows set to true to enable shadows.
     */
    BlinnPhongShader(
            TextureMap * diffusion, TextureMap * specularity,
            float phongExponent, float mirrorCoefficient,
            bool useShadows) {
        diffuse = diffusion;
        specular = specularity;
        phongExp = phongExponent;
        mirrorCoef = mirrorCoefficient;
        useShadow = useShadows;
        roughness = 0;
        type = "BlinnPhong";
    }

    BlinnPhongShader(
            TextureMap * diffusion, TextureMap * specularity,
            float phongExponent,
            bool useShadows) {
        diffuse = diffusion;
        specular = specularity;
        phongExp = phongExponent;
        mirrorCoef = 0;
        useShadow = useShadows;
        roughness = 0;
        type = "BlinnPhong";
    }


    ~BlinnPhongShader() {
    }
    /**
     * Calculate the hit color at a single intersect point.
     * @param scene The scene where the intersect occurs
     * @param hit The structure containing hit data.
     * @return 
     */
    Vector3D getHitColor(Scene* scene, HitStruct& hit);
    
    Vector3D mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth);

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

#endif	/* BLINNPHONGSHADER_H */

