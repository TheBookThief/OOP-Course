#include<iostream>
#include<string>
class CommandHandler
{
    std::string rawCommand;
    std::string* commandArguments;
    std::size_t commandArgumentsSize;

    std::string filename;
    CommandHandler(std::string _commandName, std::stirng _filename) : commandName(_commandName), filename(_filename) {}
    void readCommand()
    {
        std::getline(std::cin, rawCommand);
        for(int i=0; i<strlen(rawCommand); i++)
        {
            if(rawCommand[i] == ' ') 
                commandArgumentsSize++;
        }
        

    }
};
int main()
{
    while(1)
    {
        std::cin>>command;
        if(command =)
    }
}