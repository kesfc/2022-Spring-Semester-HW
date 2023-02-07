#ifndef __UnrolledLL_h
#define __UnrolledLL_h
#include <ostream>
#include <iostream>
#include <cstddef>
#include <cassert>

const int NUM_ELEMENTS_PER_NODE = 6;
template<class T> class Node{
    public:
    //constructor
    Node(): next_(nullptr), prev_(nullptr), num_elements(0){}
    //// REPRESENTATIONi.
    Node<T>* next_;
    Node<T>* prev_;
    T elements [NUM_ELEMENTS_PER_NODE];
    int num_elements;
};
// A "forward declaration" of this class
template<class T> class UnrolledLL;

template <class T>
class list_iterator {
    public:
    // default constructor, copy constructor, assignment operator, & destructor
    list_iterator(Node<T>* p, int v){ptr_=p; offset=v;}
    //Accessor
    int get_offset(){return offset;}

    // dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->elements[offset];}
    // increment & decrement operators
    list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    //check to see need to move the pointer or just move offset
    if(offset != NUM_ELEMENTS_PER_NODE){
        offset++;
    }
    else{
        ptr_ = ptr_->next_;
        offset=0;
    }
    return *this;
    }
    list_iterator<T> operator++(int){// // post-increment, e.g., iter++
        list_iterator<T> temp(*this);
        if(offset < ptr_->num_elements-1){
        offset++;
        }
        else{
            ptr_ = ptr_->next_;
            offset=0;
        }
    return temp;
    }
    list_iterator<T>& operator--(){ // pre-decrement, e.g., --iter
        if(offset < ptr_->num_element-1){
            offset++;
        }
        else{
            ptr_=ptr_->prev_;
            offset=5;
        }
        return *this;
    }
    list_iterator<T> operator--(int){  // post-decrement, e.g., iter--
        list_iterator<T> temp(*this);
        if(offset != 0){
        offset--;
    }
    else{
        ptr_ = ptr_->prev_;
        offset=5;
    }
    return temp;
    }
    friend class UnrolledLL<T>;
    // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const {
        return ptr_ == r.ptr_; }
    bool operator!=(const list_iterator<T>& r) const {
        return ptr_ != r.ptr_; }
    private:
    // REPRESENTATION
    int offset;
    Node<T>* ptr_;
};

template<class T> 
class UnrolledLL{
    public:
    // default constructor, copy constructor, assignment operator, & destructor
    UnrolledLL(): head_(nullptr), tail_(nullptr), size_(0){}
    UnrolledLL(const UnrolledLL<T>& old) { this->copy_list(old);}
    UnrolledLL& operator=(const UnrolledLL<T>& old);
    ~UnrolledLL() {this->destroy_list();}
    
    //simple accessors & modifiers
    unsigned int size() const {return size_;}
    unsigned int front() const{return (head_->elements)[0];}
    unsigned int back() const{return (tail_->elements)[(tail_->num_elements)-1];}
    bool empty() const { return head_ == nullptr; }
    void clear() { this->destroy_list(); }

    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();

    //with iterator
    typedef list_iterator<T> iterator;
    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() { return iterator(head_, 0); }
    iterator end() { return iterator(nullptr, 0); }

    //print
    void print(std::ostream &os);

    private:
    //REPRESENTATION
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;

    // private helper functions
    void copy_list(const UnrolledLL<T>& old);
    void destroy_list();
};
//List Implementation

template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator=(const UnrolledLL<T>& old){
    // check for self-assignment
    if (&old != this) {
        this->destroy_list();
        this->copy_list(old);
    }
    return *this;
}

