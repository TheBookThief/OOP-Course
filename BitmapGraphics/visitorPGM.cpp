#include <iostream>
#include <string>
#include <vector>
#include "image.hpp"
#include "imagePGM.hpp"
#include "visitor.hpp"
#include "command.hpp"
#include "session.hpp"
void readImage::VisitPGM(ImagePGM &objectImagePGM)
{
    try
    {
        std::ifstream in;
        objectImagePGM.filename = inputFileName;
        objectImagePGM.colors = 1;
        in.open(objectImagePGM.filename);
        if (!in.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        in >> objectImagePGM.magicNumber >> objectImagePGM.width >> objectImagePGM.height >> objectImagePGM.maxColor;
        std::cout << objectImagePGM.magicNumber << " " << objectImagePGM.width << " " << objectImagePGM.height << " " << objectImagePGM.maxColor << std::endl;

        objectImagePGM.colorMatrix = new int **[objectImagePGM.height];
        for (int i = 0; i < objectImagePGM.height; i++)
        {
            objectImagePGM.colorMatrix[i] = new int *[objectImagePGM.width];
        }
        for (int i = 0; i < objectImagePGM.height; i++)
        {
            for (int j = 0; j < objectImagePGM.width; j++)
            {
                objectImagePGM.colorMatrix[i][j] = new int[objectImagePGM.colors];
            }
        }
        int colorChannelValue = 0;
        for (int i = 0; i < objectImagePGM.height; i++)
        {
            for (int j = 0; j < objectImagePGM.width; j++)
            {
                for (int p = 0; p < objectImagePGM.colors; p++)
                {
                    in >> colorChannelValue;
                    objectImagePGM.colorMatrix[i][j][p] = colorChannelValue;
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
void grayscale::VisitPGM(ImagePGM &objectImagePGM)
{
    /*You are really trying to grayscale a gray image huh*/
}
void monochrome::VisitPGM(ImagePGM &objectImagePGM)
{
    for (int i = 0; i < objectImagePGM.height; i++)
    {
        for (int j = 0; j < objectImagePGM.width; j++)
        {
            int monochromeValue = objectImagePGM.colorMatrix[i][j][0];
            if (monochromeValue <= objectImagePGM.maxColor / 2)
                objectImagePGM.colorMatrix[i][j][0] = 0;
            else
                objectImagePGM.colorMatrix[i][j][0] = objectImagePGM.maxColor;
        }
    }
}
void negative::VisitPGM(ImagePGM &objectImagePGM)
{
    for (int i = 0; i < objectImagePGM.height; i++)
    {
        for (int j = 0; j < objectImagePGM.width; j++)
        {
            for (int p = 0; p < objectImagePGM.colors; p++)
            {
                objectImagePGM.colorMatrix[i][j][p] = objectImagePGM.maxColor - objectImagePGM.colorMatrix[i][j][p];
            }
            // objectImagePGM.colorMatrix[i][j][0] = objectImagePGM.maxColor - objectImagePGM.colorMatrix[i][j][0];
            // objectImagePGM.colorMatrix[i][j][1] = objectImagePGM.maxColor - objectImagePGM.colorMatrix[i][j][1];
            // objectImagePGM.colorMatrix[i][j][2] = objectImagePGM.maxColor - objectImagePGM.colorMatrix[i][j][2];
        }
    }
}
void saveImage::VisitPGM(ImagePGM &objectImagePGM)
{
    try
    {
        std::ofstream out;
        out.open(objectImagePGM.filename);
        if (!out.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        out << objectImagePGM.magicNumber << std::endl
            << objectImagePGM.width << ' ' << objectImagePGM.height << ' ' << objectImagePGM.maxColor << std::endl;
        for (int i = 0; i < objectImagePGM.height; i++)
        {
            for (int j = 0; j < objectImagePGM.width; j++)
            {
                for (int p = 0; p < objectImagePGM.colors; p++)
                {
                    out << objectImagePGM.colorMatrix[i][j][p] << ' ';
                }
                // out <<  objectImagePGM.colorMatrix[i][j][0] << ' ';
                // out <<  objectImagePGM.colorMatrix[i][j][1] << ' ';
                // out <<  objectImagePGM.colorMatrix[i][j][2] << ' ';
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
void saveAsImage::VisitPGM(ImagePGM &objectImagePGM)
{
    try
    {
        std::ofstream out;
        objectImagePGM.filename = newFilename;
        out.open(objectImagePGM.filename);
        if (!out.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        out << objectImagePGM.magicNumber << std::endl
            << objectImagePGM.width << ' ' << objectImagePGM.height << ' ' << objectImagePGM.maxColor << std::endl;
        for (int i = 0; i < objectImagePGM.height; i++)
        {
            for (int j = 0; j < objectImagePGM.width; j++)
            {
                for (int p = 0; p < objectImagePGM.colors; p++)
                {
                    out << objectImagePGM.colorMatrix[i][j][p] << ' ';
                }
                // out <<  objectImagePGM.colorMatrix[i][j][0] << ' ';
                // out <<  objectImagePGM.colorMatrix[i][j][1] << ' ';
                // out <<  objectImagePGM.colorMatrix[i][j][2] << ' ';
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
void rotateLeft::VisitPGM(ImagePGM &objectImagePGM)
{
    int newHeight = objectImagePGM.width;
    int newWidth = objectImagePGM.height;
    int ***newColorMatrix = new int **[newHeight];
    for (int i = 0; i < newHeight; i++)
    {
        newColorMatrix[i] = new int *[newWidth];
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            newColorMatrix[i][j] = new int[objectImagePGM.colors];
        }
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            for (int p = 0; p < objectImagePGM.colors; p++)
            {
                newColorMatrix[newHeight - i - 1][j][p] = objectImagePGM.colorMatrix[j][i][p];
            }
            // newColorMatrix[newHeight-i-1][j][0] = objectImagePGM.colorMatrix[j][i][0];
            // newColorMatrix[newHeight-i-1][j][1] = objectImagePGM.colorMatrix[j][i][1];
            // newColorMatrix[newHeight-i-1][j][2] = objectImagePGM.colorMatrix[j][i][2];
        }
    }
    objectImagePGM.MatrixDeleter();
    objectImagePGM.width = newWidth;
    objectImagePGM.height = newHeight;
    objectImagePGM.colorMatrix = newColorMatrix;
}
void rotateRight::VisitPGM(ImagePGM &objectImagePGM)
{
    int newHeight = objectImagePGM.width;
    int newWidth = objectImagePGM.height;
    int ***newColorMatrix = new int **[newHeight];
    for (int i = 0; i < newHeight; i++)
    {
        newColorMatrix[i] = new int *[newWidth];
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            newColorMatrix[i][j] = new int[objectImagePGM.colors];
        }
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            for (int p = 0; p < objectImagePGM.colors; p++)
            {
                newColorMatrix[i][newWidth - j - 1][p] = objectImagePGM.colorMatrix[j][i][p];
            }
            // newColorMatrix[i][newWidth-j-1][0] = objectImagePGM.colorMatrix[j][i][0];
            // newColorMatrix[i][newWidth-j-1][1] = objectImagePGM.colorMatrix[j][i][1];
            // newColorMatrix[i][newWidth-j-1][2] = objectImagePGM.colorMatrix[j][i][2];
        }
    }
    objectImagePGM.MatrixDeleter();
    objectImagePGM.width = newWidth;
    objectImagePGM.height = newHeight;
    objectImagePGM.colorMatrix = newColorMatrix;
}
collage::collage(ImagePGM &_transformationImage, int _direction)
{
    transformationImagePGM = _transformationImage;
    direction = _direction;
}
void collage::VisitPGM(ImagePGM &objectImagePGM)
{
    if (direction == 1) // horizontal
    {
        if (objectImagePGM.height != transformationImagePGM.height)
        {
            std::cerr << "Size for horizontal collab is not right" << std::endl;
            return;
        }
        int newHeight = objectImagePGM.height;
        int newWidth = objectImagePGM.width + transformationImagePGM.width;
        int newColors = objectImagePGM.colors;
        int ***newColorMatrix = objectImagePGM.MatrixMaker(newHeight,
                                                           newWidth,
                                                           newColors);
        for (int i = 0; i < newHeight; i++)
        {
            for (int j = 0; j < objectImagePGM.width; j++)
            {
                for (int p = 0; p < objectImagePGM.colors; p++)
                {
                    newColorMatrix[i][j][p] = objectImagePGM.colorMatrix[i][j][p];
                }
                // newColorMatrix[i][j][0] = objectImagePGM.colorMatrix[i][j][0];
                // newColorMatrix[i][j][1] = objectImagePGM.colorMatrix[i][j][1];
                // newColorMatrix[i][j][2] = objectImagePGM.colorMatrix[i][j][2];
            }
            for (int j = 0; j < transformationImagePGM.width; j++)
            {
                for (int p = 0; p < objectImagePGM.colors; p++)
                {
                    newColorMatrix[i][j + objectImagePGM.width][p] = transformationImagePGM.colorMatrix[i][j][p];
                }
                // newColorMatrix[i][j+objectImagePGM.width][0] = transformationImagePGM.colorMatrix[i][j][0];
                // newColorMatrix[i][j+objectImagePGM.width][1] = transformationImagePGM.colorMatrix[i][j][1];
                // newColorMatrix[i][j+objectImagePGM.width][2] = transformationImagePGM.colorMatrix[i][j][2];
            }
        }
        objectImagePGM.MatrixDeleter();
        objectImagePGM.height = newHeight;
        objectImagePGM.width = newWidth;
        objectImagePGM.colors = newColors;
        objectImagePGM.colorMatrix = newColorMatrix;
    }
    else
    {
        if (objectImagePGM.width != transformationImagePGM.width)
        {
            std::cerr << "Size for vertical collab is not right" << std::endl;
            return;
        }
        int newHeight = objectImagePGM.height + transformationImagePGM.height;
        int newWidth = objectImagePGM.width;
        int newColors = objectImagePGM.colors;
        int ***newColorMatrix = objectImagePGM.MatrixMaker(newHeight,
                                                           newWidth,
                                                           newColors);
        for (int i = 0; i < objectImagePGM.height; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                for (int p = 0; p < objectImagePGM.colors; p++)
                {
                    newColorMatrix[i][j][p] = objectImagePGM.colorMatrix[i][j][p];
                }
                // newColorMatrix[i][j][0] = objectImagePGM.colorMatrix[i][j][0];
                // newColorMatrix[i][j][1] = objectImagePGM.colorMatrix[i][j][1];
                // newColorMatrix[i][j][2] = objectImagePGM.colorMatrix[i][j][2];
            }
        }
        for (int i = 0; i < transformationImagePGM.height; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                for (int p = 0; p < objectImagePGM.colors; p++)
                {
                    newColorMatrix[i + objectImagePGM.height][j][p] = transformationImagePGM.colorMatrix[i][j][p];
                }
                // newColorMatrix[i+objectImagePGM.height][j][0] = transformationImagePGM.colorMatrix[i][j][0];
                // newColorMatrix[i+objectImagePGM.height][j][1] = transformationImagePGM.colorMatrix[i][j][1];
                // newColorMatrix[i+objectImagePGM.height][j][2] = transformationImagePGM.colorMatrix[i][j][2];
            }
        }
        objectImagePGM.MatrixDeleter();
        objectImagePGM.height = newHeight;
        objectImagePGM.width = newWidth;
        objectImagePGM.colors = newColors;
        objectImagePGM.colorMatrix = newColorMatrix;
    }
}