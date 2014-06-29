#ifndef IMAGE_PROCESSING_H_INCLUDED
#define IMAGE_PROCESSING_H_INCLUDED

#include "Image.h"///\todo dependency include?

#include <limits>

///\todo make this a generic matrix color multiplicaiton thing ?
///matrix n x channels

///assumes first 3 channels are r,g,b at each pixel location
template <class DATATYPE, std::size_t DIMENSIONS>
Image<DATATYPE,DIMENSIONS> toSingleChannel(const Image<DATATYPE,DIMENSIONS>& imgIn, const double colorConversion[]){

    typename Image<DATATYPE,DIMENSIONS>::index_type dims;

    dims[0] = 1;

    if(imgIn.axisLength(0) < 3){
        throw std::runtime_error("need at least 3 channels to create luminance image");
    }

    for(std::size_t i = 1; i < DIMENSIONS+1; i++){
        dims[i] = imgIn.axisLength(i);
    }

    Image<DATATYPE,DIMENSIONS> rval(dims);


    ///perform luminance conversion
    for(std::size_t pix = 0; pix < rval.numElements(); pix++){

        std::size_t base_index = pix * imgIn.axisLength(0); //stride

        rval[pix] = imgIn[base_index] * colorConversion[0]+
                    imgIn[base_index+1] * colorConversion[1]+
                    imgIn[base_index+2] * colorConversion[2];

    }

    return rval;

}




template <class T>
MultidimensionalArray<typename T::data_type,T::array_dimensions> toLuminance(const T& imgIn){

    const MultidimensionalArray<typename T::data_type,T::array_dimensions>& img = imgIn;
     const double colorConversion[3] = {.2126, .7152, .0722};
   return toSingleChannel<typename T::data_type,T::array_dimensions-1>(img, colorConversion);


}





///expand, collapse


///if reduce, then just drop the channels.  if expand, then set channels to zero
template < class DATATYPE, std::size_t DIMENSIONS>
Image<DATATYPE,DIMENSIONS> resizeChannels(const Image<DATATYPE,DIMENSIONS>& img, const std::size_t& channels){

    typename Image<DATATYPE,DIMENSIONS>::index_type idx;

    idx[0] = channels;

    for(std::size_t i = 1; i < idx.size(); i++){

        idx[i] = img.getDimensions()[i];
    }

    Image<DATATYPE,DIMENSIONS> rval(idx);

    ///\todo don't always copy r channel
    for(std::size_t pix = 0; pix < rval.numElements();pix++){

        auto index = unlinearizeMultidimensionalIndex(pix, rval.getDimensions());

        if(index[0] < img.getDimensions()[0]){

            rval(index) = img(index);

        }else{ //if we are adding a channel we will pad with 0's

            rval(index) = 0;

        }
    }

    return rval;
}






template < class DATATYPE, std::size_t DIMENSIONS>
Image<DATATYPE,DIMENSIONS> expandGrayscaleToRGBA(const Image<DATATYPE,DIMENSIONS>& img,    DATATYPE  initial_alpha  ){

    if(!(img.getDimensions()[0]==1)){
        throw std::runtime_error("Input image not grayscale");
    }

    typename Image<DATATYPE,DIMENSIONS>::index_type idx;

    idx[0] = 4;

    for(std::size_t i = 1; i < idx.size(); i++){

        idx[i] = img.getDimensions()[i];
    }

    Image<DATATYPE,DIMENSIONS> rval(idx);

    ///\todo don't always copy r channel
    for(std::size_t pix = 0; pix < img.numElements();pix++){

        auto index = unlinearizeMultidimensionalIndex(pix, img.getDimensions());

        DATATYPE outCol =  img(index);

        for(std::size_t ch = 0;  ch < 3; ch++){

            index[0] = ch;

            rval(index) = outCol;

        }

        index[0] = 3;

        rval(index) = initial_alpha;

    }

    return rval;

}





