#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "image.hpp"
class Visitor;

class ImagePGM : public Image
{
    public:
        Image* clone() override;
        ImagePGM();
        ImagePGM& operator=(ImagePGM &_transformationImage);
        void AcceptVisitor(Visitor* visitor) override;
};