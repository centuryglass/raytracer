

#include "LightMap.h"
#include "Light.h"
#include "AreaLight.h"
#include "Camera.h"
#include "cameras/SphereCamera.h"
#include "Ray.h"

LightMap::LightMap() {
    numRays = 16;
    resolution = 200;
}

void LightMap::populateLightMap(Scene* scene) {
    set<Light *> lights = scene->getLights();
    vector<pair <Camera*, Vector3D> > cameras;
    Ray ray;
    Random * rand = new Random();
    ray.setRand(rand);
    ray.setRayNum(0);
    ray.setMaxRayNum(numRays);

    //add cameras for emitting photons from lights
    for (set<Light*>::iterator it = lights.begin(); it != lights.end(); ++it) {
        Light * light = *it;
        if (light->getType() == 'a' && ray.getMaxRayNum() > 1) {
            while (ray.getRayNum() < ray.getMaxRayNum()) {
                Vector3D pos = ((AreaLight *) light)->getLightPt(ray);
                pair<Camera*, Vector3D> p;
                p.first = new SphereCamera(pos, (pos*-1), 0.001, 1);
                p.first->setResolution(resolution, resolution);
                p.second.set(light->getIntensity());
                cameras.push_back(p);
                ray.setRayNum(ray.getRayNum() + 1);
            }
            ray.setRayNum(0);
        } else {
            Vector3D pos = light->getPosition();
            pair<Camera*, Vector3D> p;
            p.first = new SphereCamera(pos, (pos*-1), 0.001, 1);
            p.first->setResolution(resolution, resolution);
            p.second = light->getIntensity();
            cameras.push_back(p);
        }
    }

    //for each camera, shoot out rays, and save the results in the tree.
    Shape * visible = scene->getCamera()->getFieldOfView();
    int camNum = 1;
    int res = resolution / (cameras.size()/4);
    for (vector<pair<Camera*, Vector3D> >::iterator it = cameras.begin(); it != cameras.end(); ++it) {
        cout << "Building photon map: mapping light "
                << camNum << " of " << cameras.size() << endl;
        camNum++;
        (*it).first->setResolution(res, res);
        int lastPercent = 0;
        int pCount = 0;
        for (int x = 0; x < res; x++) {
            for (int y = 0; y < res; y++) {
                for (int i = 0; i < numRays; i++) {
                    ray.setRayNum(i);
                    (*it).first->computeRay(x, y, ray);
                    HitStruct hit;
                    float tmin = 0;
                    float tmax = 99999;
                    bool intersect =
                            scene->intersect(ray, tmin, tmax, hit);
                    if (intersect) {// && hit.getShape()->getShader()->getType() == "Dielectric") {
                        Vector3D photon = hit.getShape()->getShader()->
                                mapLightRay(scene, hit, (*it).second, 0);
                        HitStruct hit2;
                        Ray ray2 = ray;
                        Vector3D dir = hit.getIntersect();
                        dir.normalize();
                        //don't save photons outside of the field of view
                        if (!(visible->intersect(ray2, 0.001, hit.getT(), hit2))) {
                            if (photon[0] > 0 || photon[1] > 0 || photon[2] > 0) {
                                pair<Vector3D, Vector3D> p;
                                p.first = hit.getIntersect();
                                p.second = photon;
                                photonMap.photons.push_back(p);
                                pCount++;
                            }
                        }
                    }
                }
            }
            if (((double) x / res * 100)>(lastPercent + 5)) {
                lastPercent = (double) x / res * 100;
                cout << lastPercent << " percent complete, "
                        << pCount << " photons added to map.\n";
                pCount = 0;
            }
        }
    }
    cout << "Optimizing: ";
    photonTree = new PhotonTree
            (3 /*dim*/, photonMap,
            KDTreeSingleIndexAdaptorParams(photonMap.kdtree_get_point_count()));
    photonTree->buildIndex();
    cout << "photon map generated!\n";
    cout << "Map contains " << photonMap.photons.size() << " photons.\n";

    int CRes = res * 3;
    camNum = 1;
    for (vector<pair<Camera*, Vector3D> >::iterator it = cameras.begin(); it != cameras.end(); ++it) {
        cout << "Building caustics map: mapping light "
                << camNum << " of " << cameras.size() << endl;
        (*it).first->setResolution(CRes, CRes);
        camNum++;
        int lastPercent = 0;
        int pCount = 0;
        for (int x = 0; x < CRes; x++) {
            for (int y = 0; y < CRes; y++) {
                for (int i = 0; i < numRays; i++) {
                    ray.setRayNum(i);
                    (*it).first->computeRay(x, y, ray);
                    HitStruct hit;
                    float tmin = 0;
                    float tmax = 99999;
                    bool intersect =
                            scene->intersect(ray, tmin, tmax, hit);
                    if (intersect && hit.getShape()->getShader()->getType() == "Dielectric") {
                        Vector3D photon = hit.getShape()->getShader()->
                                mapLightRay(scene, hit, (*it).second, 0);
                        HitStruct hit2;
                        Ray ray2 = ray;
                        Vector3D dir = hit.getIntersect();
                        dir.normalize();
                        //don't save photons outside of the field of view
                        if (!(visible->intersect(ray2, 0.001, hit.getT(), hit2))) {
                            if (photon[0] > 0 || photon[1] > 0 || photon[2] > 0) {
                                pair<Vector3D, Vector3D> p;
                                p.first = hit.getIntersect();
                                p.second = photon;
                                causticsMap.photons.push_back(p);
                                pCount++;
                            }
                        }
                    }
                }
            }
            if (((double) x / CRes * 100)>(lastPercent + 5)) {
                lastPercent = (double) x / CRes * 100;
                cout << lastPercent << " percent complete, "
                        << pCount << " photons added to map.\n";
                pCount = 0;
            }
        }

    }
    cout << "Optimizing: ";
    causticsTree = new PhotonTree
            (3 /*dim*/, causticsMap,
            KDTreeSingleIndexAdaptorParams(causticsMap.kdtree_get_point_count()));
    causticsTree->buildIndex();
    cout << "photon map generated!\n";
    cout << "Map contains " << causticsMap.photons.size() << " photons.\n";
}

