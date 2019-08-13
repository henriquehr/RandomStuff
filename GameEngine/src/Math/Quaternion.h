#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include "../Logging.h"

class Quaternion {

public:
    float x;
    float y;
    float z;
    float w;

    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Quaternion &q);
    Quaternion(const Vector3 &v, float angle);
    ~Quaternion();
    static float magnitude(Quaternion *q);
    static void identity(Quaternion *destination);
    static void zeros(Quaternion *destination);
    static void normalize(Quaternion *destination);
    static void conjugate(Quaternion *destination);
    static void inverse(Quaternion *destination);
    static void createFromAxisAngle(Quaternion *destination, const Vector3 &v, float angle);
    static float dotProduct(const Quaternion &q, const Quaternion &q1);
    static float toAxisAngle(Quaternion *q, Vector3 *v);

    inline Quaternion operator+(const Quaternion &q) { Quaternion r(*this); r.add(q); return r; }
    inline Quaternion operator-(const Quaternion &q) { Quaternion r(*this); r.subtract(q); return r; }
    inline Quaternion operator*(const Quaternion &q) { Quaternion r(*this); r.multiply(q); return r; }
    inline Quaternion operator=(const Quaternion &q) { this->copy(q); return *this; }
    inline bool operator==(const Quaternion &q) { return (this->x == q.x && this->y == q.y && this->z == q.z && this->w == q.w); }
    inline bool operator!=(const Quaternion &q) { return (this->x != q.x || this->y != q.y || this->z != q.z || this->w != q.w); }
    
private:
    void copy(const Quaternion &q);
    void add(const Quaternion &q);
    void subtract(const Quaternion &q);
    void multiply(const Quaternion &q);
};
#endif // !QUATERNION_H