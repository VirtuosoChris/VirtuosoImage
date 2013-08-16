#include "SharedPtrDeleters.h"
#include <iostream>

///inline definitions.  relatively big templated class so methods are divided into categorized definition files.  should be self explanatory

#include "mdarrayConstructors.tcc"
#include "mdarrayIO.tcc"
#include "mdarrayFunctions.tcc"
#include "mdarrayAccessors.tcc"
#include "mdarrayOperators.tcc"

#include <sstream>

template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
typename MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::slice_type MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::getSlice(const typename MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::index_type& loc,const typename MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::index_type& dims){
        return SLICE_MAKER<MultidimensionalArray<DATATYPE,DIMENSIONS, BUFFERTYPE>, slice_type>::getSlice(*this,loc,dims );
}



template <std::size_t DIMENSIONS>
std::ostream& operator<<(std::ostream& str, const std::array<std::size_t, DIMENSIONS>& arr)
{

    str<<'{';
    for(std::size_t i = 0; i < DIMENSIONS-1; i++)
    {
        str<<arr[i]<<", ";
    }

    str<<arr[DIMENSIONS-1]<<'}';

    return str;
}




template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
void MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::clamp(const DATATYPE& min_val, const DATATYPE& max_val)
{

    for(std::size_t i =0; i < numElements(); i++)
    {

        (*this)[i] = std::max<DATATYPE>(  std::min<DATATYPE>((*this)[i], max_val), min_val);

    }
}



template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::copySubregionFromTo(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::index_type& from, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::index_type& to)const
{

    index_type size = to;

    for(std::size_t i = 0; i < DIMENSIONS; i++)
    {

        size[i] -= from[i];
    }

    return copySubregion(from,size);

}














template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::copySubregion(const MultidimensionalArray<DATATYPE,DIMENSIONS, BUFFERTYPE>::index_type& location, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::index_type& regionSize)const
{

    for(std::size_t i = 0u; i < DIMENSIONS; i++)
    {

        if(location[i] > getDimensions()[i] || ( (location[i] + regionSize[i]) > getDimensions()[i]) )
        {

            std::stringstream sstr;

            sstr<<"Subregion goes out of bounds of main image with location "<<location<<" and size "<<regionSize<<'\n'
            <<"Actual dimensions of the array: "<<getDimensions();

            throw std::runtime_error(sstr.str());
        }

    }

    MultidimensionalArray<DATATYPE,DIMENSIONS> rImg(regionSize);


    std::size_t ptr = 0;

    subregionIterateOverDimension<DATATYPE,DIMENSIONS, DIMENSIONS-1,BUFFERTYPE>::copy(
        ptr,
        rImg,
        *this,
        location,
        location,
        regionSize
    );
    return rImg;

}










/*******************************Member methods**********************************/

template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
template <class DATATYPE_2,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator=(const MultidimensionalArray<DATATYPE_2,DIMENSIONS,BUFFERTYPE_2>& arrayIn)
{

    BUFFERTYPE::operator=(arrayIn);

    return *this;
}


template <class DATATYPE, std::size_t DIMS1, std::size_t DIMS_TO_DROP,class BUFFERTYPE>
MultidimensionalArray<DATATYPE, DIMS1 - DIMS_TO_DROP,BUFFERTYPE> collapseDimensionsLeft(const MultidimensionalArray<DATATYPE, DIMS1,BUFFERTYPE>& arrayIn)
{

    std::array<size_t, DIMS1 - DIMS_TO_DROP> dimsOut;

    std::size_t outidx=0;
    for(auto idx = DIMS_TO_DROP; idx < DIMS1; idx++,outidx++)
    {

        dimsOut[outidx] = arrayIn.dimensions[idx];

    }

    return MultidimensionalArray<DATATYPE, DIMS1 - DIMS_TO_DROP,BUFFERTYPE>(arrayIn.data, dimsOut);

}






template <class DATATYPE, std::size_t DIMS1, std::size_t DIMS_TO_DROP,class BUFFERTYPE>
MultidimensionalArray<DATATYPE, DIMS1 - DIMS_TO_DROP,BUFFERTYPE> collapseDimensionsRight(const MultidimensionalArray<DATATYPE, DIMS1,BUFFERTYPE>& arrayIn)
{

    std::array<size_t, DIMS1 - DIMS_TO_DROP> dimsOut;

    for(auto idx = 0; idx < DIMS1 - DIMS_TO_DROP; idx++)
    {

        dimsOut[idx] = arrayIn.dimensions[idx];

    }

    return MultidimensionalArray<DATATYPE, DIMS1 - DIMS_TO_DROP>(arrayIn.data, dimsOut);


}






/*************************other methods*******************/



template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
void MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::abs( )
{
    for(std::size_t i = 0; i <  numElements(); i++)
    {
        (*this)[i] = std::abs  ( (*this)[i]);
    }
}



template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
void MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::ceil( )
{
    for(std::size_t i = 0; i <  numElements(); i++)
    {
        (*this)[i] = std::ceil<DATATYPE>  ( (*this)[i]);
    }
}


template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
void MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::floor( )
{
    for(std::size_t i = 0; i <  numElements(); i++)
    {
        (*this)[i] = std::floor<DATATYPE> ( (*this)[i]);
    }
}



template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
void MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::negate()
{

    for(std::size_t i = 0; i < numElements(); i++)
    {
        (*this)[i] = -((*this)[i]);
    }

}



template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
void MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::bitwiseNegation()
{

    for(std::size_t i = 0; i < numElements(); i++)
    {
        (*this)[i] = ~((*this)[i]);
    }

}




