#pragma once

#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

class Calculator {
private:
  std::map<std::string, Matrix> _matrices;
  std::string _filename;

  std::array<std::string, 4> get_usr_cmd();
  bool file_overwrite_matrix();
  bool file_create_backup();
  void file_read();

public:
  Calculator(std::string filename);
  void Start_Calc();
  ~Calculator();
};
