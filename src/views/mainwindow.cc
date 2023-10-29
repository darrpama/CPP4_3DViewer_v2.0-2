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

  // color buttons
  background_color_button_ = findChild<QPushButton*>("background_color");
  points_color_button_ = findChild<QPushButton*>("points_color");
  lines_color_button_ = findChild<QPushButton*>("lines_color");

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

  // Edge types
  edge_type_none_ = findChild<QRadioButton*>("edge_type_none");
  edge_type_solid_ = findChild<QRadioButton*>("edge_type_solid");
  edge_type_dashed_ = findChild<QRadioButton*>("edge_type_dashed");
  vertice_type_none_ = findChild<QRadioButton*>("vertice_type_none");

  // set default values
  central_projection_radio_->setChecked(true);
  edge_type_none_->setChecked(true);
  vertice_type_none_->setChecked(true);
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);
  QSize newSize = event->size();
}

void MainWindow::on_central_projection_radio_toggled(bool checked) {
  if (checked) controller_.SetProjectionType(s21::ProjectionType::CENTRAL);
  canvas_->UpdateWidget();
}

void MainWindow::on_parallel_projection_radio_toggled(bool checked) {
  if (checked) controller_.SetProjectionType(s21::ProjectionType::PARALLEL);
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
void MainWindow::ApplyTranslation() {
  controller_.ApplyTranslation(
    (float) position_x_->value(), 
    (float) position_y_->value(), 
    (float) position_z_->value()
  );
  canvas_->UpdateWidget();
}

void MainWindow::ApplyRotation() {
  controller_.ApplyRotation(
    rotation_x_->value(),
    rotation_y_->value(),
    rotation_z_->value()
  );
  canvas_->UpdateWidget();
}

void MainWindow::on_scale_control_valueChanged(double x) {
  controller_.ApplyScale((float) x);
  canvas_->UpdateWidget();
}

void MainWindow::on_background_color_clicked() {
  QColor color = QColorDialog::getColor();
  controller_.SetBackgroundColor(color);
  background_color_button_->setStyleSheet(MakeColorStyle(color));
  canvas_->UpdateWidget();
}

void MainWindow::on_points_color_clicked() {
  QColor color = QColorDialog::getColor();
  controller_.SetPointsColor(color);
  points_color_button_->setStyleSheet(MakeColorStyle(color));
  canvas_->UpdateWidget();
}

void MainWindow::on_lines_color_clicked() {
  QColor color = QColorDialog::getColor();
  controller_.SetLinesColor(color);
  lines_color_button_->setStyleSheet(MakeColorStyle(color));
  canvas_->UpdateWidget();
}

QString MainWindow::MakeColorStyle(QColor color) {
  return "background-color: rgb(" +
    QString::number(color.red()) + ", " +
    QString::number(color.green()) + ", " +
    QString::number(color.blue()) + ");";
}


void MainWindow::on_edge_type_none_clicked() {
  controller_.SetEdgeType(s21::EdgeType::NO_EDGE);
  canvas_->UpdateWidget();
}

void MainWindow::on_edge_type_solid_clicked() {
  controller_.SetEdgeType(s21::EdgeType::SOLID);
  canvas_->UpdateWidget();
}

void MainWindow::on_edge_type_dashed_clicked() {
  controller_.SetEdgeType(s21::EdgeType::DASHED);
  canvas_->UpdateWidget();
}


void MainWindow::on_edge_thikness_sliderMoved(int position) {
  controller_.SetEdgeThikness(position);
  canvas_->UpdateWidget();
}


void MainWindow::on_vertice_type_none_clicked() {
  controller_.SetVerticeType(s21::VerticeType::NO_VERTICE);
  canvas_->UpdateWidget();
}


void MainWindow::on_vertice_type_circle_clicked() {
  controller_.SetVerticeType(s21::VerticeType::CIRCLE);
  canvas_->UpdateWidget();
}


void MainWindow::on_vertice_type_square_clicked() {
  controller_.SetVerticeType(s21::VerticeType::SQUARE);
  canvas_->UpdateWidget();
}

void MainWindow::on_vertice_size_sliderMoved(int position) {
  controller_.SetVerticeSize(position);
  canvas_->UpdateWidget();
}

