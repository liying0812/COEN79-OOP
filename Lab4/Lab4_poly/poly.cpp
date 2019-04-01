//
//  poly.cpp
//  Lab4_poly
//
//  Created by Liying Liang  on 2/1/19.
//  Copyright © 2019 Liying_Liang. All rights reserved.
//  Invariants: The largest degree is 29, thus current_degree<=MAXIMUM_DEGREE and exponent<=MAXIMUM_DEGREE
//  Thus, ensure function degree()<MAXIMUM_DEGREE

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly.hpp"

namespace coen79_lab4{
    
    //MEMBER FUNCTION
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coeff[exponent]=coefficient;
        update_current_degree();
    }
    
    
    void polynomial::add_to_coef(double amount, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coeff[exponent]+=amount;
        update_current_degree();
    }
    
    void polynomial::clear( ){
        for (unsigned int i=0; i<CAPACITY; i++){
            coeff[i]=0.0;
        }
    }
    
    //HELPER MEMBER FUNCTION
    void polynomial::update_current_degree(){
        unsigned int max_index=0;
        if(coeff[29]!=0){
            max_index=29;
        }
        else{
            for (unsigned int i=0; i<MAXIMUM_DEGREE; i++){
                if((coeff[i+1]!=0)&&coeff[i+1]>coeff[i]){
                    max_index=i+1;
                }
            }
        }
        current_degree=max_index;
    }
    
    //const member function
    polynomial polynomial::antiderivative( ) const{
        assert(degree()<MAXIMUM_DEGREE);
        polynomial p;
        for (unsigned int i=1; i<CAPACITY; i++){
            p.coeff[i]=coeff[i-1]/(i);  //think more??
        }
        p.coeff[0]=0;
        return p;
    }
    
    double polynomial::coefficient(unsigned int exponent) const{
        if(exponent>MAXIMUM_DEGREE){
            return 0;
        }
        return coeff[exponent];
    }
    
    //?????
    double polynomial::definite_integral(double x0, double x1) const{
        polynomial res = antiderivative();
        
        return res.eval(x1) - res.eval(x0);
    }
    
    unsigned int polynomial::degree( ) const{
        if (current_degree==0){
            return 0;
        }
        return current_degree;
    }
    
    polynomial polynomial::derivative( ) const{
        polynomial p;
        for (unsigned int i=0; i<CAPACITY&&(i+1)<CAPACITY; i++){
            p.coeff[i]=coeff[i+1]*(i+1);
        }
        return p;
    }
    
    double polynomial::eval(double x) const{
        double sum;
        if ((is_zero())||((x==0)&&(coeff[0])==0)){
            sum=0.0;
        }
        else{
            sum=coeff[0];
            for (unsigned int i=1; i<CAPACITY; i++){
                sum+=coeff[i]*pow(x,i);
            }
        }
        return sum;
    }
    
    bool polynomial::is_zero( ) const{
        for (unsigned int i=0; i<CAPACITY; i++){
            if (coeff[i]!=0){
                return false;
                break;
            }
        }
        return true; 
    }
    
    
    unsigned int polynomial::next_term(unsigned int e) const{
        unsigned int index=0;
        for (unsigned int i=e+1; i<CAPACITY; i++){
            if(coeff[i]!=0){
                index=i;
                break;
            }
        }
        return index; 
    }
    
    unsigned int polynomial::previous_term(unsigned int e) const{
        unsigned int index=0;
        if(e==0){
            index=UINT_MAX;
        }
        
        else{
            for (unsigned int i=e-1; i>0; i--){
                if(coeff[i]!=0){
                    index=i;
                    break;
                }
            }
        
            if((index==0)&&(coeff[0]!=0)){
                index=0;
            }
        }
    
        return index;
    }

    
    //CONSTANT OPERATOR
    double polynomial::operator( ) (double x) const{
        return eval(x);
    }
    
    //NON-MEMBER FUNCTION
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        polynomial p;
        for (unsigned int i=0; i<30; i++){
            p.assign_coef((p1.coefficient(i)+p2.coefficient(i)), i);
        }
        
        p.update_current_degree();
        return p;
    }
    
    polynomial operator -(const polynomial& p1, const polynomial& p2){
        polynomial p;
        for (unsigned int i=0; i<30; i++){
            p.assign_coef((p1.coefficient(i)-p2.coefficient(i)), i);
        }
         p.update_current_degree();
        return p;
    }
    
    polynomial operator *(const polynomial& p1, const polynomial& p2){
        assert(p1.degree( ) + p2.degree( ) <= 29); //can't use maximum_degree
        polynomial p;

        for (unsigned int i=0; i<30; i++){
            for(unsigned int j=0; j<30&&(i+j)<30; j++){
                if(p1.coefficient(i)!=0&&p2.coefficient(j)!=0){
                    if(p.coefficient(i+j)==0){
                        p.assign_coef((p1.coefficient(i)*p2.coefficient(j)), i+j);
                    }
                    else{
                        double tmp=p.coefficient(i+j);
                        p.assign_coef((tmp+p1.coefficient(i)*p2.coefficient(j)), i+j);
                    }
                }
            }
        }
        
        p.update_current_degree();
        return p;
    }
    
    std::ostream& operator << (std::ostream& out, const polynomial& p){
        unsigned int max_index=0;
        for (unsigned int i=29; i>0; i--){
            if(p.coefficient(i)!=0){
                max_index=i;
                break;
            }
        }
        
        
        if(p.is_zero()){
            out<<0.0;
        }
        
        else{
            if(p.coefficient(max_index)!=0&&max_index!=0&&max_index!=1){
                if(p.coefficient(max_index)<0){
                    out<<"-"<<"  "<<(-1)*p.coefficient(max_index)<<"x"<<"^"<<max_index;
                }
                else{
                    out<<p.coefficient(max_index)<<"x"<<"^"<<max_index;
                }
            }
        
            //p.degree();
            for (unsigned int i=max_index-1; i>1; i--){
                if (p.coefficient(i)!=0){
                    if(p.coefficient(i)>0){
                        out<<" "<<"+"<<" "<<p.coefficient(i)<<"x"<<"^"<<i;
                    }
                    else{
                        out<<" "<<"-"<<" "<<(-1)*p.coefficient(i)<<"x"<<"^"<<i;
                    }
                }
            }
        
            if(p.coefficient(1)!=0){
                if(max_index!=1){
                if (p.coefficient(1)>0){
                    out<<" "<<"+"<<" "<<p.coefficient(1)<<"x";
                }
                else{
                    out<<" "<<"-"<<" "<<(-1)*p.coefficient(1)<<"x";
                }
                }
                else if(max_index==1){
                    if (p.coefficient(1)>0){
                        out<<p.coefficient(1)<<"x";
                    }
                    else{
                        out<<"-"<<" "<<(-1)*p.coefficient(1)<<"x";
                    }
                }
            }
        
            if(p.coefficient(0)!=0){
                if(max_index!=0){
                    if (p.coefficient(0)>0){
                        out<<" "<<"+"<<" "<<p.coefficient(0);
                        //std::cout<<"max_index:"<<max_index;
                    }
                    else{
                        out<<" "<<"-"<<" "<<(-1)*p.coefficient(0);
                    }
                }
                else if(max_index==0){
                    if (p.coefficient(0)>0){
                        out<<p.coefficient(0);
                    }
                    else{
                        out<<"-"<<"  "<<(-1)*p.coefficient(0)<<" ";
                    }
                }
            }
        }
        return out;
    }
     
}

