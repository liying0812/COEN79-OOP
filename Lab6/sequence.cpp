
//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.




 #include <iostream>
 #include <algorithm> //provides copy function
 #include <cassert> //for assert function
 #include "sequence.hpp" //header file for class
 #include "node.hpp" // provides node class
 
 using namespace std; //For copy function


 namespace coen79_lab6
 {
     // Default private member variable initialization function.
     void sequence::init()
     {
         //Initializing pointers to NULL
         head_ptr = NULL;
         tail_ptr = NULL;
         cursor = NULL;
         precursor = NULL;
         
         //Initializiing many_nodes (or our counter) to 0
         many_nodes = 0;
     }
 
 
     //CONSTRUCTOR IMPLEMENTATION for default constructor
     sequence::sequence ()
     {
         init();
     }
 
     //Copy Constructor
     sequence::sequence(const sequence& source)
     {
         init();
         *this = source; 
     }
     
     //destructor
     sequence::~sequence( ){
         list_clear(head_ptr);
         many_nodes=0;
     }
     
     // MODIFICATION MEMBER FUNCTIONS
     void sequence::start( ){
         if (head_ptr==NULL){
             precursor=cursor=NULL;
             
         }
         else{
             precursor=cursor=head_ptr;
         }
     }
     
     void sequence::end(){
         if (head_ptr==NULL){
             precursor=cursor=NULL;
         }
         else {
             precursor=cursor;
             cursor=cursor->link();
             while(cursor->link()!=NULL){
                 precursor=precursor->link();
                 cursor=cursor->link();
             }
             //cursor=precursor->link();
             tail_ptr=cursor;
         }
     }
     
     void sequence::advance( ){
         if(!is_item()){
             precursor=NULL;
             return;
         }
         else if(cursor->link()==NULL){
             cursor=NULL;
         }
         else if(cursor==precursor){
             cursor=precursor->link();
         }
         else{
             precursor = cursor;
             cursor = cursor->link();
         }

     }
     
     void sequence::insert(const value_type& entry){
         if(head_ptr==NULL){
             //cout<<"option1"<<endl;
             list_head_insert(head_ptr, entry);
             cursor=tail_ptr=head_ptr;
         }
         else if(cursor==head_ptr){
             node* tmp = new node(entry, cursor);
             head_ptr = tmp;
             tail_ptr = cursor;
             cursor=head_ptr;
             //cout<<"here: "<<cursor->data()<<endl;
             //cout<<"here: "<<cursor->link()->data()<<endl;

         }
         else if(cursor==NULL){
             list_head_insert(head_ptr, entry);
             cursor=head_ptr;
             //precursor=NULL;
         }
         else{
             list_insert(precursor, entry);
             cursor=precursor->link();
         }
         many_nodes++;
         
     }
     
     void sequence::attach(const value_type& entry){
         if(head_ptr==NULL){
             list_head_insert(head_ptr, entry);
             tail_ptr=head_ptr;
             cursor=head_ptr;
             precursor=NULL;
         }
         else if(cursor==NULL||precursor==NULL){
             list_insert(tail_ptr, entry);
             precursor=tail_ptr;
             tail_ptr=tail_ptr->link();
             cursor=tail_ptr;
         }
         else{
             list_insert(cursor, entry);
             precursor=cursor;
             cursor=cursor->link();
         }
         many_nodes++;
     }
     
     
     void sequence::operator =(const sequence& source){
         init();
         if(this==&source){
             return;
         }
         else if(source.many_nodes==0){
             list_copy(source.head_ptr, head_ptr, tail_ptr);
             precursor=cursor=NULL;
         }

         //if the source only has one element
         else if(source.cursor==source.head_ptr){
             list_copy(source.head_ptr, head_ptr, tail_ptr);
             cursor=tail_ptr=head_ptr;
             precursor=NULL;
         }
         
         //question about this
         //if the source has more than one element
         else{
             list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
             list_copy(source.cursor, cursor, tail_ptr);
             if(cursor!=NULL&&precursor!=NULL){
                 precursor->set_link(cursor);
             }
         }
     }

     
     void sequence::remove_current( ){
         assert(is_item());
         if(precursor==NULL){
             precursor=cursor;
         }
         else if(cursor==head_ptr){
             //cout<<"front: "<<head_ptr->data()<<endl;
             //cout<<"last: "<<tail_ptr->data()<<endl;
             node* tmp=cursor;
             cursor=head_ptr=head_ptr->link();
             delete tmp;
             precursor=NULL;
//             head_ptr=head_ptr->link();
//             list_head_remove(cursor);
//             cursor=head_ptr;
//             precursor=NULL;
             //cout<<"current: "<<cursor->link()->data()<<endl;
             //cout<<"front: "<<head_ptr->data()<<endl;
             //cout<<"last: "<<tail_ptr->data()<<endl;
         }
         else if(cursor==tail_ptr){
             //cursor=cursor->link();
             list_remove(precursor);
             tail_ptr=precursor;
             cursor=NULL;
//             cout<<"front: "<<head_ptr->data()<<endl;
//             cout<<"last: "<<tail_ptr->data()<<endl;
         }
         else{
             cursor=cursor->link();
             list_remove(precursor);
//             cout<<"front: "<<head_ptr->data()<<endl;
//              cout<<"last: "<<tail_ptr->data()<<endl;
         }
         many_nodes--; 
     }
     
     
     // CONSTANT MEMBER FUNCTIONS
     sequence::size_type sequence::size( ) const{
         return many_nodes;
     }
     
     bool sequence::is_item( ) const{
         return(cursor!=NULL);
     }
     
     sequence::value_type sequence::current( ) const{
         assert(is_item());
         return cursor->data();
     }
 
 }


