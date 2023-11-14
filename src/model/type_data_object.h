#ifndef CPP4_3DVIEWER2_MODEL_TYPE_DATA_OBJECT_H
#define CPP4_3DVIEWER2_MODEL_TYPE_DATA_OBJECT_H

#include <map>
#include <variant>
#include <vector>

namespace s21 {

enum class TypeData { kVertexes, kFacets };

class TypeDataObject {
 public:
  TypeDataObject() {}
  ~TypeDataObject() {}
  TypeDataObject(const TypeDataObject& other) {
    data_object = other.data_object;
  }
  void operator=(const TypeDataObject& other) {
    auto it_2 = other.data_object.begin();
    for (auto it = data_object.begin(); it != data_object.end(); ++it) {
      it->second = it_2->second;
      it_2++;
    }
  }

  using variant_vector =
      std::variant<std::vector<double>, std::vector<unsigned int>>;
  using type_data_object = std::map<TypeData, variant_vector>;

  variant_vector& operator[](TypeData type) { return data_object[type]; }

  type_data_object data_object = {
      {TypeData::kVertexes, std::vector<double>()},
      {TypeData::kFacets, std::vector<unsigned int>()}};
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_TYPE_DATA_OBJECT_H