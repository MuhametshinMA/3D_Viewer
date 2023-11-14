#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <any>
#include <typeindex>

#include "model_renderer.h"

// QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
// QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr, Controller* controller = nullptr);
  ~MainWindow();

 private slots:
  void handleOpenFileButtonClick();
  void handleAffinCommand(TypeCommand key, double value);
  void handleCancel();
  void handleReset();
  void handleChangeProperties(PropertyKey key, std::any value);
  void handleChooseRecord(TypeRecord key);

 private:
  Ui::MainWindow* ui;
  Controller* controller_;
  ModelRenderer* widget_;
  std::map<std::type_index,
           std::function<void(const std::any&, PropertyKey, MainWindow*)>>
      handlers_ = {
          {typeid(int),
           [](const std::any& value, PropertyKey key, MainWindow* self) {
             int intValue = std::any_cast<int>(value);
             self->controller_->SetPropertyValue(key, intValue);
           }},
          {typeid(float),
           [](const std::any& value, PropertyKey key, MainWindow* self) {
             float floatValue = std::any_cast<float>(value);
             self->controller_->SetPropertyValue(key, floatValue);
           }},
          {typeid(QColor),
           [](const std::any& value, PropertyKey key, MainWindow* self) {
             QColor colorValue = std::any_cast<QColor>(value);
             self->controller_->SetPropertyValue(key, colorValue);
           }}};
};
}  // namespace s21

#endif  // MAINWINDOW_H
