#ifndef CPP4_3DVIEWER2_MODEL_I_MODEL_H
#define CPP4_3DVIEWER2_MODEL_I_MODEL_H

#include "type_command.h"

namespace s21 {
class IModel {
 public:
  virtual void LoadObjectFromFile(std::string) = 0;
  virtual void AffineTransformation(TypeDataCommand) = 0;
  virtual void CancelTransformation() = 0;
  virtual void ResetObject() = 0;
  virtual void SendObjectInfo(std::string) = 0;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_I_MODEL_H
