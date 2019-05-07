/* 
 * File:   TextureCalculator.cpp
 * Author: Anthony
 * 
 * Created on April 14, 2013, 12:03 PM
 */

#include "TextureCalculator.h"
#include <cmath>
#include <iostream>
using namespace std;
#include "Random.h"
using namespace sivelab;

TextureCalculator::TextureCalculator() {
    //For each integer coordinate, generate a random normalized gradient.
    Random rand;
    for (int y = 0; y < 50; y++) {
        for (int x = 0; x < 50; x++) {
            perlinGradients[x][y] = rand.uniform();
        }
    }

}

Vector3D TextureCalculator::perlinNoiseFunction(double x, double y){
    while (x > 49) x -= 49;
    while (y > 49) y -= 49;
    Vector3D color;
    double cval = 0;
    for (int i = 0; i <= 1;i++) {
        for (int j = 0; j <= 1; j++) {
            double xCorner=(int)x+i;
            double yCorner=(int)y+j;
            double weight =  ((1- abs(x-xCorner))
            * (1-(abs(y-yCorner))));
            double perlinVal = perlinGradients[(int)xCorner][(int)yCorner];
            cval += perlinVal *  weight;
        }
    }
    color.set(cval, cval, cval);
    return color;
}
Vector3D TextureCalculator::turbulenceFunction(double x, double y, int i){
    Vector3D color;
    for(int n = 1; n<=i;n++ ){
        color += 
            (perlinNoiseFunction(pow(2,n)*x,pow(2,n)*y)*((double)1/pow(2,n)));
    }   
    return color;
}

