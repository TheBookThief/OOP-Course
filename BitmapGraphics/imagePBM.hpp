#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "image.hpp"
/**
* @brief Class for the PBM format images.
*/

class Visitor;

class ImagePBM : public Image
{
    public:
        /**
         * @brief Default clone method.
        */
        Image* clone() override;
        /**
         * @brief Default constructor
        */
        ImagePBM();
        /**
         * @brief Redefinition of = operator to perform a deep copy.
        */
        ImagePBM& operator=(ImagePBM &_transformationImage);
        /**
         * @brief Function to accept a visitor. Will execute the visitor's implementation of how to affect a PBM object. 
        */
        void AcceptVisitor(Visitor* visitor) override;
};