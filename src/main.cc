#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow *window = new MainWindow();
  window->setWindowTitle(QString("3DViewer 2.0"));
  window->show();

  return a.exec();
}
