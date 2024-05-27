#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "image.hpp"
class Visitor;

class ImagePBM : public Image
{
    public:
        Image* clone() override;
        ImagePBM();
        ImagePBM& operator=(ImagePBM &_transformationImage);
        void AcceptVisitor(Visitor* visitor) override;
};