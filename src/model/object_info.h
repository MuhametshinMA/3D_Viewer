#ifndef CPP4_3DVIEWER2_OBJECT_INFO_H
#define CPP4_3DVIEWER2_OBJECT_INFO_H

#include <regex>

namespace s21 {
class ObjectInfo {
 public:
  ObjectInfo() {}
  ~ObjectInfo() {}

  void SetPath(std::string path) {
    std::regex reg_free(R"([a-zA-Z_\-\d]+\.[o]+[b]+j)");
    std::string::const_iterator it_begin = path.begin();
    std::string::const_iterator it_end = path.end();
    std::smatch sm;
    std::regex_search(it_begin, it_end, sm, reg_free);
    path_ = sm[0];
  }

  void SetVertex(size_t vertex_count) { vertex_count_ = vertex_count; }
  void SetFacet(size_t facet_count) { facet_count_ = facet_count; }
  size_t GetVertexCount() const { return vertex_count_; }
  size_t GetFacetCount() const { return facet_count_; }
  std::string GetPath() const { return path_; }

 private:
  size_t vertex_count_;
  size_t facet_count_;
  std::string path_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_OBJECT_INFO_H
