#pragma once
#include<iostream>
#include<string>
#include<vector>
class Image;
class Command;

class session
{
    public:
        static int sessionCounter;
        int uniqueSessionID;
        std::vector<Image*> activeImages;
        std::vector<int> pendingOperationsID;
        session(std::vector<Image*> &_activeImages);
        void printInfo(std::ostream& out = std::cout);
        void appendCommand(command &command);
        ~session();
};

class sessionHandler
{
    public:
        std::vector<session*> activeSessions;
        int activeSessionID;
        void sendCommandToSession(command &_command);
        void changeActiveSession(int newSessionNumber);
        void createNewSession(std::vector<Image*> &initialImages, std::ostream &out = std::cout);
        void executeCommand(command &_command);
        void executeLoadCommand(command &currentCommand);
        void executeSaveCommand(command &currentCommand);
        void executeUndoCommand(command &currentCommand);
        void executeSaveAsCommand(command &currentCommand);
        void executeAddCommand(command &currentCommand);
        class CommandReader
        {
            public:
                std::string rawCommand;
                int rawCommandSize;
                command* readCommand();
                static std::string findExtension(std::string filename);
        };
        CommandReader CommandReaderWorker;
};