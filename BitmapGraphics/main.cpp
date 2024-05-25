#include<iostream>
#include<string>
#include<vector>
#include "visitor.hpp"
#include "session.hpp"
#include "command.hpp"
#include "image.hpp"
#include "imagePPM.hpp"
int main()
{
    sessionHandler* sessionHandlerWorker = new sessionHandler();

    while(1)
    {
        command* currentCommand = sessionHandlerWorker->CommandReaderWorker.readCommand();
        sessionHandlerWorker->executeCommand(*currentCommand);
    }

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