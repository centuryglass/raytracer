/* 
 * File:   PortalShader.h
 * Author: Anthony
 * When light hits an object with this shader, just send it somewhere else
 * Created on May 11, 2013, 11:51 AM
 */

#ifndef PORTALSHADER_H
#define	PORTALSHADER_H
#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"
#include "Ray.h"
#include "Matrix4x4.h"
using namespace ablib;
class PortalShader : public Shader {
private:
    Matrix4x4 transformation;
public:

    /**
     * Instantiates a new Portal shader.
     * @param transform the transformation matrix
     */
    PortalShader(Matrix4x4 transform) {
        transformation = transform;
        type = "Portal";
    }


    ~PortalShader() {
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
     * through the object (always <1,1,1> here)
     */
    
    Vector3D mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth);
    
    Vector3D getShadow(HitStruct &hit, Light * l, Scene * scene) {
        Vector3D s(1,1,1);
        return s;
    }
};

#endif	/* PORTALSHADER_H */

