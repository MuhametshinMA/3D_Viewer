#include "model.h"

#include <fstream>

#include "exceptions.h"
#include "parser_factory.h"

namespace s21 {

void Model::LoadObjectFromFile(std::string path) {
  data_object_->ClearCurrentDataObject();
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("can't open file");
  }

  std::vector<std::unique_ptr<IParser>> parsers = CreateParsers();

  std::string line;
  while (std::getline(file, line)) {
    for (auto& parser : parsers) {
      parser->ParseLine(line);
    }
  }

  SendObjectInfo(path);

  file.close();
  data_object_->FindMinMaxValues();
  data_object_->UpdateDataObject();
}

void Model::AffineTransformation(TypeDataCommand command) {
  invoker_->Execute(command);
}

void Model::CancelTransformation() { invoker_->Undo(); }

void Model::ResetObject() {
  invoker_->ResetStack();
  data_object_->ResetDataObject();
}

void Model::SendObjectInfo(std::string path) {
  const std::variant<std::vector<double>, std::vector<unsigned int>>&
      vertex_data = data_object_->GetCurrentDataObject().data_object.at(
          TypeData::kVertexes);

  const std::variant<std::vector<double>, std::vector<unsigned int>>&
      facet_data = data_object_->GetCurrentDataObject().data_object.at(
          TypeData::kFacets);

  const std::vector<double>& vertexData =
      std::get<std::vector<double>>(vertex_data);

  const std::vector<unsigned int>& facetData =
      std::get<std::vector<unsigned int>>(facet_data);

  object_info_->SetVertex(vertexData.size());
  object_info_->SetFacet(facetData.size() / 2);
  object_info_->SetPath(path);
}

std::vector<std::unique_ptr<IParser>> Model::CreateParsers() {
  ParserFactory parserFactory;

  std::vector<std::unique_ptr<IParser>> parsers;
  for (auto& pair : data_object_->GetCurrentDataObject().data_object) {
    TypeData type = pair.first;
    std::variant<std::vector<double>, std::vector<unsigned int>>& data =
        pair.second;

    std::unique_ptr<IParser> parser = parserFactory.CreateParser(type, data);
    if (parser) {
      parsers.push_back(std::move(parser));
    } else {
      throw UnsupportedTypeException();
    }
  }
  return parsers;
}

ObjectInfo Model::GetObjectInfo() { return *object_info_; }

DataObject& Model::GetDataObject() { return *data_object_; }

const TypeDataObject& Model::GetSourceDataObject() const {
  return data_object_->GetSourceDataObject();
}

TypeDataObject& Model::GetCurrentDataObject() {
  return data_object_->GetCurrentDataObject();
}

}  // namespace s21
