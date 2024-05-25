#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "imagePPM.hpp"
class command;

class Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) = 0;
        // virtual void VisitPGM(ImagePGM &objectImagePGM) = 0;
        // virtual void VisitPBM(ImagePBM &objectImagePBM) = 0;
};
// void ImagePGM::AcceptVisitor(Visitor* visitor)
// {
//     visitor->VisitPGM(*this);
// }
// void ImagePBM::AcceptVisitor(Visitor* visitor)
// {
//     visitor->VisitPBM(*this);
// }


/* Load image method */
class readImage : public Visitor
{
    public:
        std::string inputFileName;
        readImage(std::string _inputFileName);
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};

/* Grayscale */
class grayscale : public Visitor
{
    public:
        const double BLUE_MODIFIER = 0.114;
        const double RED_MODIFIER = 0.299;
        const double GREEN_MODIFIER = 0.587;
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};

/* Monochrome */
class monochrome : public Visitor
{
    public:
        const double BLUE_MODIFIER = 0.114;
        const double RED_MODIFIER = 0.299;
        const double GREEN_MODIFIER = 0.587;
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};

/* Negative */
class negative : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};

/* Save Image */
class saveImage : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};

/* Save as Image */
class saveAsImage : public Visitor
{
    public:
        std::string newFilename;
        saveAsImage(std::string _newFilename);
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};

/* RotateLeft */
class rotateLeft : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};

/* Rotate Right */
class rotateRight : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};

/* Collage */
class collage : public Visitor
{
    public:
        ImagePPM transformationImage;
        int direction;
        collage(ImagePPM &_transformationImage, int _direction);
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};