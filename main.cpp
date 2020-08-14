/* 
 * File:   main.cpp
 * Author: oal
 *
 * Created on 29 November 2013, 16:01
 */

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "Roulette_Wheel.h"
#include "Neural_Network.h"

#define EVOLUTION true

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {



    int root_seed = 656987;
    srand(root_seed);
    int pop_size = 100, num_bits = 72;
    double high = 10.0, low = -10.0;
    int input_nodes = 2, hidden_nodes = 2, output_nodes = 1;

    //double sigmoid_val;
    Roulette_Wheel ga(&pop_size, &num_bits);

    Neural_Network neural_object(&input_nodes, &hidden_nodes, &output_nodes, &high, &low );
    double inputs[4][neural_object.get_num_inputs()];
    double outputs[neural_object.get_num_outputs()];
    double desired_ouputs[4];
//  neural_object.Compute_Hidden_States(inputs);
//  neural_object.Compute_Output_States(outputs);

    //Definition of the input vector
    //for(int s = 0; s < 4; s++){
    //for (int i = 0; i < neural_object.get_num_inputs(); i++) {
    inputs[0][0] = 0;
    inputs[0][1] = 0;
    inputs[1][0] = 1;
    inputs[1][1] = 0;
    inputs[2][0] = 0;
    inputs[2][1] = 1;
    inputs[3][0] = 1;
    inputs[3][1] = 1;
    ////        
    desired_ouputs[0] = 0;
    desired_ouputs[1] = 1;
    desired_ouputs[2] = 1;
    desired_ouputs[3] = 0;

    //}
   // if( EVOLUTION ){
    for (int generations = 0; generations <1000; generations++) {
       // cerr << " Gen = " << generations << endl;
        for (int ind = 0; ind < ga.get_popn_size(); ind++) {
          double  fitness = 0.0;

            neural_object.Init_Weights_Params(ga.get_genes(ind));
           
            for (int steps = 0; steps < 4; steps++) { //step 1 input 0-0 output 0; step 2 input 0-1 output 1; step 3 input 1-0 output 1; step 4 input 1-1 output 0  
                neural_object.Step(inputs[steps], outputs);
                fitness += 1.0- fabs(desired_ouputs[steps] - outputs[0]);
            }//end of steps
            //fitness /= 4;
            ga.Compute_fitness(fitness,ind); //call a ga function to assign fitness
            
        }//end of individuals
        ga.rank_fitness();
        ga.Compute_Wheel();
        ga.Breeding();
    
        //ga.dump_genes();)
        ga.Breeding_With_Mutation(); //call a ga function to do breeding
    }//end of generations
  //  }
//    else {
//        //int generations = 999;
//    //ga.load_chromosomes( generations ); 
//        for (int ind = 0; ind < ga.get_popn_size(); ind++) {
//          double  fitness = 0.0;
//            neural_object.Init_Weights_Params(ga.get_genes(ind));
//           
//            for (int steps = 0; steps < 4; steps++) { //step 1 input 0-0 output 0; step 2 input 0-1 output 1; step 3 input 1-0 output 1; step 4 input 1-1 output 0  
//                neural_object.Step(inputs[steps], outputs);
//                fitness += 1.0- fabs(desired_ouputs[steps] - outputs[0]);
//                //print fitness and outputs
//            }//end of steps            
//        }
//    }
    return 0;

}