template <class T> //add a new element to the Unrolled
void UnrolledLL<T>::push_front(const T& v){
    size_++;
    if (!head_){//if there us no element in the unrolled
        Node<T> *newp=new Node<T>;
        (newp->elements)[0]=v;
        (newp->num_elements)=1;
        head_=newp;
        tail_=newp;
        return;
    }
    else{
        unsigned int first_size=head_->num_elements;
        if(first_size<NUM_ELEMENTS_PER_NODE){ //if the first Node is not full yet
            for(unsigned int i=first_size; i>0; i--){
                (head_->elements)[i]=(head_->elements)[i-1];
            }//pushing every element one position back
            (head_->elements)[0]=v;//put the element at index 1
            (head_->num_elements)+=1; //size++
        }
        else{
            //creat a new Node linked with the head, put element in the first index of 
            // the array of the Node and point head to new node
            Node<T> *newp=new Node<T>;
            (newp->elements)[0]=v;
            newp->next_=head_;
            head_->prev_=newp;
            head_=newp;
            newp->num_elements=1;
        }
        
    }
}
template <class T>
void UnrolledLL<T>::push_back(const T&v){
    size_++;
    if(!tail_){//if there is no element in the Node's array
        Node<T> *newp=new Node<T>;
        (newp->elements)[0]=v;
        (newp->num_elements)=1;
        head_=newp;
        tail_=newp;
        return;
    }
    else{
        unsigned int last_size=tail_->num_elements;
        if(last_size!=NUM_ELEMENTS_PER_NODE){//if the the last Node array is not full
            (tail_->elements)[last_size]=v; //add the element at the index = num_elements
            tail_->num_elements+=1; //araay size ++
        }
        else{
        // if the last node is full, creat a New Node, and do similar thing as push_front
            Node<T> *newp=new Node<T>;
            (newp->elements)[0]=v;
            newp-> num_elements=1;
            tail_->next_=newp;
            newp->prev_=tail_;
            tail_=newp;
        }
    }
}
template <class T>
void UnrolledLL<T>::pop_front(){
    if(size_==0){ //if there is no element, it will just return
        return;
    }
    else{
        size_--;
        unsigned int first_size=head_->num_elements;
        if(first_size==1){
    //if the first node's array is 1; just delet the node, and set second Node as head
            Node<T> *newp=head_;
            head_=head_->next_;
            delete newp;
            head_->prev_=nullptr;
        }
        else{
        //just all elements other than the first one to the right and num_elements--
            for(unsigned int i=0; i<first_size-1; i++){
                (head_->elements)[i]=(head_->elements)[i+1];
            }
            head_->num_elements-=1;
        }
    }
}
template <class T>
void UnrolledLL<T>::pop_back(){
    if(size_==0){//if there is no element, it will just return
        return;
    }
    else{
        size_--;
        unsigned int last_size=tail_->num_elements;
        if(last_size==1){
    //if the last Node's array size is zero, it need to delete this node and change tail
            Node<T> *newp=tail_;
            tail_=tail_->prev_;
            delete newp;
            tail_->next_=nullptr;
        }
        else{
            tail_->num_elements-=1;
        }
    }
}
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>:: insert(iterator itr, const T& v){
    size_++;
    Node<T> *newp=itr.ptr_;
    int index=itr.offset;
    if (newp->num_elements!=NUM_ELEMENTS_PER_NODE){
    //if the given iterator pointed node's array is not full yet, pushing all element at
    //and behind the given offset 1 position back, then put the element at offset position
        for(int i=newp->num_elements; i>index; i--){
            (newp->elements)[i]=(newp->elements)[i-1];
        }
        (newp->elements)[index]=v;
        newp->num_elements+=1;
    }
    else{
        //if the iterator pointed node's array is full
        Node<T> *temp= new Node<T>;
        for(int i=index; i<NUM_ELEMENTS_PER_NODE; i++){
            (temp->elements)[i-index]=(newp->elements)[i];
        }//creat a new node and copy all elements at or behind the iterator's offset to 
        //the new node's array
        temp->num_elements=NUM_ELEMENTS_PER_NODE-index;
        newp->num_elements=index+1;
        (newp->elements)[index]=v;
        //if the insertion is happening at the last node, it need to change head
        if(newp==tail_){
            newp->next_=temp;
            temp->prev_=newp;
            head_=temp;
            temp->next_=nullptr;
        }
        else{
            //link the new node with others
            temp->next_=newp->next_;
            temp->prev_=newp;
            newp->next_=temp;
        }
    }
    return itr;
}
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr){
    size_--;
    Node<T> *newp=itr.ptr_;
    int index=itr.offset;
    if(size_==0){// if there is nothing just return
        return itr;
    }
    else if (size_==1){// if size is 1, just delete it 
        head_=tail_=nullptr;
        itr.offset=0;
        itr.ptr_=nullptr;
        newp->num_elements=0;
        delete newp;
    }
    else if(newp->num_elements==1){
    //if the iterator pointer Node array size is one it need to delete the Node and adjust
    //pointers(prev, next, head tail)
        if(newp==head_){
            Node<T> *temp=newp;
            newp=newp->next_;
            newp->prev_=nullptr;
            head_=newp;
            temp->num_elements=0;
            delete temp;
        }
        else if(newp==tail_){
            Node<T> *temp=newp;
            newp=newp->prev_;
            newp->next_=nullptr;
            tail_=newp;
            temp->num_elements=0;
            delete temp;
        }
        else{
            Node<T> *temp=newp;
            Node<T> *temp1=newp->prev_;
            newp=newp->next_;
            newp->prev_=temp->prev_;
            temp1->next_=newp;
            temp->num_elements=0;
            delete temp;
        }
        itr.offset=0;
        itr.ptr_=newp;
    }
    else{
        newp->num_elements-=1;
        int array_size=newp->num_elements;
        if(index==array_size){
            itr++;
            (newp->elements)[index]=0;
        }
        else{
            for (int i=index; i<array_size; i++){
                (newp->elements)[i]=(newp->elements)[i+1];
            }
            (newp->elements)[array_size]=0;
        }
    }
    return itr;
}

