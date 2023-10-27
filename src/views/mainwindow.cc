#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(s21::Controller &controller, QWidget *parent)
  : QMainWindow(parent)
  , ui_(new Ui::MainWindow)
  , controller_(controller)
{
  ui_->setupUi(this);
  canvas_ = findChild<Canvas*>("canvas");
  canvas_->SetController(&controller_);

  // upload ui
  upload_button_ = findChild<QPushButton*>("uploadButton");
  filepath_label_ = findChild<QLabel*>("filepath_label");

  // projection
  central_projection_radio_ = findChild<QRadioButton*>("central_projection_radio");
  parallel_projection_radio_ = findChild<QRadioButton*>("parallel_projection_radio");
  
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

  // set default values
  QPalette palette = upload_button_->palette();
  QColor iconColor("red");
  palette.setColor(QPalette::ButtonText, iconColor);
  upload_button_->setPalette(palette);
  central_projection_radio_->setChecked(true);
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);
  QSize newSize = event->size();
}

void MainWindow::on_central_projection_radio_toggled(bool checked) {
  if (checked) controller_.SetCentralProjection();
  canvas_->UpdateWidget();
}

void MainWindow::on_parallel_projection_radio_toggled(bool checked) {
  if (checked) controller_.SetParallelProjection();
  canvas_->UpdateWidget();
}

void MainWindow::on_uploadButton_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
    this, tr("Select File"), "", tr("All Files (*.*)")
  );
  if (!file_path.isEmpty()) {
    std::string file = file_path.toStdString();
    filepath_label_->setText(file_path);
    controller_.ParseObjFile(file);
  }
}

// position X
void MainWindow::on_position_x_valueChanged(double x) {
  controller_.ApplyTranslationX((float) x);
  canvas_->UpdateWidget();
}

void MainWindow::on_position_y_valueChanged(double y) {
  controller_.ApplyTranslationY((float) y);
  canvas_->UpdateWidget();
}

void MainWindow::on_position_z_valueChanged(double z) {
  controller_.ApplyTranslationZ((float) z);
  canvas_->UpdateWidget();
}

void MainWindow::on_rotation_x_valueChanged(double x) {
  controller_.ApplyRotationX((float) x);
  canvas_->UpdateWidget();
}

void MainWindow::on_rotation_y_valueChanged(double y) {
  controller_.ApplyRotationY((float) y);
  canvas_->UpdateWidget();
}

void MainWindow::on_rotation_z_valueChanged(double z) {
  controller_.ApplyRotationZ((float) z);
  canvas_->UpdateWidget();
}

void MainWindow::on_scale_control_valueChanged(double x) {
  controller_.ApplyScale((float) x);
  canvas_->UpdateWidget();
}

void MainWindow::on_background_color_clicked() {
  controller_.SetBackgroundColor(QColorDialog::getColor());
  canvas_->UpdateWidget();
}

