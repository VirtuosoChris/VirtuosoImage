///copy constructor.  makes a copy of the data.  optimized to copy straight from another arraybuffer
template <class DATATYPE,std::size_t DIMENSIONS>
template <class DATATYPE_2>
ArrayBuffer<DATATYPE,DIMENSIONS>::ArrayBuffer(const ArrayBuffer<DATATYPE_2,DIMENSIONS>& arrayIn)
    :dimensions(arrayIn.getDimensions()),
    data(new DATATYPE[numElements()])
{
    for(std::size_t i = 0; i < numElements(); i++){
        (*this)[i] =   static_cast<DATATYPE>( arrayIn[i] );
    }
}


template <class DATATYPE,std::size_t DIMENSIONS>
ArrayBuffer<DATATYPE,DIMENSIONS>::ArrayBuffer(const ArrayBuffer<DATATYPE,DIMENSIONS>& arrayIn)
{

    copyData(arrayIn.dataPtr(), arrayIn.getDimensions());

}


template <class DATATYPE,std::size_t DIMENSIONS>
ArrayBuffer<DATATYPE, DIMENSIONS>::ArrayBuffer(std:: istream& stream)

{
    read(stream);
}




template <class DATATYPE,std::size_t DIMENSIONS>
ArrayBuffer<DATATYPE, DIMENSIONS>::ArrayBuffer()
{

    for(auto it = dimensions.begin(); it != dimensions.end(); it++){

        *it = 0;
    }

}

template <class DATATYPE,std::size_t DIMENSIONS>
ArrayBuffer<DATATYPE, DIMENSIONS>::ArrayBuffer(DATATYPE* ptrIn, const index_type& dimensionsIn, bool copy_array)
    :  dimensions(dimensionsIn)
{
    if(copy_array){
        copyData(ptrIn,dimensionsIn);
    }
    else{
        data = std::shared_ptr<DATATYPE>(ptrIn, NoopDeleter<DATATYPE>()); ///since we did not allocate this memory, we will not free it.
    }
}




template <class DATATYPE,std::size_t DIMENSIONS>
ArrayBuffer<DATATYPE, DIMENSIONS>::ArrayBuffer(const index_type& dimensionsIn)
:
    dimensions(dimensionsIn),
    data(new DATATYPE[numElements()], ArrayDeleter<DATATYPE>()) //array deleter
{

}




template <class DATATYPE,std::size_t DIMENSIONS>
ArrayBuffer<DATATYPE, DIMENSIONS>::ArrayBuffer(const index_type& dimensionsIn,const DATATYPE& initial_value)
:
    dimensions(dimensionsIn),
    data(new DATATYPE[numElements()], ArrayDeleter<DATATYPE>()) //array deleter
{

    for(std::size_t i = 0; i < numElements();i++){
        (*this)[i] = initial_value;
    }

}




template <class DATATYPE,std::size_t DIMENSIONS>
ArrayBuffer<DATATYPE, DIMENSIONS>::ArrayBuffer(const std::shared_ptr<DATATYPE>& ptrIn, const index_type& dimensionsIn)
    :
    dimensions(dimensionsIn),
    data(ptrIn)
{

}




////**************************************************************/

template <class DATATYPE,std::size_t DIMENSIONS>
std::size_t ArrayBuffer<DATATYPE, DIMENSIONS>::numElements()const{

    std::size_t returnVal = 1;
    for(auto it =  getDimensions().begin(); it != getDimensions().end(); it++){
        returnVal*= *it;
    }

    return returnVal;
}



template <class DATATYPE,std::size_t DIMENSIONS>
ArrayBuffer< DATATYPE, DIMENSIONS>::operator bool()const{
    return data.get() && numElements();
}


///linear indexing operator
template <class DATATYPE,std::size_t DIMENSIONS>
inline const DATATYPE& ArrayBuffer< DATATYPE, DIMENSIONS>::operator[](const std::size_t& idx)const
{
    return (data.get())[idx];
}



///linear indexing operator
template <class DATATYPE,std::size_t DIMENSIONS>
inline DATATYPE& ArrayBuffer< DATATYPE, DIMENSIONS>::operator[](const std::size_t& idx)
{
    return data.get()[idx];
}



template <class DATATYPE,std::size_t DIMENSIONS>
inline void ArrayBuffer< DATATYPE, DIMENSIONS>::copyData(const DATATYPE* ptr)
{
    memcpy(data.get(), ptr, sizeBytes());
}



