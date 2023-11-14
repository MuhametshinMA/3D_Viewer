#ifndef AFFINE_TRANSFORMATION_H
#define AFFINE_TRANSFORMATION_H

#include <cmath>

#include "data_object.h"

namespace s21 {

class AffineReceiver;

class IAffineCommand {
 public:
  IAffineCommand(AffineReceiver &receiver) : receiver_(receiver){};
  virtual ~IAffineCommand() = default;
  virtual void execute(double a) = 0;
  virtual void undo(double a) = 0;

 protected:
  AffineReceiver &receiver_;
};

class AffineReceiver {
 public:
  AffineReceiver(std::vector<double> &vertexes) : vertexes_(vertexes){};
  ~AffineReceiver() = default;

  void MoveX(double x) {
    int index = 0;
    for (auto &value : vertexes_) {
      index++;
      if (index % 3 == 1) {
        value += x;
      }
    }
  };

  void MoveY(double y) {
    int index = 0;
    for (auto &value : vertexes_) {
      index++;
      if (index % 3 == 2) {
        value += y;
      }
    }
  };

  void MoveZ(double z) {
    int index = 0;
    for (auto &value : vertexes_) {
      index++;
      if (index % 3 == 0) {
        value += z;
      }
    }
  };

  void RotateX(double x) {
    x *= M_PI / 180;
    if (fabs(0. - x) > 1e-7) {
      for (auto i = vertexes_.begin(); i < vertexes_.end(); i += 3) {
        double y = i[1];
        double z = i[2];
        i[1] = y * cos(x) + z * sin(x);
        i[2] = -y * sin(x) + z * cos(x);
      }
    }
  };

  void RotateY(double y) {
    y *= M_PI / 180;
    if (fabs(0. - y) > 1e-7) {
      for (auto i = vertexes_.begin(); i < vertexes_.end(); i += 3) {
        double x = i[0];
        double z = i[2];
        i[0] = x * cos(y) + z * sin(y);
        i[2] = -x * sin(y) + z * cos(y);
      }
    }
  };

  void RotateZ(double z) {
    z *= M_PI / 180;
    if (fabs(0. - z) > 1e-7) {
      for (auto i = vertexes_.begin(); i < vertexes_.end(); i += 3) {
        double x = i[0];
        double y = i[1];
        i[0] = x * cos(z) + y * sin(z);
        i[1] = -x * sin(z) + y * cos(z);
      }
    }
  };

  void Scale(double s) {
    float skal_n = 1 + (s / 100);
    if (skal_n < 0.009) skal_n = 0.01;
    for (auto i = vertexes_.begin(); i < vertexes_.end(); i += 3) {
      i[0] = i[0] * skal_n;
      i[1] = i[1] * skal_n;
      i[2] = i[2] * skal_n;
    }
  };

 private:
  std::vector<double> &vertexes_;
};

class AffineCommandMoveX : public IAffineCommand {
 public:
  AffineCommandMoveX(AffineReceiver &receiver) : IAffineCommand(receiver){};
  ~AffineCommandMoveX() = default;
  void execute(double a) override { receiver_.MoveX(a); };
  void undo(double a) override { receiver_.MoveX(-a); };
};

class AffineCommandMoveY : public IAffineCommand {
 public:
  AffineCommandMoveY(AffineReceiver &receiver) : IAffineCommand(receiver){};
  ~AffineCommandMoveY() = default;
  void execute(double a) override { receiver_.MoveY(a); };
  void undo(double a) override { receiver_.MoveY(-a); };
};

class AffineCommandMoveZ : public IAffineCommand {
 public:
  AffineCommandMoveZ(AffineReceiver &receiver) : IAffineCommand(receiver){};
  ~AffineCommandMoveZ() = default;
  void execute(double a) override { receiver_.MoveZ(a); };
  void undo(double a) override { receiver_.MoveZ(-a); };
};

class AffineCommandRotateX : public IAffineCommand {
 public:
  AffineCommandRotateX(AffineReceiver &receiver) : IAffineCommand(receiver){};
  ~AffineCommandRotateX() = default;
  void execute(double a) override { receiver_.RotateX(a); };
  void undo(double a) override { receiver_.RotateX(-a); };
};

class AffineCommandRotateY : public IAffineCommand {
 public:
  AffineCommandRotateY(AffineReceiver &receiver) : IAffineCommand(receiver){};
  ~AffineCommandRotateY() = default;
  void execute(double a) override { receiver_.RotateY(a); };
  void undo(double a) override { receiver_.RotateY(-a); };
};

class AffineCommandRotateZ : public IAffineCommand {
 public:
  AffineCommandRotateZ(AffineReceiver &receiver) : IAffineCommand(receiver){};
  ~AffineCommandRotateZ() = default;
  void execute(double a) override { receiver_.RotateZ(a); };
  void undo(double a) override { receiver_.RotateZ(-a); };
};

class AffineCommandScale : public IAffineCommand {
 public:
  AffineCommandScale(AffineReceiver &receiver) : IAffineCommand(receiver){};
  ~AffineCommandScale() = default;
  void execute(double a) override { receiver_.Scale(a); };
  void undo(double a) override { receiver_.Scale(-a); };
};

}  // namespace s21

#endif  // AFFINE_TRANSFORMATION_H
