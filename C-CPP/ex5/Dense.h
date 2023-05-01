//
// Created by yuval on 01-Oct-21.
//

#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h"

class Dense{


//***********************************//
//******** PRIVATE MEMBERS **********//
//***********************************//
 private:
  Matrix _weights;
  Matrix _bias;
  ActivationType _act_type;

//***********************************//
//******** PUBLIC MEMBERS ***********//
//***********************************//
 public:
  /**
   * Constructor
   * @param weights Matrix with weights
   * @param bias Matrix with biases
   * @param act_type Activation type
   */
  Dense(Matrix weights, Matrix bias, ActivationType act_type): _weights(weights),
  _bias(bias), _act_type(act_type){}

  /**
   * Getter for layer's weights
   * @return Matrix with weights
   */
  Matrix get_weights()const{return _weights;}

  /**
   * Getter for layer's bias
   * @return bias Matrix
   */
  Matrix get_bias()const{return _bias;}

  /**
   * Getter for Activation type
   * @return layers activation type
   */
  ActivationType get_activation()const{return _act_type;}

//***********************************//
//*********** OPERATORS *************//
//***********************************//

/**
 * Operator () implementation
 * @return output matrix after layer was applied
 */
  Matrix operator() (Matrix& input_mat);
};

#endif //DENSE_H
