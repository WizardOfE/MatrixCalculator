#pragma once

#include "Matrix.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Calculator {
private:
  std::map<std::string, Matrix> _matrices;

  std::array<std::string, 4> get_usr_cmd();
  bool file_add_matrix();
  bool file_overwrite_matrix();
  bool file_create_backup();
  void file_read(std::string filename);

public:
  Calculator(std::string filename);
  void Start_Calc();
  ~Calculator();
};
