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


void MainWindow::on_uploadButton_clicked()
{
  QString filePath = QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("All Files (*.*)"));
  if (!filePath.isEmpty())
  {
    std::cout << "file choosed!" << std::endl;
    // TODO: что делать когда файл выбран?
  }
}


void MainWindow::on_spinBox_4_valueChanged(int arg1)
{

}

