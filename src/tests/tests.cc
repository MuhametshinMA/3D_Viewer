#include <gtest/gtest.h>

#include "model.h"

TEST(OpenFile, open_file) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kVertexes);
  auto vetr = std::get<std::vector<double>>(vertex);

  std::vector<double> ori({1, -1, -1, 1,  -1, 1,  -1,        -1,
                           1, -1, -1, -1, 1,  1,  -0.999999, 0.999999,
                           1, 1,  -1, 1,  1,  -1, 1,         -1});
  auto it = ori.begin();
  for (auto i : vetr) {
    double eps = 1e-6;
    EXPECT_NEAR(*it, i, eps);
    ++it;
  }
}

TEST(OpenFile, open_file1) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kFacets);
  auto vetr = std::get<std::vector<unsigned int>>(vertex);

  std::vector<unsigned int> ori(
      {1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
       2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
       0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4,
       0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 3, 3, 1, 3, 2, 2, 7, 7, 3, 4, 0});
  auto it = ori.begin();
  for (auto i : vetr) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(Aphine, aphine_rotate_x) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kVertexes);
  auto vetr = std::get<std::vector<double>>(vertex);

  model->AffineTransformation(
      s21::TypeDataCommand(s21::TypeCommand::kRotateX, 0.33));

  auto vertex_changed =
      model->GetDataObject().GetCurrentDataObject().data_object.at(
          s21::TypeData::kVertexes);
  auto vetr_changed = std::get<std::vector<double>>(vertex_changed);

  std::vector<double> ori({1,        -1.00574,  -0.994224, 1,        -0.994224,
                           1.00574,  -1,        -0.994224, 1.00574,  -1,
                           -1.00574, -0.994224, 1,         0.994224, -1.00574,
                           0.999999, 1.00574,   0.994225,  -1,       1.00574,
                           0.994224, -1,        0.994224,  -1.00574});
  auto it_ch = vetr_changed.begin();
  double eps = 1e-5;
  for (auto i : ori) {
    EXPECT_NEAR(*it_ch, i, eps);
    ++it_ch;
  }
}

TEST(Aphine, aphine_rotate_y) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kVertexes);
  auto vetr = std::get<std::vector<double>>(vertex);

  model->AffineTransformation(
      s21::TypeDataCommand(s21::TypeCommand::kRotateY, 0.33));

  auto vertex_changed =
      model->GetDataObject().GetCurrentDataObject().data_object.at(
          s21::TypeData::kVertexes);
  auto vetr_changed = std::get<std::vector<double>>(vertex_changed);

  std::vector<double> ori({0.994224,  -1, -1.00574, 1.00574,  -1, 0.994224,
                           -0.994224, -1, 1.00574,  -1.00574, -1, -0.994224,
                           0.994224,  1,  -1.00574, 1.00574,  1,  0.994225,
                           -0.994224, 1,  1.00574,  -1.00574, 1,  -0.994224});
  // auto it = ori.begin();
  auto it_ch = vetr_changed.begin();
  double eps = 1e-5;
  for (auto i : ori) {
    EXPECT_NEAR(*it_ch, i, eps);
    ++it_ch;
  }
}

TEST(Aphine, aphine_rotate_z) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kVertexes);
  auto vetr = std::get<std::vector<double>>(vertex);

  model->AffineTransformation(
      s21::TypeDataCommand(s21::TypeCommand::kRotateZ, 0.33));

  auto vertex_changed =
      model->GetDataObject().GetCurrentDataObject().data_object.at(
          s21::TypeData::kVertexes);
  auto vetr_changed = std::get<std::vector<double>>(vertex_changed);

  std::vector<double> ori(
      {0.994224,  -1.00574,  -1,        0.994224,  -1.00574,  1,
       -1.00574,  -0.994224, 1,         -1.00574,  -0.994224, -1,
       1.00574,   0.994224,  -0.999999, 1.00574,   0.994224,  1,
       -0.994224, 1.00574,   1,         -0.994224, 1.00574,   -1});
  auto it_ch = vetr_changed.begin();
  double eps = 1e-5;
  for (auto i : ori) {
    EXPECT_NEAR(*it_ch, i, eps);
    ++it_ch;
  }
}

