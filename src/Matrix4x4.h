/* 
 * File:   matrix4x4.h
 * Author: Anthony
 *
 * Created on April 2, 2013, 4:26 PM
 */

#ifndef MATRIX4X4_H
#define	MATRIX4X4_H

#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;
#include "Vector3D.h"
using namespace sivelab;

namespace ablib {

    class MatrixCol {
    private:
        double &a, &b, &c, &d;
    public:

        MatrixCol
        (double &w, double &x, double &y, double &z) : a(w), b(x), c(y), d(z) {
        }

        ~MatrixCol() {
        }
        const double operator[](const int i) const {
            // do a sanity check to make sure indices are OK!
            assert(i >= 0 && i < 4);
            if (i == 0)return a;
            if (i == 1)return b;
            if (i == 2)return c;
            if (i == 3)return d;
        }

        double& operator[](const int i) {
            // do a sanity check to make sure indices are OK!
            assert(i >= 0 && i < 4);
            if (i == 0)return a;
            if (i == 1)return b;
            if (i == 2)return c;
            if (i == 3)return d;
        }
    };

    class Matrix4x4 {
    public:

        Matrix4x4() {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    data[x][y] = 0;
                }
            }
        }

        Matrix4x4(const double a, const double b, const double c,const double d,
                const double e, const double f, const double g, const double h,
                const double i, const double j, const double k, const double l,
                const double m, const double n, const double o, const double p){
            data[0][0] = a;
            data[1][0] = b;
            data[2][0] = c;
            data[3][0] = d;
            data[0][1] = e;
            data[1][1] = f;
            data[2][1] = g;
            data[3][1] = h;
            data[0][2] = i;
            data[1][2] = j;
            data[2][2] = k;
            data[3][2] = l;
            data[0][3] = m;
            data[1][3] = n;
            data[2][3] = o;
            data[3][3] = p;
        }

        ~Matrix4x4() {
        }
        /*
                const MatrixCol operator[](const int i) const {
                    // do a sanity check to make sure indices are OK!
                    assert(i >= 0 && i < 3);
                    MatrixCol m(data[i][0], data[i][1], data[i][2],data[i][3]);
                    return m;
                }
         * */

        MatrixCol operator[](const int i) {
            // do a sanity check to make sure indices are OK!
            assert(i >= 0 && i < 4);
            MatrixCol m(data[i][0], data[i][1], data[i][2], data[i][3]);
            return m;
        }

        void set(const double a, const double b, const double c, const double d,
                const double e, const double f, const double g, const double h,
                const double i, const double j, const double k, const double l,
                const double m, const double n, const double o, const double p){
            data[0][0] = a;
            data[1][0] = b;
            data[2][0] = c;
            data[3][0] = d;
            data[0][1] = e;
            data[1][1] = f;
            data[2][1] = g;
            data[3][1] = h;
            data[0][2] = i;
            data[1][2] = j;
            data[2][2] = k;
            data[3][2] = l;
            data[0][3] = m;
            data[1][3] = n;
            data[2][3] = o;
            data[3][3] = p;
        }

        double determinant();

        Matrix4x4 inverse();
        
        Vector3D multByVector(const Vector3D & v,double v3);

        void set(Matrix4x4& v) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    data[x][y] = v[x][y];
                }
            }

        }

        Matrix4x4 clamp(double min, double max) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    if (data[x][y] < min) data[x][y] = min;
                    if (data[x][y] > max) data[x][y] = max;
                }
            }
            return *this;
        }

        Matrix4x4 &operator=(const Matrix4x4 & rhs) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    data[x][y] = rhs.data[x][y];
                }
            }
            return *this;
        }

        Matrix4x4 &operator+=(const Matrix4x4 & rhs) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    data[x][y] += rhs.data[x][y];
                }
            }
            return *this;
        }

        Matrix4x4 &operator-=(const Matrix4x4 & rhs) {

            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    data[x][y] -= rhs.data[x][y];
                }
            }
            return *this;
        }

        Matrix4x4& operator*=(const double c) {

            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    data[x][y] *= c;
                }
            }
            return *this;
        }

        Matrix4x4& operator/=(const double c) {

            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    data[x][y] /= c;
                }
            }
            return *this;
        }

        Matrix4x4 operator*=(const Matrix4x4 & rhs) {

            double tempData[4][4];
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    double d = 0;
                    for (int n = 0; n < 4; n++) {
                        d += data[n][y] * rhs.data[x][n];
                    }
                    tempData[x][y] = d;
                    d = 0;
                }
            }
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    data[x][y] = tempData[x][y];
                }
            }
            return *this;
        }
        
        



    private:
        friend std::ostream& operator<<(std::ostream& os, Matrix4x4 & v);
        double data[4][4];

        double det2x2(double a, double b, double c, double d) {
            return a * d - b*c;
        }

        double det3x3(double a, double b, double c,
                double d, double e, double f,
                double g, double h, double i) {
            double det = 0;
            det += a * det2x2(e, f, h, i);
            det -= b * det2x2(d, f, g, i);
            det += c * det2x2(d, e, g, h);
            return det;
        }

        void rowAdd(int r1, int r2, double m) {
            //r1 = r1 + r2*m           
            for (int x = 0; x < 4; x++) {
                data[x][r1] += (data [x][r2] * m);
            }
        }

        void rowSwap(int r1, int r2) {
            for (int x = 0; x < 4; x++) {
                double temp = data[x][r1];
                data[x][r1] = data[x][r2];
                data[x][r2] = temp;
            }
        }

        void rowMult(int r, double m) {
            for (int x = 0; x < 4; x++) {
                data[x][r] *= m;
            }
        }
    };

    const Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4 & rhs);
    const Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4 & rhs);
    const Matrix4x4 operator*(const double rhs, const Matrix4x4 & lhs);
    const Matrix4x4 operator*(const Matrix4x4& lhs, const Vector3D& rhs);
    const Matrix4x4 operator/(const Matrix4x4& lhs, const double rhs);
    const ablib::Matrix4x4 operator*(const ablib::Matrix4x4 &rhs,
            const ablib::Matrix4x4 &lhs);


}

#endif	/* MATRIX4X4_H */

