//
//  pattern.cpp
//  Lab1
//
//  Created by liying liang on 1/11/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "pattern.hpp"
using namespace std;

void pattern(){
    
    cout << "0123456789" << endl;
    
    //use setw to fix the distance between the strings 
    cout << setw(11);
    cout << "9876543210";
    cout << setw(20);
    cout << "0123456789" << endl;
    
    cout << setw(13);
    cout << "9876543210";
    cout << setw(22);
    cout << "0123456789" << endl;
    
    cout << setw(15);
    cout << "9876543210";
    cout << setw(24);
    cout << "0123456789" << endl;
    
    cout << setw(17);
    cout << "9876543210";
    cout << setw(26);
    cout << "0123456789" << endl;
    
    cout << setw(19);
    cout << "9876543210";
    cout << setw(28);
    cout << "0123456789" << endl;
    
}

