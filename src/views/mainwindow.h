#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H

#define GL_SILENCE_DEPRECATION

#include "../controllers/controller.h"
#include "canvas.h"

#include <iostream>

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(s21::Controller &controller, QWidget *parent = nullptr);
  ~MainWindow();
  void resizeEvent(QResizeEvent* event);

private slots:
  void on_uploadButton_clicked();
  void on_position_x_valueChanged(double);
  void on_position_y_valueChanged(double);
  void on_position_z_valueChanged(double);
  void on_rotation_x_valueChanged(double);
  void on_rotation_y_valueChanged(double);
  void on_rotation_z_valueChanged(double);
  void on_scale_control_valueChanged(double);

private:
  s21::Controller controller_;
  Ui::MainWindow *ui;
  Canvas *canvas_;
  QPushButton *upload_button_;
  QDoubleSpinBox *position_x_;
  QDoubleSpinBox *position_y_;
  QDoubleSpinBox *position_z_;
  QDoubleSpinBox *rotation_x_;
  QDoubleSpinBox *rotation_y_;
  QDoubleSpinBox *rotation_z_;
  QDoubleSpinBox *scale_x_;
  QDoubleSpinBox *scale_y_;
  QDoubleSpinBox *scale_z_;

};
#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
