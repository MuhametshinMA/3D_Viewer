#ifndef CPP4_3DVIEWER2_MODEL_PARSER_H
#define CPP4_3DVIEWER2_MODEL_PARSER_H

#include <regex>
#include <sstream>

#include "i_parser.h"

namespace s21 {

class VertexesParser : public IParser {
 public:
  VertexesParser(std::vector<double> &data_object)
      : data_object_(data_object) {}
  void ParseLine(std::string line) override {
    if (line.substr(0, 2) == "v ") {
      std::istringstream iss(line);

      std::string v;
      double x, y, z;

      if (iss >> v >> x >> y >> z) {
        data_object_.push_back(x);
        data_object_.push_back(y);
        data_object_.push_back(z);
      }
    }
  };

 private:
  std::vector<double> &data_object_;
};

class FacetsParser : public IParser {
 public:
  FacetsParser(std::vector<unsigned int> &data_object)
      : data_object_(data_object) {}
  void ParseLine(std::string line) override {
    std::regex pattern(R"( \d+\/)");
    std::string::const_iterator it = line.begin();
    std::string::const_iterator end = line.end();
    std::smatch match;

    if (line.substr(0, 2) == "f ") {
      std::vector<double> temp_facets;
      while (std::regex_search(it, end, match, pattern)) {
        temp_facets.push_back(std::stod(match[0].str().c_str()) - 1);
        it = match.suffix().first;
      }

      ConnectFacetsByLine(temp_facets);
    }
  };

 private:
  std::vector<unsigned int> &data_object_;

  void ConnectFacetsByLine(std::vector<double> &temp_facets) {
    if (temp_facets.size() > 2) {
      data_object_.push_back(temp_facets.front());
      for (auto it = ++temp_facets.begin(); it != temp_facets.end(); it++) {
        data_object_.push_back(*it);
        data_object_.push_back(*it);
      }
      data_object_.push_back(temp_facets.front());
    } else {
      for (auto i : temp_facets) {
        data_object_.push_back(i);
      }
    }
  }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_PARSER_H
