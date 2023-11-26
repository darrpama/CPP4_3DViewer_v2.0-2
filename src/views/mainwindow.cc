#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);
  canvas_ = findChild<Canvas*>("canvas");
  InitValues();
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::InitProjectionType() {
  switch (s21::ControllerSingleton::GetInstance().GetProjectionType()) {
    case s21::ProjectionType::CENTRAL:
      ui_->central_projection_radio->setChecked(true);
      break;
    case s21::ProjectionType::PARALLEL:
      ui_->parallel_projection_radio->setChecked(true);
      break; 
    default:
      ui_->central_projection_radio->setChecked(true);
      break;
  };
}

void MainWindow::InitColors() {
  ui_->background_color->setStyleSheet(MakeColorStyle(
    s21::ControllerSingleton::GetInstance().GetColor(s21::ColorType::BG_COLOR)
  ));
  ui_->points_color->setStyleSheet(MakeColorStyle(
    s21::ControllerSingleton::GetInstance().GetColor(s21::ColorType::VERTICE_COLOR)
  ));
  ui_->lines_color->setStyleSheet(MakeColorStyle(
    s21::ControllerSingleton::GetInstance().GetColor(s21::ColorType::EDGE_COLOR)
  ));
}

void MainWindow::InitEdgeType() {
  switch (s21::ControllerSingleton::GetInstance().GetEdgeType()) {
    case s21::EdgeType::DASHED:
      ui_->edge_type_dashed->setChecked(true);
      break;
    case s21::EdgeType::SOLID:
      ui_->edge_type_solid->setChecked(true);
      break;
    case s21::EdgeType::NO_EDGE:
      ui_->edge_type_none->setChecked(true);
      break;
    default:
      ui_->edge_type_solid->setChecked(true);
      break;
  }
}

void MainWindow::InitVerticeType() {
  switch (s21::ControllerSingleton::GetInstance().GetVerticeType()) {
    case s21::VerticeType::CIRCLE:
      ui_->vertice_type_circle->setChecked(true);
      break;
    case s21::VerticeType::NO_VERTICE:
      ui_->vertice_type_none->setChecked(true);
      break;
    case s21::VerticeType::SQUARE:
      ui_->vertice_type_square->setChecked(true);
      break;
    default:
      ui_->vertice_type_square->setChecked(true);
      break;
  }
}

void MainWindow::InitEdgeThickness() {
  ui_->edge_thikness->setValue(s21::ControllerSingleton::GetInstance().GetEdgeThickness());
}

void MainWindow::InitVerticeSize() {
  ui_->vertice_size->setValue(s21::ControllerSingleton::GetInstance().GetVerticeSize());
}

void MainWindow::InitTranslations() {
  ui_->position_x->setValue(s21::ControllerSingleton::GetInstance().GetTranslationX());
  ui_->position_y->setValue(s21::ControllerSingleton::GetInstance().GetTranslationY());
  ui_->position_z->setValue(s21::ControllerSingleton::GetInstance().GetTranslationZ());
}

void MainWindow::InitRotations() {
  ui_->rotation_x->setValue(s21::ControllerSingleton::GetInstance().GetRotationX());
  ui_->rotation_y->setValue(s21::ControllerSingleton::GetInstance().GetRotationY());
  ui_->rotation_z->setValue(s21::ControllerSingleton::GetInstance().GetRotationZ());
}

void MainWindow::InitScale() {
  ui_->scale_control->setValue(s21::ControllerSingleton::GetInstance().GetScale());
}

void MainWindow::InitValues() {
  InitProjectionType();
  InitColors();
  InitEdgeType();
  InitVerticeType();
  InitEdgeThickness();
  InitVerticeSize();
  InitTranslations();
  InitRotations();
  InitScale();
  canvas_->UpdateWidget();
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);
  QSize newSize = event->size();
}

void MainWindow::on_upload_button_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
    this, tr("Select File"), "", tr("All Files (*.*)")
  );
  if (!file_path.isEmpty()) {
    ui_->filepath_label->setText(file_path);
    s21::ControllerSingleton::GetInstance().ParseObjFile(file_path);
    SetObjectInfo();
    InitValues();
  }
}

void MainWindow::on_reset_transform_button_clicked() {
  s21::ControllerSingleton::GetInstance().SetTranslationX(0.0f);
  s21::ControllerSingleton::GetInstance().SetTranslationY(0.0f);
  s21::ControllerSingleton::GetInstance().SetTranslationZ(0.0f);
  s21::ControllerSingleton::GetInstance().ApplyScale(1.0f);
  s21::ControllerSingleton::GetInstance().SetRotationX(0.0f);
  s21::ControllerSingleton::GetInstance().SetRotationY(0.0f);
  s21::ControllerSingleton::GetInstance().SetRotationZ(0.0f);
  ui_->position_x->setValue(0.0f);
  ui_->position_y->setValue(0.0f);
  ui_->position_z->setValue(0.0f);
  ui_->rotation_x->setValue(0.0f);
  ui_->rotation_y->setValue(0.0f);
  ui_->rotation_z->setValue(0.0f);
  ui_->scale_control->setValue(1.0f);
  canvas_->UpdateWidget();
}

