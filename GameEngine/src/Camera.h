#ifndef CAMERA_H
#define CAMERA_H

#include "Math/Math.h"

class Camera {
public:
    int width;
    int height;
    float aspect_ratio;
    float near;
    float far;
    float fov;
    Matrix4 projection;
    Matrix4 world_view;

public:
    Camera();
    ~Camera();
  
    void updatePerspective(int w, int h, float n, float f);
    void setPositionOrientation(const Vector3 &pos, float rot_x, float rot_y);
    void lookAt(Vector3 pos, Vector3 looking_at, Vector3 up);
    Matrix4 getMatrix() const;
};
#endif