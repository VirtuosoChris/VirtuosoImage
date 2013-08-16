///non-class functions associated with MultidimensionalArray
#include <cmath>
#include <limits>



template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
DATATYPE mean(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& img){

    double sum=0.0;
    double reciprocal = 1.0 / img.numElements();

    for(std::size_t i= 0; i < img.numElements(); i++){

        sum+= img[i];

    }

    return sum * reciprocal;

}

template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE>
std::pair<DATATYPE,DATATYPE> minMax(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& arr)
{
    DATATYPE minEl = std::numeric_limits<DATATYPE>::max();
    DATATYPE maxEl = -std::numeric_limits<DATATYPE>::max(); ///\todo what about unsigned?

    for(int i = 0; i < arr.numElements(); i++ )
    {

        minEl = std::min<DATATYPE>(minEl ,arr[i]);
        maxEl = std::max<DATATYPE>(maxEl, arr[i]);

    }

    return std::pair<DATATYPE,DATATYPE>(minEl,maxEl);
}





template <std::size_t DIMENSIONS,class BUFFERTYPE>
bool any(const MultidimensionalArray<bool, DIMENSIONS,BUFFERTYPE>& arr){

    for(std::size_t i = 0; i < arr.numElements();i++){
        if(arr[i])return true;
    }
    return false;
}

template <std::size_t DIMENSIONS,class BUFFERTYPE>
bool  all(const MultidimensionalArray<bool, DIMENSIONS,BUFFERTYPE>& arr){

    for(std::size_t i = 0; i < arr.numElements();i++){
        if(!arr[i])return false;
    }
    return true;
}

template <std::size_t DIMENSIONS,class BUFFERTYPE>
inline bool  none(const MultidimensionalArray<bool, DIMENSIONS,BUFFERTYPE>& arr){

    return !(any(arr));
}


template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> abs(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& arr){
    MultidimensionalArray<DATATYPE,DIMENSIONS> rval;
    for(std::size_t i = 0u; i < arr.numElements();i++){
        rval[i] = abs<DATATYPE>(arr[i]);
    }
    return rval;
}


template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> floor(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& arr){
    MultidimensionalArray<DATATYPE,DIMENSIONS> rval;
    for(std::size_t i = 0u; i < arr.numElements();i++){
        rval[i] = std::floor<DATATYPE>(arr[i]);
    }
    return rval;
}

template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> ceil(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& arr){
    MultidimensionalArray<DATATYPE,DIMENSIONS> rval;
    for(std::size_t i = 0u; i < arr.numElements();i++){
        rval[i] = std::ceil<DATATYPE>(arr[i]);
    }
    return rval;
}

