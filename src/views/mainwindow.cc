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


void MainWindow::InitProjectionType() {
  switch (s21::Controller::GetInstance().GetProjectionType()) {
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
    s21::Controller::GetInstance().GetColor(s21::ColorType::BG_COLOR)
  ));
  ui_->points_color->setStyleSheet(MakeColorStyle(
    s21::Controller::GetInstance().GetColor(s21::ColorType::VERTICE_COLOR)
  ));
  ui_->lines_color->setStyleSheet(MakeColorStyle(
    s21::Controller::GetInstance().GetColor(s21::ColorType::EDGE_COLOR)
  ));
}

void MainWindow::InitEdgeType() {
  switch (s21::Controller::GetInstance().GetEdgeType()) {
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
  switch (s21::Controller::GetInstance().GetVerticeType()) {
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
  ui_->edge_thikness->setValue(s21::Controller::GetInstance().GetEdgeThickness());
}

void MainWindow::InitVerticeSize() {
  ui_->vertice_size->setValue(s21::Controller::GetInstance().GetVerticeSize());
}

void MainWindow::InitGIFVariables() {
  is_recording_ = false;
  time_ = 0.0;
  record_time_ = new QTimer(this);
  connect(record_time_, &QTimer::timeout, this, Recording);
}

void MainWindow::InitTranslations() {
  ui_->position_x->setValue(s21::Controller::GetInstance().GetTranslationX());
  ui_->position_y->setValue(s21::Controller::GetInstance().GetTranslationY());
  ui_->position_z->setValue(s21::Controller::GetInstance().GetTranslationZ());
}

void MainWindow::InitRotations() {
  ui_->rotation_x->setValue(s21::Controller::GetInstance().GetRotationX());
  ui_->rotation_y->setValue(s21::Controller::GetInstance().GetRotationX());
  ui_->rotation_z->setValue(s21::Controller::GetInstance().GetRotationX());
}

void MainWindow::InitScale() {
  ui_->scale_control->setValue(s21::Controller::GetInstance().GetScale());
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
  InitGIFVariables();
  canvas_->UpdateWidget();
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);
  QSize newSize = event->size();
}

// SLOTS
void MainWindow::on_upload_button_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
    this, tr("Select File"), "", tr("All Files (*.*)")
  );
  if (!file_path.isEmpty()) {
    ui_->filepath_label->setText(file_path);
    s21::Controller::GetInstance().ParseObjFile(file_path);
    SetObjectInfo();
    InitValues();
  }
}

void MainWindow::on_reset_transform_button_clicked() {
  s21::Controller::GetInstance().ApplyTranslation(0.0f, 0.0f, 0.0f);
  s21::Controller::GetInstance().ApplyScale(1.0f);
  s21::Controller::GetInstance().ApplyRotation(0.0f, 0.0f, 0.0f);
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
  s21::Controller::GetInstance().NormalizeObject();
  canvas_->UpdateWidget();
}

void MainWindow::on_scale_control_valueChanged(double x) {
  s21::Controller::GetInstance().ApplyScale((float) x);
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
  s21::Controller::GetInstance().SetEdgeThickness(position);
  canvas_->UpdateWidget();
}

void MainWindow::on_vertice_size_sliderMoved(int position) {
  s21::Controller::GetInstance().SetVerticeSize(position);
  canvas_->UpdateWidget();
}

void MainWindow::on_screencast_button_clicked() {
  MakeScreencast(canvas_);
}


void MainWindow::SetObjectInfo() {
  ui_->vertex_count_label->setText(QString::number(s21::Controller::GetInstance().GetVertexCount()));
  ui_->face_count_label->setText(QString::number(s21::Controller::GetInstance().GetFaceCount()));
  ui_->edge_count_label->setText(QString::number(s21::Controller::GetInstance().GetEdgeCount()));
}

// position X
void MainWindow::ApplyTranslation() {
  s21::Controller::GetInstance().ApplyTranslation(
    ui_->position_x->value(), 
    ui_->position_y->value(), 
    ui_->position_z->value()
  );
  canvas_->UpdateWidget();
}

void MainWindow::ApplyRotation() {
  s21::Controller::GetInstance().ApplyRotation(
    ui_->rotation_x->value(),
    ui_->rotation_y->value(),
    ui_->rotation_z->value()
  );
  canvas_->UpdateWidget();
}

void MainWindow::SetColor(QWidget *widget, s21::ColorType type) {
  QColor color = QColorDialog::getColor();
  s21::Controller::GetInstance().SetColor(type, color);
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
  s21::Controller::GetInstance().SetVerticeType(type);
  canvas_->UpdateWidget();
}

void MainWindow::SetEdgeType(s21::EdgeType type) {
  s21::Controller::GetInstance().SetEdgeType(type);
  canvas_->UpdateWidget();
}

void MainWindow::SetProjectionType(s21::ProjectionType type, bool checked) {
  if (checked) s21::Controller::GetInstance().SetProjectionType(type);
  canvas_->UpdateWidget();
}

void MainWindow::MakeScreenshot(QWidget* widget) {
  QPixmap pixmap = widget->grab();
  QString folderPath = QDir::currentPath() + "/saved";
  QDir folderDir(folderPath);
  if (!folderDir.exists()) {
    folderDir.mkpath(".");
  }

  QString imagePath = folderPath + "/widget_image.png";
  if (pixmap.save(imagePath)) {
    std::cout << "image saved!" << std::endl;
  } else {
    std::cout << "image not saved... there is an error!" << std::endl;
  }
}

void MainWindow::Recording() {
  if (!is_recording_ && time_ <= 5.0) {
    GIF_.push_back(widget->grab().toImage());
    time_ += 0.1;
  } else {
    SaveGIF();
    record_time_->stop();
  }
}

void MainWindow::MakeScreencast(QWidget* widget) {


  QVector<QImage> GIF;
  QGifImage gif(QSize(640, 480));

  gif.setDefaultTransparentColor(Qt::black);
  gif.setDefaultDelay(100);

  for (QVector<QImage>::Iterator frame = GIF.begin(); frame != GIF.end(); frame++) {
    gif.addFrame(*frame);
  }

  gif.save();
  GIF.clear();

}
