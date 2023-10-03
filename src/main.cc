#include "controllers/controller.h"
#include "models/model.h"
#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model = s21::Model();
  s21::Controller controller = s21::Controller(model);
  MainWindow *window = new MainWindow(controller);

  window->setWindowTitle(QString("3DViewer 2.0"));
  window->show();

  return a.exec();
}
