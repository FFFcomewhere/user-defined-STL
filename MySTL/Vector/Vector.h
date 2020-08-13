#ifndef __VECTOR_H
#define __VECTOR_H

#include<iostream>
#include<memory>
#include<initializer_list>
using namespace std;

template<typename T>
class Vector
{
private:
    T* elem;
    T* enditer;
    T* cap;
    static std::allocator<T> alloc; 

public:
    typedef T*  iterator;
    typedef const T* const_iterator;

    //构造函数
    Vector(){elem = nullptr; enditer = nullptr; cap = nullptr;}
    Vector(const Vector<T>& other);
    Vector(initializer_list<T> List);
    Vector(iterator Beg,iterator End);
    Vector(int n,T value);
    void operator=(Vector<T>& other);

    //基础处理函数
    bool empty() const {return elem==enditer;}
    size_t size() const {return enditer-elem;}
    size_t capacity() const {return cap-elem;}
    iterator begin() const {return elem;}
    iterator end() const {return enditer;}
    void reserve(size_t newcapacity);
    void resize(size_t newsize);
    ~Vector();

    //非变序函数
    T at(int index)const;
    T back()const {return *(enditer-1);}
    T front()const {return *elem;}
    int find(T value)const;

    //变序函数
    void push_back(const T& value);
    void pop_back();
    void insert(int index,T value);
    void assign(int n,T value);
    void erase(int index);
    void clear();


    //重置运算符
    T&   operator[](int index)const;
    bool operator==(const Vector<T>& other)const;
    bool operator!=(const Vector<T>& other)const;
    bool operator>=(const Vector<T>& other)const;
    bool operator<=(const Vector<T>& other)const;
    bool operator>(const Vector<T>& other)const;
    bool operator<(const Vector<T>& other)const;


private:
    void checkCap(){if(enditer==cap) reserve(2*capacity());}
    void alloc_n(size_t n);
    void free();

};

template <typename T>
std::allocator<T> Vector<T>::alloc;

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
    T* const newData = alloc.allocate(other.size());
    T* p = newData;
    for (const auto& i : other)
        alloc.construct(p++,i);
    elem = newData;
    enditer = cap = elem + other.size();
}

template<typename T>
Vector<T>::Vector(initializer_list<T> List)
{
    T* const newData = alloc.allocate(List.size());
    T* p = newData;
    for (const auto& i : List)
        alloc.construct(p++,i);
    elem = newData;
    enditer = cap = elem + List.size();
}

template<typename T>
Vector<T>::Vector(iterator Beg,iterator End)
{
    iterator other = Beg;
    int thesize = End-Beg;
    T* const newData = alloc.allocate(thesize);
    T* p = newData;
    while (other != End)
        alloc.construct(p++,*other++);
    elem = newData;
    enditer = cap = elem + thesize;
}

template<typename T>
Vector<T>::Vector(int n,T value)
{
    T* const newData = alloc.allocate(n);
    T* p = newData;
    for (int i=0; i!=n; ++i)
        alloc.construct(p++,value);
    elem = newData;
    enditer = cap = elem + n;
}


template<typename T>
void Vector<T>::operator=(Vector<T>& other)
{
    cout<<endl<<"copy "<<endl;

    T* const newData = alloc.allocate(other.size());
    T* p = newData;
    for (const auto& i : other)
        alloc.construct(p++,i);
    elem = newData;
    enditer = cap = elem + other.size();

    return ;
}

template<typename T>
Vector<T>::~Vector()
{
   free();
}

template<typename T>
void Vector<T>::resize(size_t newsize)
{
    if (newsize > size())
    {
        if (newsize > capacity())
            reserve(2*newsize);
        
        for (size_t i = size(); i != newsize; ++i)
            alloc.construct(enditer);
    }
    else if (newsize < size())
    {
        while (enditer != elem + newsize)
            alloc.destroy(--enditer);
    }
}

