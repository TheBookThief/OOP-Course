#include<iostream>
#include<string>
#include<vector>
#include "imagePPM.hpp"
#include "visitor.hpp"
ImagePPM &ImagePPM::operator=(const ImagePPM &_transformationImage)
{
    height = _transformationImage.height;
    width = _transformationImage.width;
    colors = _transformationImage.colors;
    maxColor = _transformationImage.maxColor;
    magicNumber = _transformationImage.magicNumber;
    filename = _transformationImage.filename;
    colorMatrix = Image::MatrixMaker(height, width, colors);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for(int p = 0; p < colors; p++)
            {
                colorMatrix[i][j][p] = _transformationImage.colorMatrix[i][j][p];    
            }
        }
    }
    return *this;
}
void ImagePPM::AcceptVisitor(Visitor *visitor)
{
    visitor->VisitPPM(*this);
}
Image *ImagePPM::clone()
{
    return new ImagePPM(*this);
}
ImagePPM::ImagePPM()
{
    this->colors = 3;
    this->maxColor = 255;
}