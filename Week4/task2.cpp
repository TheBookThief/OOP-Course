#include<iostream>
#include "task2.hpp"
int main()
{
    Counted a;
    Counted::getCount();
    {
        Counted b;
        Counted::getCount();
        Counted c;
        Counted::getCount();
    }
    Counted d;
    Counted::getCount();
}