#include"Vector\Vector.h"
#include<list>
#include<iterator>
int main()
{
  list<int> a{1,23,4};
  a.insert(a.begin(),20);
  copy(a.begin(), a.end(), ostream_iterator<int>(cout," "));

}