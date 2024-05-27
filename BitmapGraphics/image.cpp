#include<iostream>
#include<string>
#include<vector>
#include "command.hpp"
#include "image.hpp"
#include "imagePPM.hpp"
#include "visitor.hpp"
int ***Image::MatrixMaker(int height, int width, int colors)
{
    int ***newColorMatrix = new int **[height];
    for (int i = 0; i < height; i++)
    {
        newColorMatrix[i] = new int *[width];
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newColorMatrix[i][j] = new int[colors];
        }
    }
    return newColorMatrix;
}
void Image::PrintDetails(std::ostream &out)
{
    out << "For image " << filename << " in session:" << std::endl;
    if (pendingCommands.size() == 0)
    {
        out << "No pending transformations" << std::endl;
        return;
    }
    for (command *i : pendingCommands)
    {
        i->printInfo(out);
    }
}
Image::~Image()
{
    if(colorMatrix == nullptr) return;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            delete[] colorMatrix[i][j];
        }
        delete[] colorMatrix[i];
    }
    delete[] colorMatrix;
}