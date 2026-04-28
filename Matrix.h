/**
 * @file Matrix.h
 * @brief Matrix file
 *
 * @author Levi Interian (linterianuc23@georgefox.edu) and Ethan Quirie (equirie24@georgefox.edu)
 */
#pragma once

#include <ostream>

/**
 * Matrix object for holding 2d array
 */
class Matrix {
private:
  int **_data;  /// Matrix data
  int _rows;    /// number of rows in 2d array
  int _cols;    /// number of columns in 2d array

public:

  /**
   * Matrix constructor
   * @param rows number of rows
   * @param cols number of columns
   * @param data 2d array of matrix data
   **/
  Matrix(int rows, int cols, int **data) : _data(data), _rows(rows), _cols(cols) {};

  /**
   * Matrix copy constructor
   * @param other matrix to copy
   */
  Matrix(const Matrix &other);

  /**
   *
   * @param other Matrix to equal
   * @return new matrix
   */
  Matrix& operator=(const Matrix &other);

  /**
   * default constructor
   */
  Matrix();

  /**
   * destructor
   */
  ~Matrix();

  /**
   * Addition operator
   * @param other Matrix
   * @return New matrix
   */
  Matrix &operator+(Matrix &other);

  /**
   * addition compound assignment
   * @param other Matrix
   * @return Added matrix
   */
  Matrix &operator+=(Matrix &other);

  /**
   * Subtraction operator
   * @param other matrix
   * @return new matrix
   */
  Matrix &operator-(Matrix &other);

  /**
   * Subtraction compound operator
   * @param other Matrix
   * @return new matrix
   */
  Matrix &operator-=(Matrix &other);

  /**
   * Multiplication operator
   * @param other Matrix
   * @return Matrix
   */
  Matrix &operator*(Matrix &other);

  /**
   * Multiplication compound operator
   * @param other Matrix
   * @return New matrix
   */
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

  /**
   * Compare two operators
   * @param lhs left matrix
   * @param rhs right
   * @return if equal
   */
  friend bool operator==(const Matrix &lhs, const Matrix &rhs);

  /**
   * Left shift operator
   * @param os outstream item
   * @param matrix to output
   * @return outstream output
   */
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

};
