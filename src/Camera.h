/*Camera.h
 *Author: Anthony Brown
 *Abstract base class for classes that create viewing rays for scene rendering
 */

#ifndef __CAMERA__
#define __CAMERA__

#include "Vector3D.h"
#include "Ray.h"
#include "Basis.h"
#include "Random.h"
using namespace sivelab;
#include <string>
#include <set>
using namespace std;
class Shape;

class Camera {
protected:
    void applyDepthOfField(Ray& r, Vector3D& dir);
    Vector3D position;
    float focalLength;
    float imagePlaneWidth;
    float depthOfField;
    float lensRadius;
    int resX;
    int resY;
    Basis basis;
    string name;
public:
    /**
     * Create a new camera.
     * @param pos Camera position
     * @param dir Camera direction
     * @param fLength focal length
     * @param ipWidth image plane width
     */
    Camera(const Vector3D& pos, const Vector3D& dir,
            float fLength, float ipWidth);
    
    ~Camera() {
    }
    /**
     * re-calculate the camera's basis so that it faces a specified point in
     * the scene
     * @param point the point for the camera to center on
     */
    void setLookAtPoint(const Vector3D& point);
    
     

    void setPosition(const Vector3D& pos) {
        position = pos;
    }
    void setFocalLength(float fLength) {
        focalLength = fLength;
    }

    void setImagePlaneWidth(float ipWidth) {
        imagePlaneWidth = ipWidth;
    }
    void setDepthOfField(float depth){
        depthOfField = depth;
    }
    void setLensRadius(float radius){
        lensRadius = radius;
    }
    Shape * getFieldOfView();
    void setResolution(int x, int y) {
        resX = x;
        resY = y;
    }

    int getResX() {
        return resX;
    }

    int getResY() {
        return resY;
    }

    /**
     * Given a direction vector, calculate an orthonormal basis pointing in that
     * direction
     * @param dir the direction vector
     */
    void setBasis(const Vector3D& dir);

    /**
     * For a given pixel on the image, set the viewing ray to point through
     * that pixel.
     * @param i pixel x-coordinate
     * @param j pixel y-coordinate
     * @param ray the viewing ray to be set.
     */
    virtual void computeRay(int i, int j, Ray& ray) = 0;

    std::string getName() {
        return name;
    }

    void setName(string newName) {
        name = newName;
    }
};
#endif			
