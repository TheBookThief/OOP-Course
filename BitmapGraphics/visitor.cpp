#include<iostream>
#include "visitor.hpp"
int main()
{
    ImagePPM* sampleImagePPM = new ImagePPM();
    
    readImage* sampleImageReader = new readImage("federer.ppm");
    sampleImageReader->VisitPPM(*sampleImagePPM);
    
    // saveAsImage* saverAsImage = new saveAsImage("federer_new.ppm");
    // saverAsImage->VisitPPM(*sampleImagePPM);

    // monochrome* monochromer = new monochrome();
    // monochromer->VisitPPM(*sampleImagePPM);

    // negative* negativer = new negative();
    // negativer->VisitPPM(*sampleImagePPM);

    rotate* rotator = new rotate();
    rotator->VisitPPM(*sampleImagePPM);

    // grayscale* grayscaleImageMaker = new grayscale();
    // grayscaleImageMaker->VisitPPM(*sampleImagePPM);
    
    
    saveImage* saverImage = new saveImage();
    saverImage->VisitPPM(*sampleImagePPM);
}   