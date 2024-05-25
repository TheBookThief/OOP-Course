#pragma once
#include<iostream>
#include<string>
#include<vector>
class Visitor;
class command;

class Image
{
    public:
        int*** colorMatrix;
        int width, height, colors, maxColor;
        std::string magicNumber;
        std::string filename;
        std::vector<command*> pendingCommands;
        virtual Image* clone() = 0;
        virtual void AcceptVisitor(Visitor* visitor) = 0;
        virtual void PrintDetails(std::ostream &out = std::cout);
        static int*** MatrixMaker(int _height, int _width, int _colors);
        ~Image();
};