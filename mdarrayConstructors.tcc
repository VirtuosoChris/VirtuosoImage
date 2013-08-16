template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE>
template <typename... Args>
inline MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::MultidimensionalArray(const Args&... cargs)
    : BUFFERTYPE(cargs...)
{

}

template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE>
template <typename... Args>
inline MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::MultidimensionalArray(  Args&... cargs)
    : BUFFERTYPE(cargs...)
{

}



template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE>
template <class DATATYPE_2, class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::MultidimensionalArray(const MultidimensionalArray<DATATYPE_2,DIMENSIONS,BUFFERTYPE_2>& arr):
        BUFFERTYPE( *((BUFFERTYPE_2*) (&arr)) )
{

}

