#ifndef CPP4_3DVIEWER2_3DVIEWER2_RECORD_H
#define CPP4_3DVIEWER2_3DVIEWER2_RECORD_H

#include <QFileDialog>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QTime>
#include <QTimer>

#include "qgifimage.h"

namespace s21 {

enum class TypeRecord { kBmp, kJpeg, kGif };

class Record : public QTimer {
  Q_OBJECT
 public:
  explicit Record(QObject* parent = nullptr);
  ~Record();

  void ChooseRecord(QOpenGLWidget* widget, TypeRecord key);

 private slots:
  void slotRecordGif(QOpenGLWidget*);

 private:
  QTime time_;
  QGifImage* gif_;

  QString GetPath();

  void RecordExtension(QOpenGLWidget* widget, std::string extension);

  void RecordGif(QOpenGLWidget* widget);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_3DVIEWER2_RECORD_H
