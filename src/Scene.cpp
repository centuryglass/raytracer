//Author: Anthony Brown
#include "Scene.h"
#include "Ray.h"
#include "shapes/ShapeContainer.h"
//removes all stored scene elements

Scene::Scene() {
    shapes = new ShapeContainer();
    color.set(0, 0, 0);
    useShadow = true;
    generatePhotonMap = true;
    photonRadius = 2;
}

Scene::~Scene() {
    delete shapes;
}

void Scene::resetScene() {
    shapes->clear();
    lights.clear();
}

//Returns true if r intersects a shape within the scene
//Hitstruct contains information about the closest collision

bool Scene::intersect(Ray &r, float tmin, float tmax, HitStruct &hit) {
    hit.reset();
    if (shapes->shapeCount() == 0) return false;


    return shapes->intersect(r, tmin, tmax, hit);
}

void Scene::insertShape(Shape * shape) {
    shapes->addShape(shape);
}

void Scene::buildShapeTree() {
    shapes->buildTree();
    if(generatePhotonMap){
        lightMap = new LightMap();
        lightMap->populateLightMap(this);
    }
}

int Scene::shapeCount() {
    return shapes->shapeCount();
}