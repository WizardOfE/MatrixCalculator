#include <string>
#include "Matrix.h"
#include "Calculator.h"
#include <iostream>
#include <fstream>
#include <sstream>



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
            std::cout << o << " | "<<name << "\n";

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

    Matrix k = _matrices["A"];

    std::cout << k;
}

Calculator::~Calculator() {

}

