#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "image.hpp"
class Visitor;

class ImagePPM : public Image
{
    public:
        Image* clone() override;
        ImagePPM& operator=(ImagePPM &_transformationImage);
        void AcceptVisitor(Visitor* visitor) override;
};