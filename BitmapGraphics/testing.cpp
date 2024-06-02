#include<iostream>
#include<string>
#include<vector>
#include "visitor.hpp"
#include "session.hpp"
#include "command.hpp"
#include "image.hpp"
#include "imagePPM.hpp"
#include "testing.hpp"
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
        std::cout<<"Test3 failed"<<std::endl;
        return;
    }
    if(sessionHandler::CommandReader::findExtension("randomname.ppppppppm") != "ppppppppm") 
    {
        std::cout<<"Test3 failed"<<std::endl;
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