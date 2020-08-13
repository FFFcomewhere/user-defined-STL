#ifndef _LIST_H
#define _LIST_H

#include<iostream>
#include<initializer_list>
using namespace std;

template<class T> 
struct Node
{
public:
    T data;
    Node<T>*  prev;
    Node<T>*  next;
public:
    Node () {prev = next = nullptr ;}
    Node (T Data, Node<T>* Prev, Node<T>* Next)
    {
        data = Data;
        prev = Prev;
        next = Next;
    }
};


template<typename T>
class List
{
private:
    Node<T>* head;
    size_t   count;
private:
    void first_new_node(T data);
public:
    void new_node(Node<T>* &now, T data);    

public:
    typedef Node<T>* iterator;
    
    List () : count(0) {;}
    List (const initializer_list<T>& other);


    size_t size () {return count;}
    iterator begin () {return head->next;}
    iterator end () {return head->prev;}

    T front();

    void push_front(T data);

};

template<typename T>
List<T>::List(const initializer_list<T>& other)
{   
    for(const auto& i : other)
        new_node(head++,i);
}

template<typename T>
void List<T>::first_new_node(T data)
{
    Node<T>* new_Node = new Node<T>(data, head->prev, head->next);

    cout<<head<<" "<<head->prev<<" "<<head->next<<endl;

    head->prev = new_Node;
    head->next = new_Node;

    ++count;
}

template<typename T>
void List<T>::new_node(Node<T>* &now, T data)
{
    Node<T>* new_Node = new  Node<T>(data, now->prev, now);
    now->prev->next = new_Node;
    now->prev = new_Node;

    ++count;
}

template<typename T>
T List<T>::front()
{
    return head->next->data;
}

template<typename T>
void List<T>::push_front(T data)
{
//    new_node(begin(), data);
    first_new_node(data);
}

#endif
