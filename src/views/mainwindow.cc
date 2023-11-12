#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);
  canvas_ = findChild<Canvas*>("canvas");
}

void MainWindow::SetValues() {
  // Set default values
  
  ui_->central_projection_radio->setChecked(true);
  ui_->parallel_projection_radio->setChecked(true);


  ui_->edge_type_solid->setChecked(true);
  ui_->vertice_type_circle->setChecked(true);

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
// TODO: remove hardcoded values
void MainWindow::SetDefaultValues() {
  s21::Controller::GetInstance().SetEdgeType(s21::EdgeType::SOLID);
  s21::Controller::GetInstance().SetEdgeThikness(10);
  s21::Controller::GetInstance().SetVerticeType(s21::VerticeType::CIRCLE);
  s21::Controller::GetInstance().SetVerticeSize(3); 
  canvas_->UpdateWidget();
}

MainWindow::~MainWindow() {
  delete ui_;
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
    s21::Controller::GetInstance().ParseObjFile(file_path);
    SetObjectInfo();
    SetDefaultValues();
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
  s21::Controller::GetInstance().SetEdgeThikness(position);
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

void MainWindow::MakeScreencast(QWidget* widget) {
  const int width = 640;
  const int height = 480;
  const int fps = 10;
  const int durationSeconds = 5;
  const int totalFrames = fps * durationSeconds;

  QString folderPath = QDir::currentPath() + "/saved";
  QDir folderDir(folderPath);
  if (!folderDir.exists()) {
      folderDir.mkpath(".");
  }

  QString webpPath = "/Users/myregree/Desktop/anime.webp";
  
  QImageWriter webpWriter(webpPath);
  webpWriter.setFormat("webp");
  webpWriter.setQuality(100);
  // gifWriter.setText("FrameRate", QString::number(fps));
  QElapsedTimer timer;
  timer.start();
  
  std::cout << "[ Start record ]" << std::endl;
  
  for (int frame = 0; frame < totalFrames; ++frame) {
    std::cout << "frame #" << frame << std::endl;
    qreal progress = static_cast<qreal>(frame) / totalFrames;
    QPixmap pixmap = widget->grab();
    QImage image = pixmap.toImage();

    if (webpWriter.write(image)) {
      std::cout << " -> image written" << std::endl;
    } else {
      std::cout << " -> image not written. ERROR: " << webpWriter.errorString().toStdString() << std::endl;
    }

    int frameTime = 1000 / fps; // in milliseconds
    int elapsed = timer.elapsed();
    int remainingTime = frameTime - elapsed;
    if (remainingTime > 0) {
      QThread::msleep(remainingTime);
    }
    timer.restart();
  }

  // // print supported formats
  // std::cout << "Supported formats: " << std::endl;
  // QList formats = QImageWriter::supportedImageFormats();
  // for (size_t i = 0; i < formats.size(); i++)
  // {
  //   std::cout << formats.at(i).toStdString() << std::endl;
  // }
  
  std::cout << "[ End record ]" << std::endl;
  webpWriter.device()->close();
}
