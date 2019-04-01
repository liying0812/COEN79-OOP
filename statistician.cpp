//
//  statistician.cpp
//  Lab_2
//
//  Created by Liying Liang  on 1/18/19.
//  Copyright © 2019 Liying_Liang. All rights reserved.
//

#include <iostream>
#include "statistician.hpp"
using namespace coen79_lab2;
using namespace std;

namespace coen79_lab2
{
    
statistician::statistician( ){
    count=0;
    total=0.0;
    tiniest=0.0;
    largest=0.0;
}

void statistician::next(double r){
    count++;
    if (count>1){
        if(r<tiniest){
            tiniest=r;
        }
        else if(r>largest){
            largest=r;
        }
    }
    else if(count==1){
        tiniest=r;
        largest=r; 
    }
    total+=r;
}

void statistician::reset( ){
    count=0;
    total=0.0;
    tiniest=0.0;
    largest=0.0;
}


double statistician::mean( ) const{
    assert(count>0);
    return total/count;
}

double statistician::minimum( ) const{
    assert(count>0);
    return tiniest;
}

double statistician::maximum( ) const{
    assert(count>0);
    return largest;
}



// FRIEND FUNCTIONS
statistician operator + (const statistician& s1, const statistician& s2){
    statistician s3=statistician();
    s3.count=s1.count+s2.count;
    s3.total=s1.total+s2.total;
    if(s1.tiniest>s2.tiniest){
        s3.tiniest=s2.tiniest;
    }
    else{
        s3.tiniest=s1.tiniest;
    }
    
    if(s1.largest>s2.largest){
        s3.largest=s1.largest;
    }
    else{
        s3.largest=s2.largest;
    }
    
    return s3;
}

statistician operator * (double scale, const statistician& s){
    statistician s3=s;
    s3.total=s.total*scale;
    if(scale>=0){
        s3.tiniest=s.tiniest*scale;
        s3.largest=s.largest*scale;
    }
    else{
        s3.largest=s.tiniest*scale;
        s3.tiniest=s.largest*scale;
    }
    return s3;
}


//non-member function
bool operator ==(const statistician& s1, const statistician& s2){
    return ((s1.length()==0&&s2.length()==0)||(s1.length()==s2.length()&&s1.sum()==s2.sum()&&s1.mean()==s2.mean()&&s1.minimum()==s2.minimum()&&s1.maximum()==s2.maximum())); 
}
}
