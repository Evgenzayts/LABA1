#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <iostream>
#include <header.hpp>

using nlohmann::json;
using namespace std;

void print_name(const Student& student, std::ostream& os) {
  if (student.name.empty()) {
    os << "null";
  } else {
    os << std::any_cast<std::string>(student.name);
  }
}

void print_group(const Student& student, std::ostream& os) {
  if (student.group.type() == typeid(std::nullptr_t)) {
    os << "null";
  } else if (student.group.type() == typeid(unsigned long int)) {
    os << std::any_cast<unsigned long int>(student.group);
  } else {
    os << std::any_cast<std::string>(student.group);
  }
}

void print_avg(const Student& student, std::ostream& os) {
  if (student.avg.type() == typeid(std::nullptr_t)) {
    os << "null";
  } else if (student.avg.type() == typeid(unsigned long int)) {
    os << std::any_cast<unsigned long int>(student.avg);
  } else if (student.avg.type() == typeid(double)) {
    os << std::any_cast<double>(student.avg);
  } else {
    os << std::any_cast<std::string>(student.avg);
  }
}

void print_debt(const Student& student, std::ostream& os) {
  if (student.debt.type() == typeid(std::nullptr_t)) {
    os << "null";
  } else if (student.debt.type() == typeid(std::string)) {
    os << std::any_cast<std::string>(student.debt);
  } else {
    stringstream line;
    line
        << std::any_cast<std::vector<std::string> >(student.debt).size()
        << " items";
    os << line.str();
  }
}

void print(const Student& student, std::ostream& os) {
  os << setiosflags(ios::left)  << "| " << setw(20);
  print_name(student, os);
  os << "| " << setw(10);
  print_group(student, os);
  os << "| " << setw(7);
  print_avg(student, os);
  os << "| " << setw(10);
  print_debt(student, os);
  os << "|" << endl;
}

void print(const std::vector<Student>& students, std::ostream& os) {
  os << "|        name         |   group   |  avg   |   debt    |" << endl;
  os << "|---------------------|-----------|--------|-----------|" << endl;
  for (auto const& student : students) {
    print(student, os);
    os << "|---------------------|-----------|--------|-----------|" << endl;
  }
}


void test_path(std::string& jsonPath) {
  if (jsonPath.empty()) {
    throw std::runtime_error{"incorrect path to file"};
  }
}

void test_file(std::string& jsonPath, std::ifstream& file) {
  if (!file) {
    throw std::runtime_error{"unable to open json: " + jsonPath};
  }
}

void test_count(nlohmann::json& data) {
  auto items = data.at("items");
  auto count = data.at("_meta").at("count");
  if (count != items.size()) {
    throw std::runtime_error{"count is not right"};
  }
}

void test_array(nlohmann::json& items) {
  if (!items.is_array()) {
    throw std::runtime_error{"items isn't array"};
  }
}


int main() {
  string jsonPath = JsonPath;
  test_path(jsonPath);

  std::ifstream file{jsonPath};
  test_file(jsonPath, file);

  json data;
  file >> data;
  test_array(data.at("items"));
  test_count(data);

  std::vector<Student> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<Student>();
    students.push_back(student);
  }
  print(students, std::cout);
}
