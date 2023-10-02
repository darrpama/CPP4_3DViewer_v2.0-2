#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(s21::Controller &controller, QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , controller_(controller)
{
  ui->setupUi(this);
  canvas_ = findChild<Canvas*>("canvas");
  canvas_->SetController(controller_);
  upload_button_ = findChild<QPushButton*>("uploadButton");
  
  // position spins
  position_x_ = findChild<QDoubleSpinBox*>("position_x");
  position_y_ = findChild<QDoubleSpinBox*>("position_y");
  position_z_ = findChild<QDoubleSpinBox*>("position_z");

  // rotation spins
  rotation_x_ = findChild<QDoubleSpinBox*>("rotation_x");
  rotation_y_ = findChild<QDoubleSpinBox*>("rotation_y");
  rotation_z_ = findChild<QDoubleSpinBox*>("rotation_z");

  // scale spins
  scale_x_ = findChild<QDoubleSpinBox*>("scale_x");
  scale_y_ = findChild<QDoubleSpinBox*>("scale_y");
  scale_z_ = findChild<QDoubleSpinBox*>("scale_z");

  QPalette palette = upload_button_->palette();
  QColor iconColor("red");
  palette.setColor(QPalette::ButtonText, iconColor);
  upload_button_->setPalette(palette);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);
  QSize newSize = event->size();

  // Calculate the desired size for the QOpenGLWidget
  int glWidgetWidth = newSize.width();
  int glWidgetHeight = newSize.height();

  // Resize the QOpenGLWidget
  canvas_->resize(glWidgetWidth, glWidgetHeight);
}

void MainWindow::on_uploadButton_clicked() {
  QString file_path = QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("All Files (*.*)"));
  if (!file_path.isEmpty()) {
    std::cout << "file choosed!" << std::endl;
    std::string file = file_path.toStdString();
    controller_.ParseObjFile(file);
  }
}

// position X
void MainWindow::on_position_x_valueChanged(double x) {
  controller_.ApplyTranslation(x, position_y_->value(), position_z_->value());
}

void MainWindow::on_position_y_valueChanged(double y) {
  controller_.ApplyTranslation(position_x_->value(), y, position_z_->value());
}

void MainWindow::on_position_z_valueChanged(double z) {
  controller_.ApplyTranslation(position_x_->value(), position_y_->value(), z);
}

void MainWindow::on_rotation_x_valueChanged(double x) {
  controller_.ApplyRotation(x, rotation_y_->value(), rotation_z_->value());
}

void MainWindow::on_rotation_y_valueChanged(double y) {
  controller_.ApplyRotation(rotation_x_->value(), y, rotation_z_->value());
}

void MainWindow::on_rotation_z_valueChanged(double z) {
  controller_.ApplyRotation(rotation_x_->value(), rotation_y_->value(), z);
}

void MainWindow::on_scale_x_valueChanged(double x) {
  controller_.ApplyScale(x, scale_y_->value(), scale_z_->value());
}

void MainWindow::on_scale_y_valueChanged(double y) {
  controller_.ApplyScale(scale_x_->value(), y, scale_z_->value());
}

void MainWindow::on_scale_z_valueChanged(double z) {
  controller_.ApplyScale(scale_x_->value(), scale_y_->value(), z);
}

