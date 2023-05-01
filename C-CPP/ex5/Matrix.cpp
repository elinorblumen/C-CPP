//
// Created by ElinorB on 15/12/2021.
//
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cmath>
#define DEFAULT_SIZE 1
#define NON_VALID_INPUT_SIZE "Error: non valid input size!"
#define NON_VALID_MATRIX "Error: nullptr input matrix!"
#define EMPTY_INPUT_MATRIX "Error: empty input matrix!"
#define BAD_DOT_MULTIPLICATION "Error: Can't dot multiply two matrices with different size!"
#define NON_VALID_MATRIX_ADDITION "Error: Can't add two matrices with different size"
#define BAD_MULTIPLICATION "Error: Can't multiply two matrices with different size!"
#define BAD_ADDITION "Error: Can't add two matrices with different size!"
#define MEM_ALLOC_FAIL "Error: Failed to allocate memory!"
#define IS_ERROR "Error: input stream error!"



//***********************************//
//********** CONSTRUCTORS ***********//
//***********************************//
/**
   * Constructor
   * @param rows num of rows
   * @param cols num of cols
   */
Matrix::Matrix(int rows, int cols){

    if(rows<1 || cols<1){
            print_err(NON_VALID_INPUT_SIZE);
            return;
    }
    _mat = new float[rows*cols]();
    if(_mat == nullptr){
            print_err (MEM_ALLOC_FAIL);
            return;
    }

    _mat_dims = new matrix_dims();
    if(_mat_dims == nullptr){
            delete[] _mat;
            print_err (MEM_ALLOC_FAIL);
            return;
        }
    _mat_dims->rows = rows;
    _mat_dims->cols = cols;
}

/**
* Default constructor
*/
Matrix::Matrix(){

    Matrix(DEFAULT_SIZE, DEFAULT_SIZE);
}

/**
* Copy constructor
* @param m Matrix to be copied
*/
Matrix::Matrix(const Matrix &m){

    if(!col_row_check (m)){
            print_err (NON_VALID_INPUT_SIZE);
            return;
    }

    int new_rows = m._mat_dims->rows;
    int new_cols = m._mat_dims->cols;

    _mat = new float[new_rows*new_cols];
    if(!_mat){
            print_err (MEM_ALLOC_FAIL);
            return;
        }

    _mat_dims = new matrix_dims;
    if(!_mat_dims){
        delete[] _mat;
        print_err (MEM_ALLOC_FAIL);
        return;
    }
    _mat_dims->rows = new_rows;
    _mat_dims->cols = new_cols;

    for (int i = 0; i < new_rows*new_cols; ++i){
        _mat[i] = m._mat[i];
    }
}

Matrix::~Matrix(){

    delete[] _mat;
    delete _mat_dims;
}

//***********************************//
//*********** OPERATORS *************//
//***********************************//

/**
 * operator [] implementation
 * @param i index
 * @return the value at Matrix[i] index
 */
float& Matrix::operator[](const int i){

    if(!col_row_check (*this)){
            print_err (NON_VALID_INPUT_SIZE);
            return _mat[0];
        }
    return _mat[i];
}


/**
 * const operator [] implementation
 * @param i index
 * @return the value at Matrix[i] index
 */
//float Matrix::operator[](const int i)const{
//
//    if(!col_row_check (*this)){
//            print_err (NON_VALID_INPUT_SIZE);
//            return 0;
//        }
//    return _mat[i];
//}
/**
 * + operator implementation
 * @param m right hand side matrix
 * @return new matrix that holds the sum of the two matrices.
 */
Matrix Matrix::operator+(Matrix& m){

    if(!matrix_size_check (m)){
            print_err (BAD_ADDITION);
            return Matrix();
    }
    if(!col_row_check (m) || !col_row_check (*this)){
        print_err (NON_VALID_INPUT_SIZE);
        return Matrix();
    }
    Matrix new_mat(get_rows(), get_cols());
    for(int i = 0 ; i < get_rows()*get_cols(); ++i){
        new_mat._mat[i] = _mat[i]+m._mat[i];
    }
    return new_mat;
}
/**
 * = operator implementation
 * @param m matrix to be assigned from
 * @return current newly assigned matrix reference
 */
