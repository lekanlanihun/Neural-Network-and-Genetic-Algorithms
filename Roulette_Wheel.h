/* 
 * File:   Roulette_Wheel.h
 * Author: oal
 *
 * Created on 29 November 2013, 16:03
 */

#ifndef ROULETTE_WHEEL_H
#define	ROULETTE_WHEEL_H

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include "Neural_Network.h"
using namespace std;

class Roulette_Wheel {
public:

    Roulette_Wheel() {
    }
   
    Roulette_Wheel(const Roulette_Wheel& orig);
    Roulette_Wheel(int *, int *);

    void Init_Chromosome(void);
    void rank_fitness();

    void Compute_fitness(double fitness, int individual);

    void Compute_Wheel();

    void Breeding_With_Mutation();
    
    void Breeding();
    
    void Cross_Over(int*,int *,int);

    inline int get_popn_size(void) {
        return pop_size;
    }

    int get_num_bits(void) {
        return num_bits;
    }

    int* get_genes(int ind) {
        
        return chromosome[ind];      
    }
    
    //   void print_chromosomes();


    virtual ~Roulette_Wheel();

private:
    int individuals;
    int pop_size;
    int num_bits;
    int ** chromosome;
    int ** Temporary_Chromosome;
    double *fitness;
    int * Ranked_Fitness;
    double *fitness_probabilty;
    double *Cummulative_Probabilty_fitness;
    int Total_Sum_fitness;
    double mutation_rate;
    int num_elite;
    int * Father;
    int * Mother;
    int ** offsrings;
    int * index_cross_over_point;
    //int chromosome[pop_size][num_bits];  

};

#endif	/* ROULETTE_WHEEL_H */

