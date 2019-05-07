/*Shader.h
 *Author: Anthony Brown
 *An abstract base class for all shaders
 */

#ifndef __SHADER__
#define __SHADER__

#include "Vector3D.h"
#include "Scene.h"
#include "HitStruct.h"
using namespace sivelab;
#include <string>
using namespace std;

class Scene;
class HitStruct;

class Shader {
protected:
    string name;
    string type;
    double roughness;

public:

    Shader() {
        roughness = 0;
    }

    ~Shader() {
    }
    /**
     * Given a hitpoint, return the color data for that hit
     * @param scene The scene in which the hit occured.
     * @param hit The hitStructure containing data about the hit
     * @return The calculated color value.
     */
    virtual Vector3D getHitColor(Scene* scene, HitStruct& hit) = 0;

    //If asked, return a shadow multiplier. This is 0,0,0, except
    //in the case of luminous or transparent objects.
    virtual Vector3D getShadow(HitStruct &hit, Light * l, Scene * scene) = 0;

    Vector3D calculateShadowMult
    (HitStruct& hit, Light * light, Vector3D lightDir, Scene * scene);

    bool calculateReflection(HitStruct& hit, Scene * scene);
    
    virtual Vector3D mapLightRay(Scene* scene, HitStruct& hit, Vector3D light,int depth) = 0;

    void setRoughness(double r) {
        roughness = r;
    }
    string getType(){return type;}
    std::string getName() {
        return name;
    }

    void setName(string newName) {
        name = newName;
    }
};
#endif	
