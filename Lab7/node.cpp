//
//  node.cpp
//  Lab7
//
//  Created by Liying Liang  on 2/21/19.
//  Copyright © 2019 Liying_Liang. All rights reserved.
//
//Invariants for node class:
//  1. Each node has a string vaiable storing the product name and a float variable representing the product price and the link that pointing to the next product
//  2. Node is used to create linked list that can only move forward 

#ifndef ITEM_CPP
#define ITEM_CPP

#include <iostream>
#include "node.hpp"

namespace coen79_lab7
{
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    node* node::getLink() {
        return link;
    }
    
    const node* node::getLink() const {
        return link;
    }
    
    std::string node::getName() const{
        return name;
    }
    
    float node::getPrice() const {
        return price;
    }
    
    
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {
        // COMPLETE THE IMPLEMENTATION...
        node *newNode = new node(newName, newPrice, NULL);
        tail->setLink(newNode);
        tail = newNode;
        tail->setLink(NULL);
    }
    
    
    void list_clear(node*& head) {
        // COMPLETE THE IMPLEMENTATION...
        if(head!=NULL){
            delete head;
        }
        head=NULL;
    }
    
    
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = new_head;
        
        const node *cur = old_head;
        while (cur != NULL) {
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    
    
    void list_head_remove(node*& head) {
        // COMPLETE THE IMPLEMENTATION...
        assert(head!=NULL);
        if(head->getLink()!=NULL){
            node* temp=head->getLink();
            delete head;
            head=temp;
        }
        else{//not sure if needed
            delete head;
            head=NULL;
        }
    }
    
    
    void list_print(node *head) {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
    
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
}

#endif
