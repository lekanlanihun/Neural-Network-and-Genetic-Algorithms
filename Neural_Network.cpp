/* 
 * File:   Neural_Network.cpp
 * Author: oal
 * 
 * Created on 09 December 2013, 18:06
 */

#include "Neural_Network.h"

Neural_Network::Neural_Network(int *input_nodes, int *hidden_nodes, int *output_nodes, double *high_, double *low_) {
    Input_nodes = *input_nodes;
    Hidden_nodes = *hidden_nodes;
    Output_nodes = *output_nodes;
    high = *high_;
    low = *low_;
 count_net_parameters();
 
    input_weights_params = new double *[Hidden_nodes];
    for (int i = 0; i < Hidden_nodes; i++) {
        input_weights_params[i] = new double [Input_nodes + 1];
    }

    hidden_weights_params = new double *[Output_nodes];
    for (int i = 0; i < Output_nodes; i++) {
        hidden_weights_params[i] = new double [Hidden_nodes + 1];

    }

    //    input_values_vector = new double[Input_nodes];
    hidden_activation_values_vector = new double[Hidden_nodes];
    Output_activation_values_vector = new double[Output_nodes];
    //    chromosome_neural=new int[9];

}

Neural_Network::Neural_Network(const Neural_Network& orig) {
}

void Neural_Network::count_net_parameters( void ){
     num_parameters_required=0;
     
    for(int i = 0; i < Input_nodes; i++){
     for (int j = 0; j < Hidden_nodes; j++) {   
         num_parameters_required++;
     }
     }
     
    for (int j = 0; j < Hidden_nodes; j++) {
        for (int i = 0; i <Output_nodes; i++) {
            num_parameters_required++;
        }
        }
    
     for (int j = 0;j < Hidden_nodes; j++) 
         num_parameters_required++;
    
        for (int i = 0; i < Output_nodes; i++)
            num_parameters_required++;   
}


//Initialising the network weights

void Neural_Network::Init_Weights_Params(int *genes) {
    //transform each binary chromosome into integer
    //transform each integer chromosome into real in [0, 1] ,i.e by dividing the integer value by 255
    //scale the weights gotten from above in [-x, +x] for each chromosome or gene.
  
    double param[num_parameters_required];
    for (int i = 0; i < num_parameters_required; i++) {
        param[i] = 0.0;
        for (int j = 0; j < 8; j++) {
           param[i] += (genes[j + ((8)*i)])*pow(2,j);
        }        
      param[i] = (param[i]/255.0);
      param[i] = (param[i]*(high-low)) + low;
    }
    
    int counter = 0;
    for (int i = 0; i < Hidden_nodes; i++) {
        for (int j = 0; j <= Input_nodes; j++) {
                input_weights_params[i][j] = param[counter++];
//                                cout << "Input_Weight_Params[" << i << "][" << j << "]" << " " << input_weights_params[i][j] << endl;
        }
    }
        for (int i = 0; i < Output_nodes; i++) {
        for (int j = 0; j <= Hidden_nodes; j++) {
                hidden_weights_params[i][j] = param[counter++];
                                //cout << " hidden_weights_params[" << i << "][" << j << "]" << " " << hidden_weights_params[i][j] << endl;
        }
        }
    
    if(counter != num_parameters_required){
        cout << " HELP THRE IS A BUG counter = "<< counter << " num_param = " << num_parameters_required << endl;
        exit(0);
    }

}

void Neural_Network::Step(double *input_values_vector, double *outputs) {

    Compute_Hidden_States(input_values_vector);
    Compute_Output_States(outputs);

}

/**
 * 
 * @param input_values_vector
 */
void Neural_Network::Compute_Hidden_States(double *input_values_vector) {//These must be number in between [0, 1]
        //for (int j = 0; j < Input_nodes; j++)
    //cerr << " input " << input_values_vector[j] << endl;
        //getchar();
    
    for (int i = 0; i < Hidden_nodes; i++) {
        hidden_activation_values_vector[i] = input_weights_params[i][Input_nodes];

        for (int j = 0; j < Input_nodes; j++) {
            hidden_activation_values_vector[i] += (input_weights_params[i][j])*(input_values_vector[j]);
        }
        hidden_activation_values_vector[i] = (1.0) / (1.0 + exp(-hidden_activation_values_vector[i]));
        //        cout << " hidden_activation_values_vector[" << i << "]" << " " << hidden_activation_values_vector[i] << endl;
        //        getchar();
    }
}

void Neural_Network::Compute_Output_States(double *outputs) {
    for (int i = 0; i < Output_nodes; i++) {
        Output_activation_values_vector[i] = hidden_weights_params[i][Hidden_nodes];

        for (int j = 0; j < Hidden_nodes; j++) {
            Output_activation_values_vector[i] += (hidden_weights_params[i][j])*(hidden_activation_values_vector[j]);

        }
        Output_activation_values_vector[i] = (1.0) / (1.0 + exp(-Output_activation_values_vector[i]));
        outputs[i] = Output_activation_values_vector[i];

                //cout << " outputs[" << i << "]" << " " << outputs[i] << endl;
                //getchar();
    }
}

Neural_Network::~Neural_Network() {

    for (int i = 0; i < Hidden_nodes; i++) {
        delete [] input_weights_params[i];
    }
    delete [] input_weights_params;

    for (int i = 0; i < Output_nodes; i++) {

        delete [] hidden_weights_params[i];
    }
    delete [] hidden_weights_params;

    //    delete [] input_values_vector;

    delete [] hidden_activation_values_vector;
    delete [] Output_activation_values_vector;

}

