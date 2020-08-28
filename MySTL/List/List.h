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
    Node<T>* tail;
    size_t   count;

public:
    typedef Node<T>* iterator;
    
    List () ;
    List (iterator Beg, iterator End);
    List (const initializer_list<T>& other);
    List (List<T>& other);
    List (int n, T value);
    void operator=(const List<T>& other);
    
    bool empty () {return count==0;}
    size_t size () {return count;}
    iterator begin () {return head->next;}
    iterator end () {return tail;}

    T front () {return begin()->data;}
    T back() {return end()->prev->data;}
    int find(T elem);

    void push_front (T data) ;
    void push_back(T data);
    void pop_front();
    void pop_back();
    void insert(int place, T elem);
    void erase(iterator now);
    void erase(iterator Beg, iterator End);
    

    int distance(iterator Beg, iterator End);   //计算迭代器的距离
    bool advance(iterator& now, int Distance);
    void free();
    void show();
private:
    void init_List();
    void new_node(Node<T>* now, T data);  
    void free_node(Node<T>* now);

};

template<typename T>
void List<T>::init_List()
{
    head = new Node<T>();
    tail = new Node<T>();
    head->next = tail;
    tail->prev = head;
    count = 0;
}

template<typename T>
void List<T>::new_node(Node<T>* now, T data)
{
    Node<T>* new_Node = new  Node<T>(data, now->prev, now);
    now->prev->next = new_Node;
    now->prev = new_Node;

    ++count;
    return ;
}

template<typename T>
void List<T>::free_node(Node<T>* now)
{
    now->prev->next = now->next;
    now->next->prev = now->prev;

    delete now;
    --count;

    return ;
}

template<typename T>
List<T>::List()
{
    init_List();
}

template<typename T>
List<T>::List(iterator Beg, iterator End)
{
    init_List();
    auto i = Beg;
    while(i->next)
    {
        new_node(tail, i->data);
        i = i->next;
    }

}
template<typename T>
List<T>::List(const initializer_list<T>& other)
{   
    init_List();

    for (const auto& i : other)
        new_node(tail,i);
}

template<typename T>
List<T>::List(List<T>& other)
{
    init_List();
    iterator i = other.begin();
    while(i->next)
    {
        new_node(tail,i->data);
        i = i->next;
    }

}

template<typename T>
List<T>::List(int n, T value)
{
    init_List();

    for (int i = 0; i < n; ++i)
        new_node(tail,value);
}

template<typename T>
void List<T>::operator=(const List<T>& other)
{
    this(other);

    return ;
}

template<typename T>
void List<T>::push_front(T data)
{
   new_node(head->next,data);
   return ;
}

template<typename T>
void List<T>::push_back(T data)
{
    new_node(tail,data);  
    return ;
}

template<typename T>
void List<T>::pop_front()
{
    if (empty())
        return ;
    else
        free_node(begin());

    return ;
}

template<typename T>
void List<T>::pop_back()
{
    if (empty())
        return ;
    else
        free_node(end()->prev);

    return ;
}

template<typename T>
void List<T>::insert(int place, T elem)
{
    auto i = begin();
    if(advance(i,place))
    new_node(i,elem);

    return ;
}

template<typename T>
void List<T>::erase(iterator now)
{
    free_node(now);
    return ;
}

template<typename T>
void List<T>::erase(iterator Beg, iterator End)
{
    while(Beg != End)
    {
        free_node(Beg);
        Beg = Beg->next;
    }

    return ;
}

template<typename T>
int List<T>::find(T elem)
{
    auto i = begin();
    while(i->next)
    {
        if (i->data == elem)
            return distance(begin(), i);
        i = i->next;
    }

    return -1;
}

template<typename T>
void List<T>::free()
{
    auto i = head;
    while(i != tail)
    {
        auto j = i;
        i = i->next;
        free_node(j);
    }

    init_List();
    return ;
}


template<typename T>
void List<T>::show()
{
    auto i = begin();
    while(i != end())
    {
        cout<<i->data<<" ";
        i = i->next;
    }
    cout<<endl;
    return ;
}

template<typename T>
int List<T>::distance(iterator Beg, iterator End)
{
    int dis = 0;
    auto i = Beg;
    while(i->next)
    {
        ++dis;
        i = i->next;
    }
    return dis;
}  

template<typename T>
bool List<T>::advance(iterator& now, int Distance)
{
    if (Distance == 0)
        return 0;
    else if (Distance > 0 && distance(now, end()->prev) < Distance)
        return 0;
    else if (Distance < 0 && distance(begin(), now) < -Distance)
        return 0;
    


    if (Distance > 0)
    {
        for(int i = 0; i<Distance; ++i)
            now = now->next;
    }
    else if (Distance < 0)
    {
        for(int i = 0; i< -Distance; ++i)
            now = now->prev;
    }
    
    return 1;
}

#endif
