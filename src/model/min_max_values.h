#ifndef CPP4_3DVIEWER2_MODEL_MIN_MAX_VALUES_H
#define CPP4_3DVIEWER2_MODEL_MIN_MAX_VALUES_H

namespace s21 {

class MinMaxValues {
 public:
  MinMaxValues() : x_min(0), x_max(0), y_min(0), y_max(0), z_min(0), z_max(0){};
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_MIN_MAX_VALUES_H
