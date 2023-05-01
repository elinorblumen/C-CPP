// Matrix.h
#include <stdlib.h>
#include <string>
#ifndef MATRIX_H
#define MATRIX_H

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and in main.cpp.
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * Class that represents a matrix object
 */
class Matrix{

//***********************************//
//******** PRIVATE MEMBERS **********//
//***********************************//
 private:
  /**
   * Double array that holds the matrix values
   */
  float* _mat;

  /**
   * matrix dimensions struct
   */
  matrix_dims* _mat_dims;

  /**
   * Helper function that returns the calculated index of the matrix
   * @param x the row index
   * @param y the col index
   * @return calculated index of the matrix
   */
  size_t index(int x, int y) const;

  /**
   * Helper function that checks whether the current matrix
   * and the given m matrix has the same row and column size
   * @param m other matrix
   * @return 1 if they have same size, 0 otherwise
   */
  int matrix_size_check(const Matrix& m);

  /**
   * Helper to determine whether matrix has legal row and column values
   * @param m given matrix
   * @return 1 if values are legal 0 otherwise
   */
  int col_row_check(const Matrix& m)const;

  /**
* Helper function that prints given error message to std::err.
* @param error_msg the given message to be printed
*/
  void print_err(std::string error_msg)const;


//***********************************//
//******** PUBLIC MEMBERS ***********//
//***********************************//
 public:
  /**
   * Constructor
   * @param rows num of rows
   * @param cols num of cols
   */
  Matrix(int rows, int cols);

  /**
   * Default constructor
   */
  Matrix();

  /**
   * Copy constructor
   * @param m Matrix to be copied
   */
  Matrix(const Matrix &m);

  /**
   * Destructor
   */
  ~Matrix();

  /**
   * Getter for the number of rows
   * @return Number of rows in matrix
   */
  int get_rows() const;

  /**
 * Getter for the number of columns
 * @return Number of columns in matrix
 */
  int get_cols() const;

  /**
   * Method that transposes the matrix
   */
  Matrix& transpose();

  /**
   * Method that transforms the current matrix
   * into a column matrix
   */
  Matrix& vectorize();

  /**
   * Prints matrix elements.
   */
  void plain_print();

  /**
   * Returns a matrix which is the elementwise multiplication
   * of this matrix and the given one
   * @param m given matrix to multiply with
   * @return new elementwise multiplied matrix
   */
  Matrix dot(const Matrix m);

  /**
   * returns the Frobenius norm of the current matrix
   * @return the calculated norm
   */
  float norm();
//***********************************//
//*********** OPERATORS *************//
//***********************************//

  float operator()(const int i, const int j);
  float& operator[](const int i);
  Matrix operator+(Matrix& m);
  Matrix& operator=(const Matrix m);
  friend Matrix operator*(Matrix &lhs, Matrix &rhs);
  friend Matrix operator*(Matrix &m, const float c);
  friend Matrix operator*(const float c, Matrix &m);
  Matrix& operator+=(const Matrix m);

  friend std::ostream &operator<< (std::ostream &os, const Matrix &matrix);
  friend std::istream &operator>> (std::istream &is, Matrix &matrix);


};
#endif //MATRIX_H
