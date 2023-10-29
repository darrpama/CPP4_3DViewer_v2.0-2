#include "screencastthread.h"
#include "mainwindow.h"

ScreencastThread::ScreencastThread(QWidget* widget) : widget_(widget) {}

void ScreencastThread::run() {
  MainWindow::MakeScreencast(widget_);
}