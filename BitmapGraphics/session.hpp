#ifndef SESSION_HPP
#define SESSION_HPP
class session
{
    public:
        static int sessionCounter;
        int uniqueSessionID;
        std::vector<Image*> activeImages;
        session(std::vector<Image*> &_activeImages);
        void addImageToSession(Image *image);
        void printInfo(std::ostream& out = std::cout);
        void acceptCommand(command &command);
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
};
#endif