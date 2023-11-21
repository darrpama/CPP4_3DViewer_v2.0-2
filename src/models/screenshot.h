#include <QWidget>
namespace s21 {

class ScreenshotStrategy {
 public:
  virtual void Make(QWidget *widget) = 0;
};

class BmpScreenshotStrategy : public ScreenshotStrategy {
  void Make(QWidget *widget);
};

class JpgScreenshotStrategy : public ScreenshotStrategy {
  void Make(QWidget *widget);
};

class ScreenshotContext {
 private:
  ScreenshotStrategy* strategy_;

 public:
  ScreenshotContext() {}
  ScreenshotContext(ScreenshotStrategy* strategy) : strategy_(strategy) {}
  void SetStrategy(ScreenshotStrategy* strategy) {strategy_ = strategy;}
  void MakeScreenshot(QWidget *widget) {strategy_->Make(widget);}
};
  
}  // namespace s21
