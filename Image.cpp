#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "stb_image.h"

#include <string>

#include <stdexcept>

#include <complex>

#include <limits>

#include "stb_image.h"


///deleter struct to pass to shared ptr that frees memory allocated by stbi image loader
template <class T>
struct StbiDeleter
{

    void operator()(T* data)
    {
        stbi_image_free(data);
    }

};


LDRImage loadImage(const std::string& filename, int convertToChannels)
{



    int width=0,height=0,channels=0;

    auto pixels = stbi_load(filename.c_str(),&width,&height,&channels, convertToChannels);

    if(!pixels)
    {
        throw std::runtime_error(std::string("LDRImage load error: \nFile")+filename+"\nReason:"+stbi_failure_reason());

    }

     std::array<std::size_t ,3> arr= {{(std::size_t)channels,(std::size_t)width,(std::size_t)height}};
    return MultidimensionalArray<unsigned char, 3>(std::shared_ptr<unsigned char>(pixels,StbiDeleter<unsigned char>()),

                                                   // {(std::size_t)channels,(std::size_t)width,(std::size_t)height}
                                                   arr

                                                    );//

}





HDRImage loadHDRImage(const std::string& filename, int convertToChannels)
{

    int width=0,height=0,channels=0;

    auto pixels = stbi_loadf(filename.c_str(), &width,&height,&channels, convertToChannels);

    if(!pixels)
    {
        throw std::runtime_error(std::string("HDRImage load error: \nFile")+filename+"\nReason:"+stbi_failure_reason());

    }

    std::array<std::size_t ,3> arr= {{(std::size_t)channels,(std::size_t)width,(std::size_t)height}};

    return HDRImage(std::shared_ptr<float>(pixels,StbiDeleter<float>()),

                  arr
          //          {{(std::size_t)channels,(std::size_t)width,(std::size_t)height} }

                    );//

}





bool writeHDRImage(HDRImage& img, const std::string& filename)
{
    if(!img)
    {
        throw std::runtime_error("Image::Write called on incomplete image");
    }
    
    std::string extension = filename.substr(filename.length()-4, 4);
    
    int width =img.getDimensions()[1];
    int height=img.getDimensions()[2];
    int channels=img.getDimensions()[0];
    
    for(int i =0; i < img.numElements(); i++)
    {
        img[i] = std::max<float>(0.0, img[i]);
    }
    
    //special case branching... mostly becuase jpeg doens't write with this writer.  This allows autodetection of the extension regardless though.
    
    if(extension != ".hdr")
    {
        throw std::runtime_error("Unrecognized extension for writeHDRImage");
    }
    
    return stbi_write_hdr(filename.c_str(), width, height, channels, img.dataPtr());
}



///\todo is there a write error message too?
bool writeImage(const LDRImage& img, const std::string& filename)
{

    if(!img)
    {
        throw std::runtime_error("Image::Write called on incomplete image");
    }

    std::string extension = filename.substr(filename.length()-4, 4);

    int width =img.getDimensions()[1];
    int height=img.getDimensions()[2];
    int channels=img.getDimensions()[0];

    //special case branching... mostly becuase jpeg doens't write with this writer.  This allows autodetection of the extension regardless though.

    if(extension == ".png")
    {

        return stbi_write_png(filename.c_str(), width, height, channels, img.dataPtr(), width*channels);

    }
    else if(extension==".bmp")
    {

        return stbi_write_bmp(filename.c_str(), width, height, channels, img.dataPtr());

    }
    else if(extension == ".tga")
    {

        return stbi_write_tga(filename.c_str(), width, height, channels, img.dataPtr());
    }
    else
    {
        throw std::runtime_error("Unimplemented extension for image writer");
    }

    return false;
}



///\todo overload different kinds of samplers.  This assumes that we will be using clamp to edge behavior


