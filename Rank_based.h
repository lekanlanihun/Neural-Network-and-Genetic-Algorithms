/* 
 * File:   Rank_based.h
 * Author: oal
 *
 * Created on 04 January 2014, 18:46
 */

#ifndef RANK_BASED_H
#define	RANK_BASED_H
#include "Roulette_Wheel.h"

class Rank_based:public Roulette_Wheel {
public:
    Rank_based();
    Rank_based(const Rank_based& orig);
    virtual ~Rank_based();
private:

};

#endif	/* RANK_BASED_H */

