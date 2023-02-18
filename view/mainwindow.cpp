#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedWidth(1411);
  setFixedHeight(814);
}

MainWindow::~MainWindow() {
  removeData(&fileData);
  delete ui;
}

void MainWindow::on_pushButton_chooseFile_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Choose file", "../objFiles", ".obj files (*.obj)");

  if (!fileName.isEmpty()) {
    if ((fileData.facetsArray || fileData.vertexArray) && needToFree) {
      removeData(&fileData);
    }

    std::string expression = fileName.toStdString();
    const char *str = expression.c_str();

    int code = parseObj(str, &fileData);
    if (code == FILE_NOT_FOUND) {
      ui->label_FileName->setText("File not found");
      needToFree = false;
    } else if (code == MALLOC_ERROR) {
      ui->label_FileName->setText("MALLOC ERROR");
      needToFree = false;
    } else if (code) {
      ui->label_FileName->setText("Error! Can't open file.");
      needToFree = false;
    } else {
      ui->label_FileName->setText(str);
      ui->label_NumberOfFacets->setText(QString::number(fileData.countFacets));
      ui->label_NumberOfVertexes->setText(
          QString::number(fileData.countVertexes));
      ui->openGLWidget->fileData = fileData;
      ui->openGLWidget->update();
      needToFree = true;
    }
  }
}

