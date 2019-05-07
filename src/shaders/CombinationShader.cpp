/* 
 * File:   CombinationShader.cpp
 * Author: Anthony
 * 
 * Created on May 11, 2013, 6:55 PM
 */

#include "CombinationShader.h"
#include <vector>
using namespace std;

Vector3D CombinationShader::getShadow(HitStruct &hit, Light * l, Scene * scene) {
    Vector3D shadowMult;
    for (std::set<pair<Shader*, double> >::iterator it = shaders.begin();
            it != shaders.end(); ++it) {
        HitStruct subHit = hit;
        shadowMult += (it->first->getShadow(subHit, l, scene) * it->second);
    }
    return shadowMult;
}

Vector3D CombinationShader::getHitColor(Scene* scene, HitStruct& hit) {
    Vector3D shade;
    for (std::set<pair<Shader*, double> >::iterator it = shaders.begin();
            it != shaders.end(); ++it) {
        HitStruct subHit = hit;
        shade += (it->first->getHitColor(scene, subHit) * it->second);
    }
    shade.clamp(0,1);
    return shade;
}

Vector3D CombinationShader::mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth){
    vector <double> probabilities;
    for (std::set<pair<Shader*, double> >::iterator it = shaders.begin();
            it != shaders.end(); ++it) {
        probabilities.push_back(it->second);
    }
    double sum = 0;
    for (vector<double>::iterator it = probabilities.begin();
            it != probabilities.end(); ++it) sum += (*it);
    for (vector<double>::iterator it = probabilities.begin();
            it != probabilities.end(); ++it) (*it) /= sum;
    double rand = hit.getViewingRay().getRand();
    
    std::set<pair<Shader*, double> >::iterator it2 = shaders.begin();
     for (vector<double>::iterator it = probabilities.begin();
            it != probabilities.end(); ++it){
         if(rand <= (*it)) return it2->first->mapLightRay(scene, hit, light,depth);
         it2++;
     }
}