#include"List.h"
#include<iterator>
int main()
{
    List<char> obj1{'a','b','c'};
    obj1.show();
    obj1.erase(obj1.begin());
    obj1.show();
    obj1.push_front('a');
    obj1.show();
    cout<<obj1.find('b')<<endl;
    obj1.clear();
    obj1.show();


    List<char> obj2(3,'a');
    obj1 = obj2;
    obj1.show();
    obj1.pop_front();
    obj1.show();
    obj1.insert(1,'c');
    obj1.show();
    

    return 0;
}
