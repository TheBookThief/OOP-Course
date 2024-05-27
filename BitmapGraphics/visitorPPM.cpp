#include <iostream>
#include <string>
#include <vector>
#include "image.hpp"
#include "imagePPM.hpp"
#include "visitor.hpp"
#include "command.hpp"
#include "session.hpp"
readImage::readImage(std::string _inputFileName)
{
    inputFileName = _inputFileName;
}
saveAsImage::saveAsImage(std::string _newFilename)
{
    newFilename = _newFilename;
}
void readImage::VisitPPM(ImagePPM &objectImagePPM)
{
    try
    {
        std::ifstream in;
        objectImagePPM.filename = inputFileName;
        objectImagePPM.colors = 3;
        in.open(objectImagePPM.filename);
        if (!in.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        in >> objectImagePPM.magicNumber >> objectImagePPM.width >> objectImagePPM.height >> objectImagePPM.maxColor;
        std::cout << objectImagePPM.magicNumber << " " << objectImagePPM.width << " " << objectImagePPM.height << " " << objectImagePPM.maxColor << std::endl;

        objectImagePPM.colorMatrix = new int **[objectImagePPM.height];
        for (int i = 0; i < objectImagePPM.height; i++)
        {
            objectImagePPM.colorMatrix[i] = new int *[objectImagePPM.width];
        }
        for (int i = 0; i < objectImagePPM.height; i++)
        {
            for (int j = 0; j < objectImagePPM.width; j++)
            {
                objectImagePPM.colorMatrix[i][j] = new int[objectImagePPM.colors];
            }
        }
        int colorChannelValue = 0;
        for (int i = 0; i < objectImagePPM.height; i++)
        {
            for (int j = 0; j < objectImagePPM.width; j++)
            {
                for (int p = 0; p < objectImagePPM.colors; p++)
                {
                    in >> colorChannelValue;
                    objectImagePPM.colorMatrix[i][j][p] = colorChannelValue;
                }
            }
        }
        in.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void grayscale::VisitPPM(ImagePPM &objectImagePPM)
{
    for (int i = 0; i < objectImagePPM.height; i++)
    {
        for (int j = 0; j < objectImagePPM.width; j++)
        {
            int grayscaleValue = objectImagePPM.colorMatrix[i][j][0] * RED_MODIFIER +
                                 objectImagePPM.colorMatrix[i][j][1] * GREEN_MODIFIER +
                                 objectImagePPM.colorMatrix[i][j][2] * BLUE_MODIFIER;
            objectImagePPM.colorMatrix[i][j][0] = grayscaleValue;
            objectImagePPM.colorMatrix[i][j][1] = grayscaleValue;
            objectImagePPM.colorMatrix[i][j][2] = grayscaleValue;
        }
    }
}
void monochrome::VisitPPM(ImagePPM &objectImagePPM)
{
    for (int i = 0; i < objectImagePPM.height; i++)
    {
        for (int j = 0; j < objectImagePPM.width; j++)
        {
            int monochromeValue = objectImagePPM.colorMatrix[i][j][0] * RED_MODIFIER +
                                  objectImagePPM.colorMatrix[i][j][1] * GREEN_MODIFIER +
                                  objectImagePPM.colorMatrix[i][j][2] * BLUE_MODIFIER;
            if (monochromeValue <= objectImagePPM.maxColor / 2)
                monochromeValue = 0;
            else
                monochromeValue = objectImagePPM.maxColor;
            objectImagePPM.colorMatrix[i][j][0] = monochromeValue;
            objectImagePPM.colorMatrix[i][j][1] = monochromeValue;
            objectImagePPM.colorMatrix[i][j][2] = monochromeValue;
        }
    }
}
void negative::VisitPPM(ImagePPM &objectImagePPM)
{
    for (int i = 0; i < objectImagePPM.height; i++)
    {
        for (int j = 0; j < objectImagePPM.width; j++)
        {
            for (int p = 0; p < objectImagePPM.colors; p++)
            {
                objectImagePPM.colorMatrix[i][j][p] = objectImagePPM.maxColor - objectImagePPM.colorMatrix[i][j][p];
            }
        }
    }
}
void saveImage::VisitPPM(ImagePPM &objectImagePPM)
{
    try
    {
        std::ofstream out;
        out.open(objectImagePPM.filename);
        if (!out.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        out << objectImagePPM.magicNumber << std::endl
            << objectImagePPM.width << ' ' << objectImagePPM.height << ' ' << objectImagePPM.maxColor << std::endl;
        for (int i = 0; i < objectImagePPM.height; i++)
        {
            for (int j = 0; j < objectImagePPM.width; j++)
            {
                for (int p = 0; p < objectImagePPM.colors; p++)
                {
                    out << objectImagePPM.colorMatrix[i][j][p] << ' ';
                }
            }
            out << std::endl;
        }
        out.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void saveAsImage::VisitPPM(ImagePPM &objectImagePPM)
{
    try
    {
        std::ofstream out;
        objectImagePPM.filename = newFilename;
        out.open(objectImagePPM.filename);
        if (!out.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        out << objectImagePPM.magicNumber << std::endl
            << objectImagePPM.width << ' ' << objectImagePPM.height << ' ' << objectImagePPM.maxColor << std::endl;
        for (int i = 0; i < objectImagePPM.height; i++)
        {
            for (int j = 0; j < objectImagePPM.width; j++)
            {
                for (int p = 0; p < objectImagePPM.colors; p++)
                {
                    out << objectImagePPM.colorMatrix[i][j][p] << ' ';
                }
            }
            out << std::endl;
        }
        out.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void rotateLeft::VisitPPM(ImagePPM &objectImagePPM)
{
    int newHeight = objectImagePPM.width;
    int newWidth = objectImagePPM.height;
    int ***newColorMatrix = new int **[newHeight];
    for (int i = 0; i < newHeight; i++)
    {
        newColorMatrix[i] = new int *[newWidth];
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            newColorMatrix[i][j] = new int[objectImagePPM.colors];
        }
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            for (int p = 0; p < objectImagePPM.colors; p++)
            {
                newColorMatrix[newHeight - i - 1][j][p] = objectImagePPM.colorMatrix[j][i][p];
            }
        }
    }
    objectImagePPM.MatrixDeleter();
    objectImagePPM.width = newWidth;
    objectImagePPM.height = newHeight;
    objectImagePPM.colorMatrix = newColorMatrix;
}
void rotateRight::VisitPPM(ImagePPM &objectImagePPM)
{
    int newHeight = objectImagePPM.width;
    int newWidth = objectImagePPM.height;
    int ***newColorMatrix = new int **[newHeight];
    for (int i = 0; i < newHeight; i++)
    {
        newColorMatrix[i] = new int *[newWidth];
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            newColorMatrix[i][j] = new int[objectImagePPM.colors];
        }
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            for (int p = 0; p < objectImagePPM.colors; p++)
            {
                newColorMatrix[i][newWidth - j - 1][p] = objectImagePPM.colorMatrix[j][i][p];
            }
        }
    }
    objectImagePPM.MatrixDeleter();
    objectImagePPM.width = newWidth;
    objectImagePPM.height = newHeight;
    objectImagePPM.colorMatrix = newColorMatrix;
}
collage::collage(ImagePPM &_transformationImage, int _direction)
{
    transformationImagePPM = _transformationImage;
    direction = _direction;
}
void collage::VisitPPM(ImagePPM &objectImagePPM)
{
    if (direction == 1) // horizontal
    {
        if (objectImagePPM.height != transformationImagePPM.height)
        {
            std::cerr << "Size for horizontal collab is not right" << std::endl;
            return;
        }
        int newHeight = objectImagePPM.height;
        int newWidth = objectImagePPM.width + transformationImagePPM.width;
        int newColors = objectImagePPM.colors;
        int ***newColorMatrix = Image::MatrixMaker(newHeight,
                                                   newWidth,
                                                   newColors);
        for (int i = 0; i < newHeight; i++)
        {
            for (int j = 0; j < objectImagePPM.width; j++)
            {
                for (int p = 0; p < objectImagePPM.colors; p++)
                {
                    newColorMatrix[i][j][p] = objectImagePPM.colorMatrix[i][j][p];
                }
            }
            for (int j = 0; j < transformationImagePPM.width; j++)
            {
                for (int p = 0; p < objectImagePPM.colors; p++)
                {
                    newColorMatrix[i][j + objectImagePPM.width][p] = transformationImagePPM.colorMatrix[i][j][p];
                }
            }
        }
        objectImagePPM.MatrixDeleter();
        objectImagePPM.height = newHeight;
        objectImagePPM.width = newWidth;
        objectImagePPM.colors = newColors;
        objectImagePPM.colorMatrix = newColorMatrix;
    }
    else
    {
        if (objectImagePPM.width != transformationImagePPM.width)
        {
            std::cerr << "Size for vertical collab is not right" << std::endl;
            return;
        }
        int newHeight = objectImagePPM.height + transformationImagePPM.height;
        int newWidth = objectImagePPM.width;
        int newColors = objectImagePPM.colors;
        int ***newColorMatrix = objectImagePPM.MatrixMaker(newHeight,
                                                           newWidth,
                                                           newColors);
        for (int i = 0; i < objectImagePPM.height; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                for (int p = 0; p < objectImagePPM.colors; p++)
                {
                    newColorMatrix[i][j][p] = objectImagePPM.colorMatrix[i][j][p];
                }
            }
        }
        for (int i = 0; i < transformationImagePPM.height; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                for (int p = 0; p < objectImagePPM.colors; p++)
                {
                    newColorMatrix[i + objectImagePPM.height][j][p] = transformationImagePPM.colorMatrix[i][j][p];
                }
            }
        }
        objectImagePPM.MatrixDeleter();
        objectImagePPM.height = newHeight;
        objectImagePPM.width = newWidth;
        objectImagePPM.colors = newColors;
        objectImagePPM.colorMatrix = newColorMatrix;
    }
}