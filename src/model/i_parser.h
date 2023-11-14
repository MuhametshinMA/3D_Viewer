#ifndef CPP4_3DVIEWER2_MODEL_I_PARSER_H
#define CPP4_3DVIEWER2_MODEL_I_PARSER_H

#include "data_object.h"

namespace s21 {

class IParser {
 public:
  IParser() {}
  virtual void ParseLine(std::string line) = 0;

  virtual ~IParser() {}
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_MODEL_I_PARSER_H
