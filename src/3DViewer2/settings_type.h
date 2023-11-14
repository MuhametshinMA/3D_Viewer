#ifndef CPP4_3DVIEWER2_3DVIEWER2_SETTINGS_TYPE_H
#define CPP4_3DVIEWER2_3DVIEWER2_SETTINGS_TYPE_H

#include <QColor>

namespace s21 {

enum class PropertyKey {
  kLineWidth,
  kLineType,
  kLineColor,
  kVertexSize,
  kVertexType,
  kVertexColor,
  kBackGroundColor,
  kProection
};

enum class TypeLine { kSolid, kDotted };
enum class TypeProjection { kParallel, kCenter };
enum class TypeVertexes { kAbsent, kRound, kSquare };

}  // namespace s21

#endif  // CPP4_3DVIEWER2_3DVIEWER2_SETTINGS_TYPE_H
