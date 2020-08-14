/* 
 * File:   Roulette_Wheel.cpp
 * Author: oal
 * 
 * Created on 29 November 2013, 16:03
 */

#include "Roulette_Wheel.h"

Roulette_Wheel::Roulette_Wheel(int *pop_size_, int *Num_Bits_) {
    pop_size = *pop_size_;
    num_bits = *Num_Bits_;
    num_elite = 1;

    chromosome = new int *[pop_size];
    for (int i = 0; i < pop_size; i++) {
        chromosome[i] = new int[num_bits];
    }

    Temporary_Chromosome = new int *[pop_size];
    for (int i = 0; i < pop_size; i++) {
        Temporary_Chromosome[i] = new int[num_bits];
    }
    offsrings = new int *[pop_size]; 
    for (int i = 0; i < pop_size; i++) {
        offsrings[i] = new int[num_bits];
    }
    Init_Chromosome();

    fitness = new double[pop_size];
    Ranked_Fitness = new int[pop_size];
    fitness_probabilty = new double[pop_size];
    Cummulative_Probabilty_fitness = new double[pop_size];
    Father = new int[num_bits];
    Mother = new int[num_bits];
    index_cross_over_point = new int[(2 * num_bits) - 1];
}

void Roulette_Wheel::Init_Chromosome(void) {
    for (int p = 0; p < pop_size; p++) {
        for (int b = 0; b < num_bits; b++) {
            chromosome[p][b] = rand() % 2;
        }
    }
}

void Roulette_Wheel::Compute_fitness(double fit_ness, int individual) {

    fitness[individual] = fit_ness;

    //cout<<" fitness["<<individual<<"]"<<" "<<fitness[individual]<<endl;
}

void Roulette_Wheel::rank_fitness() {
    double temp_value;
    int tmp;
    double fitness_cpy[pop_size];
    for (int i = 0; i < pop_size; i++) {
        Ranked_Fitness[i] = i;
        fitness_cpy[i] = fitness[i];
    }

    for (int i = 0; i < pop_size - 1; i++) {
        for (int j = 0; j < pop_size - i - 1; j++) {
            if (fitness_cpy[j] > fitness_cpy[j + 1]) {
                temp_value = fitness_cpy[j];
                fitness_cpy[j] = fitness_cpy[j + 1];
                fitness_cpy[j + 1] = temp_value;
                /*
                tmp = j;
                Ranked_Fitness[j] = j+1;
                Ranked_Fitness[j+1]=tmp;
                 */

                temp_value = Ranked_Fitness[j];
                Ranked_Fitness[j] = Ranked_Fitness[j + 1];
                Ranked_Fitness[j + 1] = temp_value;

            }
        }
    }
    for (int i = 0; i < pop_size; i++) {
        fitness_probabilty[i] = (fitness[Ranked_Fitness[i]]) / fitness[Ranked_Fitness[pop_size - 1]];
    }

     cout << " BEST fitness[" << Ranked_Fitness[pop_size - 1] << "] = " << fitness[Ranked_Fitness[pop_size - 1]] << endl;
     getchar();
}

void Roulette_Wheel::Compute_Wheel() {
    Cummulative_Probabilty_fitness[0] = fitness_probabilty[0];
    for (int i = 1; i < pop_size; i++) {
        Cummulative_Probabilty_fitness[i] = Cummulative_Probabilty_fitness[i - 1] + fitness_probabilty[i];
    }
}

