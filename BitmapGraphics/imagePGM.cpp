#include<iostream>
#include<string>
#include<vector>
#include "ImagePGM.hpp"
#include "visitor.hpp"
ImagePGM &ImagePGM::operator=(const ImagePGM &_transformationImage)
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
void ImagePGM::AcceptVisitor(Visitor *visitor)
{
    visitor->VisitPGM(*this);
}
Image *ImagePGM::clone()
{
    return new ImagePGM(*this);
}
ImagePGM::ImagePGM()
{
    this->colors = 1;
    this->maxColor = 255;
}