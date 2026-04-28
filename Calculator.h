/**
 * @file Calculator.h
 * @brief Calculator for processing matrix calculations
 *
 * @author Levi Interian (linterianuc23@georgefox.edu) and Ethan Quirie (equirie24@georgefox.edu)
 */

#pragma once

#include "Matrix.h"
#include <map>
#include <string>

/**
 * Calculator class for user mathematics
 */
class Calculator {
private:
  std::map<std::string, Matrix> _matrices;  /// map of matricies
  std::string _filename;                    /// file name of given file

  /**
   * parse user info
   * @return parsed user info
   */
  std::array<std::string, 4> get_usr_cmd();

  /**
   * replaces the given file with a new one
   * @return if overwriting was successful
   */
  bool file_overwrite_matrix();

  /**
    * Creates a backup for the given file
    * @return if success creating back up
    */
  bool file_create_backup();

  /**
   * read the file that was given
   */
  void file_read();

public:
  /**
   * create a calculator object
   * @param filename file name to use
   */
  Calculator(std::string filename);

  /**
   * Begin main code for calculations
   */
  void Start_Calc();

  /**
   * Calculator destructor
   */
  ~Calculator();
};
