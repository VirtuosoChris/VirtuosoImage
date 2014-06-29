#ifndef VIRTUOSO_GRADIENT_H_INCLUDED
#define VIRTUOSO_GRADIENT_H_INCLUDED

#include "convolution.h"
///\todo right now assumes 1 channel.  todo, make one that does generic "whole image, gradient along n axis" todo make one that makes x,y image.
///make one that takes an rval
///\todo gradient type difference
template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE_IN>
MultidimensionalArray<DATATYPE,DIMENSIONS> computeHorizontalGradient(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_IN>& imageIn)
{

    //MultidimensionalArray<DATATYPE,DIMENSIONS> flImg(imageIn.getDimensions());

     double kernel[] = {-.50, 0.0, .50};
     double kernel2[] = {.25,.5,.25};//separable sobel operator



    return conv1DX(conv1DY(imageIn,kernel2,kernel2+3), kernel, kernel+3);


}


template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE_IN>
MultidimensionalArray<DATATYPE,DIMENSIONS> computeVerticalGradient(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_IN>& imageIn)
{

//    MultidimensionalArray<DATATYPE,DIMENSIONS> flImg(imageIn.getDimensions());

    double kernel1[] = {-.50, 0.0, .50};
    double kernel2[] = {.25,.5,.25};//separable sobel operator

    return conv1DY(conv1DX(imageIn,kernel2,kernel2+3), kernel1, kernel1+3);

}


#endif // VIRTUOSO_GRADIENT_H_INCLUDED
