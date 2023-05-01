//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"
#include "Matrix.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit
{
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork{

//***********************************//
//******** PRIVATE MEMBERS **********//
//***********************************//
 private:
  Matrix* _weights;
  Matrix* _biases;
  digit* _dig;

//***********************************//
//******** PUBLIC MEMBERS ***********//
//***********************************//
 public:
  /**
   * Constructor
   */
  MlpNetwork(Matrix* weights_arr, Matrix* bias_arr);

//***********************************//
//*********** OPERATORS *************//
//***********************************//
/**
 * Operator () implementation
 * @param input input matrix
 * @return digit outcome
 */
  digit operator() (Matrix& input);
};

#endif // MLPNETWORK_H
