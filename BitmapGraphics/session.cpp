#include<iostream>
#include<vector>
#include<string>
#include "session.hpp"
session::session(std::vector<Image *> &_activeImages)
{
    sessionCounter++;
    uniqueSessionID = sessionCounter;
    for (Image *image : _activeImages)
    {
        activeImages.push_back(image->clone());
    }
}
void session::addImageToSession(Image *image)
{
    activeImages.push_back(image->clone());
}
void session::printInfo(std::ostream &out)
{
    for (Image *image : activeImages)
    {
        image->PrintDetails(out);
    }
}
void session::acceptCommand(command &command)
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
    activeSessions[activeSessionID]->acceptCommand(_command);
}
void sessionHandler::changeActiveSession(int newSessionNumber)
{
    if (newSessionNumber - 1 < activeSessions.size())
        activeSessionID = newSessionNumber - 1;
    else
        std::cerr << "Invalid session number." << std::endl;
}
void sessionHandler::createNewSession(std::vector<Image *> &initialImages, std::ostream &out)
{
    session *newSession = new session(initialImages);
    activeSessionID = newSession->uniqueSessionID;
    activeSessions.push_back(newSession);
    newSession->printInfo(out);
}