Vector3D LightMap::getClosest(Vector3D target, double max) {
    vector <pair<long unsigned int, double> > results;
    nanoflann::SearchParams params;
    double sum = 0;
    Vector3D photon;
    if (causticsMap.photons.size() > 5) {
        double cMax = .01;
        causticsTree->radiusSearch(&target[0], cMax, results, params);
        if (results.size() > 5) {//one photon isn't enough for a good render
            for (vector<pair<long unsigned int, double> >::iterator it = results.begin();
                    it != results.end(); it++) {
                //if ((*it).second == 0) return photonMap.photons[(*it).first].second;
                double strength = pow((cMax - (*it).second) / cMax, 3);
                sum += 1;
                //      sum++;
                photon += (causticsMap.photons[(*it).first].second * strength);
            }

            if (photon[0] > 0 || photon[1] > 0 || photon[2] > 0)
              photon *= (1.0 / sum);
            photon.clamp(0, 1);
        }
        results.clear();
    }
    Vector3D photon2;
    photonTree->radiusSearch(&target[0], max, results, params);
    if (results.size() > 0) {//one photon isn't enough for a good render
        sum = 0;
        //Average all visible photons
        for (vector<pair<long unsigned int, double> >::iterator it = results.begin();
                it != results.end(); it++) {
            double strength = pow((max - (*it).second) / max, 5);
            sum += 1;
            //      sum++;
            photon2 += (photonMap.photons[(*it).first].second * strength);
        }

        if (photon2[0] > 0 || photon2[1] > 0 || photon2[2] > 0){
            photon2 *= (1.0 / sum);
            photon += photon2;
        }       
        photon.clamp(0, 1);
    }
    //cout<<photon<<endl;
    return photon;

}
