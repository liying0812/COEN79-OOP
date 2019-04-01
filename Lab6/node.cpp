
// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include <iostream>
#include "node.hpp"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
        const node *cursor;
        size_t answer;
        
        answer = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            ++answer;
        
        return answer;
    }
    
    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
        head_ptr = new node(entry, head_ptr);
    }
    
    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
        node *insert_ptr;
        
        insert_ptr = new node(entry, previous_ptr->link( ));
        previous_ptr->set_link(insert_ptr);
    }
    
    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            if (target == cursor->data( ))
                return cursor;
        
        return NULL;
    }
    
    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            if (target == cursor->data( ))
                return cursor;
        
        return NULL;
    }
    
    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
        node *cursor;
        size_t i;
        
        assert (0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link( );
        
        return cursor;
    }
    
    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
        const node *cursor;
        size_t i;
        
        assert (0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link( );
        
        return cursor;
    }
    
    void list_head_remove(node*& head_ptr)
    {
        node *remove_ptr;
        
        remove_ptr = head_ptr;
        head_ptr = head_ptr->link( );
        delete remove_ptr;
    }
    
    void list_remove(node* previous_ptr)
    {
        node *remove_ptr;
        
        remove_ptr = previous_ptr->link( );
        previous_ptr->set_link( remove_ptr->link( ) );
        delete remove_ptr;
    }
    
    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
        while (head_ptr != NULL)
            list_head_remove(head_ptr);
    }
    
    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
        head_ptr = NULL;
        tail_ptr = NULL;
        
        // Handle the case of the empty list.
        if (source_ptr == NULL)
            return;
        
        // Make the head node for the newly created list, and put data in it.
        list_head_insert(head_ptr, source_ptr->data( ));
        tail_ptr = head_ptr;
        
        // Copy the rest of the nodes one at a time, adding at the tail of new list.
        source_ptr = source_ptr->link( );
        while (source_ptr != NULL)
        {
            list_insert(tail_ptr, source_ptr->data( ));
            tail_ptr = tail_ptr->link( );
            source_ptr = source_ptr->link( );
        }
    }
    
    //questions
    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
        head_ptr=NULL;
        tail_ptr=NULL;
        
        if (start_ptr==NULL || start_ptr == end_ptr){
            return;
        }
        
        //set head pointer
        list_head_insert(head_ptr, start_ptr->data( ));
        //tail_ptr=start_ptr; //question about this??
        tail_ptr = head_ptr;
        
        start_ptr=start_ptr->link();
        while(start_ptr != NULL && start_ptr!=end_ptr){
            //list_insert(tail_ptr, head_ptr->data());
            list_insert(tail_ptr, start_ptr->data());
            tail_ptr=tail_ptr->link();
            start_ptr=start_ptr->link();
        }
        
    }
    
    
    size_t list_occurrences(node* head_ptr, const node::value_type& target){
        size_t count=0;
        node* cursor;
        cursor=head_ptr;
        while(cursor!=NULL){
            if(cursor->data()==target){
                count++;
            }
            cursor=cursor->link();
        }
        return count;
    }
    
    
    //not sure
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
        assert(position>0 && position<=(list_length(head_ptr)+1));
        node* cursor;
        node* temp;
        node* next;
        if(position==1){
            cursor=head_ptr;
            list_head_insert(head_ptr, entry);
            head_ptr->set_link(cursor);
        }
        else if(head_ptr==NULL){
            list_head_insert(head_ptr, entry);
        }
        else {
            temp=head_ptr;
            for(size_t i=1; i<position-1; i++){
                temp=temp->link();
            }
            
            cursor=temp->link();
            list_insert(temp, entry);
            next=temp->link();
            next->set_link(cursor);
            
            
        }
    }
    
    //not sure
    node::value_type list_remove_at(node*& head_ptr, size_t position){
        assert(head_ptr!=NULL && position>0 && position<=list_length(head_ptr));
        node::value_type data;
        node* cursor=head_ptr;
        node* del;
        node* prev;
        
        if(position==1){
            data=head_ptr->data();
            head_ptr=head_ptr->link();
        }
        else{
            for (size_t i=1; i<position-1; i++){
                cursor=cursor->link();
            }
            prev=cursor;
            cursor=cursor->link();
            del=cursor;
            data=del->data();
            cursor=cursor->link();
            prev->set_link(cursor);
            //del=NULL; //or delete
        }
        return data;
    }
    
    
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
        assert(head_ptr!=NULL&&(1<=start)&&(start<=finish)&&(finish<=list_length(head_ptr)));
        
        node* list_head=NULL; //dynamic memory
        node* list_tail=NULL;
        
        //node* cursor=head_ptr;//OR node* cursor=head_ptr->link();
        
        for(size_t pos=1; pos<start; pos++){
            head_ptr=head_ptr->link();
        }
        
        //set data for the head node
        list_head_insert(list_head, head_ptr->data( ));
        list_tail=list_head;
        
        head_ptr=head_ptr->link();
        for(size_t i=start+1; i<=finish; i++){ //not sure about the for loop
            list_insert(list_tail, head_ptr->data( ));
            list_tail = list_tail->link( );
            head_ptr=head_ptr->link();
        }
        
        //        head_ptr=NULL;
        //        tail_ptr=NULL;
        //
        //        if (start_ptr==NULL || start_ptr == end_ptr){
        //            return;
        //        }
        //
        //        //set head pointer
        //        list_head_insert(head_ptr, start_ptr->data( ));
        //        //tail_ptr=start_ptr; //question about this??
        //        tail_ptr = head_ptr;
        //
        //        start_ptr=start_ptr->link();
        //        while(start_ptr != NULL && start_ptr!=end_ptr){
        //            //list_insert(tail_ptr, head_ptr->data());
        //            list_insert(tail_ptr, start_ptr->data());
        //            tail_ptr=tail_ptr->link();
        //            start_ptr=start_ptr->link();
        //        }
        //
        
        
        
        return list_head;
    }
    
    
    void list_print (const node* head_ptr){
        if(head_ptr==NULL){
            std::cout<<std::endl;
            return;
        }
        
        const node* cursor=head_ptr;
        while(cursor!=NULL){
            std::cout<<cursor->data()<<", ";
            cursor=cursor->link();
        }
        std::cout<<std::endl;
    }
    
    
    void list_remove_dups(node* head_ptr){
        node* current=head_ptr;
        node* next;
        node* dup;
        while(current!=NULL && current->link()!=NULL){
            next=current->link();
            while(next!=NULL){
                if(current->data()==next->data()){
                    dup=next;
                    next=next->link();
                    current->set_link(next);
                    dup=NULL; //or delete
                }
                else{
                    next=next->link();
                }
            }
            current=current->link();
        }
    }
    
    
    node* list_detect_loop (node* head_ptr){
        node* slow_runner=head_ptr;
        node* fast_runner=head_ptr;
        while(fast_runner!=NULL&&fast_runner->link()!=NULL){
            slow_runner=slow_runner->link();
            fast_runner=fast_runner->link()->link();
            if(slow_runner==fast_runner) {
                std::cout<<"the poiners met!"<<std::endl;
                break;
            }
        }
        if(fast_runner==NULL || fast_runner->link()==NULL){return NULL;}
        slow_runner=head_ptr;
        while(slow_runner!=fast_runner){
            slow_runner=slow_runner->link();
            fast_runner=fast_runner->link();
        }
        return fast_runner;
    }
    
}
