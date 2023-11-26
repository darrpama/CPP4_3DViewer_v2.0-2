#include "../models/settings.h"

#include <gtest/gtest.h>

#include <iostream>

bool compareFloats(float a, float b);

TEST(SettingsTest, ProjectionType) {
  s21::Settings settings = s21::Settings();
  settings.SetProjectionType(s21::ProjectionType::CENTRAL);

  EXPECT_TRUE(settings.GetProjectionType() == s21::ProjectionType::CENTRAL);
}

TEST(SettingsTest, Color) {
  s21::Settings settings = s21::Settings();
  settings.SetColor(s21::ColorType::BG_COLOR, s21::Color(11, 0, 0));
  settings.SetColor(s21::ColorType::EDGE_COLOR, s21::Color(0, 22, 0));
  settings.SetColor(s21::ColorType::VERTICE_COLOR, s21::Color(0, 0, 33));
  s21::Color bg_color = settings.GetColor(s21::ColorType::BG_COLOR);
  s21::Color edge_color = settings.GetColor(s21::ColorType::EDGE_COLOR);
  s21::Color vertice_color = settings.GetColor(s21::ColorType::VERTICE_COLOR);
  EXPECT_TRUE(bg_color.red == 11 && bg_color.green == 0 && bg_color.blue == 0);
  EXPECT_TRUE(edge_color.red == 0 && edge_color.green == 22 &&
              edge_color.blue == 0);
  EXPECT_TRUE(vertice_color.red == 0 && vertice_color.green == 0 &&
              vertice_color.blue == 33);
}

TEST(SettingsTest, EdgeType) {
  s21::Settings settings = s21::Settings();

  settings.SetEdgeType(s21::EdgeType::DASHED);
  EXPECT_TRUE(settings.GetEdgeType() == s21::EdgeType::DASHED);

  settings.SetEdgeType(s21::EdgeType::NO_EDGE);
  EXPECT_TRUE(settings.GetEdgeType() == s21::EdgeType::NO_EDGE);

  settings.SetEdgeType(s21::EdgeType::SOLID);
  EXPECT_TRUE(settings.GetEdgeType() == s21::EdgeType::SOLID);
}

TEST(SettingsTest, VerticeType) {
  s21::Settings settings = s21::Settings();

  settings.SetVerticeType(s21::VerticeType::CIRCLE);
  EXPECT_TRUE(settings.GetVerticeType() == s21::VerticeType::CIRCLE);

  settings.SetVerticeType(s21::VerticeType::NO_VERTICE);
  EXPECT_TRUE(settings.GetVerticeType() == s21::VerticeType::NO_VERTICE);

  settings.SetVerticeType(s21::VerticeType::SQUARE);
  EXPECT_TRUE(settings.GetVerticeType() == s21::VerticeType::SQUARE);
}

TEST(SettingsTest, EdgeThickness) {
  s21::Settings settings = s21::Settings();

  settings.SetEdgeThickness(2);
  EXPECT_TRUE(settings.GetEdgeThickness() == 2);
}

TEST(SettingsTest, VerticeSize) {
  s21::Settings settings = s21::Settings();

  settings.SetVerticeSize(2);
  EXPECT_TRUE(settings.GetVerticeSize() == 2);
}

TEST(SettingsTest, Translations) {
  s21::Settings settings = s21::Settings();
  settings.SetTranslationX(2.0f);
  EXPECT_TRUE(compareFloats(settings.GetTranslationX(), 2.0f));

  settings.SetTranslationY(3.0f);
  EXPECT_TRUE(compareFloats(settings.GetTranslationY(), 3.0f));

  settings.SetTranslationZ(4.0f);
  EXPECT_TRUE(compareFloats(settings.GetTranslationZ(), 4.0f));
}

TEST(SettingsTest, Rotations) {
  s21::Settings settings = s21::Settings();
  settings.SetRotationX(2.0f);
  EXPECT_TRUE(compareFloats(settings.GetRotationX(), 2.0f));

  settings.SetRotationY(3.0f);
  EXPECT_TRUE(compareFloats(settings.GetRotationY(), 3.0f));

  settings.SetRotationZ(4.0f);
  EXPECT_TRUE(compareFloats(settings.GetRotationZ(), 4.0f));
}

TEST(SettingsTest, LoadSettings) {
  s21::Settings settings = s21::Settings();
  settings.LoadSettings();
}

bool compareFloats(float a, float b) {
  float threshold = 0.00001;
  if (abs(a - b) >= threshold) {
    return false;
  }

  return true;
}