void Roulette_Wheel::Breeding_With_Mutation() {

    double r_value = 0.0;
    mutation_rate = 0.01;
    for (int individual = 0; individual < pop_size; individual++) {
        for (int j = 0; j < num_bits; j++) {
            r_value = rand() / (double(RAND_MAX) + 1);
            if (r_value < mutation_rate) {
                if (offsrings[individual][j] == 0) {
                    Temporary_Chromosome[individual][j] = 1;
                } else {
                    Temporary_Chromosome[individual][j] = 0;
                }
            } else {
                Temporary_Chromosome[individual][j] = offsrings[individual][j];
            }
        }


    }
    for (int i = 0; i < pop_size; i++) {
        for (int j = 0; j < num_bits; j++) {
            chromosome[i][j] = Temporary_Chromosome[i][j];
          
            ////               cout<<"  chromosome["<<i<<"]"<<"["<<j<<"]"<< chromosome[i][j]<<endl;
        }
    }
    //    
    //    double r_value = 0.0; 
    //    mutation_rate=0.01;
    //    for(int individual=0; individual<pop_size; individual++)
    //    {
    //        if(individual < num_elite){
    //            for(int j=0;j<num_bits;j++){
    //                 Temporary_Chromosome[individual][j]=chromosome[Ranked_Fitness[pop_size-1-individual]][j];
    //                 //cout << " " << fitness[Ranked_Fitness[pop_size-1-individual]] << endl;
    //                 //getchar();
    //             }
    //         }
    //         else{
    //            
    //            r_value = (rand()/(double(RAND_MAX)+1)) * Cummulative_Probabilty_fitness[pop_size-1];
    //            
    //            if((Cummulative_Probabilty_fitness[individual] > r_value)){
    //                for(int j=0;j<num_bits;j++){
    //                    r_value = rand()/(double(RAND_MAX)+1);
    //                    if (r_value < mutation_rate){
    //                        if(chromosome[Ranked_Fitness[individual]][j]==0){
    //                            Temporary_Chromosome[individual][j]=1;
    //                        }
    //                        else{
    //                            Temporary_Chromosome[individual][j]=0;
    //                        }     
    //                    }
    //                    else{
    //                        Temporary_Chromosome[individual][j]=chromosome[Ranked_Fitness[individual]][j];
    //                    }
    //                }
    //            }   
    //         }
    //    }  
    //    for(int i=0;i<pop_size;i++){
    //        for(int j=0;j<num_bits;j++){
    //              chromosome[i][j]= Temporary_Chromosome[i][j];
    ////               cout<<"  chromosome["<<i<<"]"<<"["<<j<<"]"<< chromosome[i][j]<<endl;
    //          }
    //      }

}

void Roulette_Wheel::Breeding() {
    double r_value = 0.0;
    int counter = 1;
 while(counter<=2){
      // r_value = (rand() / (double(RAND_MAX) + 1)) * Cummulative_Probabilty_fitness[pop_size - 1];
    for (int individual = 0; individual < pop_size; individual++) {
      // while(counter<=2){ 
        if (individual < num_elite) {
            for (int j = 0; j < num_bits; j++) {
                offsrings[individual][j] = chromosome[Ranked_Fitness[pop_size - 1 - individual]][j];
            }
        } 
        else {
           
             r_value = (rand() / (double(RAND_MAX) + 1)) * Cummulative_Probabilty_fitness[pop_size - 1];
//                cout<<"r_value="<<" "<<r_value<<endl;
//                getchar();
                if (Cummulative_Probabilty_fitness[individual] > r_value) {

                    
                        if (counter== 1) {
                            for (int j = 0; j < num_bits; j++) {
                                Father[j] = chromosome[Ranked_Fitness[individual]][j];

                                }
                        } else {
//                        if (counter== 2) {
                            for (int j = 0; j < num_bits; j++) {
                            Mother[j] = chromosome[Ranked_Fitness[individual]][j];
                            }
                        }
                }
                 
              
            
        
              Cross_Over(Father,Mother,individual);
        }
//           for(int j=0;j<num_bits;j++){
//           cout<<chromosome[Ranked_Fitness[individual]][j]<<endl;
//           getchar();
      
      //  }
        // counter++;
    //   }  
    }
 counter++;
           
    }
//    for(int i=0;i<num_bits;i++){
//        cout<<"Father["<<i<<" "<<Father[i]<<endl;
//        cout<<"Mother["<<i<<" "<<Mother[i]<<endl;
//        getchar();
//    }
    
    
}

void Roulette_Wheel::Cross_Over(int *ptrFather, int *ptrMother, int individuals) {
    int cross_over_point;
    cross_over_point = rand() % num_bits + 1;

    // cross_over_point= rand()%((2*num_bits)-1)+1;
    // cross_over_point= 2*(1+rand()%((2*num_bits)-1)+1);
    for (int j = 0; j < cross_over_point; j++) {
        offsrings[individuals][j] = ptrFather[j];
    }
    
    for (int j = cross_over_point; j < num_bits; j++) {
        offsrings[individuals][j] = ptrMother[j];

    }

}



Roulette_Wheel::~Roulette_Wheel() {
    for (int i = 0; i < pop_size; i++) {
        delete[] Temporary_Chromosome[i];
    }
    delete[] Temporary_Chromosome;

    for (int i = 0; i < pop_size; i++) {
        delete[] chromosome[i];
    }
    delete[] chromosome;
    for (int i = 0; i < pop_size; i++) {
        delete[] offsrings[i];
    }
    delete[] offsrings;
    delete [] fitness;
    delete[] fitness_probabilty;
    delete[] Ranked_Fitness;
    delete[] Cummulative_Probabilty_fitness;
    delete [] Father;
    delete [] Mother;
    delete []index_cross_over_point;
}
