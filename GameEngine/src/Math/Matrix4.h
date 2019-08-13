#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>
#include <iomanip>
#include <string.h>

#include "Math.h"
#include "../Logging.h"

#define MATRIX_LENGTH 16
#define MATRIX_SIZE (sizeof(float) * MATRIX_LENGTH)

/*
column-major
this->matrix[0][0] = 0; this->matrix[0][1]  = 1; this->matrix[0][2]  = 2;  this->matrix[0][3] = 3;
this->matrix[1][0] = 4; this->matrix[1][1]  = 5; this->matrix[1][2]  = 6;  this->matrix[1][3] = 7;
this->matrix[2][0] = 8; this->matrix[2][1]  = 9; this->matrix[2][2]  = 10; this->matrix[2][3] = 11;
this->matrix[3][0] = 12; this->matrix[3][1] = 13; this->matrix[3][2] = 14; this->matrix[3][3] = 15;
*/
class Matrix4 {
public:
    float matrix[MATRIX_LENGTH];

public:    
    Matrix4() {
        this->fill(0.0f);
    }

    Matrix4(const float n) {
        this->fill(0.0f);
        this->matrix[0]  = n;
        this->matrix[5]  = n;
        this->matrix[10] = n;
        this->matrix[15] = n;
    }

    Matrix4(const Matrix4 &m) {
        this->copy(m);
    }

    Matrix4(const float *m) {
        this->copy(m);
    }

    ~Matrix4() {}

    inline void zeros() {
        this->fill(0.0f);
    }

    inline static Matrix4 createIdentity() {
        Matrix4 result;
        result.matrix[0]  = 1.0f; 
        result.matrix[5]  = 1.0f; 
        result.matrix[10] = 1.0f; 
        result.matrix[15] = 1.0f;
        return result;
    }

    inline static Matrix4 createTranspose(const Matrix4 &m) {
        Matrix4 result;
        result.matrix[0]  = m.matrix[0]; result.matrix[1]  = m.matrix[4]; result.matrix[2]  = m.matrix[8];  result.matrix[3]  = m.matrix[12];
        result.matrix[4]  = m.matrix[1]; result.matrix[5]  = m.matrix[5]; result.matrix[6]  = m.matrix[9];  result.matrix[7]  = m.matrix[13];
        result.matrix[8]  = m.matrix[2]; result.matrix[9]  = m.matrix[6]; result.matrix[10] = m.matrix[10]; result.matrix[11] = m.matrix[14];
        result.matrix[12] = m.matrix[3]; result.matrix[13] = m.matrix[7]; result.matrix[14] = m.matrix[11]; result.matrix[15] = m.matrix[15];
        return result;
    }

    inline Matrix4 createTranspose() const {
        Matrix4 result;
        result.matrix[0]  = this->matrix[0]; result.matrix[1]  = this->matrix[4]; result.matrix[2]  = this->matrix[8];  result.matrix[3]  = this->matrix[12];
        result.matrix[4]  = this->matrix[1]; result.matrix[5]  = this->matrix[5]; result.matrix[6]  = this->matrix[9];  result.matrix[7]  = this->matrix[13];
        result.matrix[8]  = this->matrix[2]; result.matrix[9]  = this->matrix[6]; result.matrix[10] = this->matrix[10]; result.matrix[11] = this->matrix[14];
        result.matrix[12] = this->matrix[3]; result.matrix[13] = this->matrix[7]; result.matrix[14] = this->matrix[11]; result.matrix[15] = this->matrix[15];
        return result;
    }

    inline static Matrix4 createTranslation(const Vector3 &v) {
        Matrix4 result;
        result.matrix[0]  = 1.0f;
        result.matrix[5]  = 1.0f;
        result.matrix[10] = 1.0f;
        result.matrix[12] = v.x;
        result.matrix[13] = v.y;
        result.matrix[14] = v.z;
        result.matrix[15] = 1.0f;
        return result;
    }

    inline static Matrix4 createScale(const Vector3 &v) {
        Matrix4 result;
        result.matrix[0]  = v.x;
        result.matrix[5]  = v.y;
        result.matrix[10] = v.z;
        result.matrix[15] = 1.0f;
        return result;
    }

