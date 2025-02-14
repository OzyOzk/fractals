#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"
#include <fstream>

namespace bitmap
{

    Bitmap::Bitmap(int width, int height, std::string name) :_width(width), _height(height), _pPixels(new uint8_t[width*height * 3]{}), _name(name)
    {

    }
     
    bool Bitmap::write(std::string s)
    {
        bitmap::BitmapFileHeader fileHeader;
        bitmap::BitmapInfoHeader infoHeader;
        fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader)
            + (_width * _height * 3);
        fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

        infoHeader.width = _width;
        infoHeader.height = _height;


        std::ofstream file;
        file.open(s, std::ios::out|std::ios::binary);

        if (!file) return false;

        file.write((char*) &fileHeader, sizeof(fileHeader));
        file.write((char*) &infoHeader, sizeof(infoHeader));
        file.write((char*) _pPixels.get(), _width*_height*3);

        file.close();

        return true;
    }

    void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
    {
        uint8_t * pPixel = _pPixels.get(); //get returns raw pointer address for unique_ptr;  
        pPixel += (y *3)* _width + (x*3);
        pPixel[0] = blue;
        pPixel[1] = green;
        pPixel[2] = red;

        //lookup endian file format
    }

    Bitmap::~Bitmap()
    {

    }

    std::string Bitmap::getname () const
    {
        return _name;
    }
}