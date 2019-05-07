/* 
 * File:   Mesh.cpp
 * Author: Anthony
 * 
 * Created on April 14, 2013, 5:19 PM
 */

#include "Mesh.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

bool Mesh::intersect(Ray& r, float tmin, float tmax, HitStruct &hit) {
    if (!bbox.intersect(r))return false;
    bool hitFound = false;
    axis = -1;//this exclusion method doesn't quite work yet, so it's turned off
    if (axis != -1) {
        //because our bounding boxes have no overlap and are divided along
        //an axis, a hit in the closer box means we don't have to bother
        //looking for a hit in the farther box
        if (r.getDirection()[axis] > 0) {
            if (left->intersect(r, tmin, tmax, hit)) return true;
            else return right->intersect(r, tmin, tmax, hit);
        } else {
            if (right->intersect(r, tmin, tmax, hit)) return true;
            else return left->intersect(r, tmin, tmax, hit);
        }

    } else {
        for (set<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
            if ((*it)->intersect(r, tmin, tmax, hit)) {
                tmax = hit.getT();
                hitFound = true;
            }
        }
    }
    return hitFound;

}

void Mesh::getTextureCoordinates
(HitStruct & hit, double& s, double& t) {
    //figure out which shape is being hit
    HitStruct subHit;
    bool foundHit = false;
    float tmin = 0.001;
    float tmax = 99999;
    Ray r = hit.getViewingRay();
    axis = -1;//this exclusion method doesn't quite work yet, so it's turned off
    if (axis != -1) {
        if (r.getDirection()[axis] > 0) {
            if (left->intersect(r, tmin, tmax, subHit)) foundHit = true;
            else if (right->intersect(r, tmin, tmax, subHit)) foundHit = true;
        } else {
            if (right->intersect(r, tmin, tmax, subHit)) foundHit = true;
            else if (left->intersect(r, tmin, tmax, subHit)) foundHit = true;
        }

    } else {
        for (set<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
            if ((*it)->intersect(r, tmin, tmax, subHit)) {
                tmax = subHit.getT();
                foundHit = true;
            }
        }
    }
    if (foundHit) {
        subHit.getShape()->getTextureCoordinates(subHit, s, t);
    } else {
        s = 0;
        t = 0;
    }
    if (s > 1) s = 1;
    if (s < 0) s = 0;
    if (t > 1) t = 1;
    if (t < 0) t = 0;
}

