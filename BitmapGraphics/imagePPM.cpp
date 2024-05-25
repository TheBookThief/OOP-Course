#include<iostream>
#include<string>
#include<vector>
#include "imagePPM.hpp"
#include "visitor.hpp"
ImagePPM &ImagePPM::operator=(ImagePPM &_transformationImage)
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
            colorMatrix[i][j][0] = _transformationImage.colorMatrix[i][j][0];
            colorMatrix[i][j][1] = _transformationImage.colorMatrix[i][j][1];
            colorMatrix[i][j][2] = _transformationImage.colorMatrix[i][j][2];
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