//
//  counter.cpp
//  Lab1
//
//  Created by liying liang on 1/11/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include <iostream>
#include <string>
#include "counter.hpp"
using namespace std;

void counter(){
    
    //string variable to hold input
    string input;
    
    //asks user for input
    cout<<"Please enter a sentence: "<<endl;
    
    //cin to input string
    getline(cin, input);
    
    //counter initialize to 0
    int count=0;
    
    //count non-alpha
    int non_alpha=0;
    
    //loop through the input
    for (int i=0; i<input.length(); i++){
        
        //check if alphanumerical
        //if yes increment counter
        if(isalnum(input[i])&&input[i]!=' '){
            count++;
        }
        //if no, increment non-alpha
        else{
            //ignore the space 
            if (input[i]!=' '){
                non_alpha++;
            }
        }
    }
    
    //print the output
    cout<<"\"" << input << "\"" <<" has "<<count<<" alphanumeric characters and "<<non_alpha<<" non-alphanumeric characters."<<endl;
    
}
