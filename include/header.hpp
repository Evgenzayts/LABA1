// Copyright 2021 Evgenzayts evgenzaytsev2002@yandex.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <any>
#include <nlohmann/json.hpp>
#include <string>

using nlohmann::json;

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

void from_json(const json& j, Student& s);

#endif // INCLUDE_HEADER_HPP_