void MainWindow::on_radioButton_solid_clicked() {
  ui->openGLWidget->stripple = false;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_dashed_clicked() {
  ui->openGLWidget->stripple = true;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_none_clicked() {
  ui->openGLWidget->vertexDisplayMethod = NONE;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_circle_clicked() {
  ui->openGLWidget->vertexDisplayMethod = CIRCLE;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_square_clicked() {
  ui->openGLWidget->vertexDisplayMethod = SQUARE;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_parallel_clicked() {
  ui->openGLWidget->projectionType = PARALLEL;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_central_clicked() {
  ui->openGLWidget->projectionType = CENTRAL;
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_apply_clicked() {
  set_move(&fileData, ui->doubleSpinBox_move_x->value(),
           ui->doubleSpinBox_move_y->value(),
           ui->doubleSpinBox_move_z->value());
  set_rotate(&fileData, ui->doubleSpinBox_rotate_x->value(),
             ui->doubleSpinBox_rotate_y->value(),
             ui->doubleSpinBox_rotate_z->value());
  set_scale(&fileData, ui->doubleSpinBox_scale->value());
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_save_image_clicked() {
  QString path = QFileDialog::getSaveFileName(this, NULL, NULL,
                                              "JPEG (*.jpeg) ;; BMP (*.bmp)");
  if (!path.isNull()) ui->openGLWidget->grabFramebuffer().save(path, NULL, 100);
}

void MainWindow::on_pushButton_save_settings_clicked() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");

  settings.setValue("move_x", ui->doubleSpinBox_move_x->value());
  settings.setValue("move_y", ui->doubleSpinBox_move_y->value());
  settings.setValue("move_z", ui->doubleSpinBox_move_z->value());
  settings.setValue("rotate_x", ui->doubleSpinBox_rotate_x->value());
  settings.setValue("rotate_y", ui->doubleSpinBox_rotate_y->value());
  settings.setValue("rotate_z", ui->doubleSpinBox_rotate_z->value());
  settings.setValue("scale", ui->doubleSpinBox_scale->value());
  settings.setValue("projection_parallel",
                    ui->radioButton_parallel->isChecked());
  settings.setValue("edge_solid", ui->radioButton_solid->isChecked());
  settings.setValue("edge_dashed", ui->radioButton_dashed->isChecked());
  settings.setValue("vertices_circle", ui->radioButton_circle->isChecked());
  settings.setValue("vertices_square", ui->radioButton_square->isChecked());
  settings.setValue("backR", ui->sliderBackroundR->value());
  settings.setValue("backG", ui->sliderBackroundG->value());
  settings.setValue("backB", ui->sliderBackroundB->value());
  settings.setValue("lineR", ui->slider_lineR->value());
  settings.setValue("lineG", ui->slider_lineG->value());
  settings.setValue("lineB", ui->slider_lineB->value());
  settings.setValue("vertR", ui->slider_vertR->value());
  settings.setValue("vertG", ui->slider_vertG->value());
  settings.setValue("vertB", ui->slider_vertB->value());
  settings.setValue("lineWidth", ui->lineLineWidth->text());
  settings.setValue("vertScale", ui->line_vertScale->text());
  settings.setValue("sliderLineWidth", ui->slider_lineWidth->value());
  settings.setValue("sliderVertScale", ui->slider_vertScale->value());
}

void MainWindow::on_pushButton_loa_settings_clicked() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");

  ui->doubleSpinBox_move_x->setValue(settings.value("move_x").toDouble());
  ui->doubleSpinBox_move_y->setValue(settings.value("move_y").toDouble());
  ui->doubleSpinBox_move_z->setValue(settings.value("move_z").toDouble());
  ui->doubleSpinBox_rotate_x->setValue(settings.value("rotate_x").toDouble());
  ui->doubleSpinBox_rotate_y->setValue(settings.value("rotate_y").toDouble());
  ui->doubleSpinBox_rotate_z->setValue(settings.value("rotate_z").toDouble());
  ui->doubleSpinBox_scale->setValue(settings.value("scale").toDouble());

  if (settings.value("projection_parallel").toBool()) {
    ui->radioButton_parallel->setChecked(true);
    on_radioButton_parallel_clicked();
  } else {
    ui->radioButton_central->setChecked(true);
    on_radioButton_central_clicked();
  }

  if (settings.value("edge_solid").toBool()) {
    ui->radioButton_solid->setChecked(true);
    on_radioButton_solid_clicked();
  } else {
    ui->radioButton_dashed->setChecked(true);
    on_radioButton_dashed_clicked();
  }

  if (settings.value("vertices_circle").toBool()) {
    ui->radioButton_circle->setChecked(true);
    on_radioButton_circle_clicked();
  } else if (settings.value("vertices_square").toBool()) {
    ui->radioButton_square->setChecked(true);
    on_radioButton_square_clicked();
  } else {
    ui->radioButton_none->setChecked(true);
    on_radioButton_none_clicked();
  }

  ui->sliderBackroundR->setValue(settings.value("backR").toInt());
  ui->sliderBackroundG->setValue(settings.value("backG").toInt());
  ui->sliderBackroundB->setValue(settings.value("backB").toInt());
  ui->slider_lineR->setValue(settings.value("lineR").toInt());
  ui->slider_lineG->setValue(settings.value("lineG").toInt());
  ui->slider_lineB->setValue(settings.value("lineB").toInt());
  ui->slider_vertR->setValue(settings.value("vertR").toInt());
  ui->slider_vertG->setValue(settings.value("vertG").toInt());
  ui->slider_vertB->setValue(settings.value("vertB").toInt());
  ui->lineLineWidth->setText(settings.value("lineWidth").toString());
  ui->line_vertScale->setText(settings.value("vertScale").toString());
  ui->slider_lineWidth->setValue(settings.value("sliderLineWidth").toInt());
  ui->slider_vertScale->setValue(settings.value("sliderVertScale").toInt());

  settings.endGroup();
}

void MainWindow::on_pushButton_clicked() {
  ui->pushButton->setEnabled(false);
  ui->progressBar_gif->setValue(0);
  gif.setDefaultDelay(100);
  timer = new QTimer(this);
  timer->setInterval(200);
  connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));
  timer->start();
  QTimer::singleShot(20000, this, SLOT(stop_timer()));
}

void MainWindow::stop_timer() {
  timer->stop();
  QFileDialog call(this);
  QString fileName =
      call.getSaveFileName(this, "Save a gif", "", "gif (*.gif)");
  if (!fileName.isEmpty()) {
    gif.save(fileName);
  }
  delete timer;
  ui->pushButton->setEnabled(true);
}

void MainWindow::make_gif() {
  QImage image = ui->openGLWidget->grabFramebuffer();
  gif.addFrame(image);
  ui->progressBar_gif->setValue(ui->progressBar_gif->value() + 1);
}

void MainWindow::on_slider_vertScale_valueChanged(int value) {
  ui->line_vertScale->setText(QString::number(value));
  ui->openGLWidget->VertScale = value;
  ui->openGLWidget->update();
}

void MainWindow::on_slider_lineWidth_valueChanged(int value) {
  ui->lineLineWidth->setText(QString::number(value));
  ui->openGLWidget->LineWidth = value;
  ui->openGLWidget->update();
}

void MainWindow::on_slider_lineR_valueChanged(int value) {
  ui->openGLWidget->LineR = value;
  ui->openGLWidget->update();
}

void MainWindow::on_slider_lineG_valueChanged(int value) {
  ui->openGLWidget->LineG = value;
  ui->openGLWidget->update();
}

void MainWindow::on_slider_lineB_valueChanged(int value) {
  ui->openGLWidget->LineB = value;
  ui->openGLWidget->update();
}

void MainWindow::on_slider_vertR_valueChanged(int value) {
  ui->openGLWidget->VertR = value;
  ui->openGLWidget->update();
}

void MainWindow::on_slider_vertG_valueChanged(int value) {
  ui->openGLWidget->VertG = value;
  ui->openGLWidget->update();
}

void MainWindow::on_slider_vertB_valueChanged(int value) {
  ui->openGLWidget->VertB = value;
  ui->openGLWidget->update();
}

void MainWindow::on_sliderBackroundR_valueChanged(int value) {
  ui->openGLWidget->BackR = value;
  ui->openGLWidget->update();
}

void MainWindow::on_sliderBackroundG_valueChanged(int value) {
  ui->openGLWidget->BackG = value;
  ui->openGLWidget->update();
}

void MainWindow::on_sliderBackroundB_valueChanged(int value) {
  ui->openGLWidget->BackB = value;
  ui->openGLWidget->update();
}
