/*Ray.h
 *Author: Anthony Brown
 *Represents 3D rays parametrically, as a direction vector and an origin vector
 */
#ifndef __RAY__
#define __RAY__

#include "Vector3D.h"
#include "Random.h"
using namespace sivelab;
#include <set>
#include <cmath>
using namespace std;

class Ray {
private:
    Vector3D direction;
    Vector3D origin;
    int rayNumber;
    int maxRayNumber;
    Random * rand;
    Vector3D lastPhoton;
public:

    Ray() {
        rayNumber = 0;
        maxRayNumber = 1;
    }

    double getRand() {
        return rand->uniform();
    }

    Random * getRandPtr() {
        return rand;
    }

    void setRand(Random * r) {
        rand = r;
    }

    ~Ray() {
    }

    void setDirection(const Vector3D& dir) {
        direction = dir;
    }

    void setOrigin(const Vector3D& orig) {
        origin = orig;
    }

    Vector3D getDirection() {
        return direction;
    }

    Vector3D getOrigin() {
        return origin;
    }

    void setPhoton(const Vector3D& photon) {
        lastPhoton.set(photon);
    }

    Vector3D getPhoton() {
        return lastPhoton;
    }

    int getRayNum() {
        return rayNumber;
    }

    void setRayNum(int n) {
        rayNumber = n;
    }

    int getMaxRayNum() {
        return maxRayNumber;
    }

    void setMaxRayNum(int n) {
        maxRayNumber = n;
    }
};
#endif		
