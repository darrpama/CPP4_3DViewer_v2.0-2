
#ifndef SCREENCASTTHREAD_H
#define SCREENCASTTHREAD_H

#include <QThread>
#include <QWidget>

class ScreencastThread : public QThread {
 public:
  explicit ScreencastThread(QWidget* widget);

 protected:
  void run() override;

 private:
  QWidget* widget_;
};

#endif // SCREENCASTTHREAD_H