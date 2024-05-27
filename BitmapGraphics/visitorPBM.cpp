#include <iostream>
#include <string>
#include <vector>
#include "image.hpp"
#include "imagePBM.hpp"
#include "visitor.hpp"
#include "command.hpp"
#include "session.hpp"
void readImage::VisitPBM(ImagePBM &objectImagePBM)
{
    try
    {
        std::ifstream in;
        objectImagePBM.filename = inputFileName;
        objectImagePBM.colors = 1;
        in.open(objectImagePBM.filename);
        if (!in.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        in >> objectImagePBM.magicNumber >> objectImagePBM.width >> objectImagePBM.height >> objectImagePBM.maxColor;
        std::cout << objectImagePBM.magicNumber << " " << objectImagePBM.width << " " << objectImagePBM.height << " " << objectImagePBM.maxColor << std::endl;

        objectImagePBM.colorMatrix = new int **[objectImagePBM.height];
        for (int i = 0; i < objectImagePBM.height; i++)
        {
            objectImagePBM.colorMatrix[i] = new int *[objectImagePBM.width];
        }
        for (int i = 0; i < objectImagePBM.height; i++)
        {
            for (int j = 0; j < objectImagePBM.width; j++)
            {
                objectImagePBM.colorMatrix[i][j] = new int[objectImagePBM.colors];
            }
        }
        int colorChannelValue = 0;
        for (int i = 0; i < objectImagePBM.height; i++)
        {
            for (int j = 0; j < objectImagePBM.width; j++)
            {
                for (int p = 0; p < objectImagePBM.colors; p++)
                {
                    in >> colorChannelValue;
                    objectImagePBM.colorMatrix[i][j][p] = colorChannelValue;
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
void grayscale::VisitPBM(ImagePBM &objectImagePBM)
{
    /*You are really trying to grayscale a gray image huh*/
}
void monochrome::VisitPBM(ImagePBM &objectImagePBM)
{
    /*uoy era yllaer gniyrt ot emorhconom a 1-0 egami huh*/
}
void negative::VisitPBM(ImagePBM &objectImagePBM)
{
    for (int i = 0; i < objectImagePBM.height; i++)
    {
        for (int j = 0; j < objectImagePBM.width; j++)
        {
            for (int p = 0; p < objectImagePBM.colors; p++)
            {
                objectImagePBM.colorMatrix[i][j][p] = objectImagePBM.maxColor - objectImagePBM.colorMatrix[i][j][p];
            }
        }
    }
}
void saveImage::VisitPBM(ImagePBM &objectImagePBM)
{
    try
    {
        std::ofstream out;
        out.open(objectImagePBM.filename);
        if (!out.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        out << objectImagePBM.magicNumber << std::endl
            << objectImagePBM.width << ' ' << objectImagePBM.height << ' ' << objectImagePBM.maxColor << std::endl;
        for (int i = 0; i < objectImagePBM.height; i++)
        {
            for (int j = 0; j < objectImagePBM.width; j++)
            {
                for (int p = 0; p < objectImagePBM.colors; p++)
                {
                    out << objectImagePBM.colorMatrix[i][j][p] << ' ';
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
void saveAsImage::VisitPBM(ImagePBM &objectImagePBM)
{
    try
    {
        std::ofstream out;
        objectImagePBM.filename = newFilename;
        out.open(objectImagePBM.filename);
        if (!out.is_open())
        {
            throw std::runtime_error("File does not exist/can't be opened.");
        }
        out << objectImagePBM.magicNumber << std::endl
            << objectImagePBM.width << ' ' << objectImagePBM.height << ' ' << objectImagePBM.maxColor << std::endl;
        for (int i = 0; i < objectImagePBM.height; i++)
        {
            for (int j = 0; j < objectImagePBM.width; j++)
            {
                for (int p = 0; p < objectImagePBM.colors; p++)
                {
                    out << objectImagePBM.colorMatrix[i][j][p] << ' ';
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
void rotateLeft::VisitPBM(ImagePBM &objectImagePBM)
{
    int newHeight = objectImagePBM.width;
    int newWidth = objectImagePBM.height;
    int ***newColorMatrix = new int **[newHeight];
    for (int i = 0; i < newHeight; i++)
    {
        newColorMatrix[i] = new int *[newWidth];
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            newColorMatrix[i][j] = new int[objectImagePBM.colors];
        }
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            for (int p = 0; p < objectImagePBM.colors; p++)
            {
                newColorMatrix[newHeight - i - 1][j][p] = objectImagePBM.colorMatrix[j][i][p];
            }
        }
    }
    objectImagePBM.MatrixDeleter();
    objectImagePBM.width = newWidth;
    objectImagePBM.height = newHeight;
    objectImagePBM.colorMatrix = newColorMatrix;
}
void rotateRight::VisitPBM(ImagePBM &objectImagePBM)
{
    int newHeight = objectImagePBM.width;
    int newWidth = objectImagePBM.height;
    int ***newColorMatrix = new int **[newHeight];
    for (int i = 0; i < newHeight; i++)
    {
        newColorMatrix[i] = new int *[newWidth];
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            newColorMatrix[i][j] = new int[objectImagePBM.colors];
        }
    }
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            for (int p = 0; p < objectImagePBM.colors; p++)
            {
                newColorMatrix[i][newWidth - j - 1][p] = objectImagePBM.colorMatrix[j][i][p];
            }
        }
    }
    objectImagePBM.MatrixDeleter();
    objectImagePBM.width = newWidth;
    objectImagePBM.height = newHeight;
    objectImagePBM.colorMatrix = newColorMatrix;
}
collage::collage(ImagePBM &_transformationImage, int _direction)
{
    transformationImagePBM = _transformationImage;
    direction = _direction;
}
void collage::VisitPBM(ImagePBM &objectImagePBM)
{
    if (direction == 1) // horizontal
    {
        if (objectImagePBM.height != transformationImagePBM.height)
        {
            std::cerr << "Size for horizontal collab is not right" << std::endl;
            return;
        }
        int newHeight = objectImagePBM.height;
        int newWidth = objectImagePBM.width + transformationImagePBM.width;
        int newColors = objectImagePBM.colors;
        int ***newColorMatrix = objectImagePBM.MatrixMaker(newHeight,
                                                           newWidth,
                                                           newColors);
        for (int i = 0; i < newHeight; i++)
        {
            for (int j = 0; j < objectImagePBM.width; j++)
            {
                for (int p = 0; p < objectImagePBM.colors; p++)
                {
                    newColorMatrix[i][j][p] = objectImagePBM.colorMatrix[i][j][p];
                }
            }
            for (int j = 0; j < transformationImagePBM.width; j++)
            {
                for (int p = 0; p < objectImagePBM.colors; p++)
                {
                    newColorMatrix[i][j + objectImagePBM.width][p] = transformationImagePBM.colorMatrix[i][j][p];
                }
            }
        }
        objectImagePBM.MatrixDeleter();
        objectImagePBM.height = newHeight;
        objectImagePBM.width = newWidth;
        objectImagePBM.colors = newColors;
        objectImagePBM.colorMatrix = newColorMatrix;
    }
    else
    {
        if (objectImagePBM.width != transformationImagePBM.width)
        {
            std::cerr << "Size for vertical collab is not right" << std::endl;
            return;
        }
        int newHeight = objectImagePBM.height + transformationImagePBM.height;
        int newWidth = objectImagePBM.width;
        int newColors = objectImagePBM.colors;
        int ***newColorMatrix = objectImagePBM.MatrixMaker(newHeight,
                                                           newWidth,
                                                           newColors);
        for (int i = 0; i < objectImagePBM.height; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                for (int p = 0; p < objectImagePBM.colors; p++)
                {
                    newColorMatrix[i][j][p] = objectImagePBM.colorMatrix[i][j][p];
                }
            }
        }
        for (int i = 0; i < transformationImagePBM.height; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                for (int p = 0; p < objectImagePBM.colors; p++)
                {
                    newColorMatrix[i + objectImagePBM.height][j][p] = transformationImagePBM.colorMatrix[i][j][p];
                }
            }
        }
        objectImagePBM.MatrixDeleter();
        objectImagePBM.height = newHeight;
        objectImagePBM.width = newWidth;
        objectImagePBM.colors = newColors;
        objectImagePBM.colorMatrix = newColorMatrix;
    }
}