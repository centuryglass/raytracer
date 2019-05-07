/*NormalMapShader.h
 *Author: Anthony Brown
 *Produces color info using surface normals
 *primarily for debugging purposes
 */

#ifndef __NORMALMAPSHADER__
#define __NORMALMAPSHADER__

#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"

using namespace sivelab;

class NormalMapShader : public Shader {
public:

    NormalMapShader() {
        type = "NormalMap";
    }

    ~NormalMapShader() {
    }
    /**
     * Returns hit a hit color set to give information about the normal vector
     * at the intersect point.
     * @param scene The scene where the intersect occurs
     * @param hit the structure containing intersect data
     * @return the appropriate color value for the intersect point.
     */
    Vector3D getHitColor(Scene* scene, HitStruct& hit);
    
    Vector3D mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth){
        return getHitColor(scene, hit);
    }

    Vector3D getShadow(HitStruct &hit, Light * l, Scene * scene) {
        Vector3D s;
        return s;
    }
};
#endif	
