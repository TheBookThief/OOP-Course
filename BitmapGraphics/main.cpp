#include<iostream>
#include<string>
#include<vector>
#include "visitor.hpp"
#include "session.hpp"
#include "command.hpp"
#include "image.hpp"
#include "imagePPM.hpp"
void Test1()
{
    ImagePPM* sampleImagePPM = new ImagePPM();
    
    readImage* sampleImageReader = new readImage("federer.ppm");
    sampleImageReader->VisitPPM(*sampleImagePPM);

    grayscale* grayscaleImageMaker = new grayscale();
    grayscaleImageMaker->VisitPPM(*sampleImagePPM);

    saveImage* saverImage = new saveImage();
    saverImage->VisitPPM(*sampleImagePPM);
}
void Test2()
{
    ImagePBM* sampleImagePBM = new ImagePBM();
    
    readImage* sampleImageReader = new readImage("sample.pbm");
    sampleImageReader->VisitPBM(*sampleImagePBM);

    rotateRight* rotator = new rotateRight();
    rotator->VisitPBM(*sampleImagePBM);
    rotator->VisitPBM(*sampleImagePBM);

    saveImage* saverImage = new saveImage();
    saverImage->VisitPBM(*sampleImagePBM);
}
void Test3()
{
    if(sessionHandler::CommandReader::findExtension("randomname.ppm") != "ppm") 
    {
        std::cerr<<"Test3 failed"<<std::endl;
        return;
    }
    if(sessionHandler::CommandReader::findExtension("randomname.ppppppppm") != "ppppppppm") 
    {
        std::cerr<<"Test3 failed"<<std::endl;
        return;
    }
    sessionHandler::CommandReader::findExtension("noextension"); // Should throw exception
}
void Test4()
{
    ImagePPM* sampleImagePPM = new ImagePPM();
    
    readImage* sampleImageReader = new readImage("federer.ppm");
    sampleImageReader->VisitPPM(*sampleImagePPM);

    monochrome* monochromeImageMaker = new monochrome();
    monochromeImageMaker->VisitPPM(*sampleImagePPM);

    saveImage* saverImage = new saveImage();
    saverImage->VisitPPM(*sampleImagePPM);
}
void Test5()
{
    ImagePPM* sampleImagePPM = new ImagePPM();
    
    readImage* sampleImageReader = new readImage("federer.ppm");
    sampleImageReader->VisitPPM(*sampleImagePPM);

    negative* negativeImageMaker = new negative();
    negativeImageMaker->VisitPPM(*sampleImagePPM);

    saveImage* saverImage = new saveImage();
    saverImage->VisitPPM(*sampleImagePPM);
}
void Test6()
{
    ImagePBM* sampleImagePBM = new ImagePBM();
    
    readImage* sampleImageReader = new readImage("sample.pbm");
    sampleImageReader->VisitPBM(*sampleImagePBM);

    negative* negativeImageMaker = new negative();
    negativeImageMaker->VisitPBM(*sampleImagePBM);

    saveImage* saverImage = new saveImage();
    saverImage->VisitPBM(*sampleImagePBM);
}
int main()
{
    Test6();
    exit(0);
    sessionHandler* sessionHandlerWorker = new sessionHandler();

    while(1)
    {
        command* currentCommand = sessionHandlerWorker->CommandReaderWorker.readCommand();
        sessionHandlerWorker->executeCommand(*currentCommand);
    }

    delete sessionHandlerWorker;

    // ImagePPM* sampleImagePPM = new ImagePPM();
    
    // readImage* sampleImageReader = new readImage("federer.ppm");
    // sampleImageReader->VisitPPM(*sampleImagePPM);


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
}   