template <class DATATYPE,std::size_t DIMENSIONS>
void ArrayBuffer< DATATYPE, DIMENSIONS>::copyData(const DATATYPE* ptr, const index_type& dimensionsIn)
{

    if(dimensions!= dimensionsIn)  //check if we actually need to reallocate the buffer
    {
        dimensions = dimensionsIn; //set the dimensions to the new dimensions
        data.reset(new DATATYPE[numElements()], ArrayDeleter<DATATYPE>());//allocate memory
    }

    copyData(ptr);

}



template <class DATATYPE, std::size_t DIMENSIONS>
inline DATATYPE& ArrayBuffer<DATATYPE, DIMENSIONS>::operator()(const index_type& index)
{

    return data.get()[ linearizeMultidimensionalIndex(index, dimensions) ];

}



template <class DATATYPE, std::size_t DIMENSIONS>
template <typename... Args>
const DATATYPE& ArrayBuffer<DATATYPE,DIMENSIONS>::operator()(const Args&... args )const{
    return (*this)[linearizeMultidimensionalIndex( getDimensions(),args...)];
}



template <class DATATYPE, std::size_t DIMENSIONS>
template <typename... Args>
DATATYPE& ArrayBuffer<DATATYPE,DIMENSIONS>::operator()(const Args&... args ) {
    return (*this)[linearizeMultidimensionalIndex(getDimensions(),args...)];
}







template <class DATATYPE,std::size_t DIMENSIONS>
void ArrayBuffer<DATATYPE, DIMENSIONS>::read(std:: istream& stream)

{
    stream.read(static_cast<  char*>(&(dimensions)),sizeof(index_type));

    data.reset( sizeBytes() );

    stream.read(static_cast<  char*> (data.get()),sizeBytes());



}




template <class DATATYPE, std::size_t DIMENSIONS>
const std::array<std::size_t, DIMENSIONS>& ArrayBuffer<DATATYPE,DIMENSIONS>::getDimensions()const{
    return dimensions;
}


template <class DATATYPE,std::size_t dimensions>
const DATATYPE* ArrayBuffer<DATATYPE, dimensions>::ptrToIndex(const index_type& index)const{

    return &((*this)(index));

}




template <class DATATYPE, std::size_t DIMENSIONS>
const DATATYPE& ArrayBuffer<DATATYPE, DIMENSIONS>::operator()(const index_type& index)const
{
  return data.get()[linearizeMultidimensionalIndex(index,dimensions)];

}









template <class DATATYPE,std::size_t DIMENSIONS>
DATATYPE* ArrayBuffer< DATATYPE, DIMENSIONS>::dataPtr() {
  return data.get();
}




template <class DATATYPE,std::size_t DIMENSIONS>
const DATATYPE* ArrayBuffer< DATATYPE, DIMENSIONS>::dataPtr()const{
  return data.get();
}








template <class DATATYPE,std::size_t DIMENSIONS>
void ArrayBuffer<DATATYPE, DIMENSIONS>::write(std:: ostream& stream)const

{
    stream.write(static_cast<  char*>(&(dimensions)),sizeof(index_type));

    stream.write(static_cast<  char*> (data.get()),sizeBytes());

}




template <class DATATYPE,std::size_t DIMENSIONS>
const DATATYPE*  ArrayBuffer<DATATYPE, DIMENSIONS>::ptr(const std::array<std::size_t,DIMENSIONS>& idx)const{
    return &((*this)(idx));
}


template <class DATATYPE,std::size_t DIMENSIONS>
DATATYPE*  ArrayBuffer<DATATYPE, DIMENSIONS>::ptr(const std::array<std::size_t,DIMENSIONS>& idx){
    return &((*this)(idx));
}


template <class DATATYPE,std::size_t DIMENSIONS>
template <typename... Args>
const DATATYPE*  ArrayBuffer<DATATYPE, DIMENSIONS>::ptr(const Args&... args )const{
        return ptr ( {{args...}} );
}


template <class DATATYPE,std::size_t DIMENSIONS>
template <typename... Args>
DATATYPE*  ArrayBuffer<DATATYPE, DIMENSIONS>::ptr(const Args&... args ){
    return ptr( {{static_cast<std::size_t>(args)...}} );
}





template <class DATATYPE,std::size_t dimensions>
std::size_t ArrayBuffer<DATATYPE, dimensions>::sizeBytes()const{

    return numElements() * sizeof(DATATYPE);

}


