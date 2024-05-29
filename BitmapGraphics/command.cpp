#include<iostream>
#include<string>
#include<vector>
#include "command.hpp"
int command::commandCounter = 0;
command *command::clone() const
{
    return new command(*this);
}
command::command(){}
command::command(std::vector<std::string> &_commandArguments)
{
    commandCounter++;
    uniqueCommandID = commandCounter;
    for (std::string i : _commandArguments)
    {
        commandArguments.push_back(i);
    }
}
void command::printInfo(std::ostream &out) const
{
    for (std::string s : commandArguments)
    {
        out << s;
    }
    out << std::endl;
}
int command::getCommandID() const
{
    return uniqueCommandID;
}