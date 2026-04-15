#pragma once

#include <ostream>

class Matrix {
private:
  // TODO declare array - fixed length must be hard coded?
public:
  // TODO update constructor declaration to match internal state - unsure of
  // what data should be
  Matrix(int length, int width, double data);
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
