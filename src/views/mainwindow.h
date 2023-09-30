#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H

#include "../controllers/controller.h"
#include "canvas.h"

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
  MainWindow(s21::Controller &controller, QWidget *parent = nullptr);
  ~MainWindow();
  void resizeEvent(QResizeEvent* event);

private slots:
  void on_uploadButton_clicked();

private:
  s21::Controller controller_;
  Ui::MainWindow *ui;
  Canvas *canvas_;
  QPushButton *upload_button_;
};
#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
