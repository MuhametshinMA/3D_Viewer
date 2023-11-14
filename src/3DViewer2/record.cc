#include "record.h"

namespace s21 {

Record::Record(QObject* parent) : QTimer(parent) { gif_ = new QGifImage(); }
Record::~Record() { delete gif_; }

void Record::ChooseRecord(QOpenGLWidget* widget, TypeRecord key) {
  switch (key) {
    case TypeRecord::kBmp:
      RecordExtension(widget, ".bmp");
      break;
    case TypeRecord::kJpeg:
      RecordExtension(widget, ".jpeg");
      break;
    case TypeRecord::kGif:
      RecordGif(widget);
      break;
    default:
      break;
  }
}

QString Record::GetPath() {
  return QFileDialog::getExistingDirectory(
      nullptr, QFileDialog::tr("Select Directory"), QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}

void Record::RecordExtension(QOpenGLWidget* widget, std::string extension) {
  widget->grab().save(GetPath() + "/" + QDate::currentDate().toString() + " " +
                      QTime::currentTime().toString() +
                      QString::fromStdString(extension));
}

void Record::slotRecordGif(QOpenGLWidget* widget) {
  QTime end = QTime::currentTime();
  gif_->addFrame(widget->grabFramebuffer(), 100);
  if (time_.secsTo(end) > 5) {
    stop();
    auto file_name = QFileDialog::getSaveFileName(nullptr, ("Save As..."), ".",
                                                  ("Images (*.gif)"));
    gif_->save(file_name);
  }
}

void Record::RecordGif(QOpenGLWidget* widget) {
  if (!isActive()) {
    time_ = QTime::currentTime();
    connect(this, &QTimer::timeout, this,
            [this, widget]() { slotRecordGif(widget); });
    start(100);
  } else {
    stop();
  }
}

}  // namespace s21
