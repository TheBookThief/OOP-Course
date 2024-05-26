#pragma once
#include<iostream>
#include<string>
#include<vector>

class command
{
    public:
        static int commandCounter;
        int uniqueCommandID;
        std::vector<std::string> commandArguments;
        command* clone();
        command();
        command(std::vector<std::string> &_commandArguments);
        void printInfo(std::ostream &out = std::cout);
};