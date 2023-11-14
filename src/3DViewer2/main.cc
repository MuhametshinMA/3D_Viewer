#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model *model = new s21::Model;
  s21::ModelSettings &settings = s21::ModelSettings::getInstance();
  s21::Record *record = new s21::Record;
  s21::Controller controller(model, settings, record);
  s21::MainWindow w(nullptr, &controller);
  w.show();
  return a.exec();
}
