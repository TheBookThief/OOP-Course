#include<iostream>
#include<string>
#include<vector>
#include "visitor.hpp"
#include "session.hpp"
#include "command.hpp"
#include "image.hpp"
#include "imagePPM.hpp"
#include "testing.hpp"
int main()
{
    sessionHandler* sessionHandlerWorker = new sessionHandler();

    while(1)
    {
        std::cout<<std::endl<<"Awaiting command:"<<std::endl;
        command* currentCommand = sessionHandlerWorker->CommandReaderWorker.readCommand();
        int commandExecutionStatus = sessionHandlerWorker->executeCommand(*currentCommand);
        if(commandExecutionStatus == 0) break;
    }

    delete sessionHandlerWorker;
}   