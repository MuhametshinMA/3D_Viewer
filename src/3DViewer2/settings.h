#ifndef CPP4_3DVIEWER2_3DVIEWER2_SETTINGS_H
#define CPP4_3DVIEWER2_3DVIEWER2_SETTINGS_H

#include <QSettings>

#include "settings_type.h"

namespace s21 {

class ModelSettings : public QSettings {
 public:
  static ModelSettings& getInstance() {
    static ModelSettings instance;
    return instance;
  }

  void setPropertyValue(PropertyKey key, const QVariant& value) {
    auto it = setters.find(key);
    if (it != setters.end()) {
      it->second(value);
    }
  }

  QVariant getPropertyValue(PropertyKey key) {
    auto it = getters.find(key);
    if (it != getters.end()) {
      return it->second();
    }
    return QVariant();
  }

 private:
  ModelSettings() : QSettings() {}

  using SetterMap = std::map<PropertyKey, std::function<void(const QVariant&)>>;
  using GetterMap = std::map<PropertyKey, std::function<QVariant()>>;

  SetterMap setters = {
      {PropertyKey::kLineWidth,
       [&](const QVariant& value) { setValue("LineWidth", value.toFloat()); }},
      {PropertyKey::kLineType,
       [&](const QVariant& value) { setValue("LineType", value.toInt()); }},
      {PropertyKey::kLineColor,
       [&](const QVariant& value) {
         setValue("LineColor", value.value<QColor>());
       }},
      {PropertyKey::kVertexSize,
       [&](const QVariant& value) { setValue("VertexSize", value.toFloat()); }},
      {PropertyKey::kVertexType,
       [&](const QVariant& value) { setValue("VertexType", value.toInt()); }},
      {PropertyKey::kVertexColor,
       [&](const QVariant& value) {
         setValue("VertexColor", value.value<QColor>());
       }},
      {PropertyKey::kBackGroundColor,
       [&](const QVariant& value) {
         setValue("BackGroundColor", value.value<QColor>());
       }},
      {PropertyKey::kProection,
       [&](const QVariant& value) { setValue("kProection", value.toInt()); }}};

  GetterMap getters = {
      {PropertyKey::kLineWidth, [&]() { return value("LineWidth").toFloat(); }},
      {PropertyKey::kLineType, [&]() { return value("LineType").toInt(); }},
      {PropertyKey::kLineColor,
       [&]() { return value("LineColor").value<QColor>(); }},
      {PropertyKey::kVertexSize,
       [&]() { return value("VertexSize").toFloat(); }},
      {PropertyKey::kVertexType, [&]() { return value("VertexType").toInt(); }},
      {PropertyKey::kVertexColor,
       [&]() { return value("VertexColor").value<QColor>(); }},
      {PropertyKey::kBackGroundColor,
       [&]() { return value("BackGroundColor").value<QColor>(); }},
      {PropertyKey::kProection, [&]() { return value("kProection").toInt(); }}};
};

}  // namespace s21

#endif  // CPP4_3DVIEWER2_3DVIEWER2_SETTINGS_H
