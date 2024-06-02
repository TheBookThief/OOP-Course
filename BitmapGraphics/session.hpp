#pragma once
#include<iostream>
#include<string>
#include<vector>
/**
* @brief Class for handling sessions.
*/
class Image;
class Command;

class session
{
    public:
        /**
         * @brief Counts the number of created sessions.
        */
        static int sessionCounter;
        /**
         * @brief Unique ID of the current session object.
        */
        int uniqueSessionID;
        /**
         * @brief Contains the all images present in the session object.
        */
        std::vector<Image*> activeImages;
        /**
         * @brief Contains the unique operation id-s which were cast on the session.
        */
        std::vector<int> pendingOperationsID;
        /**
         * @brief Constructor which creates a session based on the initial images to be in it.
        */
        session(const std::vector<Image*> &_activeImages);
        /**
         * @brief Prints informations about the session and its images.
        */
        void printInfo(std::ostream& out = std::cout);
        // void appendCommand(command &command);
        /**
         * @brief Destructor used to remove all images from the sesssion and the session itself.
        */
        ~session();
};
/**
* @brief The sessionHandler class is responsible for executing the correct command
* based on the user's input. The subclass CommandReader is responsible for reading
* and interpreting the user's input.
*/
class sessionHandler
{
    private:
        /**
         * @brief ID of the session to which any transformation would be performed.
        */
        int activeSessionID;
    public:
        /**
         * @brief All started sessions in the current execution of the program.
        */
        std::vector<session*> activeSessions;
        //void sendCommandToSession(command &_command);
        // void changeActiveSession(int newSessionNumber);
        /**
         * @brief Created a new session with the initial images in it.
         * @param initialImages Images to be loaded to the session when it is created
         * @param out Channel for outputing information about the session, default value is std::cout.
        */
        void createNewSession(std::vector<Image*> &initialImages, std::ostream &out = std::cout);
        /**
         * @brief General method for executing a command after it's read. It's purpose is 
         * to send it to the right method for actually performing the command.
         * @return Status of program after completing command 1 - continue executing command, 0 - marks end of program
        */
        int executeCommand(const command &_command);
        /**
         * @brief Executes the load command given by the user.
        */
        void executeLoadCommand(const command &currentCommand);
        /**
         * @brief Executes the save command given by the user.
        */
        void executeSaveCommand(const command &currentCommand);
        /**
         * @brief Executes the undo command given by the user.
        */
        void executeUndoCommand(const command &currentCommand);
        /**
         * @brief Executes the saveas command given by the user.
        */
        void executeSaveAsCommand(const command &currentCommand);
        /**
         * @brief Executes the add image command given by the user.
        */
        void executeAddImageCommand(const command &currentCommand);
        /**
         * @brief Prints info about the active session.
        */
        void executeSessionInfoCommand(const command &currentCommand);
        /**
         * @brief Changes the active session given by the user.
        */
        void executeChangeActiveSessionCommand(const command &currentCommand);
        /**
         * @brief Appends a transformation to the active session.
        */
        void executeAddTransformationCommand(const command &currentCommand);
        /**
         * @brief Creates a collage using the inputted images.
        */
        void executeMakeCollageCommand(const command &currentCommand);
        /**
         * @brief Prints the basics of all commands to the user.
        */
        void executeHelpCommand(const command &currentCommand);
        /**
         * @brief Erases all sessions and their respective images.
        */
        ~sessionHandler();
        /**
         * @brief CommandReader class used to read the user's input
         * and provide it to the sessionHandler class for execution
        */
        class CommandReader
        {
            public:
                /**
                * @brief Raw string representing the input.
                */
                std::string rawCommand;
                /**
                * @brief Length of the raw input.
                */
                int rawCommandSize;
                /**
                * @brief Default method to read user's input from the terminal.
                */
                command* readCommand();
                /**
                * @brief Return's the extension of the string provided
                * @param filename a string which should be representing a filename. Must not include quotes.
                */
                static std::string findExtension(std::string filename);
        };
        /**
        * @brief Sample worker for reading the input.
        */
        CommandReader CommandReaderWorker;
};