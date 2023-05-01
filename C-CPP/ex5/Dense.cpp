//
// Created by ElinorB on 15/12/2021.
//
#include "Dense.h"
#include "Matrix.h"

/**
 * Operator () implementation
 * @return output matrix after layer was applied
 */
Matrix Dense::operator() (Matrix& input_mat){

    Activation activation(_act_type);
    Matrix temp = (_weights*input_mat)+_bias;
    return activation(temp);
}
