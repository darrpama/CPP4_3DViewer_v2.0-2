#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas_ = findChild<QOpenGLWidget*>("canvas");
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

    // Check if a file was selected
    if (!filePath.isEmpty())
    {
        std::cout << "file choosed!" << std::endl;
        // Do something with the selected file path
        // For example, you can display the file path in a QLabel or process the file
    }
}

