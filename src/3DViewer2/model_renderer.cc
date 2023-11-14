#include "model_renderer.h"

#include <cmath>

#include "type_data_object.h"

namespace s21 {

void ModelRenderer::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_LIGHT0);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

void ModelRenderer::paintGL() {
  QColor back_ground_color =
      controller_.GetPropertyValue(s21::PropertyKey::kBackGroundColor)
          .value<QColor>();
  glClearColor(back_ground_color.redF(), back_ground_color.greenF(),
               back_ground_color.blueF(), back_ground_color.alphaF());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  projection_mode_[static_cast<TypeProjection>(
      controller_.GetPropertyValue(PropertyKey::kProection).toInt())]();

  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  glMatrixMode(GL_MODELVIEW);

  glEnableClientState(GL_VERTEX_ARRAY);

  // begin: draw vertexes
  const auto& vertex_data_object =
      controller_.GetDataObject().GetCurrentDataObject().data_object;

  const std::variant<std::vector<double>, std::vector<unsigned int>>&
      vertex_data = vertex_data_object.at(TypeData::kVertexes);

  if (std::holds_alternative<std::vector<double>>(vertex_data)) {
    const std::vector<double>& vertexData =
        std::get<std::vector<double>>(vertex_data);
    glVertexPointer(3, GL_DOUBLE, 0, vertexData.data());
  }

  glPointSize(controller_.GetPropertyValue(PropertyKey::kVertexSize).toFloat());

  QColor vertex_color =
      controller_.GetPropertyValue(PropertyKey::kVertexColor).value<QColor>();

  glColor3d(vertex_color.redF(), vertex_color.greenF(), vertex_color.blueF());

  vertex_mode_[static_cast<TypeVertexes>(
      controller_.GetPropertyValue(PropertyKey::kVertexType).toInt())]();
  // end: draw vertexes

  // begin: draw line
  glLineWidth(controller_.GetPropertyValue(PropertyKey::kLineWidth).toFloat());

  const auto& facet_data_object =
      controller_.GetDataObject().GetCurrentDataObject().data_object;

  const std::variant<std::vector<double>, std::vector<unsigned int>>&
      facet_data = facet_data_object.at(TypeData::kFacets);

  line_mode_[static_cast<TypeLine>(
      controller_.GetPropertyValue(PropertyKey::kLineType).toInt())]();

  QColor line_color =
      controller_.GetPropertyValue(PropertyKey::kLineColor).value<QColor>();
  glColor3d(line_color.redF(), line_color.greenF(), line_color.blueF());

  if (std::holds_alternative<std::vector<unsigned int>>(facet_data)) {
    const std::vector<unsigned int>& facetData =
        std::get<std::vector<unsigned int>>(facet_data);

    glDrawElements(GL_LINES, facetData.size(), GL_UNSIGNED_INT,
                   facetData.data());
  }
  // end: draw line

  glDisableClientState(GL_VERTEX_ARRAY);
  CoordinateAxis();
}

void ModelRenderer::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  glLoadIdentity();
  aspectRatio = qreal(width) / qreal(height);
}

void ModelRenderer::CoordinateAxis() {
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(20, 0x3333);
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glColor3f(0.2, 0.8, 0.8);
  glVertex3f(0.0f, -10000.0f, 0.0f);
  glVertex3f(0.0f, 10000.0f, 0.0f);

  glColor3f(0.2, 0.8, 0.8);
  glVertex3f(0.0f, 0.0f, -10000.0f);
  glVertex3f(0.0f, 0.0f, 10000.0f);

  glColor3f(0.2, 0.8, 0.8);
  glVertex3f(-10000.0f, 0.0f, 0.0f);
  glVertex3f(10000.0f, 0.0f, .0f);
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

void ModelRenderer::mousePressEvent(QMouseEvent* mo) {
  mPos = mo->pos();
  update();
}

void ModelRenderer::mouseMoveEvent(QMouseEvent* mo) {
  xRot = 0.5 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 0.5 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void ModelRenderer::wheelEvent(QWheelEvent* event) {
  QPoint delta = event->angleDelta();
  int degrees = delta.y();
  int steps = degrees / 15;
  double scaleFactor = 1.0;  // How fast we zoom
  const qreal minFactor = 0.5;
  const qreal maxFactor = 10.0;
  if (steps > 0)
    zRot = (zRot >= maxFactor) ? zRot : (zRot + scaleFactor);
  else
    zRot = (zRot <= minFactor) ? minFactor : (zRot - scaleFactor);
  update();
}

}  // namespace s21
