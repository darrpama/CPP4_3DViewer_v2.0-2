#include "controllers/controller.h"
#include "models/model.h"
#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QVector<GLfloat> vertices_array;
  vertices_array.reserve(3000000);

  QVector<GLuint> faces_array;
  faces_array.reserve(5000000);

  QVector<GLuint> face_buffer;
  face_buffer.reserve(12);

  QVector<GLuint> triangle_buffer;
  triangle_buffer.reserve(12);

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer, &triangle_buffer);
  s21::Transform transform = s21::Transform();
  s21::OBJParser parser = s21::OBJParser(&object);
  s21::Renderer renderer = s21::Renderer(&object, &transform);

  s21::Model model = s21::Model(&object, &parser, &transform, &renderer);
  
  s21::Controller& controller = s21::Controller::GetInstance();
  controller.SetModel(&model);
  MainWindow *window = new MainWindow();

  // window->setWindowTitle(QString("3DViewer 2.0"));
  window->show();

  return a.exec();
}
