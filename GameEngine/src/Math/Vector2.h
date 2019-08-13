#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2 {
public:
    float x;
    float y;

public:
    Vector2() {
        this->x = 0; this->y = 0;
    }
    
    Vector2(float n) {
        this->y = n; this->x = n;
    }
    
    Vector2(float x, float y) {
        this->x = x; this->y = y;
    }
    
    Vector2(const Vector2 &v) {
        this->x = v.x; this->y = v.y;
    }
    
    Vector2(const float *v) {
        this->x = v[0]; this->y = v[1];
    }
    
    ~Vector2() {}

    inline float magnitude() const {
        return std::sqrt((this->x * this->x) + (this->y * this->y));
    }
    
    inline float dot(const Vector2 &v) const {
        return this->x * v.x + this->y * v.y;
    }
    
    inline void normalize() {
        (*this) /= this->magnitude();
    }
    
    inline Vector2 normalized() const {
        return (*this) / this->magnitude();
    }
    
    inline float angle(const Vector2 &v) const {
        return std::acos(this->normalized().dot(v.normalized()));
    }
    
    inline Vector2 absolute() const {
        return Vector2(std::abs(this->x), std::abs(this->y));
    }

    inline void set(float x, float y) {
        this->x = x; this->y = y;
    }
    
    inline void setZeros() {
        x = 0.0f; y = 0.0f;
    }
    
    inline void setOnes() {
        x = 1.0f; y = 1.0f;
    }
    
    inline void setUnitX() {
        x = 1.0f; y = 0.0f;
    }

    inline void setUnitY() {
        x = 0.0f; y = 1.0f;
    }

    inline static Vector2 createZeros() {
        return Vector2(0.0f);
    }
    
    inline static Vector2 createOnes() {
        return Vector2(1.0f);
    }
    
    inline static Vector2 createUnitX() {
        return Vector2(1, 0);
    }

    inline static Vector2 createUnitY() {
        return Vector2(0, 1);
    }

    inline Vector2 operator+(const Vector2 &v) const {
        return Vector2(this->x + v.x, this->y + v.y);
    }

    inline Vector2 operator+(float n) const {
        return Vector2(this->x + n, this->y + n);
    }

    inline Vector2 operator-(const Vector2 &v) const {
        return Vector2(this->x - v.x, this->y - v.y);
    }

    inline Vector2 operator-(float n) const {
        return Vector2(this->x - n, this->y - n);
    }

    inline Vector2 operator*(const Vector2 &v) const {
        return Vector2(this->x * v.x, this->y * v.y);
    }

    inline Vector2 operator*(float n) const {
        return Vector2(this->x * n, this->y * n);
    }

    inline Vector2 operator/(const Vector2 &v) const {
        return Vector2(this->x / v.x, this->y / v.y);
    }

    inline Vector2 operator/(float n) const {
        return Vector2(this->x / n, this->y / n);
    }

    inline void operator+=(const Vector2 &v) {
        this->x += v.x; this->y += v.y;
    }

    inline void operator+=(float n) {
        this->x += n; this->y += n;
    }

    inline void operator-=(const Vector2 &v) {
        this->x -= v.x; this->y -= v.y;
    }

    inline void operator-=(float n) {
        this->x -= n; this->y -= n;
    }

    inline void operator*=(const Vector2 &v) {
        this->x *= v.x; this->y *= v.y;
    }

    inline void operator*=(float n) {
        this->x *= n; this->y *= n;
    }

    inline void operator/=(const Vector2 &v) {
        this->x /= v.x; this->y /= v.y;
    }

    inline void operator/=(float n) {
        this->x /= n; this->y /= n;
    }
    
    inline void operator=(const Vector2 &v) {
        this->x = v.x; this->y = v.y;
    }

    inline Vector2 operator-() const {
        return Vector2(-this->x, -this->y);
    }

    inline bool operator==(const Vector2 &v) const {
        return (this->x == v.x && this->y == v.y);
    }

    inline bool operator!=(const Vector2 &v) const {
        return (this->x != v.x || this->y != v.y);
    }
};
#endif // !VECTOR3_H