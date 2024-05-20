#pragma once
#include<string>
class ArrayFile
{
    int* arr;
    std::string fileName;
    std::size_t size;
    bool readSuccess;
    public:
        ArrayFile() = delete;
        ArrayFile(const ArrayFile &other) = delete;

        ArrayFile(const char *filename);

        ~ArrayFile();

        int& operator[](int idx);
        const int& operator[](int idx) const;
        std::size_t getSize() const {return size;}

        bool didRead() const {return readSuccess;}

};