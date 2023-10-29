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
    position_x_->value(), 
    position_y_->value(), 
    position_z_->value()
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

void MainWindow::on_edge_thikness_sliderMoved(int position) {
  controller_.SetEdgeThikness(position);
  canvas_->UpdateWidget();
}

void MainWindow::on_vertice_size_sliderMoved(int position) {
  controller_.SetVerticeSize(position);
  canvas_->UpdateWidget();
}

void MainWindow::SetVerticeType(s21::VerticeType type) {
  controller_.SetVerticeType(type);
  canvas_->UpdateWidget();
}

void MainWindow::SetEdgeType(s21::EdgeType type) {
  controller_.SetEdgeType(type);
  canvas_->UpdateWidget();
}

void MainWindow::SetProjectionType(s21::ProjectionType type, bool checked) {
  if (checked) controller_.SetProjectionType(type);
  canvas_->UpdateWidget();
}

void MainWindow::on_screencast_button_clicked() {
  ScreencastThread* screencastThread = new ScreencastThread(this);
  screencastThread->start();
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

  QString webpPath = "/Users/myregree/Desktop/custom_affine_transformation.webp";
  
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

