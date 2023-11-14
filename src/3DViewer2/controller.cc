#include "controller.h"

#include <QDebug>

namespace s21 {

void Controller::OpenFile(std::string path) {
  try {
    model_->LoadObjectFromFile(path);

  } catch (const std::exception &e) {
    qDebug() << e.what();
  }
}

void Controller::SendAffineCommand(TypeDataCommand command) {
  model_->AffineTransformation(command);
}

void Controller::SendCancelCommand() { model_->CancelTransformation(); }

void Controller::SendReset() { model_->ResetObject(); }

void Controller::SendObjectInfo(std::string path) {
  model_->SendObjectInfo(path);
}

DataObject &Controller::GetDataObject() { return model_->GetDataObject(); }

ObjectInfo Controller::GetObjectInfo() { return model_->GetObjectInfo(); }

void Controller::SetPropertyValue(PropertyKey key, const QVariant &value) {
  settings_.setPropertyValue(key, value);
}

QVariant Controller::GetPropertyValue(PropertyKey key) {
  return settings_.getPropertyValue(key);
}

void Controller::ChooseRecord(QOpenGLWidget *widget, TypeRecord key) {
  record_->ChooseRecord(widget, key);
}

}  // namespace s21
