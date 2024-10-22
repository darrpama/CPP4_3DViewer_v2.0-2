#include "controllers/controller_singleton.h"
#include "models/model_facade.h"
#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  std::vector<GLfloat> vertices_array;
  std::vector<GLuint> faces_array;
  std::vector<s21::Face> raw_faces_array_;
  std::vector<GLuint> face_buffer;
  std::vector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer, &triangle_buffer, &raw_faces_array_);
  s21::Settings settings = s21::Settings();
  settings.LoadSettings();

  s21::Transform transform = s21::Transform(&settings);
  s21::OBJParser parser = s21::OBJParser(&object);
  s21::Renderer renderer = s21::Renderer(&object, &transform, &settings);

  s21::ModelFacade model = s21::ModelFacade(&object, &parser, &transform, &renderer, &settings);
  
  s21::ControllerSingleton& controller = s21::ControllerSingleton::GetInstance();
  controller.SetModel(&model);
  
  MainWindow *window = new MainWindow();

  window->setWindowTitle(QString("3DViewer 2.0"));
  window->show();


  return a.exec();
}
