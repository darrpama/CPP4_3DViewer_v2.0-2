#include "controllers/controller.h"
#include "models/model.h"
#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QVector<GLfloat> vertices_array;
  QVector<GLuint> faces_array;
  QVector<s21::Face> raw_faces_array_;
  QVector<GLuint> face_buffer;
  QVector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer, &triangle_buffer, &raw_faces_array_);
  s21::Settings settings = s21::Settings();
  settings.LoadSettings();

  s21::Transform transform = s21::Transform(&settings);
  s21::OBJParser parser = s21::OBJParser(&object);
  s21::Renderer renderer = s21::Renderer(&object, &transform, &settings);

  s21::Model model = s21::Model(&object, &parser, &transform, &renderer, &settings);
  
  s21::Controller& controller = s21::Controller::GetInstance();
  controller.SetModel(&model);
  
  MainWindow *window = new MainWindow();

  // window->setWindowTitle(QString("3DViewer 2.0"));
  window->show();


  return a.exec();
}
