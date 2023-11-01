#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H

#define GL_SILENCE_DEPRECATION

#include "../controllers/controller.h"
#include "canvas.h"

#include <iostream>
#include <thread>

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QColorDialog>
#include <QPalette>

#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QDir>
#include <QPainter>
#include <QImageWriter>
#include <QElapsedTimer>

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
  QString MakeColorStyle(QColor);

 private slots:
  // upload
  void on_uploadButton_clicked();
  
  // projection
  void on_central_projection_radio_toggled(bool checked) {SetProjectionType(s21::ProjectionType::CENTRAL, checked); }
  void on_parallel_projection_radio_toggled(bool checked) {SetProjectionType(s21::ProjectionType::PARALLEL, checked); }

  // transform
  void on_position_x_valueChanged(double x) { ApplyTranslation(); }
  void on_position_y_valueChanged(double y) { ApplyTranslation(); }
  void on_position_z_valueChanged(double z) { ApplyTranslation(); }
  void on_rotation_x_valueChanged(double x) { ApplyRotation(); }
  void on_rotation_y_valueChanged(double y) { ApplyRotation(); }
  void on_rotation_z_valueChanged(double z) { ApplyRotation(); }
  void on_scale_control_valueChanged(double);
  
  // colors
  void on_background_color_clicked();
  void on_points_color_clicked();
  void on_lines_color_clicked();
  
  // edge type

  void on_edge_type_none_clicked() {SetEdgeType(s21::EdgeType::NO_EDGE); }
  void on_edge_type_solid_clicked() {SetEdgeType(s21::EdgeType::SOLID); }
  void on_edge_type_dashed_clicked() {SetEdgeType(s21::EdgeType::DASHED); }

  void SetEdgeType(s21::EdgeType);

  // edge thikness
  void on_edge_thikness_sliderMoved(int);
  
  // vertice types
  void on_vertice_type_none_clicked() { SetVerticeType(s21::VerticeType::NO_VERTICE); }
  void on_vertice_type_circle_clicked() { SetVerticeType(s21::VerticeType::CIRCLE); }
  void on_vertice_type_square_clicked() { SetVerticeType(s21::VerticeType::SQUARE); }
  
  void SetVerticeType(s21::VerticeType);
  void SetProjectionType(s21::ProjectionType, bool);

  // vertice size
  void on_vertice_size_sliderMoved(int);
  
  void on_screenshot_button_clicked() { MakeScreenshot(canvas_); }
  void on_screencast_button_clicked();

private:
  s21::Controller controller_;
  Ui::MainWindow *ui_;
  Canvas *canvas_;
  QLabel *filepath_label_;
  QLabel *vertex_count_label_;
  QLabel *face_count_label_;
  QLabel *edge_count_label_;
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
  QRadioButton *central_projection_radio_;
  QRadioButton *parallel_projection_radio_;
  QPushButton *background_color_button_;
  QPushButton *points_color_button_;
  QPushButton *lines_color_button_;

  // Edge types
  QRadioButton *edge_type_none_;
  QRadioButton *edge_type_solid_;
  QRadioButton *edge_type_dashed_;

  // Vertice types
  QRadioButton *vertice_type_none_;
  QRadioButton *vertice_type_circle_;
  QRadioButton *vertice_type_square_;

  // Sliders
  QSlider *vertice_size_;
  QSlider *edge_thickness_;

  void ApplyTranslation();
  void ApplyRotation();
  void MakeScreenshot(QWidget*);
  void MakeScreencast(QWidget*);
  void SetDefaultValues();
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
