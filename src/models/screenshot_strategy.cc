#include "screenshot_strategy.h"

namespace s21 {
void BmpScreenshotStrategy::Make(QWidget *widget) {
  QPixmap pixmap = widget->grab();
  QString folderPath = QDir::currentPath() + "/saved";
  QDir folderDir(folderPath);
  if (!folderDir.exists()) {
    folderDir.mkpath(".");
  }

  QString imagePath = folderPath + "/widget_image.bmp";
  if (pixmap.save(imagePath)) {
    std::cout << "image saved!" << std::endl;
  } else {
    std::cout << "image not saved... there is an error!" << std::endl;
  }
}

void JpgScreenshotStrategy::Make(QWidget *widget) {
  QPixmap pixmap = widget->grab();
  QString folderPath = QDir::currentPath() + "/saved";
  QDir folderDir(folderPath);
  if (!folderDir.exists()) {
    folderDir.mkpath(".");
  }

  QString imagePath = folderPath + "/widget_image.jpg";
  if (pixmap.save(imagePath)) {
    std::cout << "image saved!" << std::endl;
  } else {
    std::cout << "image not saved... there is an error!" << std::endl;
  }
}

}  // namespace s21
