// Copyright 2021 Evgenzayts evgenzaytsev2002@yandex.ru

#include <gtest/gtest.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <header.hpp>

using nlohmann::json;

const std::string jsonPath = JsonPath;

TEST(Lab1, EmptyPath) {
  EXPECT_FALSE(jsonPath.empty());
}

TEST(Lab1, NoFile) {
  std::ifstream file{jsonPath};
  EXPECT_TRUE(file);
}

TEST(Lab1, NotArray) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  EXPECT_TRUE( data.at("items").is_array());
}

TEST(Lab1, RightCount) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  EXPECT_EQ(data.at("items").size(), data.at("_meta").at("count").get<size_t>());
}

TEST(ParserTest, TestGroup) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<Student>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool is_right = false;
    if (student.group.type() == typeid(std::string)) {
      is_right = true;
    } else if (student.group.type() == typeid(unsigned long int)) {
      is_right  = true;
    } else if (student.group.type() == typeid(std::nullptr_t)) {
      is_right = true;
    }
    EXPECT_TRUE(is_right);
  }
}

TEST(ParserTest, TestAvg) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<Student>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool is_right = false;
    if (student.avg.type() == typeid(std::nullptr_t)) {
      is_right = true;
    } else if (student.avg.type() == typeid(std::string)) {
      is_right = true;
    } else if (student.avg.type() == typeid(double)) {
      is_right = true;
    } else if(student.avg.type() == typeid(unsigned long int)){
      is_right = true;
    }
    EXPECT_TRUE(is_right);
  }
}

TEST(ParserTest, TestDebt) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<Student>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool is_right = false;
    if (student.debt.type() == typeid(std::nullptr_t)) {
      is_right = true;
    } else if (student.debt.type() == typeid(std::string)) {
      is_right = true;
    } else if(student.debt.type() == typeid(std::vector<std::string>)){
      is_right = true;
    }
    EXPECT_TRUE(is_right);
  }
}
