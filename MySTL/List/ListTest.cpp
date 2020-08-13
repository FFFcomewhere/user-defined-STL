#include"List.h"

int main()
{
    List<int> a;
    a.push_front(10);
    cout<<a.front()<<endl;
    auto i = a.begin();
    a.new_node(i,20);
    cout<<a.front();



    return 0;
}