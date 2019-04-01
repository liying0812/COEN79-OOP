//
//  random.cpp
//  Lab2_2
//
//  Created by Liying Liang  on 1/18/19.
//  Copyright © 2019 Liying_Liang. All rights reserved.
//

#include "random.hpp"
using namespace coen79_lab2;
using namespace std;

namespace coen79_lab2
{

rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus){
    this->seed=seed;
    this->multiplier=multiplier;
    this->increment=increment;
    this->modulus=modulus;
}


void rand_gen::set_seed(int new_seed){
    seed=new_seed; 
}

int rand_gen::next(){
    seed=(multiplier*seed+increment)%modulus;
    return seed;
}

void rand_gen::print_info(){
    cout<<"seed: "<<seed<<endl;
    cout<<"multiplier: "<<multiplier<<endl;
    cout<<"increament: "<<increment<<endl;
    cout<<"modulus: "<<modulus<<endl;
}
}
