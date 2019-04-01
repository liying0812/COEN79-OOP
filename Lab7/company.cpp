//
//  company.cpp
//  Lab7
//
//  Created by Liying Liang  on 2/21/19.
//  Copyright © 2019 Liying_Liang. All rights reserved.
//

// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)

//Invariants for Company class:
//  1. Each company object is stored in the dynamic array, and it includes the company name, a head pointer pointing to the head of     the linked list and the tail pointer pointing to the end of the link list.

#include <iostream>
#include <cassert>
#include "company.hpp"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        
        // COMPLETE THE IMPLEMENTATION...
        this->company_name=company_name;
        this->head_ptr=NULL;
        this->tail_ptr=NULL; 
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        
        // COMPLETE THE IMPLEMENTATION...
        if(this==&src){
            return;
        }
        //probably need more condition
        company_name=src.company_name;
        list_copy(src.head_ptr, head_ptr, tail_ptr); 
    }
    
    
    company& company::operator=(const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        
        // COMPLETE THE IMPLEMENTATION...
        if(this==&src){
            return *this; //not sure
        }
        company_name=src.company_name;
        list_copy(src.head_ptr, head_ptr, tail_ptr);
        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        assert(product_name.length() > 0);
        
        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            // COMPLETE THE IMPLEMENTATION...
            head_ptr = new node(product_name, price, NULL);
            tail_ptr = head_ptr; //need???
            
            //list_init(hed_ptr, tail_ptr, product_name, price);
        }
        else {
            // COMPLETE THE IMPLEMENTATION...
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }
    
    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        
        // COMPLETE THE IMPLEMENTATION...
        if(!list_contains_item(head_ptr, product_name)){
            return false;
        }
        
        node* target=list_search(head_ptr, product_name);
        target->setName(head_ptr->getName());
        target->setPrice(head_ptr->getPrice());
        list_head_remove(head_ptr);
        return true;
        
    }
    
    
}
