/*Light.h
 *Author: Anthony Brown
 *Represents a point of light in the scene
 */
#ifndef __LIGHT__
#define __LIGHT__

#include "Vector3D.h"
using namespace sivelab;

class Light {
protected:
    char type;
    Vector3D pos;
    Vector3D intens;
public:

    Light(const Vector3D& position, const Vector3D& intensity) {
        pos = position;
        intens = intensity;
        type = 'p';
    }

    ~Light() {
    }

    Vector3D getPosition() {
        return pos;
    }

    Vector3D getIntensity() {
        return intens;
    }
    
    char getType(){return type;}
};
#endif	