#include <iostream>
#include "circular-list.h"
using namespace std;

int main()
{
    CircularList<int> l;
    l.push(5);
    l.push(3);
    l.push(4);
    l.push(13);
    l.insert(l.find(4), 6);
    l.remove(l.begin());

    auto i = l.begin();
    if (i.valid())
    {
        do
        {
            cout << *i << endl;
            i.forward();
        } while (i != l.begin());
    }
}