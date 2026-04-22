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
    int column_counter = 0;
    int row_counter = 0;

    int column_max = 0;
    int row_max = 0;

    // keep count of where we are att on each section of matrix;
    int matrix_status = 0;

    std::string matrix_name = "";

    // point to a 2d array
    int **toReturn;

    // go through each line of file
    while (getline(MyReadFile, myLine)) {
        //std::cout << myLine << "\n";
        switch (matrix_status){
            // if start save name of matrix
            case 0:

                matrix_name = myLine;
                std::cout << matrix_name << "\n";
                break;
            // get number of columns
            case 1:
                column_max = std::stoi(myLine);
                std::cout << column_max << "\n";
                break;
            // get number of rows and create matric
            case 2:
                row_max = std::stoi(myLine);
                std::cout << row_max << "\n";

                // create array
                toReturn = new int *[row_max];

                for (int i = 0; i < row_max; i++) {
                    toReturn[i] = new int[column_max];
                }

                break;
            // parse data:
            default:
                std::istringstream ss(myLine);
                std::string cell;

                while (std::getline(ss, cell, ',')) {
                    std::cout << cell << " | "; // Process each cell
                }
                row_counter++;
                break;

        }
        matrix_status++;

        // if needs to be reset, reset it to loop
        if (row_max <= row_counter + 3) {
            matrix_status = 0;
        }
    }
}

Calculator::Calculator(std::string filename) {
     file_read(filename);
}

void Calculator::Start_Calc() {

}

Calculator::~Calculator() {

}

