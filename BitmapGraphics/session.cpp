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
session::session(const std::vector<Image *> &_activeImages)
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
// void session::appendCommand(command &command)
// {
//     for (Image *image : activeImages)
//     {
//         image->pendingCommands.push_back(command.clone());
//     }
// }
session::~session()
{
    for (Image *image : activeImages)
    {
        delete image;
    }
}

// void sessionHandler::sendCommandToSession(command &_command)
// {
//     activeSessions[activeSessionID]->appendCommand(_command);
// }
// void sessionHandler::changeActiveSession(int newSessionNumber)
// {
//     try
//     {
//         if (newSessionNumber < activeSessions.size())
//             activeSessionID = newSessionNumber;
//         else
//             throw std::out_of_range("Invalid session number");
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
// }
void sessionHandler::createNewSession(std::vector<Image*> &initialImages, std::ostream &out)
{
    session *newSession = new session(initialImages);
    // std::cout<<"! "<<newSession->uniqueSessionID<<std::endl;
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
std::string sessionHandler::CommandReader::findExtension(const std::string filename)
{
    try
    {
        int dotPos = filename.rfind('.');
        if (dotPos != std::string::npos)
        {
            return filename.substr(dotPos + 1);
        }
        else
        {
            throw std::logic_error("No extension of filename supplied to command found.");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return "";
}
void sessionHandler::executeLoadCommand(const command &currentCommand)
{
    try
    {
        if(currentCommand.commandArguments.size() < 2)
        {
            throw std::logic_error("Invalid number of arguments.");
            return;
        }
        std::vector<Image *> inputImages;
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
                ImagePGM *newImagePGM = new ImagePGM();
                readImage *PGMImageReader = new readImage(filename);
                newImagePGM->AcceptVisitor(PGMImageReader);
                inputImages.push_back(newImagePGM);
                delete PGMImageReader;
            }
            else if (fileExtension == "pbm")
            {
                ImagePBM *newImagePBM = new ImagePBM();
                readImage *PBMImageReader = new readImage(filename);
                newImagePBM->AcceptVisitor(PBMImageReader);
                inputImages.push_back(newImagePBM);
                delete PBMImageReader;
            }
            else
            {
                throw std::logic_error("Invalid file extension.");
                return;
            }
        }
        this->createNewSession(inputImages);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
void sessionHandler::executeSaveCommand(const command &currentCommand)
{
    try
    {
        if (currentCommand.commandArguments.size() != 1)
        {
            throw std::logic_error("Invalid number of arguments.");
            return;
        }
        saveImage *saveImageMaker = new saveImage();
        for (Image *image : activeSessions[activeSessionID]->activeImages)
        {
            for (command *tempCommand : image->pendingCommands)
            {
                if (tempCommand->commandArguments[0] == "grayscale")
                {
                    grayscale *grayscaleImageMaker = new grayscale();
                    image->AcceptVisitor(grayscaleImageMaker);
                    delete grayscaleImageMaker;
                }
                else if (tempCommand->commandArguments[0] == "monochrome")
                {
                    monochrome *monochromeImageMaker = new monochrome();
                    image->AcceptVisitor(monochromeImageMaker);
                    delete monochromeImageMaker;
                }
                else if (tempCommand->commandArguments[0] == "negative")
                {
                    negative *negativeImageMaker = new negative();
                    image->AcceptVisitor(negativeImageMaker);
                    delete negativeImageMaker;
                }
                else if (tempCommand->commandArguments[0] == "rotate")
                {
                    if (tempCommand->commandArguments[1] == "right")
                    {
                        rotateRight *rotateRightImageMaker = new rotateRight();
                        image->AcceptVisitor(rotateRightImageMaker);
                        delete rotateRightImageMaker;
                    }
                    else if (tempCommand->commandArguments[1] == "left")
                    {
                        rotateLeft *rotateLeftImageMaker = new rotateLeft();
                        image->AcceptVisitor(rotateLeftImageMaker);
                        delete rotateLeftImageMaker;
                    }
                    else
                    {
                        throw std::logic_error("Invalid rotation direction.");
                        return;
                    }
                }
                else
                {
                    throw std::logic_error("Invalid operation.");
                    return;
                }
            }
            image->AcceptVisitor(saveImageMaker);
        }
        for (Image *image : activeSessions[activeSessionID]->activeImages)
        {
            for (command *tempCommand : image->pendingCommands)
            {
                delete tempCommand;
            }
            image->pendingCommands.clear();
        }
        delete saveImageMaker;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void sessionHandler::executeUndoCommand(const command &currentCommand)
{
    try
    {
        if(currentCommand.commandArguments.size() != 1)
        {
            throw std::logic_error("Invalid number of arguments.");
            return;
        }
        if(activeSessions[activeSessionID]->pendingOperationsID.size() == 0) return;

        int commandIDToRemove = activeSessions[activeSessionID]->pendingOperationsID.back();
        activeSessions[activeSessionID]->pendingOperationsID.pop_back();
        for (Image *image : activeSessions[activeSessionID]->activeImages)
        {
            if(image->pendingCommands.size() == 0) continue;
            if(image->pendingCommands.back()->getCommandID() == commandIDToRemove)
            {
                delete image->pendingCommands.back();
                image->pendingCommands.pop_back();
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
void sessionHandler::executeSaveAsCommand(const command &currentCommand)
{
    try
    {    
        if(currentCommand.commandArguments.size() != 2)
        {
            throw std::logic_error("Invalid number of arguments");
            return;
        }
        this->executeSaveCommand(currentCommand);
        std::string firstImageExtension = CommandReader::findExtension(activeSessions[activeSessionID]->activeImages[0]->filename);
        std::string secondImageExtension = CommandReader::findExtension(currentCommand.commandArguments[1]);
        if(firstImageExtension != secondImageExtension)
        {
            throw std::logic_error("Desired file extension and original don't match");
            return;
        }
        
        const char* filename_cstr = activeSessions[activeSessionID]->activeImages[0]->filename.c_str();
        remove(filename_cstr);

        saveAsImage* saveAsImageMaker = new saveAsImage(currentCommand.commandArguments[1]);
        activeSessions[activeSessionID]->activeImages[0]->AcceptVisitor(saveAsImageMaker);
        delete saveAsImageMaker;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
void sessionHandler::executeAddImageCommand(const command &currentCommand)
{
    try
    {  
        if(currentCommand.commandArguments.size() != 2)
        {
            throw std::logic_error("Invalid number of arguments.");
            return;
        }  
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
            ImagePGM* newImage = new ImagePGM();
            readImageMaker->VisitPGM(*newImage);
            activeSessions[activeSessionID]->activeImages.push_back(newImage);
        }
        else if(fileExtension == "pbm")
        {
            ImagePBM* newImage = new ImagePBM();
            readImageMaker->VisitPBM(*newImage);
            activeSessions[activeSessionID]->activeImages.push_back(newImage);
        }
        else
        {
            throw std::logic_error("Invalid file extension.");
            return;
        }
        delete readImageMaker;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
void sessionHandler::executeChangeActiveSessionCommand(const command &currentCommand)
{
    try
    {
        if(currentCommand.commandArguments.size() != 2)
        {
            throw std::logic_error("Invalid number of arguments.");
            return;
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
        {
            activeSessionID = newSessionID;
        }
        else
        {
            throw std::logic_error("Invalid session number.");
            return;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
void sessionHandler::executeSessionInfoCommand(const command &currentCommand)
{
    activeSessions[activeSessionID]->printInfo();
}
void sessionHandler::executeAddTransformationCommand(const command &currentCommand)
{
    try
    {
        activeSessions[activeSessionID]->pendingOperationsID.push_back(currentCommand.getCommandID());
        for(Image* image : activeSessions[activeSessionID]->activeImages)
        {
            image->pendingCommands.push_back(currentCommand.clone());
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
void sessionHandler::executeMakeCollageCommand(const command &currentCommand)
{
    try
    {
        if(currentCommand.commandArguments.size() != 5)
        {
            throw std::logic_error("Invalid number of arguments");
            return;
        }
        std::string firstFileExtension = CommandReader::findExtension(currentCommand.commandArguments[2]);
        std::string secondFileExtension = CommandReader::findExtension(currentCommand.commandArguments[3]);
        if(firstFileExtension != secondFileExtension)
        {
            throw std::logic_error("Extensions of images do not match.");
            return;
        }
        int collageDirection;
        if (currentCommand.commandArguments[1] == "horizontal")
            collageDirection = 1;
        else
            collageDirection = 2;

        if (firstFileExtension == "ppm")
        {
            ImagePPM *currentTransformationImage = new ImagePPM();
            readImage *firstImageMaker = new readImage(currentCommand.commandArguments[3]);
            currentTransformationImage->AcceptVisitor(firstImageMaker);

            ImagePPM *collageResult = new ImagePPM();

            readImage *collageResultReader = new readImage(currentCommand.commandArguments[2]);
            collageResult->AcceptVisitor(collageResultReader);

            collage *collageMaker = new collage(*currentTransformationImage, collageDirection);
            collageResult->AcceptVisitor(collageMaker);
            
            saveAsImage *saveAsImageMaker = new saveAsImage(currentCommand.commandArguments[4]);
            collageResult->AcceptVisitor(saveAsImageMaker);
            delete saveAsImageMaker, collageResultReader, collageResult, firstImageMaker, currentTransformationImage, collageMaker;
            
        }
        else if (firstFileExtension == "pgm")
        {
            ImagePGM *currentTransformationImage = new ImagePGM();
            readImage *firstImageMaker = new readImage(currentCommand.commandArguments[3]);
            currentTransformationImage->AcceptVisitor(firstImageMaker);

            ImagePGM *collageResult = new ImagePGM();

            readImage *collageResultReader = new readImage(currentCommand.commandArguments[2]);
            collageResult->AcceptVisitor(collageResultReader);

            collage *collageMaker = new collage(*currentTransformationImage, collageDirection);
            collageResult->AcceptVisitor(collageMaker);
            
            saveAsImage *saveAsImageMaker = new saveAsImage(currentCommand.commandArguments[4]);
            collageResult->AcceptVisitor(saveAsImageMaker);
            delete saveAsImageMaker, collageResultReader, collageResult, firstImageMaker, currentTransformationImage, collageMaker;
        }
        else if (firstFileExtension == "pbm")
        {
            ImagePBM *currentTransformationImage = new ImagePBM();
            readImage *firstImageMaker = new readImage(currentCommand.commandArguments[3]);
            currentTransformationImage->AcceptVisitor(firstImageMaker);

            ImagePBM *collageResult = new ImagePBM();

            readImage *collageResultReader = new readImage(currentCommand.commandArguments[2]);
            collageResult->AcceptVisitor(collageResultReader);

            collage *collageMaker = new collage(*currentTransformationImage, collageDirection);
            collageResult->AcceptVisitor(collageMaker);
            
            saveAsImage *saveAsImageMaker = new saveAsImage(currentCommand.commandArguments[4]);
            collageResult->AcceptVisitor(saveAsImageMaker);
            delete saveAsImageMaker, collageResultReader, collageResult, firstImageMaker, currentTransformationImage, collageMaker;
        }
        else
        {
            throw std::logic_error("Invalid file extension.");
            return;
        }
        command *addNewCollageCommand = new command();
        addNewCollageCommand->commandArguments.push_back("add");
        addNewCollageCommand->commandArguments.push_back(currentCommand.commandArguments[4]);
        this->executeAddImageCommand(*addNewCollageCommand);
        delete addNewCollageCommand;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}
void sessionHandler::executeCommand(const command &currentCommand)
{
    try
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
        else if(commandName == "help")
        {
            this->executeHelpCommand(currentCommand);   
        }
        else if(commandName == "close")
        {
            exit(0);
        }
        else
        {
            throw std::logic_error("Invalid command");
            return;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
void sessionHandler::executeHelpCommand(const command &currentCommand)
{
    try
    {
        std::vector<std::pair<std::string,std::string>> helpMaker;
        helpMaker.push_back({"load <filenames>","Starts a new session with the specified images."});
        helpMaker.push_back({"save","Applies all operations on the images in the session."});
        helpMaker.push_back({"saveas","Applies all operations on the images in the session and saves the first loaded image with the provided new name."});
        helpMaker.push_back({"help","Displays this lol."});
        helpMaker.push_back({"close","Closes the program."});
        helpMaker.push_back({"grayscale","Applies grayscale operation to all images in session."});
        helpMaker.push_back({"monochrome","Applies monochrome operation to all images in the session."});
        helpMaker.push_back({"negative","Applies negative operation to all images in the session."});
        helpMaker.push_back({"rotate <direction>","Rotates the images in the session in the specified <direction>. <direction> = left|right."});
        helpMaker.push_back({"undo","Reverses the last step."});
        helpMaker.push_back({"add <image>","Adds the specified images to the current session."});
        helpMaker.push_back({"session info","Displays information about the current session."});
        helpMaker.push_back({"switch <session>","Switches to the speciffied session number."});
        helpMaker.push_back({"collage <direction> <image1> <image2> <outimage>","Makes a collage in the specificed direction from <image1> and <image2> and saves it as <outimage>."});
        for(auto x: helpMaker)
        {
            std::cout<<x.first;
            for(int i=0; i<10-x.first.size(); i++)
            {
                std::cout<<" ";
            }
            std::cout<<x.second;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
sessionHandler::~sessionHandler()
{
    for(auto it = activeSessions.rbegin(); it != activeSessions.rend(); it++)
    {
        delete *it;
    }
    activeSessions.clear();
}