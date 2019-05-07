/* 
 * File:   SphereCamera.h
 * Author: Anthony
 * Creates a 360 degree scene view
 * Created on April 16, 2013, 9:31 AM
 */

#ifndef SPHERECAMERA_H
#define	SPHERECAMERA_H

#include "Camera.h"

class SphereCamera : public Camera {
public:
    /**
     * Create a new sphere camera.
     * @param pos Camera position
     * @param dir Camera direction
     * @param fLength focal length
     * @param ipWidth image plane width
     */
    SphereCamera(const Vector3D& pos, const Vector3D& dir,
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
#endif	/* SPHERECAMERA_H */