    inline static Matrix4 createRotationX(float n) {
        Matrix4 result;
        result.matrix[0]  = 1.0f;
        result.matrix[5]  = std::cos(n);
        result.matrix[6]  = -std::sin(n);
        result.matrix[9]  = std::sin(n);
        result.matrix[10] = std::cos(n);
        result.matrix[15] = 1.0f;
        return result;
    }

    inline static Matrix4 createRotationY(float n) {
        Matrix4 result;
        result.matrix[0]  = std::cos(n);
        result.matrix[2]  = std::sin(n);
        result.matrix[5]  = 1.0f;
        result.matrix[8]  = -std::sin(n);
        result.matrix[9]  = 0.0f;
        result.matrix[10] = std::cos(n);
        result.matrix[15] = 1.0f;
        return result;
    }

    inline static Matrix4 createRotationZ(float n) {
        Matrix4 result;
        result.matrix[0]  = std::cos(n);
        result.matrix[1]  = -std::sin(n);
        result.matrix[4]  = std::sin(n);
        result.matrix[5]  = std::cos(n);
        result.matrix[10] = 1.0f;
        result.matrix[15] = 1.0f;
        return result;
    }

    inline static Matrix4 createRotation(float angle, const Vector3 &v) {
        Matrix4 result;
        const float a = toRadians(angle);
        const float c = std::cos(a);
        const float s = std::sin(a);
        const float t = 1.0f - c;
        const float x = v.x;
        const float y = v.y;
        const float z = v.z;
        result.matrix[0]  = c + t * x * x;
        result.matrix[1]  = t * x * y + s * z;
        result.matrix[2]  = t * x * z - s * y;
        result.matrix[4]  = t * x * y - s * z;
        result.matrix[5]  = c + t * y * y;
        result.matrix[6]  = t * y * z + s * x;
        result.matrix[8]  = t * x * z + s * y;
        result.matrix[9]  = t * x * z + s * y;
        result.matrix[10] = c + t * z * z;
        result.matrix[15] = 1.0f;
        return result;
    }
    
    inline static Matrix4 createPerspective(float fov, float aspect_ratio, 
      float near, float far) {

        const float range = near - far;
        const float _f = 1.0f / std::tan(toRadians(0.5f * fov));
        Matrix4 result;
        result.matrix[0]  = _f / aspect_ratio;
        result.matrix[5]  = _f;
        result.matrix[10] = (near + far) / range;
        result.matrix[11] = -1.0f; //(2.0f * near * far) / range;
        result.matrix[14] = (2.0f * near * far) / range; //-1.0f;
        return result;
    }

    inline static Matrix4 createOrthographic(float left, float right, 
      float bottom, float top, float near, float far) {

        Matrix4 result;
        result.matrix[0]  = 2.0f / (right - left);
        result.matrix[5]  = 2.0f / (top - bottom);
        result.matrix[10] = 2.0f / (near - far);
        result.matrix[12] = -(right + left) / (right - left);
        result.matrix[13] = -(top + bottom) / (top - bottom);
        result.matrix[14] = - (far + near) / (far - near);
        result.matrix[15] = 1.0f;
        return result;
    }
   
    inline static Matrix4 createLookAt(Vector3 pos, Vector3 look_at, Vector3 up) {
        Vector3 f = look_at - pos;
        f.normalize();
        up.normalize();
        Vector3 s = f.cross(up);
        //s.normalize();
        Vector3 u = s.cross(f);
        Matrix4 result;
        result.matrix[0]  = s.x;
        result.matrix[1]  = u.x;
        result.matrix[2]  = -f.x;
        result.matrix[4]  = s.y;
        result.matrix[5]  = u.y;
        result.matrix[6]  = -f.y;
        result.matrix[8]  = s.z;
        result.matrix[9]  = u.z;
        result.matrix[10] = -f.z;
        result.matrix[12] = -s.dot(pos);
        result.matrix[13] = -u.dot(pos);
        result.matrix[14] = f.dot(pos);
        result.matrix[15] = 1.0f;
        return result;
    }

