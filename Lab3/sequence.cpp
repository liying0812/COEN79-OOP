//
//  sequence.cpp
//  Lab3
//
//  Created by Liying Liang  on 1/24/19.
//  Copyright © 2019 Liying_Liang. All rights reserved.

//  Invariants: The number of items should be always less than the size that array can holds: used<CAPACITY
//              To make sure the current item is "valid": current_index<used

#include<iostream>
#include<cassert>
#include<cmath>
#include "sequence.hpp"
using namespace std;

namespace coen79_lab3 {
    
    sequence::sequence( ){
        for (sequence::size_type i=0; i<CAPACITY; i++){
            data[i]=0;
        }
        used=0;
        current_index=0;
    }
    
    void sequence::start(){
        current_index=0;
    }
    
    void sequence::end(){
        current_index=used-1;
    }
    
    void sequence::last(){
        current_index=CAPACITY-1;
    }
    
    void sequence::advance(){
        assert(is_item());
        current_index++;
    }
    
    void sequence::retreat(){
        if(current_index>0){
            current_index--;
        }
    }
    
    
    void sequence::insert(const value_type& entry){
        assert(size()<CAPACITY);
        std::copy(data+current_index, data+used,data+current_index+1);
        data[current_index]=entry;
        used++;
    }
    
    
    void sequence::insert_front(const value_type& entry){
        assert(size()<CAPACITY);
        std::copy(data, data+used, data+1);
        data[0]=entry;
        used++;
        current_index=0;
    }
    
    void sequence::attach(const value_type& entry){
        assert(size()<CAPACITY);
        if(used==0){
            data[used]=entry;
            used++;
        }
        std::copy(data+current_index+1, data+used, data+1);
        data[current_index+1]=entry;
        current_index++;
        used++;
    }
    
    void sequence::attach_back(const value_type& entry){
        assert(size()<CAPACITY);
        data[used]=entry;
        used++;
        current_index=used-1;
    }
    
    void sequence::remove_current(){
        assert(is_item());
        for (sequence::size_type i=current_index; i<used&&(i+1)<sequence::CAPACITY; i++){
            data[i]=data[i+1];
        }
        used--;
    }
    
    void sequence::remove_front(){
        assert(is_item());
        for(sequence::size_type i=0; i<used&&(i+1)<sequence::CAPACITY; i++){
            data[i]=data[i+1];
        }
        used--;
        current_index=0;
    }
    
    
    bool sequence::is_item( ) const{
        return current_index<used;
    }
    
    sequence::value_type sequence::current() const{
        assert(is_item());
        return data[current_index];
    }
    
    sequence::value_type sequence::operator[](int index) const{
        assert(index<used);
        return data[index];
    }
    
    double sequence::mean() const{
        sequence::value_type sum=0.0;
        for (sequence::size_type i=0; i<used; i++){
            sum+=data[i];
        }
        return (double)sum/used;
    }
    
    double sequence::standardDeviation() const{
        sequence::value_type sum=0.0;
        sequence::value_type mean_val=mean();
        for (sequence::size_type i=0; i<used; i++){
            sum+=pow((data[i]-mean_val),2);
        }
        return (double)sqrt(sum/used);
    }
    
    
    
    sequence operator+(sequence& lhs, sequence& rhs){
        assert((lhs.size()+rhs.size())<sequence::CAPACITY);
        sequence s=sequence();
        for (sequence::value_type i=0; i<lhs.size(); i++){
            s.attach_back(lhs[i]);
        }
        sequence::value_type iter=0;
        for (sequence::value_type j=lhs.size(); j<lhs.size()+rhs.size(); j++){
            s.attach_back(rhs[iter]);
            iter++;
        }
        return s;
    }
    
    sequence operator+=(sequence& lhs, sequence& rhs){
        lhs=lhs+rhs;
        return lhs;
    }
    
    sequence::value_type summation(const sequence &s){
        sequence::value_type sum=0;
        for (int i=0; i<s.size(); i++){
            sum+=s[i];
        }
        return sum;
    }
    
}
