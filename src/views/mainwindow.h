#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_uploadButton_clicked();

private:
    Ui::MainWindow *ui;
    QOpenGLWidget *canvas_;
    QPushButton *upload_button_;
};
#endif // MAINWINDOW_H