    void print() const {
        int col = 0;
        std::ostringstream ss;
        ss << "\n";
        for (int i = 0; i < MATRIX_LENGTH; i++) {
            col++;
            ss << i << "=[" << this->matrix[i] << "] ";
            if (col > 3) {
                col = 0;
                ss << "\n";
            }
        }
        ss << "\n";
        LOG(PRINT) << ss.str();
    }

    inline Matrix4 operator+(const Matrix4 &m) const {
        Matrix4 result;
        result.matrix[0]  = this->matrix[0]  + m.matrix[0];  result.matrix[1]  = this->matrix[1]  + m.matrix[1];  result.matrix[2]  = this->matrix[2]  + m.matrix[2];  result.matrix[3]  = this->matrix[3]  + m.matrix[3];
        result.matrix[4]  = this->matrix[4]  + m.matrix[4];  result.matrix[5]  = this->matrix[5]  + m.matrix[5];  result.matrix[6]  = this->matrix[6]  + m.matrix[6];  result.matrix[7]  = this->matrix[7]  + m.matrix[7];
        result.matrix[8]  = this->matrix[8]  + m.matrix[8];  result.matrix[9]  = this->matrix[9]  + m.matrix[9];  result.matrix[10] = this->matrix[10] + m.matrix[10]; result.matrix[11] = this->matrix[11] + m.matrix[11];
        result.matrix[12] = this->matrix[12] + m.matrix[12]; result.matrix[13] = this->matrix[13] + m.matrix[13]; result.matrix[14] = this->matrix[14] + m.matrix[14]; result.matrix[15] = this->matrix[15] + m.matrix[15];
        return result;
    }

    inline Matrix4 operator-(const Matrix4 &m) const {
        Matrix4 result;
        result.matrix[0]  = this->matrix[0]  - m.matrix[0];  result.matrix[1]  = this->matrix[1]  - m.matrix[1];  result.matrix[2]  = this->matrix[2]  - m.matrix[2];  result.matrix[3]  = this->matrix[3]  - m.matrix[3];
        result.matrix[4]  = this->matrix[4]  - m.matrix[4];  result.matrix[5]  = this->matrix[5]  - m.matrix[5];  result.matrix[6]  = this->matrix[6]  - m.matrix[6];  result.matrix[7]  = this->matrix[7]  - m.matrix[7];
        result.matrix[8]  = this->matrix[8]  - m.matrix[8];  result.matrix[9]  = this->matrix[9]  - m.matrix[9];  result.matrix[10] = this->matrix[10] - m.matrix[10]; result.matrix[11] = this->matrix[11] - m.matrix[11];
        result.matrix[12] = this->matrix[12] - m.matrix[12]; result.matrix[13] = this->matrix[13] - m.matrix[13]; result.matrix[14] = this->matrix[14] - m.matrix[14]; result.matrix[15] = this->matrix[15] - m.matrix[15];
        return result;
    }

