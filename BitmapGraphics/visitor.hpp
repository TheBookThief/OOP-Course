#ifndef VISITOR_HPP
#define VISITOR_HPP
#include<string>
#include<fstream>
#include<vector>
class Visitor;
class command
{
    public:
        static int commandCounter;
        int uniqueCommandID;
        std::vector<std::string> commandArguments;
        command* clone()
        {
            return new command(*this);
        }
        command(std::vector<std::string> &_commandArguments)
        {
            commandCounter++;
            uniqueCommandID = commandCounter;
            for(std::string i : _commandArguments)
            {
                commandArguments.push_back(i);
            }
        }
        void printInfo(std::ostream &out = std::cout)
        {
            for(std::string s : commandArguments)
            {
                out << s;
            }
        }
};
int command::commandCounter = 0;
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
int*** Image::MatrixMaker(int height, int width, int colors)
{
    int*** newColorMatrix = new int**[height];
    for(int i=0; i<height; i++)
    {
        newColorMatrix[i] = new int*[width];
    }
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            newColorMatrix[i][j] = new int[3];
        }
    }
    return newColorMatrix;
}
void Image::PrintDetails(std::ostream &out)
{
    out <<"For image "<<filename<<" in session:"<<std::endl;
    if(pendingCommands.size() == 0)
    {
        out << "No pending transformations" << std::endl;
        return;
    }
    for(command* i : pendingCommands)
    {
        i->printInfo(out);
    }
}
Image::~Image()
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            delete[] colorMatrix[i][j];
        }
        delete[] colorMatrix[i];
    }
    delete[] colorMatrix;
}
class ImagePPM : public Image
{
    public:
        Image* clone() override;
        ImagePPM& operator=(ImagePPM &_transformationImage)
        {
            height = _transformationImage.height;
            width = _transformationImage.width;
            colors = _transformationImage.colors;
            maxColor = _transformationImage.maxColor;
            magicNumber = _transformationImage.magicNumber;
            filename = _transformationImage.filename;
            colorMatrix = Image::MatrixMaker(height, width, colors);
            for(int i=0; i<height; i++)
            {
                for(int j=0; j<width; j++)
                {
                    colorMatrix[i][j][0] = _transformationImage.colorMatrix[i][j][0];
                    colorMatrix[i][j][1] = _transformationImage.colorMatrix[i][j][1];
                    colorMatrix[i][j][2] = _transformationImage.colorMatrix[i][j][2];
                }
            }
            return *this;
        }
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
Image* ImagePPM::clone()
{
    return new ImagePPM(*this); 
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
    
    objectImagePPM.colorMatrix = new int**[objectImagePPM.height];
    for(int i=0; i<objectImagePPM.height; i++)
    {
        objectImagePPM.colorMatrix[i] = new int*[objectImagePPM.width];
    }
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
        {
            objectImagePPM.colorMatrix[i][j] = new int[3];
        }
    }
    int redVal=0, greenVal=0, blueVal=0;
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
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
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
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
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
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
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
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
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
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
    for(int i=0; i<objectImagePPM.height; i++)
    {
        for(int j=0; j<objectImagePPM.width; j++)
        {
            out <<  objectImagePPM.colorMatrix[i][j][0] << ' '; 
            out <<  objectImagePPM.colorMatrix[i][j][1] << ' ';
            out <<  objectImagePPM.colorMatrix[i][j][2] << ' ';
        }
        out << std::endl;
    } 
    out.close();
}

/* RotateLeft */
class rotateLeft : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void rotateLeft::VisitPPM(ImagePPM &objectImagePPM)
{
    int newHeight = objectImagePPM.width;
    int newWidth = objectImagePPM.height;
    int*** newColorMatrix = new int**[newHeight];
    for(int i=0; i<newHeight; i++)
    {
        newColorMatrix[i] = new int*[newWidth];
    }
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            newColorMatrix[i][j] = new int[3];
        }
    }
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            newColorMatrix[newHeight-i-1][j][0] = objectImagePPM.colorMatrix[j][i][0];
            newColorMatrix[newHeight-i-1][j][1] = objectImagePPM.colorMatrix[j][i][1];
            newColorMatrix[newHeight-i-1][j][2] = objectImagePPM.colorMatrix[j][i][2];
        }
    }
    delete[] objectImagePPM.colorMatrix;
    objectImagePPM.width = newWidth;
    objectImagePPM.height = newHeight;
    objectImagePPM.colorMatrix = newColorMatrix;
}

