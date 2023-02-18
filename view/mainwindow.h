#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>

#include "gifimage/qgifimage.h"
#include "glview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void setProjectionType();

  data_t fileData{0, 0, nullptr, nullptr, 0};

  QTimer *timer;

  QGifImage gif;

  bool needToFree = false;
 private slots:
  void on_pushButton_chooseFile_clicked();

  void on_radioButton_solid_clicked();

  void on_radioButton_dashed_clicked();

  void on_radioButton_none_clicked();

  void on_radioButton_circle_clicked();

  void on_radioButton_square_clicked();

  void on_radioButton_parallel_clicked();

  void on_radioButton_central_clicked();

  void on_pushButton_apply_clicked();

  void on_pushButton_save_image_clicked();

  void on_pushButton_save_settings_clicked();

  void on_pushButton_loa_settings_clicked();

  void on_pushButton_clicked();

  void make_gif();

  void stop_timer();

  void on_slider_vertScale_valueChanged(int value);

  void on_slider_lineWidth_valueChanged(int value);

  void on_slider_lineR_valueChanged(int value);

  void on_slider_lineG_valueChanged(int value);

  void on_slider_lineB_valueChanged(int value);

  void on_slider_vertR_valueChanged(int value);

  void on_slider_vertG_valueChanged(int value);

  void on_slider_vertB_valueChanged(int value);

  void on_sliderBackroundB_valueChanged(int value);

  void on_sliderBackroundR_valueChanged(int value);

  void on_sliderBackroundG_valueChanged(int value);

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
