/* 
 * File:   phongShader.h
 * Author: Anthony
 *
 * Created on March 31, 2013, 1:18 PM
 */

#ifndef PHONGSHADER_H
#define	PHONGSHADER_H

#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"
#include "TextureMap.h"

using namespace sivelab;

class PhongShader : public Shader {
private:
    TextureMap * diffuse;
    TextureMap * specular;
    float phongExp;
    bool useShadow;
public:

    /**
     * Instantiates a new Phong shader.
     * @param diffusion Diffuse texture
     * @param specularity Specular texture
     * @param phongExponent phong Exponent value
     * @param useShadows set to true to enable shadows.
     */
    PhongShader(TextureMap * diffusion, TextureMap * specularity,
            float phongExponent, bool useShadows) {
        diffuse = diffusion;
        specular = specularity;
        phongExp = phongExponent;
        useShadow = useShadows;
        type = "Phong";
    }

    ~PhongShader() {
    }
    /**
     * Calculate the hit color at a single intersect point.
     * @param scene The scene where the intersect occurs
     * @param hit The structure containing hit data.
     * @return 
     */
    Vector3D getHitColor(Scene* scene, HitStruct& hit);

    /**
     * Gets the shadow cast by an object with this shader
     * @param hit where the shadow ray hits the object
     * @param l the light the object is blocking
     * @param scene
     * @return a Vector3D indicating what percent of the light source passes
     * through the object (always <0,0,0> here)
     */
    
    Vector3D mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth);
    
    Vector3D getShadow(HitStruct &hit, Light * l, Scene * scene) {
        Vector3D s;
        return s;
    }
};

#endif	/* PHONGSHADER_H */

