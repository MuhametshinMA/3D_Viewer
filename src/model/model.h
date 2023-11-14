#ifndef CPP4_3DVIEWER2_MODEL_MODEL_H
#define CPP4_3DVIEWER2_MODEL_MODEL_H

#include "affine_invoker.h"
#include "i_model.h"
#include "object_info.h"
#include "parser.h"

namespace s21 {

class Model : public IModel {
 public:
  Model() {
    data_object_ = new DataObject;
    object_info_ = new ObjectInfo;
    invoker_ = new AffineInvoker(std::get<std::vector<double>>(
        data_object_->GetCurrentDataObject().data_object.at(
            TypeData::kVertexes)));
  }

  ~Model() {
    delete data_object_;
    delete object_info_;
    delete invoker_;
  }

  void LoadObjectFromFile(std::string) override;

  void AffineTransformation(TypeDataCommand) override;

  void CancelTransformation() override;

  void ResetObject() override;

  void SendObjectInfo(std::string path) override;

  ObjectInfo GetObjectInfo();

  DataObject &GetDataObject();
  const TypeDataObject &GetSourceDataObject() const;
  TypeDataObject &GetCurrentDataObject();

 private:
  //  private methods
  std::vector<std::unique_ptr<IParser>> CreateParsers();

  //  private fields
  DataObject *data_object_;
  AffineInvoker *invoker_;
  ObjectInfo *object_info_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_MODEL_H