    inline Matrix4 operator*(const Matrix4 &m) const {
        Matrix4 result;
        result.matrix[0]  = this->matrix[0] * m.matrix[0]  + this->matrix[4] * m.matrix[1]  + this->matrix[8]  * m.matrix[2]  + this->matrix[12] * m.matrix[3];
        result.matrix[1]  = this->matrix[1] * m.matrix[0]  + this->matrix[5] * m.matrix[1]  + this->matrix[9]  * m.matrix[2]  + this->matrix[13] * m.matrix[3];
        result.matrix[2]  = this->matrix[2] * m.matrix[0]  + this->matrix[6] * m.matrix[1]  + this->matrix[10] * m.matrix[2]  + this->matrix[14] * m.matrix[3];
        result.matrix[3]  = this->matrix[3] * m.matrix[0]  + this->matrix[7] * m.matrix[1]  + this->matrix[11] * m.matrix[2]  + this->matrix[15] * m.matrix[3];
        result.matrix[4]  = this->matrix[0] * m.matrix[4]  + this->matrix[4] * m.matrix[5]  + this->matrix[8]  * m.matrix[6]  + this->matrix[12] * m.matrix[7];
        result.matrix[5]  = this->matrix[1] * m.matrix[4]  + this->matrix[5] * m.matrix[5]  + this->matrix[9]  * m.matrix[6]  + this->matrix[13] * m.matrix[7];
        result.matrix[6]  = this->matrix[2] * m.matrix[4]  + this->matrix[6] * m.matrix[5]  + this->matrix[10] * m.matrix[6]  + this->matrix[14] * m.matrix[7];
        result.matrix[7]  = this->matrix[3] * m.matrix[4]  + this->matrix[7] * m.matrix[5]  + this->matrix[11] * m.matrix[6]  + this->matrix[15] * m.matrix[7];
        result.matrix[8]  = this->matrix[0] * m.matrix[8]  + this->matrix[4] * m.matrix[9]  + this->matrix[8]  * m.matrix[10] + this->matrix[12] * m.matrix[11];
        result.matrix[9]  = this->matrix[1] * m.matrix[8]  + this->matrix[5] * m.matrix[9]  + this->matrix[9]  * m.matrix[10] + this->matrix[13] * m.matrix[11];
        result.matrix[10] = this->matrix[2] * m.matrix[8]  + this->matrix[6] * m.matrix[9]  + this->matrix[10] * m.matrix[10] + this->matrix[14] * m.matrix[11];
        result.matrix[11] = this->matrix[3] * m.matrix[8]  + this->matrix[7] * m.matrix[9]  + this->matrix[11] * m.matrix[10] + this->matrix[15] * m.matrix[11];
        result.matrix[12] = this->matrix[0] * m.matrix[12] + this->matrix[4] * m.matrix[13] + this->matrix[8]  * m.matrix[14] + this->matrix[12] * m.matrix[15];
        result.matrix[13] = this->matrix[1] * m.matrix[12] + this->matrix[5] * m.matrix[13] + this->matrix[9]  * m.matrix[14] + this->matrix[13] * m.matrix[15];
        result.matrix[14] = this->matrix[2] * m.matrix[12] + this->matrix[6] * m.matrix[13] + this->matrix[10] * m.matrix[14] + this->matrix[14] * m.matrix[15];
        result.matrix[15] = this->matrix[3] * m.matrix[12] + this->matrix[7] * m.matrix[13] + this->matrix[11] * m.matrix[14] + this->matrix[15] * m.matrix[15];
        return result;
    }

    inline Matrix4 operator*(float n) const {
        Matrix4 result;
        result.matrix[0]  = this->matrix[0]  * n; result.matrix[1]  = this->matrix[1]  * n; result.matrix[2]  = this->matrix[2]  * n; result.matrix[3]  = this->matrix[3]  * n;
        result.matrix[4]  = this->matrix[4]  * n; result.matrix[5]  = this->matrix[5]  * n; result.matrix[6]  = this->matrix[6]  * n; result.matrix[7]  = this->matrix[7]  * n;
        result.matrix[8]  = this->matrix[8]  * n; result.matrix[9]  = this->matrix[9]  * n; result.matrix[10] = this->matrix[10] * n; result.matrix[11] = this->matrix[11] * n;
        result.matrix[12] = this->matrix[12] * n; result.matrix[13] = this->matrix[13] * n; result.matrix[14] = this->matrix[14] * n; result.matrix[15] = this->matrix[15] * n;
        return result;
    }

    inline Matrix4 operator/(float n) const {
        Matrix4 result;
        result.matrix[0]  = this->matrix[0]  / n; result.matrix[1]  = this->matrix[1]  / n; result.matrix[2]  = this->matrix[2]  / n; result.matrix[3]  = this->matrix[3]  / n;
        result.matrix[4]  = this->matrix[4]  / n; result.matrix[5]  = this->matrix[5]  / n; result.matrix[6]  = this->matrix[6]  / n; result.matrix[7]  = this->matrix[7]  / n;
        result.matrix[8]  = this->matrix[8]  / n; result.matrix[9]  = this->matrix[9]  / n; result.matrix[10] = this->matrix[10] / n; result.matrix[11] = this->matrix[11] / n;
        result.matrix[12] = this->matrix[12] / n; result.matrix[13] = this->matrix[13] / n; result.matrix[14] = this->matrix[14] / n; result.matrix[15] = this->matrix[15] / n;
        return result;
    }

