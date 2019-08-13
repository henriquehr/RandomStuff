#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>

class Vector4 {
public:
    float x;
    float y;
    float z;
    float w;

public:
    Vector4() {
        this->x = 0; this->y = 0; this->z = 0; this->w = 0;
    }

    Vector4(float n) {
        this->y = n; this->x = n; this->z = n; this->w = 0;
    }

    Vector4(float x, float y, float z, float w) {
        this->x = x; this->y = y; this->z = z; this->w = w;
    }
    
    Vector4(const Vector4 &v) {
        this->x = v.x; this->y = v.y; this->z = v.z; this->w = v.w;
    }
    
    Vector4(const float *v) {
        this->x = v[0]; this->y = v[1]; this->z = v[2]; this->w = v[3];
    }

    Vector4(const Vector3 &xyz, float w) {
         this->x = xyz.x; this->y = xyz.y; this->z = xyz.z; this->w = w;
    }
    
    ~Vector4() {}

 
    inline float dot(const Vector4 &v) const {
        return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w; 
    }

    inline void set(float x, float y, float z, float w) {
        this->x = x; this->y = y; this->z = z; this->w = w;
    }

    inline void setZeros() {
        x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f;
    }

    inline void setOnes() {
        x = 1.0f; y = 1.0f; z = 1.0f; w = 1.0f;
    }

    inline void setUnitX() {
        x = 1.0f; y = 0.0f; z = 0.0f; w = 0.0f;
    }

    inline void setUnitY() {
        x = 0.0f; y = 1.0f; z = 0.0f; w = 0.0f;
    }

    inline void setUnitZ() {
        x = 0.0f; y = 0.0f; z = 1.0f; w = 0.0f;
    }

    inline void setUnitW() {
        x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f;
    }

    inline static Vector4 createZeros() {
        return Vector4(0.0f);
    }

    inline static Vector4 createOnes() {
        return Vector4(1.0f);
    }

    inline static Vector4 createUnitX() {
        return Vector4(1, 0, 0, 0);
    }
    
    inline static Vector4 createUnitY() {
        return Vector4(0, 1, 0, 0);
    }
    
    inline static Vector4 createUnitZ() {
        return Vector4(0, 0, 1, 0);
    }

    inline static Vector4 createUnitW() {
        return Vector4(0, 0, 0, 1);
    }

    inline Vector4 operator+(const Vector4 &v) const {
        return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
    }

    inline Vector4 operator+(float n) const {
        return Vector4(this->x + n, this->y + n, this->z + n, this->w + n);
    }

    inline Vector4 operator-(const Vector4 &v) const {
        return Vector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
    }

    inline Vector4 operator-(float n) const {
        return Vector4(this->x - n, this->y - n, this->z - n, this->w - n);
    }

    inline Vector4 operator*(const Vector4 &v) const {
        return Vector4(this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w);
    }

    inline Vector4 operator*(float n) const {
        return Vector4(this->x * n, this->y * n, this->z * n, this->w * n);
    }

    inline Vector4 operator/(const Vector4 &v) const {
        return Vector4(this->x / v.x, this->y / v.y, this->z / v.z, this->w / v.w);
    }

    inline Vector4 operator/(float n) const {
        return Vector4(this->x / n, this->y / n, this->z / n, this->w / n);
    }

    inline void operator+=(const Vector4 &v) {
        this->x += v.x; this->y += v.y; this->z += v.z; this->w += v.w;
    }

    inline void operator+=(float n) {
        this->x += n; this->y += n; this->z += n; this->w += n;
    }

    inline void operator-=(const Vector4 &v) {
        this->x -= v.x; this->y -= v.y; this->z -= v.z; this->w -= v.w;
    }

    inline void operator-=(float n) {
        this->x -= n; this->y -= n; this->z -= n; this->w -= n;
    }

    inline void operator*=(const Vector4 &v) {
        this->x *= v.x; this->y *= v.y; this->z *= v.z; this->w *= v.w;
    }

    inline void operator*=(float n) {
        this->x *= n; this->y *= n; this->z *= n; this->w *= n;
    }

    inline void operator/=(const Vector4 &v) {
        this->x /= v.x; this->y /= v.y; this->z /= v.z; this->w /= v.w;
    }

    inline void operator/=(float n) {
        this->x /= n; this->y /= n; this->z /= n; this->w /= n;
    }
    
    inline void operator=(const Vector4 &v) {
        this->x = v.x; this->y = v.y; this->z = v.z; this->w = v.w;
    }

    inline Vector4 operator-() const {
        return Vector4(-this->x, -this->y, -this->z, -this->w);
    }

    inline bool operator==(const Vector4 &v) const {
        return (this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w);
    }

    inline bool operator!=(const Vector4 &v) const {
        return (this->x != v.x || this->y != v.y || this->z != v.z || this->w != v.w);
    }
};
#endif // !VECTOR4_H