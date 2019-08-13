#include "Camera.h"

Camera::Camera() {
  this->width = 256;
  this->height = 256;
  this->aspect_ratio = ((float)this->width / (float)this->height);
  this->near = 0.0f;
  this->far = 100.0f;
  this->fov = 60.0f;
  this->projection = Matrix4::createIdentity();
  this->world_view = Matrix4::createIdentity();
}

Camera::~Camera() {}

void Camera::updatePerspective(int w, int h, float n, float f) {
    this->aspect_ratio = ((float)w / (float)h);
    this->near = n;
    this->far = f;
    this->projection = Matrix4::createPerspective(this->fov, this->aspect_ratio, this->near, this->far);
}

void Camera::setPositionOrientation(const Vector3 &pos, float rot_x, float rot_y) {
    Matrix4 m_rot_x = Matrix4::createRotationX(rot_x);
    Matrix4 m_rot_y = Matrix4::createRotationY(rot_y);
    Matrix4 t = Matrix4::createTranslation(-pos);
    this->world_view = m_rot_x * m_rot_y * t;
}

void Camera::lookAt(Vector3 pos, Vector3 looking_at, Vector3 up) {
    this->world_view = Matrix4::createLookAt(pos, looking_at, up);
}

Matrix4 Camera::getMatrix() const {
  return this->projection * this->world_view;
}