    inline void operator+=(const Matrix4 &m) {
        this->matrix[0]  += m.matrix[0];  this->matrix[1]  += m.matrix[1];  this->matrix[2]  += m.matrix[2];  this->matrix[3]  += m.matrix[3];
        this->matrix[4]  += m.matrix[4];  this->matrix[5]  += m.matrix[5];  this->matrix[6]  += m.matrix[6];  this->matrix[7]  += m.matrix[7];
        this->matrix[8]  += m.matrix[8];  this->matrix[9]  += m.matrix[9];  this->matrix[10] += m.matrix[10]; this->matrix[11] += m.matrix[11];
        this->matrix[12] += m.matrix[12]; this->matrix[13] += m.matrix[13]; this->matrix[14] += m.matrix[14]; this->matrix[15] += m.matrix[15];
    }

    inline void operator-=(const Matrix4 &m) {
        this->matrix[0]  -= m.matrix[0];  this->matrix[1]  -= m.matrix[1];  this->matrix[2]  -= m.matrix[2];  this->matrix[3]  -= m.matrix[3];
        this->matrix[4]  -= m.matrix[4];  this->matrix[5]  -= m.matrix[5];  this->matrix[6]  -= m.matrix[6];  this->matrix[7]  -= m.matrix[7];
        this->matrix[8]  -= m.matrix[8];  this->matrix[9]  -= m.matrix[9];  this->matrix[10] -= m.matrix[10]; this->matrix[11] -= m.matrix[11];
        this->matrix[12] -= m.matrix[12]; this->matrix[13] -= m.matrix[13]; this->matrix[14] -= m.matrix[14]; this->matrix[15] -= m.matrix[15];
    }

    inline void operator*=(const Matrix4 &m) {
        Matrix4 result;
        result.matrix[0]  = this->matrix[0] * m.matrix[0]  + this->matrix[4] * m.matrix[1]  + this->matrix[8]  * m.matrix[2]  + this->matrix[12] * m.matrix[3];
        result.matrix[1]  = this->matrix[1] * m.matrix[0]  + this->matrix[5] * m.matrix[1]  + this->matrix[9]  * m.matrix[2]  + this->matrix[13] * m.matrix[3];
        result.matrix[2]  = this->matrix[2] * m.matrix[0]  + this->matrix[6] * m.matrix[1]  + this->matrix[10] * m.matrix[2]  + this->matrix[14] * m.matrix[3];
        result.matrix[3]  = this->matrix[3] * m.matrix[0]  + this->matrix[7] * m.matrix[1]  + this->matrix[11] * m.matrix[2]  + this->matrix[15] * m.matrix[3];
        result.matrix[4]  = this->matrix[0] * m.matrix[4]  + this->matrix[4] * m.matrix[5]  + this->matrix[8]  * m.matrix[6]  + this->matrix[12] * m.matrix[7];
        result.matrix[5]  = this->matrix[1] * m.matrix[4]  + this->matrix[5] * m.matrix[5]  + this->matrix[9]  * m.matrix[6]  + this->matrix[13] * m.matrix[7];
        result.matrix[6]  = this->matrix[2] * m.matrix[4]  + this->matrix[6] * m.matrix[5]  + this->matrix[10] * m.matrix[6]  + this->matrix[14] * m.matrix[7];
        result.matrix[7]  = this->matrix[3] * m.matrix[4]  + this->matrix[7] * m.matrix[5]  + this->matrix[11] * m.matrix[6]  + this->matrix[15] * m.matrix[7];
        result.matrix[8]  = this->matrix[0] * m.matrix[8]  + this->matrix[4] * m.matrix[9]  + this->matrix[8]  * m.matrix[10] + this->matrix[12] * m.matrix[11];
        result.matrix[9]  = this->matrix[1] * m.matrix[8]  + this->matrix[5] * m.matrix[9]  + this->matrix[9]  * m.matrix[10] + this->matrix[13] * m.matrix[11];
        result.matrix[10] = this->matrix[2] * m.matrix[8]  + this->matrix[6] * m.matrix[9]  + this->matrix[10] * m.matrix[10] + this->matrix[14] * m.matrix[11];
        result.matrix[11] = this->matrix[3] * m.matrix[8]  + this->matrix[7] * m.matrix[9]  + this->matrix[11] * m.matrix[10] + this->matrix[15] * m.matrix[11];
        result.matrix[12] = this->matrix[0] * m.matrix[12] + this->matrix[4] * m.matrix[13] + this->matrix[8]  * m.matrix[14] + this->matrix[12] * m.matrix[15];
        result.matrix[13] = this->matrix[1] * m.matrix[12] + this->matrix[5] * m.matrix[13] + this->matrix[9]  * m.matrix[14] + this->matrix[13] * m.matrix[15];
        result.matrix[14] = this->matrix[2] * m.matrix[12] + this->matrix[6] * m.matrix[13] + this->matrix[10] * m.matrix[14] + this->matrix[14] * m.matrix[15];
        result.matrix[15] = this->matrix[3] * m.matrix[12] + this->matrix[7] * m.matrix[13] + this->matrix[11] * m.matrix[14] + this->matrix[15] * m.matrix[15];
        this->copy(result);
    }

