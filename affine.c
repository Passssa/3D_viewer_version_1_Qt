#include "viewer.h"

void set_move(data_t *obj, double dx, double dy, double dz) {
  for (int i = 0; i < obj->countVertexes * 3; i += 3) {
    obj->vertexArray[i] += dx;
    obj->vertexArray[i + 1] += dy;
    obj->vertexArray[i + 2] += dz;
  }
}

void set_scale(data_t *obj, double x) {
  //  x /= 100;
  for (int i = 0; i < obj->countVertexes * 3; i += 3) {
    obj->vertexArray[i] *= x;
    obj->vertexArray[i + 1] *= x;
    obj->vertexArray[i + 2] *= x;
  }
}

void set_rotate(data_t *obj, double rotate_x, double rotate_y,
                double rotate_z) {
  rotate_x *= PI / 180;
  rotate_y *= PI / 180;
  rotate_z *= PI / 180;
  double tmp[3];
  for (int i = 0; i < obj->countVertexes * 3; i += 3) {
    for (int j = 0; j < 3; j++) tmp[j] = obj->vertexArray[i + j];
    obj->vertexArray[i + 1] = tmp[1] * cos(rotate_x) - tmp[2] * sin(rotate_x);
    obj->vertexArray[i + 2] = tmp[1] * sin(rotate_x) + tmp[2] * cos(rotate_x);
    for (int j = 0; j < 3; j++) tmp[j] = obj->vertexArray[i + j];
    obj->vertexArray[i] = tmp[0] * cos(rotate_y) + tmp[2] * sin(rotate_y);
    obj->vertexArray[i + 2] = -tmp[0] * sin(rotate_y) + tmp[2] * cos(rotate_y);
    for (int j = 0; j < 3; j++) tmp[j] = obj->vertexArray[i + j];
    obj->vertexArray[i] = tmp[0] * cos(rotate_z) - tmp[1] * sin(rotate_z);
    obj->vertexArray[i + 1] = tmp[0] * sin(rotate_z) + tmp[1] * cos(rotate_z);
  }
}
