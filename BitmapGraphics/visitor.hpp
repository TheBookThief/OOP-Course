#pragma once
#include<string>
#include<fstream>
class Visitor;
class Image
{
    public:
        int*** colorMatrix;
        int width, height, colors, maxColor;
        std::string magicNumber;
        std::string filename;
        virtual void AcceptVisitor(Visitor* visitor) = 0;
};
class ImagePPM : public Image
{
    public:
        void AcceptVisitor(Visitor* visitor) override;
};
class Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) = 0;
        // virtual void VisitPGM(ImagePGM &objectImagePGM) = 0;
        // virtual void VisitPBM(ImagePBM &objectImagePBM) = 0;
};
void ImagePPM::AcceptVisitor(Visitor* visitor)
{
    visitor->VisitPPM(*this);
}
// void ImagePGM::AcceptVisitor(Visitor* visitor)
// {
//     visitor->VisitPGM(*this);
// }
// void ImagePBM::AcceptVisitor(Visitor* visitor)
// {
//     visitor->VisitPBM(*this);
// }





/* Load image method */
class readImage : public Visitor
{
    public:
        std::string inputFileName;
        readImage(std::string _inputFileName)
        {
            inputFileName = _inputFileName;    
        }
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void readImage::VisitPPM(ImagePPM &objectImagePPM)
{
    std::ifstream in;
    objectImagePPM.filename = inputFileName;
    in.open(objectImagePPM.filename);
    in >> objectImagePPM.magicNumber >> objectImagePPM.width >> objectImagePPM.height >> objectImagePPM.maxColor; 
    std::cout<<objectImagePPM.magicNumber<<" "<<objectImagePPM.width<<" "<<objectImagePPM.height<<" "<<objectImagePPM.maxColor<<std::endl;
    objectImagePPM.colorMatrix = new int**[objectImagePPM.width];
    for(int i=0; i<objectImagePPM.width; i++)
    {
        objectImagePPM.colorMatrix[i] = new int*[objectImagePPM.height];
    }
    for(int i=0; i<objectImagePPM.width; i++)
    {
        for(int j=0; j<objectImagePPM.height; j++)
        {
            objectImagePPM.colorMatrix[i][j] = new int[3];
        }
    }
    int redVal=0, greenVal=0, blueVal=0;
    for(int i=0; i<objectImagePPM.width; i++)
    {
        for(int j=0; j<objectImagePPM.height; j++)
        {
            in >> redVal >> greenVal >> blueVal;
            objectImagePPM.colorMatrix[i][j][0] = redVal;
            objectImagePPM.colorMatrix[i][j][1] = greenVal;
            objectImagePPM.colorMatrix[i][j][2] = blueVal;
        }
    } 
    in.close();
}


/* Grayscale */
class grayscale : public Visitor
{
    public:
        const double BLUE_MODIFIER = 0.114;
        const double RED_MODIFIER = 0.299;
        const double GREEN_MODIFIER = 0.587;
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void grayscale::VisitPPM(ImagePPM &objectImagePPM)
{
    for(int i=0; i<objectImagePPM.width; i++)
    {
        for(int j=0; j<objectImagePPM.height; j++)
        {
            int grayscaleValue = objectImagePPM.colorMatrix[i][j][0] * RED_MODIFIER +
                                 objectImagePPM.colorMatrix[i][j][1] * GREEN_MODIFIER +
                                 objectImagePPM.colorMatrix[i][j][2] * BLUE_MODIFIER;
            objectImagePPM.colorMatrix[i][j][0] = grayscaleValue;
            objectImagePPM.colorMatrix[i][j][1] = grayscaleValue;
            objectImagePPM.colorMatrix[i][j][2] = grayscaleValue;
        }
    } 
}

/* Monochrome */
class monochrome : public Visitor
{
    public:
        const double BLUE_MODIFIER = 0.114;
        const double RED_MODIFIER = 0.299;
        const double GREEN_MODIFIER = 0.587;
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void monochrome::VisitPPM(ImagePPM &objectImagePPM)
{
    for(int i=0; i<objectImagePPM.width; i++)
    {
        for(int j=0; j<objectImagePPM.height; j++)
        {
            int monochromeValue = objectImagePPM.colorMatrix[i][j][0] * RED_MODIFIER +
                                 objectImagePPM.colorMatrix[i][j][1] * GREEN_MODIFIER +
                                 objectImagePPM.colorMatrix[i][j][2] * BLUE_MODIFIER;
            if(monochromeValue <= 127) monochromeValue = 0;
            else monochromeValue = 255;
            objectImagePPM.colorMatrix[i][j][0] = monochromeValue;
            objectImagePPM.colorMatrix[i][j][1] = monochromeValue;
            objectImagePPM.colorMatrix[i][j][2] = monochromeValue;
        }
    } 
}

/* Negative */
class negative : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void negative::VisitPPM(ImagePPM &objectImagePPM)
{
    for(int i=0; i<objectImagePPM.width; i++)
    {
        for(int j=0; j<objectImagePPM.height; j++)
        {
            objectImagePPM.colorMatrix[i][j][0] = objectImagePPM.maxColor - objectImagePPM.colorMatrix[i][j][0];
            objectImagePPM.colorMatrix[i][j][1] = objectImagePPM.maxColor - objectImagePPM.colorMatrix[i][j][1];
            objectImagePPM.colorMatrix[i][j][2] = objectImagePPM.maxColor - objectImagePPM.colorMatrix[i][j][2];
        }
    } 
}

/* Save Image */
class saveImage : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void saveImage::VisitPPM(ImagePPM &objectImagePPM)
{
    std::ofstream out;
    out.open(objectImagePPM.filename);
    out << objectImagePPM.magicNumber << std::endl << objectImagePPM.width << ' ' << objectImagePPM.height << ' ' << objectImagePPM.maxColor << std::endl; 
    for(int i=0; i<objectImagePPM.width; i++)
    {
        for(int j=0; j<objectImagePPM.height; j++)
        {
            out <<  objectImagePPM.colorMatrix[i][j][0] << ' '; 
            out <<  objectImagePPM.colorMatrix[i][j][1] << ' ';
            out <<  objectImagePPM.colorMatrix[i][j][2] << ' ';
        }
        out << std::endl;
    } 
    out.close();
}

/* Save as Image */
class saveAsImage : public Visitor
{
    public:
        std::string newFilename;
        saveAsImage(std::string _newFilename)
        {
            newFilename = _newFilename;
        }
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void saveAsImage::VisitPPM(ImagePPM &objectImagePPM)
{
    std::ofstream out;
    objectImagePPM.filename = newFilename;
    out.open(objectImagePPM.filename);
    out << objectImagePPM.magicNumber << std::endl << objectImagePPM.width << ' ' << objectImagePPM.height << ' ' << objectImagePPM.maxColor << std::endl; 
    for(int i=0; i<objectImagePPM.width; i++)
    {
        for(int j=0; j<objectImagePPM.height; j++)
        {
            out <<  objectImagePPM.colorMatrix[i][j][0] << ' '; 
            out <<  objectImagePPM.colorMatrix[i][j][1] << ' ';
            out <<  objectImagePPM.colorMatrix[i][j][2] << ' ';
        }
        out << std::endl;
    } 
    out.close();
}

/* Rotate */
class rotate : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void rotate::VisitPPM(ImagePPM &objectImagePPM)
{
    int newHeight = objectImagePPM.width;
    int newWidth = objectImagePPM.height;
    int*** newColorMatrix = new int**[newWidth];
    for(int i=0; i<newWidth; i++)
    {
        newColorMatrix[i] = new int*[newHeight];
    }
    for(int i=0; i<newWidth; i++)
    {
        for(int j=0; j<newHeight; j++)
        {
            newColorMatrix[i][j] = new int[3];
        }
    }
    for(int i=0; i<newWidth; i++)
    {
        for(int j=0; j<newHeight; j++)
        {
            newColorMatrix[i][j][0] = objectImagePPM.colorMatrix[j][i][0];
            newColorMatrix[i][j][1] = objectImagePPM.colorMatrix[j][i][1];
            newColorMatrix[i][j][2] = objectImagePPM.colorMatrix[j][i][2];
        }
    }
    objectImagePPM.width = newWidth;
    objectImagePPM.height = newHeight;
    objectImagePPM.colorMatrix = newColorMatrix;
}