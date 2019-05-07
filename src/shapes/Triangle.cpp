//Author: Anthony Brown

#include "Triangle.h"
#include <iostream>
using namespace std;
#include "Basis.h"
#include "Matrix4x4.h"
using namespace ablib;

Triangle::Triangle(const Vector3D& u, const Vector3D& v, const Vector3D& w) {
    v0 = u;
    bbox.update(u[0], u[1], u[2]);
    v1 = v;
    bbox.update(v[0], v[1], v[2]);
    v2 = w;
    bbox.update(w[0], w[1], w[2]);

    normal = (v0 - v1).cross(v2 - v1);
    normal.normalize();
    n2 = (v2 - v1).cross(v0 - v1);
    n2.normalize();

    //for every point P on the plane, P.dot(normal) is constant
    d = (-1 * v0).dot(normal);

    for (int i = 0; i < 3; i++) {
        u1[i] = v1[i] - v0[i];
        u2[i] = v2[i] - v0[i];
    }

    t0.first = -1;
    t0.second = -1;
    t1.first = -1;
    t1.second = -1;
    t2.first = -1;
    t2.second = -1;

}

bool Triangle::intersect(Ray &r, float tmin, float tmax, HitStruct &hit) {
    if (!bbox.intersect(r))return false;
    //Efficient intersect algorithm found at
    //http://graphics.stanford.edu/courses/cs348b-98/gg/intersect.html
    float nDotD = (normal.dot(r.getDirection()));
    if (nDotD == 0)return false;
    float t = (-1 * (d + (normal.dot(r.getOrigin()))))
            / nDotD;
    if (t < tmin)return false;
    if (t > tmax)return false;

    int ax0 = 0;
    int ax1 = 1;
    int ax2 = 2;
    if (abs(normal[1]) > abs(normal[ax0]))ax0 = 1;
    if (abs(normal[2]) > abs(normal[ax0]))ax0 = 2;
    if (ax0 == 1)ax1 = 0;
    else if (ax0 == 2)ax2 = 0;

    Vector3D inter = t * r.getDirection() + r.getOrigin();
    float u0, w0,  alpha, beta;
    u0 = inter[ax1] - v0[ax1];
    w0 = inter[ax2] - v0[ax2];
    alpha = -1;
    if (u1[ax1] == 0) {
        beta = u0 / u2[ax1];
        if (beta >= 0 || beta <= 1) alpha = (w0 - beta * u2[ax2]) / u1[ax2];
    } else {
        beta = (u1[ax1] * w0 - u0 * u1[ax2]) 
                / (u1[ax1] * u2[ax2] - u2[ax1] * u1[ax2]);
        if (beta >= 0 && beta <= 1) alpha = (u0 - beta * u2[ax1]) / u1[ax1];
    }
    //cout << alpha << " " << beta<<endl;
    if (alpha < 0)return false;
    if (beta < 0)return false;
    if ((alpha + beta) > 1) return false;

    //        float gamma = (i * akjb
    //                + h * jcal
    //                + g * blkc) / m;
    //        if (gamma < 0)return false;
    //        if (gamma > 1)return false;
    //    
    //        float beta = (j * eihf
    //                + k * gfdi
    //                + l * (dheg)) / m;
    //        if (beta < 0)return false;
    //        if(beta > (1 - gamma))return false;

    if ((normal.dot(r.getDirection()))<((n2.dot(r.getDirection())))) {
        hit.add(this, t, normal, inter, r);
    } else {

        hit.add(this, t, n2, inter, r);
    }
    return true;
}

