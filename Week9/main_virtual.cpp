#include<iostream>
class Animal
{
    public:
        Animal(){}
        virtual void makeSound()
        {
            std::cout<<"Animalllll"<<std::endl;
        }
};
class Dog : public Animal
{
    public:
        virtual void makeSound() override
        {
            std::cout<<"Bow"<<std::endl;
        }
};
class Chiwawa : public Dog
{   
    public:
        void makeSound() override
        {
            std::cout<<"Chiwawawa"<<std::endl;
        }   
};
int main()
{
    Animal *dog[100];
    for(int i=0; i<10; i++)
    {
        dog[i] = new Dog();
    }
    dog[5] = new Chiwawa();
    for(int i=0; i<10; i++)
    {
        dog[i]->makeSound();
    }
    Animal *kuchi = new Chiwawa();
    kuchi->makeSound();
}