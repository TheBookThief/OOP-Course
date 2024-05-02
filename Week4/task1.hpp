#ifndef TASK1_HPP
#define TASK1_HPP

#include<cstring>
#include<iostream>

class Student
{
    public:
        Student(const char* name)
        {
            strcpy(this->name, name);
            this->id = counter;
            counter++;   
        }
        void print() const;
    private:
        char name[101];
        std::size_t id;
    private:
        static std::size_t counter;
};

std::size_t Student::counter = 0;

void Student::print() const
{
    std::cout<<this->name<<" "<<this->id<<std::endl;
}
#endif