#pragma once

#include "Matrix.h"
#include <iomanip>


struct MatrixDimMismatchException : public std::runtime_error {
  MatrixDimMismatchException(const std::string &msg)
      : std::runtime_error(msg) {}
};

Matrix::Matrix(const Matrix &other) {
  _rows = other._rows;
  _cols = other._cols;

  _data = new int*[_rows];
  for (int i = 0; i < _rows; i++) {
    _data[i] = new int[_cols];
    for (int j = 0; j < _cols; j++) {
      _data[i][j] = other._data[i][j];
    }
  }
}

Matrix::~Matrix() {
  for (int i = 0; i < _rows; i++) {
    delete[] _data[i];
  }
  delete[] _data;
}

Matrix &Matrix::operator+(Matrix &other) {
  // dimension check
  if (_rows != other._rows || _cols != other._cols) {
    throw new MatrixDimMismatchException(
        "Attempted to add two matrices with mismatching dimensions");
  }

  // create new 2d array
  int **toReturn;
  toReturn = new int *[_rows];

  for (int i = 0; i < _rows; i++) {
    toReturn[i] = new int[_cols];
  }

  // fill the array
  for (int x = 0; x < _rows; x++) {
    for (int y = 0; y < _cols; y++) {
      toReturn[x][y] = _data[x][y] + other._data[x][y];
    }
  }

  Matrix *matrixReturn = new Matrix(_rows, _cols, toReturn);

  return *matrixReturn;
}

Matrix &Matrix::operator+=(Matrix &other) {
  // dimension check
  if (_rows != other._rows || _cols != other._cols) {
    throw new MatrixDimMismatchException(
        "Attempted to add two matrices with mismatching dimensions");
  }

  // fill the array
  for (int x = 0; x < _rows; x++) {
    for (int y = 0; y < _cols; y++) {
      _data[x][y] += other._data[x][y];
    }
  }

  return *this;
}

Matrix &Matrix::operator-(Matrix &other) {
  // dimension check
  if (_rows != other._rows || _cols != other._cols) {
    throw new MatrixDimMismatchException(
        "Attempted to subtract two matrices with mismatching dimensions");
  }

  // create new 2d array
  int **toReturn;
  toReturn = new int *[_rows];

  for (int i = 0; i < _rows; i++) {
    toReturn[i] = new int[_cols];
  }

  // fill the array
  for (int x = 0; x < _rows; x++) {
    for (int y = 0; y < _cols; y++) {
      toReturn[x][y] = _data[x][y] - other._data[x][y];
    }
  }

  Matrix *matrixReturn = new Matrix(_rows, _cols, toReturn);

  return *matrixReturn;
}

Matrix &Matrix::operator-=(Matrix &other) {
  // dimension check
  if (_rows != other._rows || _cols != other._cols) {
    throw new MatrixDimMismatchException(
        "Attempted to subract two matrices with mismatching dimensions");
  }

  // fill the array
  for (int x = 0; x < _rows; x++) {
    for (int y = 0; y < _cols; y++) {
      _data[x][y] -= other._data[x][y];
    }
  }

  return *this;
}

Matrix &Matrix::operator*(Matrix &other) {
  // dimension check
  if (_rows != other._rows || _cols != other._cols) {
    throw new MatrixDimMismatchException(
        "Attempted to multiply two matrices with mismatching dimensions. The "
        "number of cols in this and the number of rows in other did not "
        "match.");
  }

  // create new 2d array
  int **toReturn;
  toReturn = new int *[_rows];

  for (int i = 0; i < _rows; i++) {
    toReturn[i] = new int[other._cols];
  }

  int tempVal;

  // fill the array
  for (int m = 0; m < _rows; m++) {
    for (int n = 0; n < other._cols; n++) {
      tempVal = 0;

      for (int i = 0; i < _cols; i++) {
        tempVal += _data[m][i] * other._data[i][n];
      }

      toReturn[m][n] = tempVal;
    }
  }

  Matrix *matrixReturn = new Matrix(_rows, _cols, toReturn);

  return *matrixReturn;
}

Matrix &Matrix::operator*=(Matrix &other) {
  // dimension check
  if (_rows != other._rows || _cols != other._cols) {
    throw new MatrixDimMismatchException(
        "Attempted to multiply two matrices with mismatching dimensions. The "
        "number of cols in this and the number of rows in other did not "
        "match.");
  }

  // create new 2d array
  int **toReturn;
  toReturn = new int *[_rows];

  for (int i = 0; i < _rows; i++) {
    toReturn[i] = new int[other._cols];
  }

  int tempVal;

  // fill the array
  for (int m = 0; m < _rows; m++) {
    for (int n = 0; n < other._cols; n++) {
      tempVal = 0;

      for (int i = 0; i < _cols; i++) {
        tempVal += _data[m][i] * other._data[i][n];
      }

      toReturn[m][n] = tempVal;
    }
  }

  _data = toReturn;

  return *this;
}

Matrix& Matrix::operator=(const Matrix &other) {
  if (this == &other) return *this;

  for (int i = 0; i < _rows; i++) delete[] _data[i];
  delete[] _data;

  _rows = other._rows;
  _cols = other._cols;

  _data = new int*[_rows];
  for (int i = 0; i < _rows; i++) {
    _data[i] = new int[_cols];
    for (int j = 0; j < _cols; j++) {
      _data[i][j] = other._data[i][j];
    }
  }
  return *this;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
  bool toReturn = true;

  if (lhs._rows != rhs._rows || lhs._cols != rhs._cols) {
    toReturn = false;
  }

  for (int x = 0; x < lhs._rows && toReturn; x++) {
    for (int y = 0; y < lhs._cols && toReturn; x++) {
      if (lhs._data[x][y] != rhs._data[x][y]) {
        toReturn = false;
      }
    }
  }

  return toReturn;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
  int cellWidth = 0;

  // determine the width of the widest number
  for (int x = 0; x < matrix._rows; x++) {
    for (int y = 0; y < matrix._cols; y++) {
      if (std::to_string(matrix._data[x][y]).length() > cellWidth) {
        cellWidth = std::to_string(matrix._data[x][y]).length();
      }
    }
  }

  // top tips of brackets
  os << "_"
     << std::string(((cellWidth * matrix._rows) + (matrix._rows - 1)), ' ')
     << "_" << "\n";
  os << "| "
     << std::string(((cellWidth * matrix._rows) + (matrix._rows - 1)), ' ')
     << "|" << "\n";

  // meat and potatoes
  for (int y = 0; y < matrix._cols; y++) {
    os << "| ";

    for (int x = 0; x < matrix._rows; x++)
      os << std::setw(cellWidth) << std::internal << matrix._data[x][y] << " ";

    os << "|" << "\n";

    // plus lines
    if (y != matrix._cols - 1) {
      os << "| ";

      for (int x = 0; x < matrix._rows; x++) {
        os << std::string(cellWidth, ' ');

        if (x != matrix._rows - 1) {
          os << "+";
        }
      }

      os << " |" << "\n";
    }
  }

  // last two lines
  os << "| "
     << std::string(((cellWidth * matrix._rows) + (matrix._rows - 1)), ' ')
     << "|" << "\n";
  os << "_"
     << std::string(((cellWidth * matrix._rows) + (matrix._rows - 1)), ' ')
     << "_" << "\n";

  return os;
}
