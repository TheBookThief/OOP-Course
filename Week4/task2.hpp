#ifndef TASK2_HPP
#define TASK2_HPP

#include<cstring>
#include<iostream>

class Counted
{
    public:
        Counted()
        {
            id = counted;
            counted++;
        }
        ~Counted()
        {
            counted--;
        }
        static void getCount()
        {
            std::cout<<counted<<std::endl;
        }
    private:
        std::size_t id;
        static std::size_t counted;
};

std::size_t Counted::counted = 0;

// static void Counted::getCount()
// {
//     std::cout<<counted<<std::endl;
// }

#endif