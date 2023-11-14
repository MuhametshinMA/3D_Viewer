#ifndef CPP4_3DVIEWER2_MODEL_TYPE_COMMAND_H
#define CPP4_3DVIEWER2_MODEL_TYPE_COMMAND_H

namespace s21 {

enum TypeCommand {
  kMoveX,
  kMoveY,
  kMoveZ,
  kRotateX,
  kRotateY,
  kRotateZ,
  kScale,
  kCancel,
  kReset
};

struct TypeDataCommand {
  TypeCommand type;
  double value;
  TypeDataCommand(TypeCommand type, double value) : type(type), value(value){};
  ~TypeDataCommand() = default;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_TYPE_COMMAND_H
