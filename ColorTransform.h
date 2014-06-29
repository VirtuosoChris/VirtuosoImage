#ifndef COLOR_TRANSFORM_H_INCLUDED
#define COLOR_TRANSFORM_H_INCLUDED


#include <Eigen/Core>
#include "Image.h"

    template<class DATATYPE, std::size_t IMG_DIMENSIONS, std::size_t >
    Image<DATATYPE,DIMENSIONS> colorTransform(const Eigen::Matrix<MAT_ROWS, MAT_COLS>& mat, const Image<DATATYPE,DIMENSIONS& img )
    {

        if(MAT_COLS != img.getDimensions()){
            throw std::runtime_error("Matrix does not match pixel size");
        }

        throw std::runtime_error("Not implemented");

    }



#endif // COLOR_TRANSFORM_H_INCLUDED
