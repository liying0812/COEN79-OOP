// "This is git command test"
//  convert.cpp
//  Lab1
//
//  Created by liying liang on 1/11/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "convert.hpp"
using namespace std;

void convert(string filename){
    ifstream inFile;
    
    //open the file
    inFile.open(argv[1]);
    
    //check if it opens successfully
    if (!inFile){
        cout<<"open fails"<<endl;
        exit(0);
    }
    
    //store the word get from the .txt file
    string word;
    
    //check if it gets to the end of the file
    while (!inFile.eof()){
        inFile>>word;
        
        //counter to keep check of the length of valid string
        int count=0;
        
        //temp variable to store the valid word
        string temp;
        
        //loop through the word
        //if is alphanumeerical put it to temp and increment counter and make it uppercase
        for (int i=0; i<word.length(); i++){
            if (isalnum(word[i])){
                temp.push_back(toupper(word[i]));
                count++;
            }
        }
        
        //check if string has length greater or equal to 10
        //yes then print it
        if (count>=10){
            cout<<temp<<endl;
        }
        
        //reset temp
        temp="";
    }
    
    inFile.close();
}