void MainWindow::on_normalize_object_button_clicked() {
  s21::ControllerSingleton::GetInstance().NormalizeObject();
  canvas_->UpdateWidget();
}

void MainWindow::on_position_x_valueChanged(double x) {
  s21::ControllerSingleton::GetInstance().SetTranslationX(
    ui_->position_x->value()
  );
  canvas_->UpdateWidget();
}

void MainWindow::on_position_y_valueChanged(double y) {
  s21::ControllerSingleton::GetInstance().SetTranslationY(
    ui_->position_y->value()
  );
  canvas_->UpdateWidget();
}

void MainWindow::on_position_z_valueChanged(double z) {
  s21::ControllerSingleton::GetInstance().SetTranslationZ(
    ui_->position_z->value()
  );
  canvas_->UpdateWidget();
}

void MainWindow::on_rotation_x_valueChanged(double val) {
  s21::ControllerSingleton::GetInstance().SetRotationX(
    ui_->rotation_x->value()
  );
  canvas_->UpdateWidget();
}
void MainWindow::on_rotation_y_valueChanged(double val) {
  s21::ControllerSingleton::GetInstance().SetRotationY(
    ui_->rotation_y->value()
  );
  canvas_->UpdateWidget();
}
void MainWindow::on_rotation_z_valueChanged(double val) {
  s21::ControllerSingleton::GetInstance().SetRotationZ(
    ui_->rotation_z->value()
  );
  canvas_->UpdateWidget();
}

void MainWindow::on_scale_control_valueChanged(double x) {
  s21::ControllerSingleton::GetInstance().ApplyScale((float) x);
  canvas_->UpdateWidget();
}

void MainWindow::on_background_color_clicked() {
  SetColor(ui_->background_color, s21::ColorType::BG_COLOR);
}

void MainWindow::on_points_color_clicked() {
  SetColor(ui_->points_color, s21::ColorType::VERTICE_COLOR);
}

void MainWindow::on_lines_color_clicked() {
  SetColor(ui_->lines_color, s21::ColorType::EDGE_COLOR);
}

void MainWindow::on_edge_thikness_sliderMoved(int position) {
  s21::ControllerSingleton::GetInstance().SetEdgeThickness(position);
  canvas_->UpdateWidget();
}

void MainWindow::on_vertice_size_sliderMoved(int position) {
  s21::ControllerSingleton::GetInstance().SetVerticeSize(position);
  canvas_->UpdateWidget();
}

void MainWindow::on_screencast_button_clicked() {}

void MainWindow::on_jpg_screenshot_button_clicked() {
  s21::ControllerSingleton::GetInstance().MakeScreenshot(canvas_, s21::ScreenshotType::JPG);
}

void MainWindow::on_bmp_screenshot_button_clicked() {
  s21::ControllerSingleton::GetInstance().MakeScreenshot(canvas_, s21::ScreenshotType::BMP);
}

void MainWindow::SetObjectInfo() {
  ui_->vertex_count_label->setText(QString::number(s21::ControllerSingleton::GetInstance().GetVertexCount()));
  ui_->face_count_label->setText(QString::number(s21::ControllerSingleton::GetInstance().GetFaceCount()));
  ui_->edge_count_label->setText(QString::number(s21::ControllerSingleton::GetInstance().GetEdgeCount()));
}

void MainWindow::SetColor(QWidget *widget, s21::ColorType type) {
  QColor color = QColorDialog::getColor();
  s21::ControllerSingleton::GetInstance().SetColor(type, color);
  widget->setStyleSheet(MakeColorStyle(color));
  canvas_->UpdateWidget();
}

QString MainWindow::MakeColorStyle(QColor color) {
  return "background-color: rgb(" +
    QString::number(color.red()) + ", " +
    QString::number(color.green()) + ", " +
    QString::number(color.blue()) + ");";
}

void MainWindow::SetVerticeType(s21::VerticeType type) {
  s21::ControllerSingleton::GetInstance().SetVerticeType(type);
  canvas_->UpdateWidget();
}

void MainWindow::SetEdgeType(s21::EdgeType type) {
  s21::ControllerSingleton::GetInstance().SetEdgeType(type);
  canvas_->UpdateWidget();
}

void MainWindow::SetProjectionType(s21::ProjectionType type, bool checked) {
  if (checked) s21::ControllerSingleton::GetInstance().SetProjectionType(type);
  canvas_->UpdateWidget();
}
