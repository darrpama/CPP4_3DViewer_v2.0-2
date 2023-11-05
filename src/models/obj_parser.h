#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H

#include "object.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <QFile>
#include <QString>


namespace s21
{
class OBJParser {
 public:
  OBJParser(Object *obj) : object_(obj) {};
  void Parse();
  size_t CountVertices();
  void SetFilePath(const QString&);
  void SetObject(Object *);

 private:
  Object *object_;
  std::string file_path_;

  void TriangulateFaces();
  std::vector<Face> TriangulateFace(const Face& face);
  void printQVector(const QVector<GLfloat>&);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H
