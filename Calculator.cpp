#include <string>
#include "Matrix.h"
#include "Calculator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <filesystem>
#include <iostream>


void Calculator::file_read(std::string filename) {
    std::ifstream MyReadFile(filename);
    std::string myLine;

    std::cout << filename << "\n";

    int matrix_status = 0;

    int **toReturn;

    //get vars
    std::string name = "";
    int column_max = 0;
    int row_max = 0;

    int column_counter = 0;
    int row_counter = 0;

    while (getline(MyReadFile, myLine)) {
        //std::cout << myLine << "\n";
        switch (matrix_status) {
            case 0 :
                name = myLine;
                row_max = 0;
                break;
            case 1:
                column_max = std::stoi(myLine);
                break;
            case 2:
                row_max = std::stoi(myLine);
                // create array
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
                    //std::cout << toReturn[row_counter][column_counter] << " | "; // Process each cell
                    column_counter++;
                }
                row_counter++;
        }

        matrix_status++;

        //std::cout << matrix_status << " | " <<(matrix_status > row_max + 2 && matrix_status > 2)<< "\n";
        if(matrix_status > row_max + 2 && matrix_status > 2) {
            for (size_t x = 0; x < row_max; x++) {
                for (size_t y = 0; y < column_max; y++) {
                    //std::cout << toReturn[x][y] << " " << "("<<x <<"," << y <<") \n";
                }
            }

            Matrix o(row_max, column_max, toReturn);
            //std::cout << o << " | "<<name << "\n";

            _matrices[name] = o;

            //td::cout << "sd" << "\n";
            matrix_status = 0;
            column_counter = 0;
            row_counter = 0;
        }
    }

}

Calculator::Calculator(std::string filename) {
	file_read(filename);
}

void Calculator::Start_Calc() {
  /*int op;
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
      std::cout << lhs << " did not exist";

    } else if (rhs != "" && _matrices.count(rhs) == 0) {

    } else if (store != "" && _matrices.count(store) == 0) {
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

      break;
    }
    default: {

      break;
    }
    }
  }

  // close up shop*/
}

Calculator::~Calculator() {
	for (auto [key, value] : _matrices) {
		//delete value;
	}

}

bool Calculator::file_create_backup(std::string filename) {
	system(("cp "+filename+" MatrixFileBackup.txt").c_str());
}