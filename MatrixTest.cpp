/* 
 * File:   MatrixTest.cpp
 * Author: Anthony
 *
 * Created on April 12, 2013, 12:45 PM
 */

#include <iostream>
using namespace std;
#include "Matrix4x4.h"
using namespace ablib;
#include "Random.h"
using namespace sivelab;

/*
 * 
 */
int main() {
    Random prng;
    Matrix4x4 m1(static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)));


    Matrix4x4 m2(static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)),
            static_cast<double> (floor(prng.uniform() * 20)));


    cout << "Random matrix m1:\n";
    cout << m1 << endl;
    cout << "m1 determinant:" << m1.determinant() << endl;
    Matrix4x4 m = m1.inverse();
    cout << "m1 inverse:\n" << m << endl;

    cout << "Random matrix m2:\n";
    cout << m2 << endl;

    m = m1 + m2;
    cout << "m1 + m2 =\n" << m << endl;
    m = m1 * m2;
    cout << "m1 * m2 =\n" << m << endl;
    
 

    return 0;
}

