/*LambertianShader.h
 *Author: Anthony Brown
 *Sets color using Lambertian shading
 */

#ifndef __LAMBERTIANSHADER__
#define __LAMBERTIANSHADER__


#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"
#include "TextureMap.h"

using namespace sivelab;

class LambertianShader : public Shader {
private:
    TextureMap * diffuse;
    double mirrorCoef;
    bool useShadow;
public:

    /**
     * Instantiate a new lambertian shader
     * @param diffusion diffusion color value
     * @param useShadows set to true to render shadows on this object.
     */
    LambertianShader(TextureMap * diffusion, bool useShadows) {
        diffuse = diffusion;
        useShadow = useShadows;
        mirrorCoef = 0;
        type = "Lambertian";
    }

    /**
     * Instantiate a new mirrored lambertian shader
     * @param diffusion diffusion color value
     * @param mirror the mirror coefficient
     * @param useShadows set to true to render shadows on this object.
     */
    LambertianShader(TextureMap * diffusion, double mirror, bool useShadows) {
        diffuse = diffusion;
        useShadow = useShadows;
        mirrorCoef = mirror;
    }

    ~LambertianShader() {
    }
    /**
     * Given a hitpoint, return the color data for that hit
     * @param scene The scene in which the hit occured.
     * @param hit The hitStructure containing data about the hit
     * @return The calculated color value.
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
#endif	
