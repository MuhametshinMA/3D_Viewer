#ifndef CPP4_3DVIEWER2_MODEL_PARSER_FACTORY_H
#define CPP4_3DVIEWER2_MODEL_PARSER_FACTORY_H

#include <memory>

#include "parser.h"

namespace s21 {
class IParserFactory {
 public:
  virtual std::unique_ptr<IParser> CreateParser(
      TypeData,
      std::variant<std::vector<double>, std::vector<unsigned int>>&) = 0;
  virtual ~IParserFactory() {}
};

class ParserFactory : public IParserFactory {
 public:
  std::unique_ptr<IParser> CreateParser(
      TypeData type,
      std::variant<std::vector<double>, std::vector<unsigned int>>& data_object)
      override {
    switch (type) {
      case TypeData::kVertexes: {
        auto& vertexData = std::get<std::vector<double>>(data_object);
        return std::make_unique<VertexesParser>(vertexData);
      }

      case TypeData::kFacets: {
        auto& facetData = std::get<std::vector<unsigned int>>(data_object);
        return std::make_unique<FacetsParser>(facetData);
      }

      default:
        throw std::runtime_error("unknown type");
    }
  }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_PARSER_FACTORY_H
