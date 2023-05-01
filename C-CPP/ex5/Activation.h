//Activation.h


#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <string>

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

class Activation {

//***********************************//
//******** PRIVATE MEMBERS **********//
//***********************************//
 private:
  ActivationType _act_type;

  /**
   * runs relu function on input matrix
   * @param m input matrix
   * @return new outcome matrix
   */
  Matrix relu_function(Matrix& m);

  /**
   * runs softmax function on input matrix
   * @param m input matrix
   * @return new outcome matrix
   */
  Matrix softmax_function(Matrix &m);

  /**
   * Helper function that prints given error message to std::err.
   * @param error_msg the given message to be printed
   */
  void print_err(std::string error_msg);


//***********************************//
//******** PUBLIC MEMBERS ***********//
//***********************************//
 public:
  /**
   * constructor for Activation object
   * @param _act_type objects activation type
   */
  Activation (ActivationType _act_type) : _act_type (_act_type){}

  /**
   * Getter for activation type
   * @return this object's activation type
   */
  ActivationType get_activation_type () const {return _act_type;}

//***********************************//
//*********** OPERATORS *************//
//***********************************//
/**
 * operator () implementation
 * @param m matrix to activate
 */
  Matrix operator()(Matrix& m);

};
#endif //ACTIVATION_H
