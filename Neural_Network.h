/* 
 * File:   Neural_Network.h
 * Author: oal
 *
 * Created on 09 December 2013, 18:06
 */

#ifndef NEURAL_NETWORK_H
#define	NEURAL_NETWORK_H

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include "Roulette_Wheel.h"
using namespace std;

class Neural_Network {
public:
    Neural_Network(int *, int*, int *, double *, double *);
    Neural_Network(const Neural_Network& orig);
    void Init_Weights_Params(int *);

    void Step(double *, double*);
    void Compute_Hidden_States(double *);
    void Compute_Output_States(double *);
    void count_net_parameters( void );
    inline int get_num_inputs(void) {
        return Input_nodes;
    }

    inline int get_num_outputs(void) {
        return Output_nodes;
    }
    
    //double Sigmoid(double *);
    virtual ~Neural_Network();
private:
    double high, low;
    double ** input_weights_params;
    double ** hidden_weights_params;
    int Hidden_nodes;
    int Input_nodes;
    int Output_nodes;
    int num_parameters_required;
    double * desired_output;
//    int chromosome_neural;
    // double sigmoid_value;
    //  double * input_values_vector;
    double * hidden_activation_values_vector;
    double * Output_activation_values_vector;
    
//double desired_ouputs[4];
};

#endif	/* NEURAL_NETWORK_H */