template <class T>
void UnrolledLL<T>:: print(std::ostream &os){
    //print by different ostream.
    os<<"UnrolledLL, size:"<<size_<<std::endl;
    for(UnrolledLL<T>::iterator itr=begin(); itr!=end(); itr++){
        os<< "node:["<<itr.ptr_->num_elements<<"]";
        while(itr.offset < (itr.ptr_->num_elements)){
            os<<" "<<(itr.ptr_->elements)[itr.offset];
            itr.offset+=1;
        }
        os<<std::endl;
    }
}

template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
    if(this==&old){ //if it is the same just return;
        return;
    }
    else{
        size_ = old.size_;
        // Handle the special case of an empty list.
        if (old.size_ == 0) {
            head_ = tail_ = nullptr;
            return;
        }
        // Create a new head node.
        head_ = new Node<T>;
        head_->num_elements=(old.head_)->num_elements;
        for(int i=0; i<head_->num_elements; i++){
            (head_->elements)[i]=((old.head_)->elements)[i];
        }
        // tail_ will point to the last node created and therefore will move
        // down the new list as it is built
        tail_ = head_;
        // old_p will point to the next node to be copied in the old list
        Node<T>* old_p = old.head_->next_;
        while (old_p!=nullptr) { // loop to copy every things
            Node<T>* newp=new Node<T>;
            tail_->next_=newp;
            newp->prev_=tail_;
            newp->num_elements=old_p->num_elements;
            for(int i=0; i<tail_->num_elements; i++){
            (newp->elements)[i]=((old_p)->elements)[i];
        }
            tail_=newp;
            old_p = old_p->next_;
        }
    }
}

template <class T>
void UnrolledLL<T>::destroy_list(){//delete everything on heap;
    Node<T>* current = head_;
    Node<T>* temp;
    while(current != nullptr)
    {
        if(current == nullptr)
        break;
        else{
        temp = current;
        current = current->next_;
        delete temp;
        }
    }
    head_=NULL;
    size_ = 0;
}

#endif