BoundingBox Mesh::buildTree() {
    if (shapeCount() > 2) {
        double center = 0;
        double gap = 0;
        double range;
        vector <double> gapsX = sortGaps(0);
        vector <double> gapsY = sortGaps(1);
        vector <double> gapsZ = sortGaps(2);

        for (set<Shape*>::iterator it = shapes.begin();
                it != shapes.end(); ++it) {
            bbox.combine((*it)->getBoundingBox());
        }
        //find the biggest gap between shapes, set it as the dividing point
        for (int i = 0; i <= 2; i++) {
            //sort gaps by location along axis
            vector <double> gaps;
            if (i == 0)gaps = gapsX;
            if (i == 1)gaps = gapsY;
            if (i == 2)gaps = gapsZ;
            if (gaps.size() > 0) {

                for (int j = 0; j < (gaps.size() - 2); j += 2) {
                    double c1 = gaps[j];
                    double c2 = gaps[j + 1];
                    if ((c2 - c1) > gap) {
                        gap = c2 - c1;
                        center = (c2 + c1) / 2;
                        axis = i;
                        range = bbox.bboxMax[i] - bbox.bboxMin[i];
                    }
                }
            }
        }
        //if the gap is less than a 10th of the range, it's probably
        //not significant enough that it should be used.
        //instead, divide by the median that most evenly splits the
        //shapes
        if (gap <= (range / 10)) {
            int imbalance = 99999;
            for (int i = 0; i <= 2; i++) {
                //sort gaps by location along axis
                vector <double> gaps;
                if (i == 0)gaps = gapsX;
                if (i == 1)gaps = gapsY;
                if (i == 2)gaps = gapsZ;
                if (gaps.size() > 0) {
                    //find center (median) point
                    double tempCenter;
                    int index = 0;
                    while ((index + 2) <= (gaps.size() / 2)) index += 2;
                    tempCenter = (gaps[index] + gaps[index + 1]) / 2;

                    int a = 0;
                    int b = 0;
                    for (set<Shape*>::iterator it = shapes.begin();
                            it != shapes.end(); ++it) {
                        if ((*it)->getCenter()[i] < tempCenter) {
                            a++;
                        } else {
                            b++;
                        }
                    }
                    //make sure to reject cases where one side doesn't get any
                    //shapes
                    if (abs(a - b) < imbalance && (a != 0) &&(b != 0)) {
                        imbalance = abs(a - b);
                        axis = i;
                        center = tempCenter;
                    }
                }
            }
        }
        //if we still haven't found a dividing point with zero overlap, divide
        //around the median object, leaving axis as -1 since the bounding boxes
        //aren't separate.
        int tempAxis = axis;
        if (axis == -1) {
            int imbalance = 99999;
            for (int i = 0; i <= 2; i++) {
                //sort shapes by size
                vector <double> centers;
                for (set<Shape*>::iterator it2 = shapes.begin();
                        it2 != shapes.end(); ++it2) {
                    centers.push_back(((*it2)->getCenter()[i]));
                }
                sort(centers.begin(), centers.end());
                //find center (median) point
                float tempCenter;
                if ((centers.size() % 2) == 0)
                    tempCenter =
                        (centers[centers.size() / 2 - 1]
                        + centers[centers.size() / 2]) / 2;
                else tempCenter = centers[centers.size() / 2];
                int a = 0;
                int b = 0;
                for (set<Shape*>::iterator it = shapes.begin();
                        it != shapes.end(); ++it) {
                    if ((*it)->getCenter()[i] < tempCenter) {
                        a++;
                    } else {
                        b++;
                    }
                }
                if (abs(a - b) < imbalance && a != 0 && b != 0) {
                    imbalance = abs(a - b);
                    tempAxis = i;
                    center = tempCenter;
                }
            }
        }
        //if we still haven't found a valid dividing point, there's just
        //too much overlap to sort these shapes into separate boxes
        if (tempAxis == -1) {
            for (set<Shape*>::iterator it = shapes.begin();
                    it != shapes.end(); ++it) {
                bbox.combine((*it)->getBoundingBox());
            }
            return bbox;
        }
        //sort all shapes into two sub-meshes
        Mesh * a = new Mesh();
        Mesh * b = new Mesh();
        int aCount = 0;
        int bCount = 0;
        //while sorting, see if there's any overlap, if there is, set axis= -1
        //to prevent inappropriate branch culling in intersection tests
        for (set<Shape*>::iterator it = shapes.begin();
                it != shapes.end(); ++it) {
            if (((*it)->getCenter())[tempAxis] < center) {
                a->addShape(*it);
                if((*it)->getBoundingBox().bboxMax[tempAxis]>center)
                    axis = -1;
                aCount++;
            } else {
                b->addShape(*it);
                if((*it)->getBoundingBox().bboxMin[tempAxis]<center)
                    axis = -1;
                bCount++;
            }
        }
        left = a;
        right = b;

        //empty shape set
        shapes.clear();
        //both trees contain elements
        bbox.combine(a->buildTree());
        bbox.combine(b->buildTree());
        shapes.insert(a);
        shapes.insert(b);
        return bbox;


    } else {
        //we're at the bottom layer of recursion
        if (shapeCount() == 2) {
            set<Shape*>::iterator it = shapes.begin();
            Shape * shape1 = *it;
            it++;
            Shape * shape2 = *it;
            bbox.combine(shape1->getBoundingBox());
            bbox.combine(shape2->getBoundingBox());
            for (int i = 0; i <= 2; i++) {
                if (shape1->getBoundingBox().bboxMin[i] <
                        shape2->getBoundingBox().bboxMin[i]) {
                    left = shape1;
                    right = shape2;
                    axis = i;
                } else if (shape2->getBoundingBox().bboxMin[i] <
                        shape1->getBoundingBox().bboxMin[i]) {
                    left = shape2;
                    right = shape1;
                    axis = i;
                }
            }
        return bbox;
        }
        bbox.combine((*(shapes.begin()))->getBoundingBox());
        return bbox;
    }

}

vector <double> Mesh::sortGaps(int ax) {
    vector <double> gaps;
    vector <double> minPts;
    vector <double> maxPts;
    for (set<Shape*>::iterator it = shapes.begin();
            it != shapes.end(); ++it) {
        minPts.push_back((*it)->getBoundingBox().bboxMin[ax]);
        maxPts.push_back((*it)->getBoundingBox().bboxMax[ax]);
    }
    sort(minPts.begin(), minPts.end());
    sort(maxPts.begin(), maxPts.end());
    int openShapes = 0;
    int j = 0;
    for(int i = 0; i < maxPts.size(); i++){
        while(minPts[j]<maxPts[i] && j<minPts.size()){
            openShapes++;
            j++;
        }
        if(openShapes == 0){
            gaps.push_back(maxPts[i]);
            gaps.push_back(minPts[j]);
        }
        openShapes--;
        
    }
    sort(gaps.begin(), gaps.end());
    return gaps;
}
int Mesh::shapeCount() {
    int count = 0;
    for (set<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
        count += (*it)->shapeCount();
    }
    return count;
}
