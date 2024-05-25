#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include "image.hpp"
#include "imagePPM.hpp"
#include "command.hpp"
#include "session.hpp"
#include "visitor.hpp"
session::session(std::vector<Image *> &_activeImages)
{
    sessionCounter++;
    uniqueSessionID = sessionCounter;
    for (Image *image : _activeImages)
    {
        activeImages.push_back(image->clone());
    }
}
void session::printInfo(std::ostream &out)
{
    for (Image *image : activeImages)
    {
        image->PrintDetails(out);
    }
}
void session::appendCommand(command &command)
{
    for (Image *image : activeImages)
    {
        image->pendingCommands.push_back(command.clone());
    }
}
session::~session()
{
    for (Image *image : activeImages)
    {
        delete[] image;
    }
}
int session::sessionCounter = 0;

void sessionHandler::sendCommandToSession(command &_command)
{
    activeSessions[activeSessionID]->appendCommand(_command);
}
void sessionHandler::changeActiveSession(int newSessionNumber)
{
    if (newSessionNumber - 1 < activeSessions.size())
        activeSessionID = newSessionNumber - 1;
    else
        std::cerr << "Invalid session number." << std::endl;
}
void sessionHandler::createNewSession(std::vector<Image*> &initialImages, std::ostream &out)
{
    session *newSession = new session(initialImages);
    activeSessionID = newSession->uniqueSessionID;
    activeSessions.push_back(newSession);
    newSession->printInfo(out);
}
command* sessionHandler::CommandReader::readCommand()
{
    std::vector<std::string> currentArguments;
    std::getline(std::cin, rawCommand);
    while (rawCommand[0] == ' ')
        rawCommand.erase(rawCommand.begin());
    rawCommand += " ";
    int lastCharacterPosition = 0;
    int rawCommandSize = (int)rawCommand.size();
    for (int i = 0; i < rawCommandSize; i++)
    {
        if (rawCommand[i] == ' ')
        {
            currentArguments.push_back(rawCommand.substr(lastCharacterPosition, i - lastCharacterPosition));
            while (i < rawCommandSize && rawCommand[i] == ' ')
            {
                i++;
            }
            lastCharacterPosition = i;
        }
    }
    command *newCommand = new command(currentArguments);
    return newCommand;
}
std::string sessionHandler::CommandReader::findExtension(std::string filename)
{
    int dotPos = filename.rfind('.');
    if(dotPos != std::string::npos)
    {
        return filename.substr(dotPos+1);
    }
    else
    {
        //throw exception
        return "";
    }
}
void sessionHandler::executeLoadCommand(command &currentCommand)
{
    std::vector<Image*> inputImages;
    for (int i = 1; i < currentCommand.commandArguments.size(); i++)
    {
        std::string filename = currentCommand.commandArguments[i];
        std::string fileExtension = CommandReader::findExtension(filename);
        if (fileExtension == "ppm")
        {
            ImagePPM *newImagePPM = new ImagePPM();
            readImage *PPMImageReader = new readImage(filename);
            newImagePPM->AcceptVisitor(PPMImageReader);
            inputImages.push_back(newImagePPM);
        }
        else if (fileExtension == "pgm")
        {
            /*todo*/
        }
        else if (fileExtension == "pbm")
        {
            /*todo*/
        }
        else
        {
            // throw exception
        }
    }
    this->createNewSession(inputImages);
}
/*A*/
void sessionHandler::executeSaveCommand(command &currentCommand)
{
    for (Image *image : activeSessions[activeSessionID]->activeImages)
    {
        for(command *tempCommand : image->pendingCommands)
        {
            if(tempCommand->commandArguments[0] == "grayscale")
            {
                grayscale* grayscaleImageMaker = new grayscale();
                image->AcceptVisitor(grayscaleImageMaker);
            }
            else if(tempCommand->commandArguments[0] == "monochrome")
            {
                monochrome* monochromeImageMaker = new monochrome();
                image->AcceptVisitor(monochromeImageMaker);
            }
            else if(tempCommand->commandArguments[0] == "negative")
            {
                negative* negativeImageMaker = new negative();
                image->AcceptVisitor(negativeImageMaker);
            }
            else if(tempCommand->commandArguments[0] == "rotate")
            {
                if(tempCommand->commandArguments[1] == "left")
                {
                    rotateRight* rotateRightImageMaker = new rotateRight();
                    image->AcceptVisitor(rotateRightImageMaker);
                }
                else if(tempCommand->commandArguments[1] == "right")
                {
                    rotateLeft* rotateLeftImageMaker = new rotateLeft();
                    image->AcceptVisitor(rotateLeftImageMaker);
                }
            }
        }
        saveImage* saveImageMaker = new saveImage();
        image->AcceptVisitor(saveImageMaker);
    }
}
void sessionHandler::executeUndoCommand(command &currentCommand)
{
    for (Image *image : activeSessions[activeSessionID]->activeImages)
    {
        if(image->pendingCommands.size())
            image->pendingCommands.pop_back();
    }
}
void sessionHandler::executeSaveAsCommand(command &currentCommand)
{
    this->executeSaveCommand(currentCommand);
    std::string firstImageExtension = CommandReader::findExtension(activeSessions[activeSessionID]->activeImages[0]->filename);
    std::string secondImageExtension = CommandReader::findExtension(currentCommand.commandArguments[1]);
    if(firstImageExtension != secondImageExtension)
    {
        /*throw*/
        return;
    }
    saveAsImage* saveAsImageMaker = new saveAsImage(currentCommand.commandArguments[1]);
    activeSessions[activeSessionID]->activeImages[0]->AcceptVisitor(saveAsImageMaker);
    // remove(activeSessions[activeSessionID]->activeImages[0]->filename.c_str());
    const char* filename_cstr = activeSessions[activeSessionID]->activeImages[0]->filename.c_str();
    remove(filename_cstr);
}
void sessionHandler::executeAddCommand(command &currentCommand)
{
    readImage* readImageMaker = new readImage(currentCommand.commandArguments[1]);
    std::string fileExtension = CommandReader::findExtension(currentCommand.commandArguments[1]);
    if(fileExtension == "ppm")
    {
        ImagePPM* newImage = new ImagePPM();
        readImageMaker->VisitPPM(*newImage);
        activeSessions[activeSessionID]->activeImages.push_back(newImage);
    }
    else if(fileExtension == "pgm")
    {
        
    }
    else if(fileExtension == "pbm")
    {

    }
}
void sessionHandler::executeCommand(command &currentCommand)
{
    std::string commandName = currentCommand.commandArguments[0];
    if(commandName == "load")
    {
        this->executeLoadCommand(currentCommand);
    }
    else if(commandName == "save")
    {
        this->executeSaveCommand(currentCommand);
    }
    else if(commandName == "undo")
    {
        this->executeUndoCommand(currentCommand);
    }
    else if(commandName == "saveas")
    {
        if(currentCommand.commandArguments.size() != 2)
        {
            /*throw*/
        }
        this->executeSaveAsCommand(currentCommand);
    }
    else if(commandName == "add")
    {
        this->executeAddCommand(currentCommand);
    }
    else if(commandName == "session")
    {

    }
    else if(commandName == "switch")
    {

    }
    else if(commandName == "collage")
    {

    }
    else if(commandName == "grayscale" || commandName == "negative"
        || commandName == "monochrome" || commandName == "rotate")
    {
        
    }

}