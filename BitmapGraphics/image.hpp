#pragma once
#include<iostream>
#include<string>
#include<vector>
/**
 * @brief Base parent class for all image types.
 * 
 * Defines the properties that each image will have. All image types - PPM, PGM, PBM inherit it.
*/

class Visitor;
class command;

class Image
{
    public:
        /**
         * @brief Matrix representing the values of the image. Dimensions are height x width x number of color channels
        */
        int*** colorMatrix = nullptr;
        /**
         * @brief Dimension of image.
        */
        int width, height, colors;
        /**
         * @brief Maximum color found in image.
        */
        int maxColor;
        /**
         * @brief An identifier with which the corresponding image fformat starts.
        */
        std::string magicNumber;
        /**
         * @brief Filename of the image.
        */
        std::string filename;
        /**
         * @brief List of commands waiting to be executed on the image.
        */
        std::vector<command*> pendingCommands;
        /**
         * @brief Default clone method.
         * @return Pointer to the newly generated image.
        */
        virtual Image* clone() = 0;
        /**
         * @brief The core method of the Visitor Design employed. Used for accepting an object (which is representing
         * some transformation function) and applying it on the image itslef.
        */
        virtual void AcceptVisitor(Visitor* visitor) = 0;
        /**
         * @brief Prints information about the image's filename and pending commands.
        */        
        virtual void PrintDetails(std::ostream &out = std::cout);
        /**
         * @brief TReturns a matrix with dimensions _height x _width x _colors
         * @param _height height of new matrix
         * @param _width width of new matrix
         * @param _colors number of color channels of new matrix
        */
        static int*** MatrixMaker(const int _height, const int _width, const int _colors);
        /**
         * @brief Method to delete the dynamically allocated matrix of the current object.
         * Relies on the correct dimensions of the image.
        */
        void MatrixDeleter();
        /**
         * @brief Default destructor. Most important function is to delete the dynamically allocated 
         * matrix for each image.
        */
        ~Image();
};