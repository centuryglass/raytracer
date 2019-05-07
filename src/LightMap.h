/* 
 * File:   LightMap.h
 * Author: Anthony
 *
 * Created on May 15, 2013, 5:09 PM
 */

#ifndef LIGHTMAP_H
#define	LIGHTMAP_H
#include "nanoflann.hpp"
using namespace nanoflann;

#include <iostream>
#include <vector>
#include <limits>
#include <functional>
#include <set>
using namespace std;
#include "Vector3D.h"
#include "Random.h"
using namespace sivelab;
#include "Scene.h"

class Scene;

struct PhotonMap {
    std::vector< pair<Vector3D, Vector3D> > photons;

    // Must return the number of data points

    inline size_t kdtree_get_point_count() const {
        return photons.size();
    }

    // Returns the distance between the vector "p1[0:size-1]" and the data point with index "idx_p2" stored in the class:

    inline double kdtree_distance(const double *p1, const size_t idx_p2, size_t size) const {
        const double d0 = p1[0] - photons[idx_p2].first[0];
        const double d1 = p1[1] - photons[idx_p2].first[1];
        const double d2 = p1[2] - photons[idx_p2].first[2];
        return d0 * d0 + d1 * d1 + d2*d2;
    }

    // Returns the dim'th component of the idx'th point in the class:
    // Since this is inlined and the "dim" argument is typically an immediate value, the
    //  "if/else's" are actually solved at compile time.

    inline double kdtree_get_pt(const size_t idx, int dim) const {
        if (dim == 0) return photons[idx].first[0];
        else if (dim == 1) return photons[idx].first[1];
        else return photons[idx].first[2];
    }

    template <class BBOX>
    bool kdtree_get_bbox(BBOX &bb) const {
        return false;
    }
};

typedef KDTreeSingleIndexAdaptor<
L2_Simple_Adaptor<double, PhotonMap >,
PhotonMap,
3 /* dim */
> PhotonTree;

class LightMap {
private:
    PhotonMap photonMap;
    PhotonMap causticsMap;
    PhotonTree * photonTree;
    PhotonTree * causticsTree;
    int numRays;
    int resolution;
public:

    LightMap();

    ~LightMap() {
        delete photonTree;
    }

    Vector3D getClosest(Vector3D target, double max);

    void populateLightMap(Scene * s);
private:

};


#endif	/* LIGHTMAP_H */

