//Author: Anthony Brown
#include "Basis.h"
using namespace sivelab;

void Basis::calculateBasis(const Vector3D& dir) {
    //W = −gaze/||gaze||
    W = dir;
    W *= -1;
    W.normalize();

    //set b to (0,1,0)
    Vector3D b(0, 1, 0);

    //if W is colinear to b, reset b to (0,0,1)
    if (((b.dot(W)) == 1) || ((b.dot(W)) == -1)) {
        b.set(1,0,0);
    }

    //U = bx W /||bx W ||
    U = b.cross(W);
    U.normalize();

    //V = W x U
    V = W.cross(U);
}


