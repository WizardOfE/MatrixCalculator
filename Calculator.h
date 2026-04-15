#pragma once

#include "Matrix.h"
#include <map>
#include <string>

class Calculator {
private:
  map<std::string, int> _matrices;

  int get_usr_cmd();
  bool file_add_matrix();
  bool file_overwrite_matrix();
  bool file_create_backup();

public:
  Calculator(std::string filename);
  void Start_Calc();
  ~Calculator();
};
