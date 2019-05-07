/* 
 * File:   TextureCalculator.h
 * Author: Anthony
 *
 * Created on April 14, 2013, 12:03 PM
 */

#ifndef TEXTURECALCULATOR_H
#define	TEXTURECALCULATOR_H

#include "Vector3D.h"
using namespace sivelab;
class TextureCalculator {
public:
    TextureCalculator();
    ~TextureCalculator(){}
    
    Vector3D perlinNoiseFunction(double x, double y);
    Vector3D turbulenceFunction(double x, double y, int i);
private:
    double perlinGradients [50][50];
};

#endif	/* TEXTURECALCULATOR_H */

