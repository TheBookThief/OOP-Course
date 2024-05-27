#include<iostream>
#include<string>
#include<vector>
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
    std::ifstream in;
    objectImagePPM.filename = inputFileName;
    objectImagePPM.colors = 3;
    in.open(objectImagePPM.filename);
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
            for(int p = 0; p < objectImagePPM.colors; p++)
            {
                in >> colorChannelValue;
                objectImagePPM.colorMatrix[i][j][p] = colorChannelValue;
            }
        }
    }
    in.close();
}
void grayscale::VisitPPM(ImagePPM &objectImagePPM)
{
    for(int i = 0; i < objectImagePPM.height; i++)
    {
        for(int j = 0; j < objectImagePPM.width; j++)
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
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
        {
            int monochromeValue = objectImagePPM.colorMatrix[i][j][0] * RED_MODIFIER +
                                 objectImagePPM.colorMatrix[i][j][1] * GREEN_MODIFIER +
                                 objectImagePPM.colorMatrix[i][j][2] * BLUE_MODIFIER;
            if(monochromeValue <= objectImagePPM.maxColor/2) monochromeValue = 0;
            else monochromeValue = objectImagePPM.maxColor;
            objectImagePPM.colorMatrix[i][j][0] = monochromeValue;
            objectImagePPM.colorMatrix[i][j][1] = monochromeValue;
            objectImagePPM.colorMatrix[i][j][2] = monochromeValue;
        }
    } 
}
void negative::VisitPPM(ImagePPM &objectImagePPM)
{
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
        {
            for(int p=0; p<objectImagePPM.colors; p++)
            {
                objectImagePPM.colorMatrix[i][j][p] = objectImagePPM.maxColor - objectImagePPM.colorMatrix[i][j][p];    
            }
            // objectImagePPM.colorMatrix[i][j][0] = objectImagePPM.maxColor - objectImagePPM.colorMatrix[i][j][0];
            // objectImagePPM.colorMatrix[i][j][1] = objectImagePPM.maxColor - objectImagePPM.colorMatrix[i][j][1];
            // objectImagePPM.colorMatrix[i][j][2] = objectImagePPM.maxColor - objectImagePPM.colorMatrix[i][j][2];
        }
    } 
}
void saveImage::VisitPPM(ImagePPM &objectImagePPM)
{
    std::ofstream out;
    out.open(objectImagePPM.filename);
    out << objectImagePPM.magicNumber << std::endl << objectImagePPM.width << ' ' << objectImagePPM.height << ' ' << objectImagePPM.maxColor << std::endl; 
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
        {
            for(int p=0; p<objectImagePPM.colors; p++)
            {
                out <<  objectImagePPM.colorMatrix[i][j][p] << ' '; 
            }
            // out <<  objectImagePPM.colorMatrix[i][j][0] << ' '; 
            // out <<  objectImagePPM.colorMatrix[i][j][1] << ' ';
            // out <<  objectImagePPM.colorMatrix[i][j][2] << ' ';
        }
        out << std::endl;
    } 
    out.close();
}
void saveAsImage::VisitPPM(ImagePPM &objectImagePPM)
{
    std::ofstream out;
    objectImagePPM.filename = newFilename;
    out.open(objectImagePPM.filename);
    out << objectImagePPM.magicNumber << std::endl << objectImagePPM.width << ' ' << objectImagePPM.height << ' ' << objectImagePPM.maxColor << std::endl; 
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
        {
            for(int p=0; p<objectImagePPM.colors; p++)
            {
                out <<  objectImagePPM.colorMatrix[i][j][p] << ' '; 
            }
            // out <<  objectImagePPM.colorMatrix[i][j][0] << ' '; 
            // out <<  objectImagePPM.colorMatrix[i][j][1] << ' ';
            // out <<  objectImagePPM.colorMatrix[i][j][2] << ' ';
        }
        out << std::endl;
    } 
    out.close();
}
void rotateLeft::VisitPPM(ImagePPM &objectImagePPM)
{
    int newHeight = objectImagePPM.width;
    int newWidth = objectImagePPM.height;
    int*** newColorMatrix = new int**[newHeight];
    for(int i=0; i<newHeight; i++)
    {
        newColorMatrix[i] = new int*[newWidth];
    }
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            newColorMatrix[i][j] = new int[objectImagePPM.colors];
        }
    }
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            for(int p=0; p<objectImagePPM.colors; p++)
            {
                newColorMatrix[newHeight-i-1][j][p] = objectImagePPM.colorMatrix[j][i][p];
            }
            // newColorMatrix[newHeight-i-1][j][0] = objectImagePPM.colorMatrix[j][i][0];
            // newColorMatrix[newHeight-i-1][j][1] = objectImagePPM.colorMatrix[j][i][1];
            // newColorMatrix[newHeight-i-1][j][2] = objectImagePPM.colorMatrix[j][i][2];
        }
    }
    delete[] objectImagePPM.colorMatrix;
    objectImagePPM.width = newWidth;
    objectImagePPM.height = newHeight;
    objectImagePPM.colorMatrix = newColorMatrix;
}
void rotateRight::VisitPPM(ImagePPM &objectImagePPM)
{
    int newHeight = objectImagePPM.width;
    int newWidth = objectImagePPM.height;
    int*** newColorMatrix = new int**[newHeight];
    for(int i=0; i<newHeight; i++)
    {
        newColorMatrix[i] = new int*[newWidth];
    }
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            newColorMatrix[i][j] = new int[objectImagePPM.colors];
        }
    }
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            for(int p=0; p<objectImagePPM.colors; p++)
            {
               newColorMatrix[i][newWidth-j-1][p] = objectImagePPM.colorMatrix[j][i][p]; 
            }
            // newColorMatrix[i][newWidth-j-1][0] = objectImagePPM.colorMatrix[j][i][0];
            // newColorMatrix[i][newWidth-j-1][1] = objectImagePPM.colorMatrix[j][i][1];
            // newColorMatrix[i][newWidth-j-1][2] = objectImagePPM.colorMatrix[j][i][2];
        }
    }
    delete[] objectImagePPM.colorMatrix;
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
    if(direction == 1) // horizontal
    {
        if(objectImagePPM.height != transformationImagePPM.height)
        {
            std::cerr<<"Size for horizontal collab is not right"<<std::endl;
            return; 
        }
        int newHeight = objectImagePPM.height;
        int newWidth = objectImagePPM.width + transformationImagePPM.width;
        int newColors = objectImagePPM.colors;
        int*** newColorMatrix = Image::MatrixMaker(newHeight,
                                                    newWidth,
                                                    newColors);
        for(int i=0; i<newHeight; i++)
        {
            for(int j=0; j<objectImagePPM.width; j++)
            {
                for(int p=0; p<objectImagePPM.colors; p++)
                {
                    newColorMatrix[i][j][p] = objectImagePPM.colorMatrix[i][j][p];    
                }
                // newColorMatrix[i][j][0] = objectImagePPM.colorMatrix[i][j][0];
                // newColorMatrix[i][j][1] = objectImagePPM.colorMatrix[i][j][1];
                // newColorMatrix[i][j][2] = objectImagePPM.colorMatrix[i][j][2];
            }
            for(int j=0; j<transformationImagePPM.width; j++)
            {
                for(int p=0; p<objectImagePPM.colors; p++)
                {
                    newColorMatrix[i][j+objectImagePPM.width][p] = transformationImagePPM.colorMatrix[i][j][p];    
                }
                // newColorMatrix[i][j+objectImagePPM.width][0] = transformationImagePPM.colorMatrix[i][j][0];
                // newColorMatrix[i][j+objectImagePPM.width][1] = transformationImagePPM.colorMatrix[i][j][1];
                // newColorMatrix[i][j+objectImagePPM.width][2] = transformationImagePPM.colorMatrix[i][j][2];
            }
        }
        delete[] objectImagePPM.colorMatrix; /*todo fix deletion*/
        objectImagePPM.height = newHeight;
        objectImagePPM.width = newWidth;
        objectImagePPM.colors = newColors;
        objectImagePPM.colorMatrix = newColorMatrix;
    }
    else
    {
        if(objectImagePPM.width != transformationImagePPM.width)
        {
            std::cerr<<"Size for vertical collab is not right"<<std::endl;
            return;
        }
        int newHeight = objectImagePPM.height + transformationImagePPM.height;
        int newWidth = objectImagePPM.width;
        int newColors = objectImagePPM.colors;
        int*** newColorMatrix = objectImagePPM.MatrixMaker(newHeight,
                                                            newWidth,
                                                            newColors);
        for(int i=0; i<objectImagePPM.height; i++)
        {
            for(int j=0; j<newWidth; j++)
            {
                for(int p=0; p<objectImagePPM.colors; p++)
                {
                    newColorMatrix[i][j][p] = objectImagePPM.colorMatrix[i][j][p];    
                } 
                // newColorMatrix[i][j][0] = objectImagePPM.colorMatrix[i][j][0];
                // newColorMatrix[i][j][1] = objectImagePPM.colorMatrix[i][j][1];
                // newColorMatrix[i][j][2] = objectImagePPM.colorMatrix[i][j][2];
            }
        }
        for(int i=0; i<transformationImagePPM.height; i++)
        {
            for(int j=0; j<newWidth; j++)
            {
                for(int p=0; p<objectImagePPM.colors; p++)
                {
                    newColorMatrix[i+objectImagePPM.height][j][p] = transformationImagePPM.colorMatrix[i][j][p];    
                }
                // newColorMatrix[i+objectImagePPM.height][j][0] = transformationImagePPM.colorMatrix[i][j][0];
                // newColorMatrix[i+objectImagePPM.height][j][1] = transformationImagePPM.colorMatrix[i][j][1];
                // newColorMatrix[i+objectImagePPM.height][j][2] = transformationImagePPM.colorMatrix[i][j][2];
            }
        }
        delete[] objectImagePPM.colorMatrix;
        objectImagePPM.height = newHeight;
        objectImagePPM.width = newWidth;
        objectImagePPM.colors = newColors;
        objectImagePPM.colorMatrix = newColorMatrix;
    }
}