template<typename T>
void Vector<T>::reserve(size_t newcapacity)
{
    if (newcapacity <= capacity() )
        return ;
    alloc_n(newcapacity);
}

template<typename T>
T Vector<T>::at(int index)const
{
    return *(elem+index);
}

template<typename T>
int Vector<T>::find(T value)const
{
    for( auto i=elem; i<enditer; ++i)
    {
        if(*i == value)
            return i-elem; 
    }
    return -1;
}

template<typename T>
void Vector<T>::push_back(const T& n)
{
    checkCap();
    alloc.construct(enditer++,n);
}

template<typename T>
void Vector<T>::pop_back()
{
    --enditer;
    alloc.destroy(enditer);
}

template<typename T>
void Vector<T>::insert(int index,T value)
{
    if (size()+1 >= capacity())
        reserve(2*size());

    int ori_size = size();
    int ori_capacity = capacity();

    T* const newData = alloc.allocate(ori_size+1);
    T* p = newData;
    for (auto i = begin(); i < end(); ++i )
    {
        if (size_t(i-begin()) == index)
            alloc.construct(p++,value);
        
        alloc.construct(p++,*i);
    }

    free();
    elem = newData;
    enditer = elem + ori_size + 1;
    cap = elem + ori_capacity +1;

    return ;
}

template<typename T>
void Vector<T>::assign(int n,T value)
{
    if (n>capacity())
        reserve(n);

    T* const newData = alloc.allocate(n);
    T* p = newData;
    for (int i = 0; i<n; ++i)  
        alloc.construct(p++,value);

    free();
    elem = newData;
    enditer = elem + n;
    cap = elem + n;

    return ;
}

template<typename T>
void Vector<T>::erase(int index)
{
    int ori_size = size();
    int ori_capacity = capacity();

    T* const newData = alloc.allocate(ori_size+1);
    T* p = newData;
    for (auto i = begin(); i < end(); ++i )
    {
        if (size_t(i-begin()) == index)
            continue;
        alloc.construct(p++,*i);
    }

    free();
    elem = newData;
    enditer = elem + ori_size - 1;
    cap = elem + ori_capacity - 1;

    return ;

}

template<typename T>
void Vector<T>::clear()
{
    while (elem != enditer)
        alloc.destroy(--enditer);
    
    

}

template<typename T>
T& Vector<T>::operator[](int index)const
{
   return *(elem+index);
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& other)const
{
    if (size() != other.size())
        return false;
    
    iterator Beg = begin();
    for (const auto& i : other)
        if(i != *Beg++)
        return false;

    return true;

}

template<typename T>
bool Vector<T>::operator!=(const Vector<T>& other)const
{
    return !(*this==other);
}

template<typename T>
bool Vector<T>::operator>=(const Vector<T>& other)const
{
    iterator Beg = begin();
    for (const auto& i : other)
        if(i >= *Beg++)
        return false;

    return true;
}

template<typename T>
bool Vector<T>::operator<=(const Vector<T>& other)const
{
    iterator Beg = begin();
    for (const auto& i : other)
        if(i <= *Beg++)
        return false;

    return true;
}

template<typename T>
bool Vector<T>::operator>(const Vector<T>& other)const
{
    return !(*this<=other);
}

template<typename T>
bool Vector<T>::operator<(const Vector<T>& other)const
{
    return !(*this>=other);
}

template<typename T>
void Vector<T>::alloc_n(size_t n)
{
    size_t ori_size = size();

    T* const newData = alloc.allocate(n);
    T* p = newData;
    for ( const auto &i : *this )
        alloc.construct(p++,i);
    
    free();
    elem = newData;
    enditer = elem + ori_size;
    cap = elem + n;
}

template<typename T>
void Vector<T>::free()
{
    
    if (elem)
    {
        for (auto p = enditer; p != elem;)
            alloc.destroy(--p);             //执行析构
        alloc.deallocate(elem,cap - elem);  //释放内存
    }
        

    
}

#endif