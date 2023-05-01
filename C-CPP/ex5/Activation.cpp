//
// Created by ElinorB on 15/12/2021.
//
#include "Activation.h"
#include <iostream>
#include <fstream>
#include <cmath>
#define DEFAULT_SIZE 1
#define NEGATIVE_SIZE "Error: negative matrix size!"
#define NON_VALID_ACT_TYPE "Error: non valid Activation type!"
#define NON_VALID_ACT_FUNC_INPUT "Error: cant use function on non vector input!"


/**
 * runs relu function on input matrix
 * @param m input matrix
 * @return new outcome matrix
 */
Matrix Activation::relu_function(Matrix& m){

    if(m.get_cols() != 1 || m.get_rows() < 1){
            Activation::print_err (NON_VALID_ACT_FUNC_INPUT);
            return m;
    }
    Matrix new_mat(m.get_rows(), m.get_cols());
    for(int i = 0; i < m.get_rows(); i++){
        if(m[i] < 0){
            new_mat[i] = 0;
        }
        else{
            new_mat[i] = m[i];
        }
    }
    return new_mat;
}

/**
 * runs softmax function on input matrix
 * @param m input matrix
 * @return new outcome matrix
 */
Matrix Activation::softmax_function( Matrix &m){

    if(m.get_cols() != 1 || m.get_rows() < 1){
        Activation::print_err (NON_VALID_ACT_FUNC_INPUT);
            return m;
    }
    float sum = 0;
    Matrix new_mat(m.get_rows(), m.get_cols());
    for(int i = 0; i < m.get_rows(); ++i){
        sum += std::exp (m[i]);
    }
    sum = 1/sum;
    for(int i = 0; i < m.get_rows(); ++i){
        new_mat[i] = sum*m[i];
    }
    return new_mat;
}

/**
 * operator () implementation
 * @param m matrix to activate
 */
Matrix Activation::operator()(Matrix& m){

    if((m.get_rows() < DEFAULT_SIZE) && (m.get_cols() < DEFAULT_SIZE)){
            Activation::print_err (NEGATIVE_SIZE);
            return m;
    }
    if(get_activation_type() == RELU){
            return relu_function (m);
    }
    if(get_activation_type() == SOFTMAX){
            return softmax_function (m);
        }
    else{
            print_err (NON_VALID_ACT_TYPE);
            return m;
    }
}
/**
* Helper function that prints given error message to std::err.
* @param error_msg the given message to be printed
*/
void Activation::print_err(std::string error_msg){
    std::cerr << error_msg << std::endl;
}
