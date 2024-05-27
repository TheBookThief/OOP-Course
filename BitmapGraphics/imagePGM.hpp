#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "image.hpp"
/**
* @brief Class for the PGM format images.
*/
class Visitor;

class ImagePGM : public Image
{
    public:
        /**
         * @brief Default clone method.
        */
        Image* clone() override;
        /**
         * @brief Default constructor
        */
        ImagePGM();
        /**
         * @brief Redefinition of = operator to perform a deep copy.
        */
        ImagePGM& operator=(ImagePGM &_transformationImage);
        /**
         * @brief Function to accept a visitor. Will execute the visitor's implementation of how to affect a PBM object. 
        */
        void AcceptVisitor(Visitor* visitor) override;
};