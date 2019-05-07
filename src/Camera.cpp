//Author: Anthony Brown
#include "Camera.h"
#include "shapes/Triangle.h"
#include "shapes/ShapeContainer.h"
using namespace sivelab;

Camera::Camera(const Vector3D& pos, const Vector3D& dir,
        float fLength, float ipWidth) {
    position = pos;
    focalLength = fLength;
    imagePlaneWidth = ipWidth;
    setResolution(500, 500); //default values
    setBasis(dir);
    depthOfField = 0;
    lensRadius = .08;
}

void Camera::setBasis(const Vector3D& dir) {
    basis.calculateBasis(dir);
}

void Camera::applyDepthOfField(Ray& ray,Vector3D& dir) {
    int rayNum = ray.getRayNum();
    int dimension = sqrt(ray.getMaxRayNum());
    //get point on lens
    float u, v;
    u = ((rayNum % dimension) + ray.getRand())
            *(lensRadius / dimension);
    v = ((rayNum / dimension) + ray.getRand())
            *(lensRadius / dimension);
    Vector3D lensPt = ((basis.getW()) * depthOfField )+
            ((basis.getU()) * u) +
            ((basis.getV()) * v);
    dir =(dir * lensPt.length()*2) - lensPt;
    dir.normalize();
    ray.setOrigin(lensPt + position);
    ray.setDirection(dir);

}

void Camera::setLookAtPoint(const Vector3D& point) {
    Vector3D point2 = point - position;
    basis.calculateBasis(point2);
}

Shape * Camera::getFieldOfView(){
    //get the four corners of the image plane
    Ray ray;
    computeRay(1,1,ray);
    Vector3D lt = ray.getOrigin()+ray.getDirection();
    computeRay(resX,1,ray);
    Vector3D rt = ray.getOrigin()+ray.getDirection();
    computeRay(1,resY,ray);
    Vector3D lb = ray.getOrigin()+ray.getDirection();
    computeRay(resX,resY,ray);
    Vector3D rb = ray.getOrigin()+ray.getDirection();

    
    Shape * t = new Triangle(position,lt*9999,rt*9999);
    Shape * b= new Triangle(position,lb*9999,rb*9999);
    Shape * l= new Triangle(position,lt*9999,lb*9999);
    Shape * r= new Triangle(position,rb*9999,rt*9999);
    ShapeContainer * s = new ShapeContainer();
    s->addShape(t);
    s->addShape(b);
    s->addShape(l);
    s->addShape(r);
    s->buildTree();
    return ((Shape *)s);
}




