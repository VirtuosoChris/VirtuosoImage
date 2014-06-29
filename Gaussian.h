#ifndef VIRTUOSO_GAUSSIAN_H_INCLUDED
#define VIRTUOSO_GAUSSIAN_H_INCLUDED


#ifndef M_PI
const double M_PI = atan(1) * 4;
#endif

#include "Convolution.h"


///evaluate the 1D gaussian curve at a particular point
inline double gaussian1D(double distanceX, double stdev)
{

    double a = 1.0 / sqrt(2.0 * M_PI * stdev * stdev);

    double exponent = (-distanceX * distanceX )/ (2.0 * stdev * stdev);

    return a * exp(exponent);

}



///evaluate the 2 dimensional gaussian curve at a particular point
inline double gaussian2D(double distanceX,double distanceY, double stdev)
{
    return gaussian1D( distanceX , stdev) * gaussian1D(distanceY, stdev);
}




inline double gaussianND(int dimensionality, double stdev, double distances[] ){

    double accum = 1.0;
    for(int i = 0; i < dimensionality; i++){
        accum *= gaussian1D(distances[i], stdev);
    }
    return accum;
}






///\todo make an N-D kernel function
template <class T>///\todo think the typing out of this one a bit better
inline void makeGaussianKernel1D(T kernelArray[], int kernelSize, double stdev)
{

    int distance = kernelSize / 2;

    double totalSum=0.0;

    for(int i = -distance, index=0; index < kernelSize; i++, index++)
    {
        totalSum+= (kernelArray[index]=  gaussian1D(i, stdev) );
    }

    //normalize
    for(int i = 0; i < kernelSize; i++)
    {
        kernelArray[i] /= totalSum;
    }

}






///how big should a gaussian kernel be to have a smooth falloff to zero at the edges
inline int idealGaussianKernelSize(double stdev)
{
    return static_cast<int>(std::ceil(stdev)) * 6 + 1;
}



template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE_IN>
MultidimensionalArray<DATATYPE,DIMENSIONS> gaussianBlur2D(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_IN>& imageIn, double sigma)
{

    std::vector<double> kernel(idealGaussianKernelSize(sigma));

    makeGaussianKernel1D(&kernel[0], kernel.size(), sigma);

    return
    conv1DY(
               conv1DX(imageIn, kernel.begin(), kernel.end())
               ,kernel.begin()
               ,kernel.end()
           )
           ;

}









#endif // VIRTUOSO_GAUSSIAN_H_INCLUDED