void Triangle::getTextureCoordinates(HitStruct & hit, double& s, double& t) {

    int ax1 = 0;
    int ax2 = 1;
    if (t0.first == -1) {//if texture coordinates aren't designated 
        //Find smin + smax.  s equals the x axis unless smin==smax, in
        //which case s equals the z axis.
        double smin, smax;
        smin = v0[0];
        if (smin > v1[0]) {
            smin = v1[0];
        }
        if (smin > v2[0]) {
            smin = v2[0];
        }
        smax = v0[0];
        if (smax < v1[0]) {
            smax = v1[0];
        }
        if (smax < v2[0]) {
            smax = v2[0];
        }
        if (smin >= smax) {
            ax1 = 2;
            smin = v0[2];
            if (smin > v1[2]) {
                smin = v1[2];
            }
            if (smin > v2[2]) {
                smin = v2[2];
            }
            smax = v0[2];
            if (smax < v1[2]) {
                smax = v1[2];
            }
            if (smax < v2[2]) {
                smax = v2[2];
            }
        }

        double tmin, tmax;
        tmin = v0[1];
        if (tmin > v1[1]) {
            tmin = v1[1];
        }
        if (tmin > v2[1]) {
            tmin = v2[1];
        }
        tmax = v0[1];
        if (tmax < v1[1]) {
            tmax = v1[1];
        }
        if (tmax < v2[1]) {
            tmax = v2[1];
        }
        if (tmin >= tmax) {
            ax2 = 2;
            tmin = v0[2];
            if (tmin > v1[2]) {
                tmin = v1[2];
            }
            if (tmin > v2[2]) {
                tmin = v2[2];
            }
            if (tmax < v1[2]) {
                tmax = v1[2];
            }
            if (tmax < v2[2]) {
                tmax = v2[2];
            }
        }
        s = ((hit.getIntersect())[ax1] - smin) / (smax - smin);
        t = ((hit.getIntersect())[ax2] - tmin) / (tmax - tmin);

    }//If the triangle has .obj texture mapping
    else {
        //find axes
        double smin, smax;
        smin = v0[0];
        if (smin > v1[0]) {
            smin = v1[0];
        }
        if (smin > v2[0]) {
            smin = v2[0];
        }
        smax = v0[0];
        if (smax < v1[0]) {
            smax = v1[0];
        }
        if (smax < v2[0]) {
            smax = v2[0];
        }
        if (smin >= smax) {
            ax1 = 2;
        }

        double tmin, tmax;
        tmin = v0[1];
        if (tmin > v1[1]) {
            tmin = v1[1];
        }
        if (tmin > v2[1]) {
            tmin = v2[1];
        }
        tmax = v0[1];
        if (tmax < v1[1]) {
            tmax = v1[1];
        }
        if (tmax < v2[1]) {
            tmax = v2[1];
        }
        if (tmin >= tmax) {
            ax2 = 2;
        }
        //find the matrix transformation from global coords. to texture coords.
        //Start by simplifying the triangles into 2d triangles
        //vector triangle
        Vector3D tv0;
        Vector3D tv1;
        Vector3D tv2;

        tv0 [0] = v0 [ax1];
        tv0 [1] = v0 [ax2];
        tv1 [0] = v1 [ax1];
        tv1 [1] = v1 [ax2];
        tv2 [0] = v2 [ax1];
        tv2 [1] = v2 [ax2];
        //texture triangle
        Vector3D tt0;
        Vector3D tt1;
        Vector3D tt2;

        tt0[0] = t0.first;
        tt0[1] = t0.second;

        tt1[0] = t1.first;
        tt1[1] = t1.second;

        tt2[0] = t2.first;
        tt2[1] = t2.second;

        //translate point zero of both triangles to 0,0,0
        //for ease of transformation
        tv1[0] -= tv0[0];
        tv2[0] -= tv0[0];
        tv1[1] -= tv0[1];
        tv2[1] -= tv0[1];

        tv0[0] = 0;
        tv0[1] = 0;

        tt1[0] -= tt0[0];
        tt2[0] -= tt0[0];
        tt1[1] -= tt0[1];
        tt2[1] -= tt0[1];

        tt0[0] = 0;
        tt0[1] = 0;

        Matrix4x4 m;
        m[3][3] = 1;

        //solve to find the matrix M where M*tv1=tt1, and M*tv2=tt2
        //t1[0]=(M[0][0]*v1[0])+(M[1][0]*v1[1])+(M[2][0]*v1[2])+M[3][0];
        //t1[1]=(M[0][1]*v1[0])+(M[1][1]*v1[1])+(M[2][1]*v1[2])+M[3][1];
        //t1[2]=(M[0][2]*v1[0])+(M[1][2]*v1[1])+(M[2][2]*v1[2])+M[3][2];

        //t2[0]=(M[0][0]*v2[0])+(M[1][0]*v2[1])+(M[2][0]*v2[2])+M[3][0];
        //t2[1]=(M[0][1]*v2[0])+(M[1][1]*v2[1])+(M[2][1]*v2[2])+M[3][1];
        //t2[2]=(M[0][2]*v2[0])+(M[1][2]*v2[1])+(M[2][2]*v2[2])+M[3][2];

        //Or, t1[i]=( M[0][i]*v1[0])+(M[1][i]*v1[1])+(M[2][i]*v1[2])
        //t2[i]=(M[0][i]*v2[0])+(M[1][i]*v2[1])+(M[2][i]*v2[2])
        //for each row i
        //(M[1][i]*v1[1]) = t1[i] - (M[0][i]*v1[0]) - (M[2][i]*v1[2])
        //(M[1][i]*v2[1]) = t2[i] - (M[0][i]*v2[0]) - (M[2][i]*v2[2])

        //M[1][i] = (t1[i] - (M[0][i]*v1[0]) - (M[2][i]*v1[2]))/v1[1],
        //M[1][i] = (t2[i] - (M[0][i]*v2[0]) - (M[2][i]*v2[2]))/v2[1],

        //(t1[i] - (M[0][i]*v1[0]) - (M[2][i]*v1[2]))/v1[1] =
        //      (t2[i] - (M[0][i]*v2[0]) - (M[2][i]*v2[2]))/v2[1]

        //(t1[i]*v2[1]) - (M[0][i]*v1[0]*v2[1]) - (M[2][i]*v1[2]*v2[1])=
        //     (t2[i]*v1[1]) - (M[0][i]*v2[0]*v1[1]) - (M[2][i]*v2[2]*v1[1])

        //(M[0][i]*v2[0]*v1[1])- (M[0][i]*v1[0]*v2[1]) =
        //      (t2[i]*v1[1]) - (t1[i]*v2[1]) 
        //      + (M[2][i]*v1[2]*v2[1]) - (M[2][i]*v2[2]*v1[1])

        //M[0][i]((v2[0]*v1[1])- (v1[0]*v2[1])) =
        //      (t2[i]*v1[1]) - (t1[i]*v2[1]) 
        //      + (M[2][i]*v1[2]*v2[1]) - (M[2][i]*v2[2]*v1[1])

        //M[0][i] = ((t2[i]*v1[1]) - (t1[i]*v2[1]) 
        //      + (M[2][i]*v1[2]*v2[1]) - (M[2][i]*v2[2]*v1[1]))
        //      /((v2[0]*v1[1])- (v1[0]*v2[1]))

        //M[2][i] is a free variable, just fix it at 0

        //then,
        //M[1][i] = (t1[i] - (M[0][i]*v1[0]) - (M[2][i]*v1[2]))/v1[1],
        for (int i = 0; i < 3; i++) {
            m[2][i] = 0;
            //  m[0][i] = ((tt2[i] * tv1[1]) - (tt1[i] * tv2[1])
            //   + (m[2][i] * tv1[2] * tv2[1]) - (m[2][i] * tv2[2] * tv1[1]))
            //   / ((tv2[0] * tv1[1])- (tv1[0] * tv2[1]));
            //Factor out m[2][i] 
            m[0][i] = ((tt2[i] * tv1[1]) - (tt1[i] * tv2[1]))
                    / ((tv2[0] * tv1[1])- (tv1[0] * tv2[1]));

            //prevent divide by zero errors again
            if (tv1[1] != 0) {
                //m[1][i] = (tt1[i] - (m[0][i] * tv1[0]) - (m[2][i]
                //* tv1[2])) / tv1[1];
                //Factor out m[2][i] 
                m[1][i] = (tt1[i] - (m[0][i] * tv1[0])) / tv1[1];
            } else if (tv2[1] != 0) {
                //m[1][i] = (tt2[i] - (m[0][i] * tv2[0])
                //- (m[2][i] * tv2[2])) / tv2[1];
                //Factor out m[2][i] 
                m[1][i] = (tt2[i] - (m[0][i] * tv2[0])) / tv2[1];

            } else {
                //m[1][i] = 
                //(tt1[i] - (m[0][i] * tv1[0]) - (m[2][i] * tv1[2])) / .0001;
                //Factor out m[2][i] 
                m[1][i] = (tt1[i] - (m[0][i] * tv1[0])) / 0.0001;
            }
        }

        //transformation matrix constructed!
        Vector3D hitPt;
        hitPt [0] = hit.getIntersect()[ax1];
        hitPt [1] = hit.getIntersect()[ax2];

        //translate hitPt the same distance we moved the vector triangle
        hitPt[0] -= v0[ax1];
        hitPt[1] -= v0[ax2];

        //transform with matrix m
        hitPt = m.multByVector(hitPt, 1);

        //reverse the transformation we performed on the texture triangle

        hitPt[0] += t0.first;
        hitPt[1] += t0.second;

        s = hitPt[0];
        t = hitPt[1];
    }
}





