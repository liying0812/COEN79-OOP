//
//  mystring.cpp
//  Lab5
//
//  Created by Liying Liang  on 2/7/19.
//  Copyright © 2019 Liying_Liang. All rights reserved.
//  Invariants:
//  1. string is stored as null-terminated string in the dynamic array that characters point to
//  2. The total length of dynamic array is stored in variable allocated
//  3. The total number of characters prior to null-terminated character is stored in current_length, and should be always less than allocated

#include <iostream>
#include <cstring>
#include "mystring.hpp"
using namespace coen79_lab5;

namespace coen79_lab5{
    
    string::string(const char str[]){
        current_length=strlen(str);
        allocated=current_length+1;
        characters=new char[allocated];
        strncpy(characters, str, current_length);
    }
    
    string::string(char c){
        current_length=1;
        allocated=current_length+1;
        characters=new char[allocated];
        characters[0]=c;
    }
    
    string::string(const string& source){
        current_length=source.length();
        allocated=current_length+1;
        characters=new char[allocated];
        for(size_t i=0; i<current_length; i++){
            characters[i]=source[i];
        }
    }
    
    string::~string( ){
        delete [] characters;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend){
        reserve(current_length+addend.length()+1);
        size_t pos=0;
        for(size_t i=strlen(characters); i<current_length+addend.length(); i++){
            characters[i]=addend[pos];
            pos++;
        }
        current_length=current_length+addend.length();
        characters[strlen(characters)]='\0';
    }
    
    void string::operator +=(const char addend[]){
        reserve(current_length+strlen(addend)+1);
        strncat(characters, addend, allocated-current_length);
        current_length=allocated-1;
    }
    
    void string::operator +=(char addend){
        reserve(current_length+1);
        current_length=current_length+1;
        characters[current_length-1]=addend;
        characters[current_length]='\0';
    }
    
    void string::reserve(size_t n){
        if(allocated==n){return;}
        if(n<allocated){
            n=allocated;
        }
        char* temp=new char[n];
        std::copy(characters, characters+current_length, temp);
        delete [] characters;
        characters=temp;
        allocated=n+1;
    }
    
    string& string::operator =(const string& source){
        if (this==&source){return *this;}
        if(allocated!=source.allocated){
            char* new_characters=new char[source.allocated];
            delete[]characters;
            characters=new_characters;
            allocated=source.allocated;
        }
        current_length=source.length();
        for(size_t i=0; i<current_length; i++){
            characters[i]=source.characters[i];
        }
        return *this;
    }
    
    void string::insert(const string& source, unsigned int position){
        assert(position<=length());
        current_length=current_length+source.length();
        allocated=current_length+1;
        char* temp=new char[allocated];
        for(unsigned int i=0; i<position; i++){
            temp[i]=characters[i];
        }
        size_t index=0;
        for (unsigned int j=position; j<source.length()+position; j++){
            temp[j]=source[index];
            index++;
        }
        unsigned int pos=position;
        for (unsigned int k=source.length()+position; k<current_length; k++){
            temp[k]=characters[pos];
            pos++;
        }
        delete [] characters;
        characters=temp;
    }
    
    void string::dlt(unsigned int position, unsigned int num){
        assert((position + num) <= length( ));
        unsigned int times=num;
        while (times>0){
            for(unsigned int i=position; i<current_length&&(i+1)<current_length; i++){
                characters[i]=characters[i+1];
            }
            times--;
        }
        current_length=current_length-num;
    }
    
    void string::replace(char c, unsigned int position){
        assert(position < length()); 
        characters[position]=c;
    }
    
    void string::replace(const string& source, unsigned int position){
        assert((position + source.length()) <= length());
        unsigned int index=0;
        for (unsigned int i=position; i<position+source.length(); i++){
            characters[i]=source[index];
            index++; 
        }
    }
    
    // CONSTANT MEMBER FUNCTIONS
    char string::operator [ ](size_t position) const{
        assert(position<length());
        return characters[position];
    }
    
    int string::search(char c) const{
        int pos=0;
        while(characters[pos]!=c){
            pos++;
        }
        if(pos>=current_length){return -1;}
        return pos;
    }
    
    int string::search(const string& substring) const{
        int index=0;
        int pos=0;
        int i=0;
        while(index<current_length){
            if(characters[index]==substring[pos]){
                for (i=index; i<substring.length(); i++){
                    if(characters[i]!=substring[i]){
                        break;
                    }
                   
                }
            }
            
            if(i>=substring.length()){
                return index;
                break;
            }
            //increment index
            index++;
        }
        return -1;
    }
    
    unsigned int string::count(char c) const{
        unsigned int count=0;
        for (size_t i=0; i<current_length; i++){
            if(characters[i]==c){
                count++;
            }
        }
        return count; 
    }
    
    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source){
        for (int i=0; i<source.length(); i++){
            outs<<source[i];
        }
        return outs;
    }
    
    bool operator ==(const string& s1, const string& s2){
        return (strcmp(s1.characters, s2.characters)==0);
    }
    
    bool operator !=(const string& s1, const string& s2){
        return (!(s1==s2));
    }
    
    bool operator > (const string& s1, const string& s2){
        if(s1==s2){return false;}
        else {
            for (int i=0; i<s1.length(); i++){
                if(s1[i]<s2[i]){
                    return false;
                    break;
                }
            }
        }
        return true;
    }
    
    bool operator < (const string& s1, const string& s2){
        if(s1==s2){return false;}
        else {
            for (int i=0; i<s1.length(); i++){
                if(s1[i]>s2[i]){
                    return false;
                    break;
                }
            }
        }
        return true;
    }
    
    bool operator >=(const string& s1, const string& s2){
        return ((s1>s2)||s1==s2);
    }
    
    bool operator <=(const string& s1, const string& s2){
        return ((s1<s2)||s1==s2);
    }
    
    
    //NON-MEMBER FUNCTIONS 
    string operator +(const string& s1, const string& s2){
        string s;
        s+=s1;
        s+=s2;
        return s;
    }
    
    string operator +(const string& s1, const char addend[ ]){
        string s;
        s+=s1;
        s+=addend;
        return s;
    }
    
    std::istream& operator >> (std::istream& ins, string& target){
        
        while (ins&&isspace(ins.peek())){
            ins.ignore();
        }
        
        target=" ";
        char temp;
        while(!ins.eof()&&!isspace(ins.peek())){
            ins>>temp;
            target+=temp;
        }
        
        return ins;
    }
    
}
