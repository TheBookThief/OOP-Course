#include<iostream>
#include<string>
#include "visitor.hpp"
#include "session.hpp"
// class CommandHandler
// {
//     std::string rawCommand;
//     std::string* commandArguments;
//     std::size_t commandArgumentsSize;

//     std::string filename;
//     CommandHandler(std::string _commandName, std::stirng _filename) : commandName(_commandName), filename(_filename) {}
//     void readCommand()
//     {
//         std::getline(std::cin, rawCommand);
//         for(int i=0; i<strlen(rawCommand); i++)
//         {
//             if(rawCommand[i] == ' ') 
//                 commandArgumentsSize++;
//         }
        

//     }
// };
int main()
{
    ImagePPM* sampleImagePPM = new ImagePPM();
    
    readImage* sampleImageReader = new readImage("federer.ppm");
    sampleImageReader->VisitPPM(*sampleImagePPM);

    // ImagePPM* sampleImagePPM2 = new ImagePPM();

    // readImage* sampleImageReader2 = new readImage("federer - Copy.ppm");
    // sampleImageReader2->VisitPPM(*sampleImagePPM2);

    // saveAsImage* saverAsImage = new saveAsImage("federer_new.ppm");
    // saverAsImage->VisitPPM(*sampleImagePPM);

    // grayscale* grayscaleImageMaker = new grayscale();
    // grayscaleImageMaker->VisitPPM(*sampleImagePPM);

    // monochrome* monochromer = new monochrome();
    // monochromer->VisitPPM(*sampleImagePPM);

    // negative* negativer = new negative();
    // negativer->VisitPPM(*sampleImagePPM);

    // rotateRight* rotator = new rotateRight();
    // rotator->VisitPPM(*sampleImagePPM);
    
    // collage* collager = new collage(*sampleImagePPM2, 2);
    // collager->VisitPPM(*sampleImagePPM);

    // saveImage* saverImage = new saveImage();
    // saverImage->VisitPPM(*sampleImagePPM);

    std::vector<Image*> testingVec;
    testingVec.push_back(sampleImagePPM);
    
    sessionHandler* currentSessionHandler = new sessionHandler();
    currentSessionHandler->createNewSession(testingVec);
}   