///\todo genericize
template < class DATATYPE, std::size_t DIMENSIONS>
Image<DATATYPE,DIMENSIONS> expandGrayscaleToRGB(const LDRImage& img ){

    //std::cerr<<"Expanding to channels "<<channels<<std::endl;
    if(!(img.getDimensions()[0]==1)){
        throw std::runtime_error("Input image not grayscale");
    }

    typename Image<DATATYPE,DIMENSIONS>::index_type idx;

    idx[0] = 3;

    for(std::size_t i = 1; i < idx.size(); i++){

        idx[i] = img.getDimensions()[i];
    }

    Image<DATATYPE,DIMENSIONS> rval(idx);

    ///\todo don't always copy r channel
    for(std::size_t pix = 0; pix < img.numElements();pix++){

        auto index = unlinearizeMultidimensionalIndex(pix, img.getDimensions());

        DATATYPE outCol =  img(index);

        for(std::size_t ch = 0;  ch < 3; ch++){

            index[0] = ch;

            rval(index) = outCol;

        }

    }

    return rval;

}







template <class DAT, std::size_t DIMS>
MultidimensionalArray<DAT, DIMS> grayscale(const MultidimensionalArray<DAT, DIMS>& imgIn){

    const double colorConversion[3] = {1.0/3.0, 1.0/3.0, 1.0/3.0};
    return toSingleChannel<DAT,2ull>(imgIn, colorConversion); ///\todo shazoo number
}




template <class DAT, std::size_t DIMS>
Image<DAT,DIMS>  expandGrayscaleToChannels(const Image<DAT,DIMS>& img, const std::size_t& channels, DAT alpha )
{

        switch(channels){

        case 4 :
                    return expandGrayscaleToRGBA<DAT,DIMS>(img,alpha);

                    break;
        case 3:
                    return expandGrayscaleToRGB<DAT,DIMS>(img);

                    break;
        default: throw std::runtime_error("Can only expand grayscale to rgb or rgba");
    }

}



///\todo how do we do an in place one?  also this could be significantly optimized
template < class DATATYPE, std::size_t DIMENSIONS>
MultidimensionalArray<DATATYPE,DIMENSIONS> saturation(const MultidimensionalArray<DATATYPE,DIMENSIONS>& img, const double& sat ){


    MultidimensionalArray<DATATYPE,DIMENSIONS> ex =
                                         expandGrayscaleToChannels<DATATYPE,DIMENSIONS-1>(
                                         grayscale<DATATYPE,DIMENSIONS>(img)
                                         ,img.getDimensions()[0]
                                        ,255
                                    )
                                         ;

    return ( img*sat)
     +
    (1.0-sat)*ex
    ;

}



///\todo buffertype on all this
template <  std::size_t DIMENSIONS>
MultidimensionalArray<unsigned char,DIMENSIONS> saturation(const MultidimensionalArray<unsigned char,DIMENSIONS>& img, const double& sat ){

    MultidimensionalArray<int ,DIMENSIONS> ex = expandGrayscaleToChannels<unsigned char,DIMENSIONS-1>(grayscale<unsigned char,DIMENSIONS>(img),img.getDimensions()[0],255);

    MultidimensionalArray<int, DIMENSIONS> rval = (1.0-sat)*ex  +   (MultidimensionalArray<int, DIMENSIONS>( img)*sat); ///\todo why do i have to cast the rhs

    rval.clamp(0,255);

    ///\todo is there any way to make casting rules work? left right?
    //return Image<unsigned char,DIMENSIONS>(    rval  );
    return rval;

 }



#endif // IMAGE_PROCESSING_H_INCLUDED


#ifdef IMAGE_PROCESSING_H_INCLUDED_OLD_SSSS
#define IMAGE_PROCESSING_H_INCLUDED

#include "Image.h"

#include <cmath>
#include <vector>

template<class DATATYPE,std::size_t DIMENSIONS>
void clampImageChannel(Image<DATATYPE,DIMENSIONS>& imageIn, const std::size_t& channel,const DATATYPE& thresh){

    for(int i = 0; i < imageIn.channels * imageIn.width * imageIn.height; i++){

        imageIn[i] = std::min(imageIn[i], thresh);

    }
}



///LDRImage extractChannel.




///looks at some square block region of an image and returns an image that is zeroed for pixels that are not local maxima
FloatImage nonMaximumSuppressionBlock(const FloatImage& imageIn, int windowRegion=12);


///\todo non float version.
Image thresholdImage(const FloatImage& imageIn, float thresh);

//void thresholdImage(FloatImage& imageIn, float thresh);



#endif
