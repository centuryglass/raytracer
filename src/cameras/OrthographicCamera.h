/*PerspectiveCamera.h
 *Author: Anthony Brown
 *Implementation of abstract camera type
 *that uses perspective ray generation 
 */

#ifndef __ORTHOGRAPHICCAMERA__
#define __ORTHOGRAPHICCAMERA__

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
    /**
     * Create a new orthographic camera.
     * @param pos Camera position
     * @param dir Camera direction
     * @param fLength focal length
     * @param ipWidth image plane width
     */
    OrthographicCamera(const Vector3D& pos, const Vector3D& dir,
            float fLength, float ipWidth)
    : Camera(pos, dir, fLength, ipWidth) {
    }
/**
 * For a given pixel on the image, set the viewing ray to point through
 * that pixel.
 * @param i pixel x-coordinate
 * @param j pixel y-coordinate
 * @param ray the viewing ray to be set.
 */
    void computeRay(int i, int j, Ray& ray);
};

#endif	
