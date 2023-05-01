
#include "MlpNetwork.h"

//***********************************//
//******** PUBLIC MEMBERS ***********//
//***********************************//
/**
 * Constructor
 */
MlpNetwork::MlpNetwork(Matrix* weights_arr, Matrix* bias_arr){

    _weights = new Matrix[4];
    _biases = new Matrix[4];
    for(int i = 0; i < 4; i++){
        _weights[i](weights_dims[i].rows, weights_dims[i].cols);
        _biases[i](bias_dims[i].rows, bias_dims[i].cols);
        _weights[i] = weights_arr[i];
        _biases[i] = bias_arr[i];
    }
    _dig = new digit();
}

//***********************************//
//*********** OPERATORS *************//
//***********************************//
/**
 * Operator () implementation
 * @param input input matrix
 * @return digit outcome
 */
digit MlpNetwork::operator() (Matrix& input){

    Activation relu_activation(RELU);
    Activation softmax_activation(SOFTMAX);
    Dense first_layer(_weights[0], _biases[0], relu_activation.get_activation_type());
    Dense second_layer(_weights[1], _biases[1], relu_activation.get_activation_type());
    Dense third_layer(_weights[2], _biases[2], relu_activation.get_activation_type());
    Dense fourth_layer(_weights[3], _biases[3], softmax_activation.get_activation_type());

    Matrix output = first_layer(input);
    Matrix output_temp = second_layer(output);
    output = third_layer(output_temp);
    output_temp = fourth_layer(output);
    float probability = 0;
    unsigned int index = 0;
    for(int i = 0; i < output_temp.get_rows()*output_temp.get_cols(); ++i){
        if(output_temp[i] > probability){
            probability = output_temp[i];
            index = i;
        }
    }
    _dig->value = index;
    _dig->probability = probability;
    return *_dig;

}