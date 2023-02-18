#include "glview.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent) {}

void glView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void glView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void glView::paintGL() {
  setGlProjection();
  glClearColor(BackR / 100, BackG / 100, BackB / 100, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // очистка буфера глубины
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -4);

  glEnableClientState(GL_VERTEX_ARRAY);  // Вкл для успешной отрисовки массивов
  if (fileData.countVertexes) {
    glVertexPointer(3, GL_DOUBLE, 0,
                    fileData.vertexArray);  // определение массива данных вершин
  }

  // Отрисовка точек
  paintVertices();
  setGlEdgeType();
  // Отрисовка линий
  if (fileData.countVertexes) {
    glDrawElements(GL_LINES, fileData.countFacets * 2, GL_UNSIGNED_INT,
                   fileData.facetsArray);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::setGlProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projectionType == CENTRAL) {
    glFrustum(-1, 1, -1, 1, 2, 1000);
    glTranslatef(0, 0, -2);
  } else {
    glOrtho(-1, 1, -1, 1, -5, 1000);
  }
}

void glView::setGlEdgeType() {
  glLineStipple(1, 0x3333);  // Настройка пунктира линий
  glLineWidth(LineWidth);
  glColor3f(LineR / 100, LineG / 100, LineB / 100);
  stripple == true ? glEnable(GL_LINE_STIPPLE) : glDisable(GL_LINE_STIPPLE);
}

void glView::paintVertices() {
  if (vertexDisplayMethod) {
    if (vertexDisplayMethod == CIRCLE) {
      glEnable(GL_POINT_SMOOTH);  // Вкл Скругление точек
    }
    glPointSize(VertScale);
    glColor3f(VertR / 100, VertG / 100, VertB / 100);
    glDrawArrays(GL_POINTS, 0, fileData.countVertexes * 3);  // Отрисовка точек
    if (vertexDisplayMethod == CIRCLE) {
      glDisable(GL_POINT_SMOOTH);
    }
  }
}
