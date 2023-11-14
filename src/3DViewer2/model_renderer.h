#ifndef CPP4_3DVIEWER2_3DVIEWER2_MODELRENGERER_H
#define CPP4_3DVIEWER2_3DVIEWER2_MODELRENGERER_H

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
//#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
//#include <GL/glut.h>
#endif

#include <QColor>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>

#include "controller.h"

namespace s21 {

class ModelRenderer : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  ModelRenderer();
  ModelRenderer(QWidget* parent, Controller& controller)
      : QOpenGLWidget(parent), controller_(controller) {}

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void CoordinateAxis();

  QColor colorVert, colorFons, colorRibs;
  void mousePressEvent(QMouseEvent* mo) override;
  void mouseMoveEvent(QMouseEvent* mo) override;
  void wheelEvent(QWheelEvent* event) override;

 private:
  float xRot, yRot, zRot = 1;
  qreal aspectRatio;
  QPoint mPos;
  Controller& controller_;
  std::map<TypeVertexes, std::function<void()>> vertex_mode_ = {
      {TypeVertexes::kAbsent, []() {}},
      {TypeVertexes::kRound,
       [&]() {
         glEnable(GL_POINT_SMOOTH);
         const auto& dataObject =
             controller_.GetDataObject().GetCurrentDataObject().data_object;
         const std::variant<std::vector<double>, std::vector<unsigned int>>&
             data = dataObject.at(TypeData::kVertexes);

         if (std::holds_alternative<std::vector<double>>(data)) {
           const std::vector<double>& vertexData =
               std::get<std::vector<double>>(data);
           GLsizei numVertices = static_cast<GLsizei>(vertexData.size() / 3);
           glDrawArrays(GL_POINTS, 0, numVertices);
         }
       }},
      {TypeVertexes::kSquare, [&]() {
         glDisable(GL_POINT_SMOOTH);

         const auto& dataObject =
             controller_.GetDataObject().GetCurrentDataObject().data_object;
         const std::variant<std::vector<double>, std::vector<unsigned int>>&
             data = dataObject.at(TypeData::kVertexes);

         if (std::holds_alternative<std::vector<double>>(data)) {
           const std::vector<double>& vertexData =
               std::get<std::vector<double>>(data);
           GLsizei numVertices = static_cast<GLsizei>(vertexData.size() / 3);
           glDrawArrays(GL_POINTS, 0, numVertices);
         }
       }}};

  std::map<TypeLine, std::function<void()>> line_mode_ = {
      {TypeLine::kDotted, [&]() { glDisable(GL_LINE_STIPPLE); }},
      {TypeLine::kSolid, [&]() {
         glEnable(GL_LINE_STIPPLE);
         glLineStipple(10, 0x3333);
       }}};

  std::map<TypeProjection, std::function<void()>> projection_mode_ = {
      {TypeProjection::kParallel,
       [&]() {
         double max;
         max = std::abs(controller_.GetDataObject().GetMinMaxValues().x_max);
         if (max <
             std::abs(controller_.GetDataObject().GetMinMaxValues().y_max))
           max = std::abs(controller_.GetDataObject().GetMinMaxValues().y_max);
         if (max <
             std::abs(controller_.GetDataObject().GetMinMaxValues().z_max))
           max = std::abs(controller_.GetDataObject().GetMinMaxValues().z_max);
         glOrtho(-aspectRatio, aspectRatio, -1.0, 1.0, -4000, 4000.0);
         glScaled(1 / max, 1 / max, 1 / max);
       }},
      {TypeProjection::kCenter, [&]() {
         glFrustum(-aspectRatio, aspectRatio, -1.0, 1.0, 1.5 / zRot, 4000.0);
         double temp =
             ceil(controller_.GetDataObject().GetMinMaxValues().x_max +
                  controller_.GetDataObject().GetMinMaxValues().y_max +
                  controller_.GetDataObject().GetMinMaxValues().z_max) /
             3 * 2.5;
         glTranslatef(0, 0, -temp);
       }}};
};
}  // namespace s21

#endif  // CPP4_3DVIEWER2_3DVIEWER2_MODELRENGERER_H
