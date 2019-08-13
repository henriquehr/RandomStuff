#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
public:
    float x;
    float y;
    float z;

public:
    Vector3() {
        this->x = 0; this->y = 0; this->z = 0;
    }

    Vector3(float n) {
        this->y = n; this->x = n; this->z = n;
    }

    Vector3(float x, float y, float z) {
        this->x = x; this->y = y; this->z = z;
    }
    
    Vector3(const Vector3 &v) {
        this->x = v.x; this->y = v.y; this->z = v.z;
    }
    
    Vector3(const float *v) {
        this->x = v[0]; this->y = v[1]; this->z = v[2];
    }
    
    ~Vector3() {}

    inline float magnitude() const {
        return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
    }

    inline float dot(const Vector3 &v) const {
        return this->x * v.x + this->y * v.y + this->z * v.z;
    }

    inline Vector3 cross(const Vector3 &v) const {
        return Vector3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
    }

    inline void normalize() {
        (*this) /= this->magnitude();
    }

    inline Vector3 normalized() const {
        return (*this) / this->magnitude();
    }

    inline float angle(const Vector3 &v) const {
        return std::acos(this->normalized().dot(v.normalized()));
    }

    inline Vector3 absolute() const {
        return Vector3(std::abs(this->x), std::abs(this->y), std::abs(this->z));
    }

    inline void set(float x, float y, float z) {
        this->x = x; this->y = y; this->z = z;
    }

    inline void setZeros() {
        x = 0.0f; y = 0.0f; z = 0.0f;
    }

    inline void setOnes() {
        x = 1.0f; y = 1.0f; z = 1.0f;
    }

    inline void setUnitX() {
        x = 1.0f; y = 0.0f; z = 0.0f;
    }

    inline void setUnitY() {
        x = 0.0f; y = 1.0f; z = 0.0f;
    }

    inline void setUnitZ() {
        x = 0.0f; y = 0.0f; z = 1.0f;
    }

    inline static Vector3 createZeros() {
        return Vector3(0.0f);
    }

    inline static Vector3 createOnes() {
        return Vector3(1.0f);
    }

    inline static Vector3 createUnitX() {
        return Vector3(1, 0, 0);
    }
    
    inline static Vector3 createUnitY() {
        return Vector3(0, 1, 0);
    }
    
    inline static Vector3 createUnitZ() {
        return Vector3(0, 0, 1);
    }

    inline Vector3 operator+(const Vector3 &v) const {
        return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    inline Vector3 operator+(float n) const {
        return Vector3(this->x + n, this->y + n, this->z + n);
    }

    inline Vector3 operator-(const Vector3 &v) const {
        return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    inline Vector3 operator-(float n) const {
        return Vector3(this->x - n, this->y - n, this->z - n);
    }

    inline Vector3 operator*(const Vector3 &v) const {
        return Vector3(this->x * v.x, this->y * v.y, this->z * v.z);
    }

    inline Vector3 operator*(float n) const {
        return Vector3(this->x * n, this->y * n, this->z * n);
    }

    inline Vector3 operator/(const Vector3 &v) const {
        return Vector3(this->x / v.x, this->y / v.y, this->z / v.z);
    }

    inline Vector3 operator/(float n) const {
        return Vector3(this->x / n, this->y / n, this->z / n);
    }

    inline void operator+=(const Vector3 &v) {
        this->x += v.x; this->y += v.y; this->z += v.z;
    }

    inline void operator+=(float n) {
        this->x += n; this->y += n; this->z += n;
    }

    inline void operator-=(const Vector3 &v) {
        this->x -= v.x; this->y -= v.y; this->z -= v.z;
    }

    inline void operator-=(float n) {
        this->x -= n; this->y -= n; this->z -= n;
    }

    inline void operator*=(const Vector3 &v) {
        this->x *= v.x; this->y *= v.y; this->z *= v.z;
    }

    inline void operator*=(float n) {
        this->x *= n; this->y *= n; this->z *= n;
    }

    inline void operator/=(const Vector3 &v) {
        this->x /= v.x; this->y /= v.y; this->z /= v.z;
    }

    inline void operator/=(float n) {
        this->x /= n; this->y /= n; this->z /= n;
    }
    
    inline void operator=(const Vector3 &v) {
        this->x = v.x; this->y = v.y; this->z = v.z;
    }

    inline Vector3 operator-() const {
        return Vector3(-this->x, -this->y, -this->z);
    }

    inline bool operator==(const Vector3 &v) const {
        return (this->x == v.x && this->y == v.y && this->z == v.z);
    }

    inline bool operator!=(const Vector3 &v) const {
        return (this->x != v.x || this->y != v.y || this->z != v.z);
    }
};
#endif // !VECTOR3_H