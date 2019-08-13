#include "Quaternion.h"


Quaternion::Quaternion() {
    LOG(WARNING) << "Needs fix.";
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 1.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::Quaternion(const Quaternion &q) {
    this->copy(q);
}

Quaternion::Quaternion(const Vector3 &v, float angle) {
    createFromAxisAngle(this, v, angle);
}

Quaternion::~Quaternion() {}

float Quaternion::magnitude(Quaternion *q) {
    return std::sqrt((q->x * q->x) + (q->y * q->y) + (q->z * q->z) + (q->w * q->w));
}

void Quaternion::identity(Quaternion *destination) {
    destination->x = 0.0;
    destination->y = 0.0;
    destination->z = 0.0;
    destination->w = 1.0;
}

void Quaternion::zeros(Quaternion *destination) {
    destination->x = 0;
    destination->y = 0;
    destination->z = 0;
    destination->w = 0;
}

void Quaternion::normalize(Quaternion *destination) {
    float length = magnitude(destination);
    if (length != 0) {
        destination->x /= length;
        destination->y /= length;
        destination->z /= length;
        destination->w /= length;
    }
}

void Quaternion::conjugate(Quaternion *destination) {
    destination->x = -destination->x;
    destination->y = -destination->y;
    destination->z = -destination->z;
}

void Quaternion::inverse(Quaternion *destination) {
    float length = magnitude(destination);
    if (length != 0) {
        destination->x = -destination->x / length;
        destination->y = -destination->y / length;
        destination->z = -destination->z / length;
        destination->w = destination->w / length;
    }
}

void Quaternion::createFromAxisAngle(Quaternion *destination, const Vector3 &v, float angle) {
    float half_angle_cos = std::cos(angle / 2.0f);
    float half_angle_sin = std::sin(angle / 2.0f);

    Vector3 norm(v);
    norm.normalize();
    destination->x = norm.x * half_angle_sin;
    destination->y = norm.y * half_angle_sin;
    destination->z = norm.z * half_angle_sin;
    destination->w = half_angle_cos;
}

float Quaternion::dotProduct(const Quaternion &q, const Quaternion &q1) {
    return q.x * q1.x + q.y * q1.y + q.z * q1.z + q.w * q1.w;
}

float Quaternion::toAxisAngle(Quaternion *q, Vector3 *v) {
    normalize(q);
    v->x = q->x;
    v->y = q->y;
    v->z = q->z;
    v->normalize();
    return (2.0f * std::acos(q->w));
}

void Quaternion::copy(const Quaternion &q) {
    this->x = q.x;
    this->y = q.y;
    this->z = q.z;
    this->w = q.w;
}

void Quaternion::add(const Quaternion &q) {
    this->x += q.x;
    this->y += q.y;
    this->z += q.z;
    this->w += q.w;
}

void Quaternion::subtract(const Quaternion &q) {
    this->x -= q.x;
    this->y -= q.y;
    this->z -= q.z;
    this->w -= q.w;
}

void Quaternion::multiply(const Quaternion &q) {
    float xx = this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y;
    float yy = this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x;
    float zz = this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w;
    float ww = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;

    this->x = xx;
    this->y = yy;
    this->z = zz;
    this->w = ww;
}