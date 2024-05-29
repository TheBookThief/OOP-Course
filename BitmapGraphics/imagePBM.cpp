#include<iostream>
#include<string>
#include<vector>
#include "imagePBM.hpp"
#include "visitor.hpp"
ImagePBM &ImagePBM::operator=(const ImagePBM &_transformationImage)
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
void ImagePBM::AcceptVisitor(Visitor *visitor)
{
    visitor->VisitPBM(*this);
}
Image *ImagePBM::clone()
{
    return new ImagePBM(*this);
}
ImagePBM::ImagePBM()
{
    this->colors = 1;
    this->maxColor = 1;
}