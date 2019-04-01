//
//  keyed_bag.cpp
//  Lab4_keyBag
//
//  Created by Liying Liang  on 1/31/19.
//  Copyright © 2019 Liying_Liang. All rights reserved.
//
//  Invariants: The total items have been inserted have to be less than CAPACITY:       used<CAPACITY, thus ensure size()<CAPACITY
//  The bag can't have negative item, thus used>=0

#include <iostream>
#include <cassert>
#include "keyed_bag.hpp"

namespace coen79_lab4{
    keyed_bag::keyed_bag( ){
        used=0;
    }
    
    void keyed_bag::erase(){
        for (keyed_bag::size_type i=0; i<CAPACITY; i++){
            keys[i]=" ";
            data[i]=0;
        }
        used=0;
    }
    
    bool keyed_bag::erase(const key_type& key){
        keyed_bag::size_type index=0;
        while(keys[index]!=key&&index<used){
            index++;
        }
        
        if(index==used){return false;}
        
        for (keyed_bag::size_type i=index; i<used&&(i+1)<CAPACITY; i++){
            keys[i]=keys[i+1];
            data[i]=data[i+1];
        }
        used--;
        return true;
    }
    
    void keyed_bag::insert(const value_type& entry, const key_type& key){
        assert(size()<CAPACITY && has_key(key)==false);
        keys[used]=key;
        data[used]=entry;
        used++;
    }
    
    void keyed_bag::operator +=(const keyed_bag& addend){
        assert(size( ) + addend.size( ) <= CAPACITY&&hasDuplicateKey(addend)==false);
        size_type temp=addend.size();
        for (keyed_bag::size_type i=0; i<temp; i++){
            keys[used]=addend.keys[i];
            data[used]=addend.data[i];
            used++;
        }
    }
    
    bool keyed_bag::has_key(const key_type& key) const{
        keyed_bag::size_type index=0;
        while(index<used&&keys[index]!=key){
            index++;
        }
        
        if(index==used){return false;}
        
        return true;
    }
    
    
    keyed_bag::value_type keyed_bag::get(const key_type& key) const{
        assert(has_key(key));
        keyed_bag::size_type index=0;
        while(index<used&&keys[index]!=key){
            index++;
        }
        return data[index];
    }
    
    keyed_bag::size_type keyed_bag::count(const value_type& target) const{
        size_type count=0;
        for (keyed_bag::size_type i=0; i<used; i++){
            if(data[i]==target){
                count++;
            }
        }
        return count;
    }
    
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
        bool has=false;
        for (keyed_bag::size_type i=0; i<used; i++){
            if(has_key(otherBag.keys[i])){
                has=true;
                break;
            }
        }
        return has;
    }
    
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
        assert(b1.size( ) + b2.size( ) <= keyed_bag::CAPACITY);
        assert(b1.hasDuplicateKey(b2)==false);
        keyed_bag b;
        b+=b1;
        b+=b2;
        return b;
    }
    
}