    inline void operator*=(float n) {
        this->matrix[0]  *= n; this->matrix[1]  *= n; this->matrix[2]  *= n; this->matrix[3]  *= n;
        this->matrix[4]  *= n; this->matrix[5]  *= n; this->matrix[6]  *= n; this->matrix[7]  *= n;
        this->matrix[8]  *= n; this->matrix[9]  *= n; this->matrix[10] *= n; this->matrix[11] *= n;
        this->matrix[12] *= n; this->matrix[13] *= n; this->matrix[14] *= n; this->matrix[15] *= n;
    }

    inline void operator/=(float n) {
        this->matrix[0]  /= n; this->matrix[1]  /= n; this->matrix[2]  /= n; this->matrix[3]  /= n;
        this->matrix[4]  /= n; this->matrix[5]  /= n; this->matrix[6]  /= n; this->matrix[7]  /= n;
        this->matrix[8]  /= n; this->matrix[9]  /= n; this->matrix[10] /= n; this->matrix[11] /= n;
        this->matrix[12] /= n; this->matrix[13] /= n; this->matrix[14] /= n; this->matrix[15] /= n;
    }

    inline Matrix4 operator=(const Matrix4 &m) {
        this->copy(m);
        return (*this);
    }
    
    inline Matrix4 operator=(float m[]) {
        this->copy(m);
        return (*this);
    }

    inline bool operator==(const Matrix4 &m) const {
        for (int c = 0; c < MATRIX_LENGTH; c++) {
            if (this->matrix[c] != m.matrix[c]) { return false; }
        }
        return true;
    }

    inline bool operator!=(const Matrix4 &m) const {
        for (int c = 0; c < MATRIX_LENGTH; c++) {
            if (this->matrix[c] != m.matrix[c]) { return true; }
        }
        return false;
    }

    inline float operator[](int index) const {
        return this->matrix[index];
    }

    inline Vector3 operator*(const Vector3 &v) const {
        return Vector3(
          this->matrix[0] * v.x + this->matrix[4] * v.y + this->matrix[8]  * v.z + this->matrix[12],
          this->matrix[1] * v.x + this->matrix[5] * v.y + this->matrix[9]  * v.z + this->matrix[13],
          this->matrix[2] * v.x + this->matrix[6] * v.y + this->matrix[10] * v.z + this->matrix[14]
        );
    }

    inline Vector4 operator*(const Vector4 &v) const {
        return Vector4(
          this->matrix[0] * v.x + this->matrix[4] * v.y + this->matrix[8]  * v.z + this->matrix[12] * v.w,
          this->matrix[1] * v.x + this->matrix[5] * v.y + this->matrix[9]  * v.z + this->matrix[13] * v.w,
          this->matrix[2] * v.x + this->matrix[6] * v.y + this->matrix[10] * v.z + this->matrix[14] * v.w,
          this->matrix[3] * v.x + this->matrix[7] * v.y + this->matrix[11] * v.z + this->matrix[15] * v.w
        );
    }

private:
    inline void copy(const Matrix4 &source) { memcpy(this->matrix, source.matrix, MATRIX_SIZE); }
    inline void copy(float m[]) { memcpy(this->matrix, m, MATRIX_SIZE); }
    inline void fill(float n) { memset(this->matrix, n, MATRIX_SIZE); }
};
#endif // !MATRIX4_H