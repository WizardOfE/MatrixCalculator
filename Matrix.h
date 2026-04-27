#pragma once

#include <ostream>

class Matrix {
private:
  int **_data;
  int _rows;
  int _cols;

public:
  Matrix(int rows, int cols, int **data)
      : _data(data), _rows(rows), _cols(cols) {};
  Matrix(const Matrix &other);

  Matrix& operator=(const Matrix &other);

  Matrix() {
    _rows = 2;
    _cols = 2;
    _data = new int *[_rows];
    for (int x = 0; x < _rows; x++) {
      _data[x] = new int[_cols];
    }
  };
  ~Matrix();
  Matrix &operator+(Matrix &other);
  Matrix &operator+=(Matrix &other);
  Matrix &operator-(Matrix &other);
  Matrix &operator-=(Matrix &other);
  Matrix &operator*(Matrix &other);
  Matrix &operator*=(Matrix &other);

  /**
   * get rows
   * @return integer of rows
   */
  int getRows();

  /**
   * Get columns
   * @return integer of matrix columns
   */
  int getCols();

  /**
   * get the internal array
   * @return matrix array
   */
  int*** getMatrixArray();

  friend bool operator==(const Matrix &lhs, const Matrix &rhs);
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

};
