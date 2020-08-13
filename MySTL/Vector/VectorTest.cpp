#include"Vector.h"
#include<iterator>

int main()
{
    //这里以int型为例，其他类型暂不测试
    Vector<int> a{1,2,3,4};                  //重载了花括号初始化
    copy(a.begin(),a.end(),ostream_iterator<int>(cout," "));
    cout<<endl;

    Vector<int> b = a;           
    copy(b.begin(),b.end(),ostream_iterator<int>(cout," "));
    cout<<endl;

    cout<<a[0]<<endl;
    cout<<a.at(1)<<endl;
    cout<<a.back()<<endl;
    a.pop_back();
    a.erase(0);
    copy(a.begin(),a.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    


    b.reserve(10);                          //重新分配内存
    cout<<b.size()<<endl;
    cout<<b.capacity()<<endl;
    b.assign(10,2);
    b.clear();
    copy(b.begin(),b.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<b.size()<<endl;
    cout<<b.capacity()<<endl;
    

    

    return 0; 
}