#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <array>
#include <vector>

#include "MultidimensionalArray.h"


typedef std::array<unsigned char, 3> RgbPixel;
typedef std::array<unsigned char, 4> RgbaPixel;


template <class DATATYPE, std::size_t DIMENSIONS,class BUFFER_TYPE = ArrayBuffer<DATATYPE,DIMENSIONS+1> >
using Image = MultidimensionalArray<DATATYPE, DIMENSIONS + 1, BUFFER_TYPE>; ///for now image is just a typedef.
///For simplicity We assume that the first dimensions is channels, and is always 1 or greater even for 1 channel images.
///to have the actual image pixel channels available, we augment the dimensions of the image by 1.  Eg, an rgba image is 4*width*height


typedef Image<unsigned char,2> LDRImage;
typedef Image<float,2> HDRImage;
typedef Image<float,2> FloatImage;

template <class DATATYPE>
using Image2D = Image<DATATYPE, 2>;

typedef  LDRImage::slice_type LDRImageSlice;



///returns the 0,0,0 index as the red channel of the top left pixel.  To get OpenGL style lower left origin, call flipVertical
LDRImage loadImage(const std::string& filename,int convertToChannels=0);

bool writeImage(const LDRImage& img, const std::string& filename);

bool writeHDRImage(const HDRImage& img, const std::string& filename);

HDRImage loadHDRImage(const std::string& filename, int convertToChannels=0);


template<class DATATYPE>
void flipHorizontal(Image2D<DATATYPE>& img);


template<class DATATYPE>
void flipVertical(Image2D<DATATYPE>& img);


template<class DATATYPE, std::size_t DIMENSIONS>
void filteredLookup(const Image<DATATYPE, DIMENSIONS>& img, const std::array<double, DIMENSIONS>& coords, DATATYPE* returnVal);


///\todo double vs float coord performance?
///\todo sse the floors and ceils?
///\todo optimize?
template <class DATATYPE, std::size_t  DIMENSIONS>
std::vector<DATATYPE> filteredLookup(const Image<DATATYPE,DIMENSIONS>& img, const std::array<double,DIMENSIONS>& coords);


template<class DATATYPE, std::size_t DIMENSIONS>
void filteredLookupNorm(const Image<DATATYPE, DIMENSIONS>& img, const std::array<double, DIMENSIONS>& coords, DATATYPE* returnVal);


template <class DATATYPE, int DIMENSIONS>
inline std::vector<DATATYPE> filteredLookupNorm(const Image<DATATYPE,DIMENSIONS>& img, const std::array<DATATYPE,DIMENSIONS>& coords);


template <class DATATYPE>
inline void interpolatePixel( DATATYPE* rval, const DATATYPE* left, const DATATYPE* right, const std::size_t& channels, const double& interpolationValue );

///given an image and coordinates, clamps the coordinates between 0 and the dimension of the image
///\todo array version, image version, returnvalue version
template <class DATATYPE, std::size_t DIMENSIONS, class COORDTYPE>
void clampPixelCoordinates(const Image<DATATYPE, DIMENSIONS>& arr,
                           std::array<COORDTYPE, DIMENSIONS>& coords);



///upscales an image by some integer value.   uses linear interpolation between pixels of the original image
template <class DATATYPE, std::size_t DIMENSIONS>
Image<DATATYPE,DIMENSIONS> upsample(const Image<DATATYPE,DIMENSIONS>& img, const std::size_t& scale);


//inline definitions of all the template methods
#include "Image.tcc"


#endif
