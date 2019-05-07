/*Basis.h
 *Author: Anthony Brown
 *Defines the orthonormal basis used by the camera class to calculate viewing rays
 */

#ifndef __BASIS__
#define __BASIS__

#include "Vector3D.h"
using namespace sivelab;

class Basis {
private:
    Vector3D U;
    Vector3D V;
    Vector3D W;
public:

    Basis() {
    }

    ~Basis() {
    }

   /**
    * Calculates an orthonormal basis centered on a given direction vector
    * @param dir the direction vector.
    */
    void calculateBasis(const Vector3D& dir);

    Vector3D getU() {
        return U;
    }

    Vector3D getV() {
        return V;
    }

    Vector3D getW() {
        return W;
    }
};
#endif		
