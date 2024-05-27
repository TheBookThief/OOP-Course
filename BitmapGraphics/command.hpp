#pragma once
#include<iostream>
#include<string>
#include<vector>
/**
 * @brief Base class for representing commands.
 * 
 * The class handles containing the commands entered by the user, keeps track of
 * their unique id-s and prepares them to be passed along the functions.
 * 
*/
class command
{
    public:
        /**
         * @brief Keeps track of the number of created commands by the user.
        */
        static int commandCounter;
        /**
         * @brief Keeps track of the unique ID of the command.
        */
        int uniqueCommandID;
        /**
         * @brief A vector used to store the arguments of each command.
        */
        std::vector<std::string> commandArguments;
        /**
         * @brief Basic clone method.
         * @return Returns a pointer to a copy of the command.
        */
        command* clone();
        /**
         * @brief Default empty constructor.
        */
        command();
        /**
         * @brief Constructor initializing the command through the command arguments passed.
         * @param _commandArguments Vector containing the parameters of the command to be created.
        */
        command(std::vector<std::string> &_commandArguments);
        /**
         * @brief Prints information about the command.
        */
        void printInfo(std::ostream &out = std::cout);
};