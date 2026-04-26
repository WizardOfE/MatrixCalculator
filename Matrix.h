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
  Matrix(const Matrix &other) {
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

  Matrix& operator=(const Matrix &other) {
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

  int getRows() { return _rows; }
  int gowCol() { return _cols; }

  friend bool operator==(const Matrix &lhs, const Matrix &rhs);
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
};