Matrix& Matrix::operator=(const Matrix m){

    if(!col_row_check (m) || !col_row_check (*this)){
            std::cerr << NON_VALID_INPUT_SIZE << std::endl;
        return *this;
    }
    if((get_rows()*get_cols()) != (m.get_rows()*m.get_cols())){
        delete[] _mat;
        _mat = new float[m.get_rows()*m.get_cols()];
        if(_mat == nullptr){
                std::cerr << MEM_ALLOC_FAIL << std::endl;
                return *this;
        }
        _mat_dims->rows = m.get_rows();
        _mat_dims->cols = m.get_cols();
    }
    for(int i = 0; i < get_rows()*get_cols(); ++i){
        _mat[i] = m._mat[i];
    }
    return *this;
}
/**
 * operator * implementation
 * @param lhs left hand side matrix
 * @param rhs  right hand side matrix
 * @return new multiplied matrix
 */
Matrix operator*(Matrix &lhs, Matrix &rhs){

    if(lhs.get_cols() != rhs.get_rows() ||
    lhs.get_cols()*lhs.get_rows() <=0 ||
    rhs.get_cols()*rhs.get_rows() <= 0)
        {
            std::cerr << BAD_MULTIPLICATION << std::endl;
            return lhs;
        }

    Matrix new_mat(lhs.get_rows(), rhs.get_cols());
    for(int i = 0; i < lhs.get_rows(); i++){
        for(int j = 0; j < rhs.get_cols(); j++) {
            float sum = 0;
            for (int k = 0; k < lhs.get_cols(); k++) {
                sum += (lhs[i*lhs.get_cols()+k] + rhs[k*rhs.get_cols()+j]);
            }
            int index = i*rhs.get_cols()+j;
            new_mat[index] = sum;
        }
    }
    return new_mat;

}
/**
 * operator * implementation with right hand side multiplication with scalar
 * @param m matrix to be multiplied
 * @param c scalar
 * @return m new multiplied matrix
 */
Matrix operator*(Matrix &m, const float c){

    if(m.get_cols()*m.get_rows() <=0)
        {
            std::cerr << NON_VALID_INPUT_SIZE << std::endl;
            return m;
        }
    Matrix new_mat = Matrix (m.get_rows(), m.get_cols());
    for(int i = 0; i < m.get_rows()*m.get_cols(); i++){
        new_mat[i] = (m[i]*c);
    }
    return new_mat;
}

/**
 * operator * implementation with left hand side multiplication with scalar
 * @param m matrix to be multiplied
 * @param c scalar
 * @return m new multiplied matrix
 */
Matrix operator*(const float c, Matrix &m){

    return operator*(m, c);
}

/**
 * operator +- implementation
 * @param m the matrix to add
 * @return current matrix with added matrix values
 */
Matrix& Matrix::operator+=(const Matrix m){

    if(!matrix_size_check (m)){
        print_err (BAD_ADDITION);
        return *this;
    }
    if(!col_row_check (m) || !col_row_check (*this)){
        print_err (NON_VALID_INPUT_SIZE);
        return *this;
    }
    for(int i = 0 ; i < get_rows()*get_cols(); ++i){
            _mat[i] += m._mat[i];
        }
    return *this;
}

/**
 * operator () implementation
 * @param i row index
 * @param j column index
 * @return the value at Matrix(i,j) index
 */
float Matrix::operator()(const int i, const int j){

    if(!col_row_check (*this)){
        print_err (NON_VALID_INPUT_SIZE);
        return 0;
    }
    return _mat[get_cols()*i + j];
}



/**
 * operator << implementation for matrix
 * @param os output stream object
 * @param matrix matrix to be outputted
 * @return output stream object containing the matrix output
 */
std::ostream& operator<< (std::ostream &os, const Matrix &matrix){

    if(matrix.get_cols()*matrix.get_rows() <=0)
        {
            std::cerr << NON_VALID_INPUT_SIZE << std::endl;
            return os;
        }
    for(int i = 0; i < matrix.get_rows(); ++i){
            for(int j = 0; j < matrix.get_cols(); ++j){
                    os << matrix._mat[i*matrix.get_cols() + j] << " ";
                }
            os << "" << std::endl;
        }
    return os;
}

/**
 * operator >> implementation
 * @param is input stream
 * @param matrix matrix to be filled
 * @return input stream object
 */
std::istream& operator>> (std::istream &is, Matrix &matrix){

    if(matrix.get_cols()*matrix.get_rows() <=0)
        {
            std::cerr << NON_VALID_INPUT_SIZE << std::endl;
            return is;
        }
    for(int i=0; i < matrix.get_cols()*matrix.get_rows() ; ++i){
        if(!is.good()){
            std::cerr << IS_ERROR <<std::endl;
            exit(1);
        }
        is >> matrix[i];
    }
    if((is.fail()) || (is.bad())){
        std::cerr << IS_ERROR << std::endl;
        exit(1);
    }
    return is;

}

