#include "Calculator.h"
#include "Matrix.h"
#include <array>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> Op_Map = {
    {"+", "0"}, {"+=", "1"}, {"-", "2"},  {"-=", "3"},
    {"*", "4"}, {"*=", "5"}, {"==", "6"}, {"<<", "7"}};

void Calculator::file_read() {
  std::ifstream MyReadFile(_filename);
  std::string myLine;

  int matrix_status = 0;

  int **toReturn;

  // get vars
  std::string name = "";
  int column_max = 0;
  int row_max = 0;

  int column_counter = 0;
  int row_counter = 0;

  while (getline(MyReadFile, myLine)) {
    // std::cout << myLine << "\n";
    switch (matrix_status) {
      // get name/variable of matrix
    case 0:
      name = myLine;
      row_max = 0;
      break;
      // get column count
    case 1:
      column_max = std::stoi(myLine);
      break;
      // get row count
    case 2:
      row_max = std::stoi(myLine);
      // set up array
      toReturn = new int *[row_max];

      for (int i = 0; i < row_max; i++) {
        toReturn[i] = new int[column_max];
      }

      break;
    default:
      std::istringstream ss(myLine);
      std::string cell;

      column_counter = 0;
      while (std::getline(ss, cell, ',')) {
        toReturn[row_counter][column_counter] = std::stoi(cell);
        // std::cout << toReturn[row_counter][column_counter] << " | "; //
        // Process each cell
        column_counter++;
      }
      row_counter++;
    }

    matrix_status++;

    // std::cout << matrix_status << " | " <<(matrix_status > row_max + 2 &&
    // matrix_status > 2)<< "\n";
    if (matrix_status > row_max + 2 && matrix_status > 2) {
      for (size_t x = 0; x < row_max; x++) {
        for (size_t y = 0; y < column_max; y++) {
          // std::cout << toReturn[x][y] << " " << "("<<x <<"," << y <<") \n";
        }
      }

      Matrix o(row_max, column_max, toReturn);
      // std::cout << o << " | "<<name << "\n";

      _matrices[name] = o;

      // td::cout << "sd" << "\n";
      matrix_status = 0;
      column_counter = 0;
      row_counter = 0;
    }
  }
}

Calculator::Calculator(std::string filename) { file_read(); }

void Calculator::Start_Calc() {
  int op;
  bool keepGoing = true;
  std::string lhs;
  std::string rhs;
  std::string store;
  std::array<std::string, 4> user_return;

  while (keepGoing) {

    // parse user input
    user_return = get_usr_cmd();
    lhs = user_return[0];
    op = std::stoi(user_return[1]);
    rhs = user_return[2];
    store = user_return[3];

    // TODO write errors, send to default case
    if (_matrices.count(lhs) == 0) {
      op = -1;
      std::cout << lhs << " did not exist" << std::endl;

    } else if (rhs != "" && _matrices.count(rhs) == 0) {
      std::cout << rhs << " did not exist" << std::endl;

    } else if (store != "" && _matrices.count(store) == 0) {
      std::cout << store << " did not exist" << std::endl;
    }

    switch (op) {
    case 0: {
      // + operator
      Matrix foo = _matrices[lhs] + _matrices[rhs];
      _matrices[store] = foo;
      std::cout << "Added " << lhs << " and " << rhs << " and stored it in "
                << store << std::endl;

      break;
    }
    case 1: {
      // += opreator
      _matrices[lhs] += _matrices[rhs];
      std::cout << "Added " << rhs << " to " << lhs << std::endl;

      break;
    }
    case 2: {
      // - operator
      Matrix foo = _matrices[lhs] - _matrices[rhs];
      _matrices[store] = foo;
      std::cout << "Subtracted " << lhs << " and " << rhs
                << " and stored it in " << store << std::endl;

      break;
    }
    case 3: {
      // -= operator
      _matrices[lhs] -= _matrices[rhs];
      std::cout << "subtracted " << rhs << " from " << lhs << std::endl;

      break;
    }
    case 4: {
      // * operator
      Matrix foo = _matrices[lhs] * _matrices[rhs];
      _matrices[store] = foo;
      std::cout << "Multiplied " << lhs << " and " << rhs
                << " and stored it in " << store << std::endl;

      break;
    }
    case 5: {
      // *= operator
      _matrices[lhs] *= _matrices[rhs];
      std::cout << "Multiplied " << lhs << " by " << rhs << std::endl;

      break;
    }
    case 6: {
      // == operator
      if (_matrices[lhs] == _matrices[rhs]) {
        std::cout << "Result was true" << std::endl;
      } else {
        std::cout << "Result was false" << std::endl;
      }

      break;
    }
    case 7: {
      // << operator
      std::cout << _matrices[lhs];

      break;
    }
    case 8: {
      // exit loop
      std::cout << "Goodbye!" << std::endl;
      keepGoing = false;

      break;
    }
    default: {
      std::cout << "Incorrect usage, try again." << std::endl;

      break;
    }
    }
  }

  // close up shop*/
  file_overwrite_matrix();
}

Calculator::~Calculator() {
  for (auto [key, value] : _matrices) {
    // delete value;
  }
}

bool Calculator::file_create_backup() {
  system(("cp " + _filename + " MatrixFileBackup.txt").c_str());
  return true;
}

/**
 * update given matrix file with new data
 * @return if successful
 */
bool Calculator::file_overwrite_matrix() {
  // open and clear the file
  std::ofstream outFile("_filename.txt");

  // if file is open
  if (outFile.is_open()) {
    for (auto [key, value] : _matrices) {
      auto o = _matrices[key];
      int colCount = o.getCols();
      int rowCount = o.getRows();

      outFile << key << "\n";
      outFile << colCount << "\n";
      outFile << rowCount << "\n";

      int **array = *o.getMatrixArray();
      for (int x = 0; x < rowCount; x++) {
        std::string rowText = "";
        for (int y = 0; y < colCount; y++) {
          rowText += std::to_string(array[rowCount][colCount]) + ",";
        }

        rowText.pop_back();
        outFile << rowText << "\n";
      }
    }
    // close the file
    outFile.close();
  } else {
    // error as file was not open
    std::cerr << "Error opening the file!";
    return false;
  }
  return true;
}

std::array<std::string, 4> Calculator::get_usr_cmd() {
  std::string user_input = "";
  std::cout << "Enter command: " << std::endl;
  getline(std::cin, user_input);
  std::cout << std::endl;
  std::stringstream split_input(user_input);

  std::string lhs = "";
  std::string op = "";
  std::string rhs = "";
  std::string store = "";

  split_input >> lhs;
  if (split_input.fail()) {
    return std::array<std::string, 4>{lhs, "-1", rhs, store};
  }
  split_input >> op;
  if (split_input.fail()) {
    return std::array<std::string, 4>{lhs, "-1", rhs, store};
  }

  if (Op_Map.count(op) == 0) {
    op = "-1";
  } else {
    op = Op_Map[op];
  }

  if (op != "7" && op != "-1") {
    split_input >> rhs;
    if (split_input.fail()) {
      return std::array<std::string, 4>{lhs, "-1", rhs, store};
    }
  }

  if (op == "0" || op == "2" || op == "4") {
    // double >> to skip the = op
    split_input >> store;
    if (split_input.fail()) {
      return std::array<std::string, 4>{lhs, "-1", rhs, store};
    }
    split_input >> store;
    if (split_input.fail()) {
      return std::array<std::string, 4>{lhs, "-1", rhs, store};
    }
  }

  return std::array<std::string, 4>{lhs, op, rhs, store};
}