/* Rotate Right */
class rotateRight : public Visitor
{
    public:
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
void rotateRight::VisitPPM(ImagePPM &objectImagePPM)
{
    int newHeight = objectImagePPM.width;
    int newWidth = objectImagePPM.height;
    int*** newColorMatrix = new int**[newHeight];
    for(int i=0; i<newHeight; i++)
    {
        newColorMatrix[i] = new int*[newWidth];
    }
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            newColorMatrix[i][j] = new int[3];
        }
    }
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            newColorMatrix[i][newWidth-j-1][0] = objectImagePPM.colorMatrix[j][i][0];
            newColorMatrix[i][newWidth-j-1][1] = objectImagePPM.colorMatrix[j][i][1];
            newColorMatrix[i][newWidth-j-1][2] = objectImagePPM.colorMatrix[j][i][2];
        }
    }
    delete[] objectImagePPM.colorMatrix;
    objectImagePPM.width = newWidth;
    objectImagePPM.height = newHeight;
    objectImagePPM.colorMatrix = newColorMatrix;
}

/* Collage */
class collage : public Visitor
{
    public:
        ImagePPM transformationImage;
        int direction;
        collage(ImagePPM &_transformationImage, int _direction);
        virtual void VisitPPM(ImagePPM &objectImagePPM) override;
};
collage::collage(ImagePPM &_transformationImage, int _direction)
{
    transformationImage = _transformationImage;
    direction = _direction;
}
void collage::VisitPPM(ImagePPM &objectImagePPM)
{
    if(direction == 1) // horizontal
    {
        if(objectImagePPM.height != transformationImage.height)
        {
            std::cerr<<"Size for horizontal collab is not right"<<std::endl;
            return;
        }
        int newHeight = objectImagePPM.height;
        int newWidth = objectImagePPM.width + transformationImage.width;
        int newColors = objectImagePPM.colors;
        int*** newColorMatrix = objectImagePPM.MatrixMaker(newHeight,
                                                            newWidth,
                                                            newColors);
        for(int i=0; i<newHeight; i++)
        {
            for(int j=0; j<objectImagePPM.width; j++)
            {
                newColorMatrix[i][j][0] = objectImagePPM.colorMatrix[i][j][0];
                newColorMatrix[i][j][1] = objectImagePPM.colorMatrix[i][j][1];
                newColorMatrix[i][j][2] = objectImagePPM.colorMatrix[i][j][2];
            }
            for(int j=0; j<transformationImage.width; j++)
            {
                newColorMatrix[i][j+objectImagePPM.width][0] = transformationImage.colorMatrix[i][j][0];
                newColorMatrix[i][j+objectImagePPM.width][1] = transformationImage.colorMatrix[i][j][1];
                newColorMatrix[i][j+objectImagePPM.width][2] = transformationImage.colorMatrix[i][j][2];
            }
        }
        delete[] objectImagePPM.colorMatrix;
        objectImagePPM.height = newHeight;
        objectImagePPM.width = newWidth;
        objectImagePPM.colors = newColors;
        objectImagePPM.colorMatrix = newColorMatrix;
    }
    else
    {
        if(objectImagePPM.width != transformationImage.width)
        {
            std::cerr<<"Size for vertical collab is not right"<<std::endl;
            return;
        }
        int newHeight = objectImagePPM.height + transformationImage.height;
        int newWidth = objectImagePPM.width;
        int newColors = objectImagePPM.colors;
        int*** newColorMatrix = objectImagePPM.MatrixMaker(newHeight,
                                                            newWidth,
                                                            newColors);
        for(int i=0; i<objectImagePPM.height; i++)
        {
            for(int j=0; j<newWidth; j++)
            {
                newColorMatrix[i][j][0] = objectImagePPM.colorMatrix[i][j][0];
                newColorMatrix[i][j][1] = objectImagePPM.colorMatrix[i][j][1];
                newColorMatrix[i][j][2] = objectImagePPM.colorMatrix[i][j][2];
            }
        }
        for(int i=0; i<transformationImage.height; i++)
        {
            for(int j=0; j<newWidth; j++)
            {
                newColorMatrix[i+objectImagePPM.height][j][0] = transformationImage.colorMatrix[i][j][0];
                newColorMatrix[i+objectImagePPM.height][j][1] = transformationImage.colorMatrix[i][j][1];
                newColorMatrix[i+objectImagePPM.height][j][2] = transformationImage.colorMatrix[i][j][2];
            }
        }
        delete[] objectImagePPM.colorMatrix;
        objectImagePPM.height = newHeight;
        objectImagePPM.width = newWidth;
        objectImagePPM.colors = newColors;
        objectImagePPM.colorMatrix = newColorMatrix;
    }
}
#endif