//***********************************//
//************ METHODS **************//
//***********************************//
/**
 * Getter for the number of rows
 * @return Number of rows in matrix
 */
int Matrix::get_rows() const{

    return _mat_dims->rows;
}

/**
* Getter for the number of columns
* @return Number of columns in matrix
*/
int Matrix::get_cols() const{

    return _mat_dims->cols;
}

/**
 * Method that transposes the matrix
 */
Matrix& Matrix::transpose(){

    if(!col_row_check (*this)){
            print_err (NON_VALID_INPUT_SIZE);
            return *this;
        }
    int original_rows = this->get_rows();
    int original_cols = this->get_cols();
    if(original_rows < 1 || original_cols < 1){
            print_err (EMPTY_INPUT_MATRIX);
            return *this;
    }
    Matrix temp(original_cols, original_rows);

    for (int i = 0; i < original_cols; ++i){
        for(int j = 0; j < original_rows; ++j){
                temp._mat[i*original_rows + j] = _mat[j*original_cols + i];
        }
    }
    for(int i = 0; i < (original_rows*original_cols); ++i){
        _mat[i] = temp._mat[i];
    }
    _mat_dims->rows = temp.get_rows();
    _mat_dims->cols = temp.get_cols();
    delete temp._mat_dims;
    delete[] temp._mat;
    return *this;
}

/**
 * Method that transforms the current matrix
 * into a column matrix
 */
Matrix& Matrix::vectorize(){

    if(!col_row_check (*this)){
            print_err (NON_VALID_INPUT_SIZE);
            return *this;
        }
    int original_rows = _mat_dims->rows;
    int original_cols = _mat_dims->cols;

    _mat_dims->rows = original_rows*original_cols;
    _mat_dims->cols = 1;

    return *this;
}

/**
 * Prints matrix elements.
 */
void Matrix::plain_print(){

    if(!col_row_check (*this)){
            print_err (NON_VALID_INPUT_SIZE);
            return;
        }
    using std::cout;
    using std::endl;

    for(int i = 0; i < this->get_rows(); ++i){
        for(int j = 0; j < this->get_cols(); ++j){
            cout << _mat[i*this->get_cols() + j] << " ";
        }
        cout << "" << endl;
    }
}

/**
 * Returns a matrix which is the elementwise multiplication
 * of this matrix and the given one
 * @param m given matrix to multiply with
 * @return new elementwise multiplied matrix
 */
Matrix Matrix::dot(const Matrix m){

    if(!col_row_check (m) || !col_row_check (*this)){
            print_err (NON_VALID_INPUT_SIZE);
            return *this;
        }
    if(!matrix_size_check (m)){
            print_err (BAD_DOT_MULTIPLICATION);
            return *this;
    }
    Matrix new_mat(get_rows(), get_cols());
    for(int i = 0; i < get_rows()*get_cols(); ++i){
        new_mat._mat[i] = _mat[i]*m._mat[i];
    }
    return new_mat;
}

/**
 * returns the Frobenius norm of the current matrix
 * @return the calculated norm
 */
float Matrix::norm(){

    if(!col_row_check (*this)){
            print_err (NON_VALID_INPUT_SIZE);
            return 0;
        }
    float norm = 0;
    for (int i = 0; i < get_rows()*get_cols(); i++){
        norm += _mat[i]*_mat[i];
    }
    return sqrtf (norm);
}

/**
 * Helper function that returns the calculated index of the matrix
 * @param x the row index
 * @param y the col index
 * @return calculated index of the matrix
 */
size_t Matrix::index (int rows, int cols) const
{
    int row_size = _mat_dims->cols;
    return rows*row_size + cols;
}

/**
* Helper function that prints given error message to std::err.
* @param error_msg the given message to be printed
*/
void Matrix::print_err(std::string error_msg)const{
    std::cerr << error_msg << std::endl;
}
/**
* Helper function that checks whether the current matrix
* and the given m matrix has the same row and column size
* @param m other matrix
* @return 1 if they have same size, 0 otherwise
*/
int Matrix::matrix_size_check(const Matrix& m){

    if(get_rows() == m.get_rows()){
        if(get_cols() == m.get_cols()){
                return 1;
        }
    }
    return 0;
}

/**
  * Helper to determine whether matrix has legal row and column values
  * @param m given matrix
  * @return 1 if values are legal 0 otherwise
  */
int Matrix::col_row_check(const Matrix& m)const{

    if((m.get_cols() >= 0) && ((m.get_rows()) >= 0)){
            return 1;
    }
    return 0;
}

