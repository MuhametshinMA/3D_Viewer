#ifndef CPP4_3DVIEWER2_MODEL_DATA_OBJECT_H
#define CPP4_3DVIEWER2_MODEL_DATA_OBJECT_H

#include <variant>

#include "min_max_values.h"
#include "type_data_object.h"

namespace s21 {

class DataObject {
 public:
  DataObject(){};
  ~DataObject(){};

  const TypeDataObject &GetSourceDataObject() const {
    return source_data_object_;
  }

  TypeDataObject &GetCurrentDataObject() { return current_data_object_; }

  void ResetDataObject() { current_data_object_ = source_data_object_; }

  void UpdateDataObject() { source_data_object_ = current_data_object_; }

  void ClearCurrentDataObject() {
    for (auto &pair : current_data_object_.data_object) {
      std::visit([](auto &&vec) { vec.clear(); }, pair.second);
    }
  }

  MinMaxValues GetMinMaxValues();
  void FindMinMaxValues();

 private:
  TypeDataObject source_data_object_;
  TypeDataObject current_data_object_;
  MinMaxValues min_max_values_;
};

inline MinMaxValues DataObject::GetMinMaxValues() { return min_max_values_; }

inline void DataObject::FindMinMaxValues() {
  std::vector<double> data_object = std::get<std::vector<double>>(
      current_data_object_.data_object.at(s21::TypeData::kVertexes));
  min_max_values_.x_min = min_max_values_.x_max = min_max_values_.y_min =
      min_max_values_.y_max = min_max_values_.z_min = min_max_values_.z_max = 0;
  int index = 1;
  for (auto value : data_object) {
    if (index % 3 == 1) {
      if (value < min_max_values_.x_min) {
        min_max_values_.x_min = value;
      }
      if (value > min_max_values_.x_max) {
        min_max_values_.x_max = value;
      }
    }

    if (index % 3 == 2) {
      if (value < min_max_values_.y_min) {
        min_max_values_.y_min = value;
      }
      if (value > min_max_values_.y_max) {
        min_max_values_.y_max = value;
      }
    }

    if (index % 3 == 0) {
      if (value < min_max_values_.z_min) {
        min_max_values_.z_min = value;
      }
      if (value > min_max_values_.z_max) {
        min_max_values_.z_max = value;
      }
    }
    index++;
  }
}
}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_DATA_OBJECT_H
