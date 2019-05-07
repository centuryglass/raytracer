#include "BoundingBox.h"

 BoundingBox::BoundingBox() {

        e = 0.001;
        bboxMin[0] = std::numeric_limits<float>::max();
        bboxMin[1] = std::numeric_limits<float>::max();
        bboxMin[2] = std::numeric_limits<float>::max();

        bboxMax[0] = -bboxMin[0];
        bboxMax[1] = -bboxMin[1];
        bboxMax[2] = -bboxMin[2];
    }

    Vector3D BoundingBox::center() {
        Vector3D c(((bboxMax[0] - bboxMin[0]) / 2) + bboxMin[0],
                ((bboxMax[1] - bboxMin[1]) / 2) + bboxMin[1],
                ((bboxMax[2] - bboxMin[2]) / 2) + bboxMin[2]);
        return c;
    }

    bool BoundingBox::intersect(Ray& r) {
        if(bboxMin[0] > bboxMax[0])return false;
        double tXmin, tXmax, tYmin, tYmax, tZmin, tZmax;
        Vector3D direction = r.getDirection();
        tXmin = (bboxMin[0] - r.getOrigin()[0]) / direction[0];
        tXmax = (bboxMax[0] - r.getOrigin()[0]) / direction[0];
        if (tXmin > tXmax) {
            double temp = tXmin;
            tXmin = tXmax;
            tXmax = temp;
        }

        tYmin = (bboxMin[1] - r.getOrigin()[1]) / direction[1];
        tYmax = (bboxMax[1] - r.getOrigin()[1]) / direction[1];
        if (tYmin > tYmax) {
            double temp = tYmin;
            tYmin = tYmax;
            tYmax = temp;
        }
        
        if (tXmin > tYmax) {
            return false;
        } else if (tYmin > tXmax) {
            return false;
        }

        tZmin = (bboxMin[2] - r.getOrigin()[2]) / direction[2];
        tZmax = (bboxMax[2] - r.getOrigin()[2]) / direction[2];
        if (tZmin > tZmax) {
            double temp = tZmin;
            tZmin = tZmax;
            tZmax = temp;
        }

        //tXmax += e;
        //tYmax += e;
        //tZmax += e;
        if (tXmin > tZmax) {
            return false;
        } else if (tYmin > tZmax) {
            return false;
        } else if (tZmin > tXmax) {
            return false;
        } else if (tZmin > tYmax) {
            return false;
        } else {
            return true;
        }
    }

    void BoundingBox::update(float x, float y, float z) {
        if (x > bboxMax[0]) bboxMax[0] = x;
        if (y > bboxMax[1]) bboxMax[1] = y;
        if (z > bboxMax[2]) bboxMax[2] = z;

        if (x < bboxMin[0]) bboxMin[0] = x;
        if (y < bboxMin[1]) bboxMin[1] = y;
        if (z < bboxMin[2]) bboxMin[2] = z;
    }

    void BoundingBox::combine(BoundingBox b2) {
        update(b2.bboxMax[0],b2.bboxMax[1],b2.bboxMax[2]);
        update(b2.bboxMin[0],b2.bboxMin[1],b2.bboxMin[2]);
    }

    void BoundingBox::reset() {
        bboxMin[0] = std::numeric_limits<float>::max();
        bboxMin[1] = std::numeric_limits<float>::max();
        bboxMin[2] = std::numeric_limits<float>::max();

        bboxMax[0] = -bboxMin[0];
        bboxMax[1] = -bboxMin[1];
        bboxMax[2] = -bboxMin[2];
    }
