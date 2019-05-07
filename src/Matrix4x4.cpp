/* 
 * File:   matrix4x4.cpp
 * Author: Anthony
 * 
 * Created on April 2, 2013, 4:26 PM
 */

#include "Matrix4x4.h"
using namespace std;

namespace ablib {

    ostream &operator<<(ostream& os, ablib::Matrix4x4& v) {
        double d;
        for (int y = 0; y < 4; y++) {
            os << '[';
            for (int x = 0; x < 4; x++) {
                double d = v[x][y];
                if (x != 0)os << ' ';
                os << d;
            }
            os << ']' << endl;
        }
        return os;
    }

    const ablib::Matrix4x4 operator+
    (const ablib::Matrix4x4 &lhs, const ablib::Matrix4x4 &rhs) {
        return ablib::Matrix4x4(lhs) += rhs;
    }

    const ablib::Matrix4x4 operator-
    (const ablib::Matrix4x4 &lhs, const ablib::Matrix4x4 &rhs) {
        return ablib::Matrix4x4(lhs) -= rhs;
    }

    const ablib::Matrix4x4 operator*
    (const ablib::Matrix4x4 &lhs, const double rhs) {
        return ablib::Matrix4x4(lhs) *= rhs;
    }

    const ablib::Matrix4x4 operator*
    (const double rhs, const ablib::Matrix4x4 &lhs) {
        return ablib::Matrix4x4(lhs) *= rhs;
    }

    const ablib::Matrix4x4 operator*
    (const ablib::Matrix4x4 &rhs, const ablib::Matrix4x4 &lhs) {
        return ablib::Matrix4x4(lhs) *= rhs;
    }

    const ablib::Matrix4x4 operator/
    (const ablib::Matrix4x4 &lhs, const double rhs) {
        return ablib::Matrix4x4(lhs) /= rhs;
    }


}

using namespace ablib;

double Matrix4x4::determinant() {
    double det = 0;
    det += data[0][0]
            * det3x3(data[1][1], data[2][1], data[3][1],
            data[1][2], data[2][2], data[3][2],
            data[1][3], data[2][3], data[3][3]);

    det -= data[1][0]
            * det3x3(data[0][1], data[2][1], data[3][1],
            data[0][2], data[2][2], data[3][2],
            data[0][3], data[2][3], data[3][3]);

    det += data[2][0]
            * det3x3(data[0][1], data[1][1], data[3][1],
            data[0][2], data[1][2], data[3][2],
            data[0][3], data[1][3], data[3][3]);

    det -= data[3][0]
            * det3x3(data[0][1], data[1][1], data[2][1],
            data[0][2], data[1][2], data[2][2],
            data[0][3], data[1][3], data[2][3]);
    return det;
}

Matrix4x4 Matrix4x4::inverse() {
    //find cofactor matrix
    Matrix4x4 cofactor;
    //cofactor(x,y) = (-1)^(x+y)determinant of 3x3 minor 
    //3x3 minor = matrix without row x, column y
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int a, b, c;
            a = 0;
            if (x == a)a++;
            b = a + 1;
            if (x == b)b++;
            c = b + 1;
            if (x == c)c++;

            int d, e, f;
            d = 0;
            if (y == d)d++;
            e = d + 1;
            if (y == e)e++;
            f = e + 1;
            if (y == f)f++;

            double det = det3x3(data[a][d], data[a][e], data[a][f],
                    data[b][d], data[b][e], data[b][f],
                    data[c][d], data[c][e], data[c][f]);
            if (((x + y) % 2) == 1 && det!= 0) det *= -1;
            cofactor[x][y] = det;
        }
    }
    //Find adj, the transpose of cofactor
    Matrix4x4 adj;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            adj[x][y] = cofactor[y][x];
        }
    }
    //inverse = 1/determinant * adj
    if (determinant() != 0) {
        adj *= (1.0 / determinant());
        return adj;
    } else {
        //cout << "Error: no inverse matrix!\n";
        return *this;
    }
}

Vector3D Matrix4x4::multByVector(const Vector3D & v, double v3) {
    Vector3D result;
    result[0]=
            (data[0][0]*v[0])+(data[1][0]*v[1])+(data[2][0]*v[2])+data[3][0]*v3;
    result[1]=
            (data[0][1]*v[0])+(data[1][1]*v[1])+(data[2][1]*v[2])+data[3][1]*v3;
    result[2]=
            (data[0][2]*v[0])+(data[1][2]*v[1])+(data[2][2]*v[2])+data[3][2]*v3;
    return result;
}