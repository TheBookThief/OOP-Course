#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "imagePPM.hpp"
#include "imagePGM.hpp"
#include "imagePBM.hpp"
class command;

class Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) = 0;
        virtual void VisitPGM(ImagePGM &objectImagePGM) = 0;
        virtual void VisitPBM(ImagePBM &objectImagePBM) = 0;
};

/* Load image method */
class readImage : public Visitor
{
    public:
        std::string inputFileName;
        readImage(std::string _inputFileName);
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/* Grayscale */
class grayscale : public Visitor
{
    public:
        const double BLUE_MODIFIER = 0.114;
        const double RED_MODIFIER = 0.299;
        const double GREEN_MODIFIER = 0.587;
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/* Monochrome */
class monochrome : public Visitor
{
    public:
        const double BLUE_MODIFIER = 0.114;
        const double RED_MODIFIER = 0.299;
        const double GREEN_MODIFIER = 0.587;
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/* Negative */
class negative : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/* Save Image */
class saveImage : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/* Save as Image */
class saveAsImage : public Visitor
{
    public:
        std::string newFilename;
        saveAsImage(std::string _newFilename);
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/* RotateLeft */
class rotateLeft : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/* Rotate Right */
class rotateRight : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/* Collage */
class collage : public Visitor
{
    public:
        ImagePPM transformationImagePPM;
        ImagePGM transformationImagePGM;
        ImagePBM transformationImagePBM;
        int direction;
        collage(ImagePPM &_transformationImage, int _direction);
        collage(ImagePGM &_transformationImage, int _direction);
        collage(ImagePBM &_transformationImage, int _direction);
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};