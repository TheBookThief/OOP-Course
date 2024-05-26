#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include "image.hpp"
#include "imagePPM.hpp"
#include "command.hpp"
#include "session.hpp"
#include "visitor.hpp"
int session::sessionCounter = 0;
session::session(std::vector<Image *> &_activeImages)
{
    uniqueSessionID = sessionCounter;
    sessionCounter++;
    for (Image *image : _activeImages)
    {
        activeImages.push_back(image->clone());
    }
}

void session::printInfo(std::ostream &out)
{
    std::cout<<"Current session is: "<<this->uniqueSessionID<<std::endl;
    for(Image *image : activeImages)
    {
        std::cout<<image->filename<<std::endl;
    }
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
        delete image;
    }
}

void sessionHandler::sendCommandToSession(command &_command)
{
    activeSessions[activeSessionID]->appendCommand(_command);
}
void sessionHandler::changeActiveSession(int newSessionNumber)
{
    if (newSessionNumber < activeSessions.size())
        activeSessionID = newSessionNumber;
    else
        std::cerr << "Invalid session number." << std::endl;
}
void sessionHandler::createNewSession(std::vector<Image*> &initialImages, std::ostream &out)
{
    session *newSession = new session(initialImages);
    std::cout<<"! "<<newSession->uniqueSessionID<<std::endl;
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
            delete PPMImageReader;
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
    std::cout<<"! Loaded Images vector"<<std::endl;
    for(int i=0; i<inputImages.size(); i++)
    {
        std::cout<<inputImages[i]->filename<<std::endl;
    }
    this->createNewSession(inputImages);
}
/*A*/
void sessionHandler::executeSaveCommand(command &currentCommand)
{
    saveImage* saveImageMaker = new saveImage();
    for (Image *image : activeSessions[activeSessionID]->activeImages)
    {
        std::cout<<"! For image : "<<image->filename<<std::endl;
        for(command *tempCommand : image->pendingCommands)
        {
            std::cout<<"! Applying command : "; tempCommand->printInfo(); std::cout<<std::endl;
            if(tempCommand->commandArguments[0] == "grayscale")
            {
                grayscale* grayscaleImageMaker = new grayscale();
                image->AcceptVisitor(grayscaleImageMaker);
                delete grayscaleImageMaker;
                std::cout<<"! Executed command grayscale"<<std::endl;
            }
            else if(tempCommand->commandArguments[0] == "monochrome")
            {
                monochrome* monochromeImageMaker = new monochrome();
                image->AcceptVisitor(monochromeImageMaker);
                delete monochromeImageMaker;
            }
            else if(tempCommand->commandArguments[0] == "negative")
            {
                negative* negativeImageMaker = new negative();
                image->AcceptVisitor(negativeImageMaker);
                delete negativeImageMaker;
            }
            else if(tempCommand->commandArguments[0] == "rotate")
            {
                if(tempCommand->commandArguments[1] == "left")
                {
                    rotateRight* rotateRightImageMaker = new rotateRight();
                    image->AcceptVisitor(rotateRightImageMaker);
                    delete rotateRightImageMaker;
                }
                else if(tempCommand->commandArguments[1] == "right")
                {
                    rotateLeft* rotateLeftImageMaker = new rotateLeft();
                    image->AcceptVisitor(rotateLeftImageMaker);
                    delete rotateLeftImageMaker;
                }
            }
        }
        image->AcceptVisitor(saveImageMaker);
    }
    for (Image *image : activeSessions[activeSessionID]->activeImages)
    {
        for(command *tempCommand : image->pendingCommands)
        {
            delete tempCommand;
        }
        image->pendingCommands.clear();
    }
    delete saveImageMaker;

}
void sessionHandler::executeUndoCommand(command &currentCommand)
{
    if(activeSessions[activeSessionID]->pendingOperationsID.size() == 0) return;

    int commandIDToRemove = activeSessions[activeSessionID]->pendingOperationsID.back();
    activeSessions[activeSessionID]->pendingOperationsID.pop_back();
    for (Image *image : activeSessions[activeSessionID]->activeImages)
    {
        if(image->pendingCommands.size() == 0) continue;
        if(image->pendingCommands.back()->uniqueCommandID == commandIDToRemove)
        {
            delete image->pendingCommands.back();
            image->pendingCommands.pop_back();
        }
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
    
    const char* filename_cstr = activeSessions[activeSessionID]->activeImages[0]->filename.c_str();
    remove(filename_cstr);

    saveAsImage* saveAsImageMaker = new saveAsImage(currentCommand.commandArguments[1]);
    activeSessions[activeSessionID]->activeImages[0]->AcceptVisitor(saveAsImageMaker);
    delete saveAsImageMaker;
}
void sessionHandler::executeAddImageCommand(command &currentCommand)
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
    delete readImageMaker;
}
void sessionHandler::executeChangeActiveSessionCommand(command &currentCommand)
{
    if(currentCommand.commandArguments.size() != 2)
    {
        /*throw*/
    }
    int newSessionID = 0;
    for(int i=0; i<currentCommand.commandArguments[1].size(); i++)
    {
        if(currentCommand.commandArguments[1][i] >= '0' && currentCommand.commandArguments[1][i] <= '9')
        {
            newSessionID *= 10;
            newSessionID += (currentCommand.commandArguments[1][i]-'0');
        }
    }
    std::cout<<"! "<<newSessionID<<" "<<activeSessions.size()<<std::endl;
    if (newSessionID < activeSessions.size())
        activeSessionID = newSessionID;
    else
    {
        /*throw*/
        std::cerr << "Invalid session number." << std::endl;
    }
}
void sessionHandler::executeSessionInfoCommand(command &currentCommand)
{
    std::cout<<"! activeSessionID : "<<activeSessionID<<std::endl;
    activeSessions[activeSessionID]->printInfo();
}
void sessionHandler::executeAddTransformationCommand(command &currentCommand)
{
    activeSessions[activeSessionID]->pendingOperationsID.push_back(currentCommand.uniqueCommandID);
    for(Image* image : activeSessions[activeSessionID]->activeImages)
    {
        image->pendingCommands.push_back(currentCommand.clone());
    }
}
void sessionHandler::executeMakeCollageCommand(command &currentCommand)
{
    std::string firstFileExtension = CommandReader::findExtension(currentCommand.commandArguments[2]);
    std::string secondFileExtension = CommandReader::findExtension(currentCommand.commandArguments[3]);
    if(firstFileExtension != secondFileExtension)
    {
        /*throw*/
    }

    int collageDirection;
    if (currentCommand.commandArguments[1] == "horizontal")
        collageDirection = 1;
    else
        collageDirection = 2;

    if (firstFileExtension == "ppm")
    {
        ImagePPM *currentTransformationImage = new ImagePPM();
        readImage *firstImageReader = new readImage(currentCommand.commandArguments[3]);
        currentTransformationImage->AcceptVisitor(firstImageReader);
        delete firstImageReader;

        ImagePPM *collageResult = new ImagePPM();

        readImage *collageResultReader = new readImage(currentCommand.commandArguments[2]);
        collageResult->AcceptVisitor(collageResultReader);
        delete collageResultReader;

        collage *collageMaker = new collage(*currentTransformationImage, collageDirection);
        collageResult->AcceptVisitor(collageMaker);
        delete collageMaker;

        saveAsImage *saveAsImageMaker = new saveAsImage(currentCommand.commandArguments[4]);
        collageResult->AcceptVisitor(saveAsImageMaker);
        delete saveAsImageMaker;
        delete currentTransformationImage;
        delete collageResult;
    }
    else if (firstFileExtension == "pgm")
    {

    }
    else if (firstFileExtension == "pbm")
    {

    }
    command *addNewCollageCommand = new command();
    addNewCollageCommand->commandArguments.push_back("add");
    addNewCollageCommand->commandArguments.push_back(currentCommand.commandArguments[4]);
    this->executeAddImageCommand(*addNewCollageCommand);
    delete addNewCollageCommand;
}
void sessionHandler::executeCommand(command &currentCommand)
{
    std::string commandName = currentCommand.commandArguments[0];
    std::cout<<"! Command is "<< commandName <<std::endl;
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
        this->executeAddImageCommand(currentCommand);
    }
    else if(commandName == "session")
    {
        this->executeSessionInfoCommand(currentCommand);
    }
    else if(commandName == "switch")
    {
        this->executeChangeActiveSessionCommand(currentCommand);
    }
    else if(commandName == "collage")
    {
        this->executeMakeCollageCommand(currentCommand);
    }
    else if(commandName == "grayscale" || commandName == "negative"
        || commandName == "monochrome" || commandName == "rotate")
    {
        this->executeAddTransformationCommand(currentCommand);   
    }
}
/*session handler destructor*/