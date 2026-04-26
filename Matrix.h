#pragma once

#include <ostream>

class Matrix {
private:
  int **_data;
  int _rows;
  int _cols;

public:
  Matrix(int rows, int cols, int **data) : _data(data), _rows(rows), _cols(cols) {};
  ~Matrix();
  Matrix &operator+(Matrix &other);
  Matrix &operator+=(Matrix &other);
  Matrix &operator-(Matrix &other);
  Matrix &operator-=(Matrix &other);
  Matrix &operator*(Matrix &other);
  Matrix &operator*=(Matrix &other);

  int getRows() {
    return _rows;
  }
  int gowCol() {
    return _cols;
  }

  friend bool operator==(const Matrix &lhs, const Matrix &rhs);
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
};
