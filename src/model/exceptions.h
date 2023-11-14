#ifndef CPP4_3DVIEWER2_3DVIEWER2_EXCEPTIONS_H
#define CPP4_3DVIEWER2_3DVIEWER2_EXCEPTIONS_H

namespace s21 {

class UnsupportedTypeException : public std::exception {
 public:
  const char* what() const noexcept override {
    return "Unsupported type encountered";
  }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER2_3DVIEWER2_EXCEPTIONS_H
