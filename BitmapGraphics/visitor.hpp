#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "imagePPM.hpp"
#include "imagePGM.hpp"
#include "imagePBM.hpp"
/**
* @brief The visitor class is the base class for each method. Declares the 
* interactions to be overriden with each image type. 
*/
class command;

class Visitor
{
    public:
        /**
        * @brief Base method for interaction with a PPM image.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) = 0;
        /**
        * @brief Base method for interaction with a PGM image.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) = 0;
        /**
        * @brief Base method for interaction with a PBM image.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) = 0;
};

/**
* @brief Class representing a method to read an image from a file.
*/
class readImage : public Visitor
{
    public:
        /**
        * @brief Name of the file to be read.
        */
        std::string inputFileName;
        /**
        * @brief Basic constructor
        * @param _inputFileName Name of file to be read
        */
        readImage(std::string _inputFileName);
        /**
        * @brief Reading method's ineraction with PPM images.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Reading method's ineraction with PGM images.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Reading method's ineraction with PBM images.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/**
* @brief Class representing a method to grayscale an image.
*/
class grayscale : public Visitor
{
    public:
        /**
        * @brief Blue coefficient in conversion to grayscale formula
        */
        const double BLUE_MODIFIER = 0.114;
        /**
        * @brief Red coefficient in conversion to grayscale formula
        */
        const double RED_MODIFIER = 0.299;
        /**
        * @brief Green coefficient in conversion to grayscale formula
        */
        const double GREEN_MODIFIER = 0.587;
        /**
        * @brief Grayscaling a PPM image.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Grayscaling a PGM image.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Grayscaling a PBM image.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/**
* @brief Class representing a method to read monochrome an image.
*/
class monochrome : public Visitor
{
    public:
        /**
        * @brief Blue coefficient in conversion to grayscale formula, used to convert to monochrome.
        */
        const double BLUE_MODIFIER = 0.114;
        /**
        * @brief Red coefficient in conversion to grayscale formula, used to convert to monochrome.
        */
        const double RED_MODIFIER = 0.299;
        /**
        * @brief Green coefficient in conversion to grayscale formula, used to convert to monochrome.
        */
        const double GREEN_MODIFIER = 0.587;
        /**
        * @brief Monochrome's a PPM image.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Monochrome's a PGM image.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Monochrome's a PBM image.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/**
* @brief Class representing a method to invert the colors of an image.
*/
class negative : public Visitor
{
    public:
        /**
        * @brief Inverts the colors of a PPM image.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Inverts the colors of a PPM image.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Inverts the colors of a PPM image.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/**
* @brief Class representing a method to apply all transformations to the file.
*/
class saveImage : public Visitor
{
    public:
        /**
        * @brief Performs the pending transformations on a PPM image.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Performs the pending transformations on a PGM image.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Performs the pending transformations on a PBM image.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/**
* @brief Class representing a method to apply all transformations to the file
* and saving it with a new name.
*/
class saveAsImage : public Visitor
{
    public:
        /**
        * @brief THe new filename under which the image will be saved.
        */
        std::string newFilename;
        /**
        * @brief Changes the name under which the image will be saved.
        */
        saveAsImage(std::string _newFilename);
        /**
        * @brief Saves a PPM image as the given name.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Saves a PGM image as the given name.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Saves a PBM image as the given name.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/**
* @brief Class representing a method to rotate the image left (counterclockwise).
*/
class rotateLeft : public Visitor
{
    public:
        /**
        * @brief Left rotation of a PPM image.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Left rotation of a PGM image.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Left rotation of a PBM image.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/**
* @brief Class representing a method to rotate the image right (clockwise).
*/
class rotateRight : public Visitor
{
    public:
        /**
        * @brief Right rotation of a PPM image.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Right rotation of a PGM image.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Right rotation of a PBM image.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};

/**
* @brief Class to create a collage from multiple images.
*/
class collage : public Visitor
{
    public:
        /**
        * @brief Dummy image used to remember the second image used for the collage in PPM workings.
        */
        ImagePPM transformationImagePPM;
        /**
        * @brief Dummy image used to remember the second image used for the collage in PGM workings.
        */
        ImagePGM transformationImagePGM;
        /**
        * @brief Dummy image used to remember the second image used for the collage in PBM workings.
        */
        ImagePBM transformationImagePBM;
        /**
        * @brief Direction of collage. Can either be 1 - horizontal or 2 - vertical
        */
        int direction;
        /**
        * @brief Collage constructor for PPM workings.
        */
        collage(ImagePPM &_transformationImage, int _direction);
        /**
        * @brief Collage constructor for PGM workings.
        */
        collage(ImagePGM &_transformationImage, int _direction);
        /**
        * @brief Collage constructor for PBM workings.
        */
        collage(ImagePBM &_transformationImage, int _direction);
        /**
        * @brief Makes a collage from the provided images by appending the dummy
        * image with which the object is constructed - PPM images.
        */
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
        /**
        * @brief Makes a collage from the provided images by appending the dummy
        * image with which the object is constructed - PGM images.
        */
        virtual void VisitPGM(ImagePGM &objectImagePGM) override;
        /**
        * @brief Makes a collage from the provided images by appending the dummy
        * image with which the object is constructed - PBM images.
        */
        virtual void VisitPBM(ImagePBM &objectImagePBM) override;
};