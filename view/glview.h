#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include <QtOpenGL>

#ifdef __cplusplus
extern "C" {
#endif

#include "../viewer.h"

#ifdef __cplusplus
}
#endif

enum projType { PARALLEL, CENTRAL };
enum vertexType { NONE, CIRCLE, SQUARE };

class glView : public QOpenGLWidget {
 public:
  glView(QWidget *parent);

  data_t fileData{0, 0, nullptr, nullptr, 0};
  bool projectionType = PARALLEL;

  bool stripple = false;
  int vertexDisplayMethod = NONE;

  void setGlProjection();
  void setGlEdgeType();
  void paintVertices();
  int getFileData(const char *fileName);

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  float VertScale;
  float LineWidth;

  float VertR = 0;
  float VertG = 0;
  float VertB = 0;

  float LineR = 0;
  float LineG = 0;
  float LineB = 0;

  float BackR = 100;
  float BackG = 100;
  float BackB = 100;
};

#endif  // GLVIEW_H
