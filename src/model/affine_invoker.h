#ifndef CPP4_3DVIEWER2_MODEL_AFFINE_INVOKER_H
#define CPP4_3DVIEWER2_MODEL_AFFINE_INVOKER_H

#include <map>
#include <memory>
#include <stack>

#include "affine_command.h"
#include "type_command.h"

namespace s21 {

class AffineInvoker {
 public:
  AffineInvoker(std::vector<double> &vertexes) : receiver_(vertexes) {
    data_command_[TypeCommand::kMoveX] =
        std::make_unique<AffineCommandMoveX>(receiver_);
    data_command_[TypeCommand::kMoveY] =
        std::make_unique<AffineCommandMoveY>(receiver_);
    data_command_[TypeCommand::kMoveZ] =
        std::make_unique<AffineCommandMoveZ>(receiver_);
    data_command_[TypeCommand::kRotateX] =
        std::make_unique<AffineCommandRotateX>(receiver_);
    data_command_[TypeCommand::kRotateY] =
        std::make_unique<AffineCommandRotateY>(receiver_);
    data_command_[TypeCommand::kRotateZ] =
        std::make_unique<AffineCommandRotateZ>(receiver_);
    data_command_[TypeCommand::kScale] =
        std::make_unique<AffineCommandScale>(receiver_);
  };

  ~AffineInvoker() = default;

  void Execute(TypeDataCommand command) {
    data_command_[command.type]->execute(command.value);
    command_stack_.push(command);
  }
  void Undo() {
    if (!command_stack_.empty()) {
      TypeDataCommand command = command_stack_.top();
      data_command_[command.type]->undo(command.value);
      command_stack_.pop();
    }
  }
  void ResetStack() {
    while (!command_stack_.empty()) command_stack_.pop();
  }

 private:
  AffineReceiver receiver_;
  std::map<TypeCommand, std::unique_ptr<IAffineCommand>> data_command_;
  std::stack<TypeDataCommand> command_stack_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_AFFINE_INVOKER_H
