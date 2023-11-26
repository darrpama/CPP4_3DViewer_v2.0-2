#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODELS_SCREENSHOT_STRATEGY_H
#define CPP4_3DVIEWER_V2_0_1_SRC_MODELS_SCREENSHOT_STRATEGY_H

#include <QDir>
#include <QPixmap>
#include <QWidget>
#include <iostream>

namespace s21 {

class ScreenshotStrategy {
 public:
  virtual void Make(QWidget *widget) = 0;
};

class BmpScreenshotStrategy : public ScreenshotStrategy {
  void Make(QWidget *widget) override;
};

class JpgScreenshotStrategy : public ScreenshotStrategy {
  void Make(QWidget *widget) override;
};

class ScreenshotContext {
 private:
  ScreenshotStrategy *strategy_;

 public:
  ScreenshotContext() {}
  explicit ScreenshotContext(ScreenshotStrategy *strategy)
      : strategy_(strategy) {}
  void SetStrategy(ScreenshotStrategy *strategy) { strategy_ = strategy; }
  void MakeScreenshot(QWidget *widget) { strategy_->Make(widget); }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_SCREENSHOT_STRATEGY_H
