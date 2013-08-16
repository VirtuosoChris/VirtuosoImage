//const methods that return information about the class


template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE>
std::size_t MultidimensionalArray< DATATYPE, DIMENSIONS,BUFFERTYPE>::axisLength(const std::size_t axis)const{
    return getDimensions()[axis];
}




template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE>
inline const typename MultidimensionalArray< DATATYPE, DIMENSIONS,BUFFERTYPE>::index_type& MultidimensionalArray< DATATYPE, DIMENSIONS,BUFFERTYPE>::getDimensions()const{

    return BUFFERTYPE::getDimensions();
}




template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE>
std::size_t MultidimensionalArray<DATATYPE, DIMENSIONS,BUFFERTYPE>::numElements()const{

    std::size_t returnVal = 1;
    for(auto it = BUFFERTYPE::getDimensions().begin(); it != BUFFERTYPE::getDimensions().end(); it++){
        returnVal*= *it;
    }

    return returnVal;
}





