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
  ~Matrix();
  Matrix &operator+(Matrix &other);
  Matrix &operator+=(Matrix &other);
  Matrix &operator-(Matrix &other);
  Matrix &operator-=(Matrix &other);
  Matrix &operator*(Matrix &other);
  Matrix &operator*=(Matrix &other);

  friend bool operator==(const Matrix &lhs, const Matrix &rhs);
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
};
