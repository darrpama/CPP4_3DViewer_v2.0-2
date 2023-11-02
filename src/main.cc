#include "controllers/controller.h"
#include "models/model.h"
#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::Object object = s21::Object();
  s21::Transform transform = s21::Transform();
  s21::Model model = s21::Model(&object, &transform);
  s21::Controller& controller = s21::Controller::GetInstance();
  controller.SetModel(&model);
  MainWindow *window = new MainWindow();

  // window->setWindowTitle(QString("3DViewer 2.0"));
  window->show();

  return a.exec();
}