TEST(Aphine, aphine_move_x) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kVertexes);
  auto vetr = std::get<std::vector<double>>(vertex);

  model->AffineTransformation(
      s21::TypeDataCommand(s21::TypeCommand::kMoveX, 0.33));

  auto vertex_changed =
      model->GetDataObject().GetCurrentDataObject().data_object.at(
          s21::TypeData::kVertexes);
  auto vetr_changed = std::get<std::vector<double>>(vertex_changed);

  std::vector<double> ori({1.33,  -1, -1, 1.33,  -1, 1,         -0.67, -1, 1,
                           -0.67, -1, -1, 1.33,  1,  -0.999999, 1.33,  1,  1,
                           -0.67, 1,  1,  -0.67, 1,  -1});
  auto it_ch = vetr_changed.begin();
  double eps = 1e-5;
  for (auto i : ori) {
    EXPECT_NEAR(*it_ch, i, eps);
    ++it_ch;
  }
}

TEST(Aphine, aphine_move_y) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kVertexes);
  auto vetr = std::get<std::vector<double>>(vertex);

  model->AffineTransformation(
      s21::TypeDataCommand(s21::TypeCommand::kMoveY, 0.33));

  auto vertex_changed =
      model->GetDataObject().GetCurrentDataObject().data_object.at(
          s21::TypeData::kVertexes);
  auto vetr_changed = std::get<std::vector<double>>(vertex_changed);

  std::vector<double> ori(
      {1, -0.67, -1,        1,        -0.67, 1, -1, -0.67, 1, -1, -0.67, -1,
       1, 1.33,  -0.999999, 0.999999, 1.33,  1, -1, 1.33,  1, -1, 1.33,  -1});
  auto it_ch = vetr_changed.begin();
  double eps = 1e-5;
  for (auto i : ori) {
    EXPECT_NEAR(*it_ch, i, eps);
    ++it_ch;
  }
}

TEST(Aphine, aphine_move_z) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kVertexes);
  auto vetr = std::get<std::vector<double>>(vertex);

  model->AffineTransformation(
      s21::TypeDataCommand(s21::TypeCommand::kMoveZ, 0.33));

  auto vertex_changed =
      model->GetDataObject().GetCurrentDataObject().data_object.at(
          s21::TypeData::kVertexes);
  auto vetr_changed = std::get<std::vector<double>>(vertex_changed);

  std::vector<double> ori({1,  -1, -0.67, 1,  -1, 1.33,      -1,       -1, 1.33,
                           -1, -1, -0.67, 1,  1,  -0.669999, 0.999999, 1,  1.33,
                           -1, 1,  1.33,  -1, 1,  -0.67});
  auto it_ch = vetr_changed.begin();
  double eps = 1e-5;
  for (auto i : ori) {
    EXPECT_NEAR(*it_ch, i, eps);
    ++it_ch;
  }
}

TEST(Aphine, aphine_scale) {
  std::unique_ptr<s21::Model> model = std::make_unique<s21::Model>();
  model->LoadObjectFromFile("../obj/kube.obj");
  auto vertex = model->GetDataObject().GetCurrentDataObject().data_object.at(
      s21::TypeData::kVertexes);
  auto vetr = std::get<std::vector<double>>(vertex);

  model->AffineTransformation(
      s21::TypeDataCommand(s21::TypeCommand::kScale, 0.33));

  auto vertex_changed =
      model->GetDataObject().GetCurrentDataObject().data_object.at(
          s21::TypeData::kVertexes);
  auto vetr_changed = std::get<std::vector<double>>(vertex_changed);

  std::vector<double> ori(
      {1.0033, -1.0033, -1.0033, 1.0033,  -1.0033, 1.0033,  -1.0033, -1.0033,
       1.0033, -1.0033, -1.0033, -1.0033, 1.0033,  1.0033,  -1.0033, 1.0033,
       1.0033, 1.0033,  -1.0033, 1.0033,  1.0033,  -1.0033, 1.0033,  -1.0033});
  auto it_ch = vetr_changed.begin();
  double eps = 1e-5;
  for (auto i : ori) {
    EXPECT_NEAR(*it_ch, i, eps);
    ++it_ch;
  }
}
