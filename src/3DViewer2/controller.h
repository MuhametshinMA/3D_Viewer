#ifndef CPP4_3DVIEWER2_3DVIEWER2_CONTROLLER_H
#define CPP4_3DVIEWER2_3DVIEWER2_CONTROLLER_H

#include "model.h"
#include "record.h"
#include "settings.h"

namespace s21 {

class Controller {
 public:
  Controller(Model* model, ModelSettings& settings, Record* record)
      : model_(model), settings_(settings), record_(record){};
  ~Controller() { delete model_; }

  void OpenFile(std::string);
  void SendAffineCommand(TypeDataCommand);
  void SendCancelCommand();
  void SendReset();
  void SendObjectInfo(std::string);
  DataObject& GetDataObject();
  ObjectInfo GetObjectInfo();

  void SetPropertyValue(PropertyKey, const QVariant&);

  QVariant GetPropertyValue(PropertyKey);

  void ChooseRecord(QOpenGLWidget*, TypeRecord);

 private:
  Model* model_;
  ModelSettings& settings_;
  Record* record_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_3DVIEWER2_CONTROLLER_H
