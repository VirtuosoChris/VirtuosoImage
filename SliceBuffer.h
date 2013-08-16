#ifndef SLICE_BUFFER_H_INCLUDED
#define SLICE_BUFFER_H_INCLUDED



template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
class SliceBuffer{

    typedef typename MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::index_type index_type ;
    typedef  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE> array_type;

    template <class A, class B>
    friend struct SLICE_MAKER ;

    template <class A,std::size_t B,class C>
    friend class MultidimensionalArray;

    array_type* arr;
    index_type location;
    index_type dimensions;

    DATATYPE& get(const index_type& idx){///\todo dep read perf test on this

        index_type idx2;

        for(std::size_t i = 0; i < idx.size(); i++){
                idx2[i]  = idx[i] + location[i];///\todo remember this
        }

        return (*arr)(idx2);

    }

  const DATATYPE& get(const index_type& idx)const {///\todo dep read perf test on this

        index_type idx2;

        for(std::size_t i = 0; i < idx.size(); i++){
                idx2[i]  = idx[i] + location[i];///\todo remember this
        }

        return (*arr)(idx2);

    }

private:

      SliceBuffer(  MultidimensionalArray<DATATYPE,DIMENSIONS, BUFFERTYPE>& arrIn,
                const index_type& positionIn,
                const index_type& regionSize )
    :arr(&arrIn),
    location(positionIn),
    dimensions(regionSize)
    {

        for(std::size_t i = 0; i < dimensions.size();i++){

            if(
                (location[i] >= arrIn.getDimensions()[i])   ||
                (location[i] + regionSize[i] > arrIn.getDimensions()[i])
               ){
                throw std::runtime_error("slice subregion goes out of bounds of original array");
            }

        }
    }



  public:

     std::size_t numElements()const{

        std::size_t returnVal = 1;

        for(auto it =  getDimensions().begin(); it != getDimensions().end(); it++){
            returnVal*= *it;
        }

            return returnVal;
     }

    const index_type& getDimensions()const{
        return dimensions;
    }

    const index_type& getLocation()const{
        return location;
    }




        ///checks if this is a valid array.  That is, the number of elements > 0 and the data pointer is not null
        operator bool()const{

            return ((bool)(*arr));

        }


      SliceBuffer& operator=(const ArrayBuffer<DATATYPE,DIMENSIONS>& r)
      {
            for(std::size_t i = 0; i < getDimensions().size();i++){

                if(getDimensions()[i] != r.getDimensions()[i]){

                    throw std::runtime_error("non-matching dimensions when assigning slice-buffer elements");
                }
            }

            for(int i = 0; i < numElements();i++){

                (*this)[i] = r[i];

            }

             return *this;
        }


        DATATYPE& operator()(const index_type& idx){
            return get(idx);
        }

        const DATATYPE& operator()(const index_type& idx)const{
                    return get(idx);
        }

        template <typename... Args>///\todo does this go here?
        const DATATYPE& operator()(const Args&... args )const{
            return get({{args...}});
        }

        template <typename... Args>
        DATATYPE& operator()(const Args&... args ){
            return get({{args...}});
        }

        DATATYPE& operator[](const std::size_t& idx){
                return get(unlinearizeMultidimensionalIndex<DIMENSIONS>( idx,getDimensions() ) );
        }

        const DATATYPE& operator[](const std::size_t& idx)const{
                return get(unlinearizeMultidimensionalIndex<DIMENSIONS>( idx,getDimensions() ) );
        }

    MultidimensionalArray<DATATYPE,DIMENSIONS> copy(){
        return arr->copySubregion(location,dimensions);
    }

};


/* these template structs are here solely to establish default behavior and overloads for slice types for a multidimensional array.  The default is to have
 here is overloaded in the case of a slice buffer of a slice buffer.  to prevent absurdity, a slice of a slice has the same type as the original slice.  */


template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
struct SLICE_TYPE {

    typedef MultidimensionalArray<DATATYPE,DIMENSIONS, SliceBuffer<DATATYPE,DIMENSIONS, BUFFERTYPE> > type;

};


template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
struct SLICE_TYPE<DATATYPE,DIMENSIONS,SliceBuffer<DATATYPE,DIMENSIONS, BUFFERTYPE> >{

    typedef MultidimensionalArray<DATATYPE,DIMENSIONS, SliceBuffer<DATATYPE,DIMENSIONS, BUFFERTYPE> > type;

};


template <class ARRAY_TYPE, class SLICE_TYPE>
struct SLICE_MAKER {

    static SLICE_TYPE getSlice(ARRAY_TYPE& array_in, const typename ARRAY_TYPE::index_type& loc, const typename ARRAY_TYPE::index_type& dims){
        return SLICE_TYPE(array_in, loc, dims);
    }

};


///if the array type equals the slice type we perform special logic to make the slice from abother slice
template < class ARRAY_SLICE_TYPE>
struct SLICE_MAKER <ARRAY_SLICE_TYPE,ARRAY_SLICE_TYPE>{

static ARRAY_SLICE_TYPE getSlice( ARRAY_SLICE_TYPE& slice_in,const typename ARRAY_SLICE_TYPE::index_type& loc, const typename ARRAY_SLICE_TYPE::index_type& dims){

        typename ARRAY_SLICE_TYPE::index_type locOut;


        ///do bounds check against original slice in addition to the bounds check that will be done on the original array

        ///take the offset into the slice and backconvert it into the original array
        for(std::size_t i = 0; i < locOut.size(); i++){

            locOut[i] = loc[i] + slice_in.getLocation()[i];

            if(
               loc[i] >= slice_in.getDimensions()[i]
               ||
                (loc[i] + dims[i]) > slice_in.getDimensions()[i]
               )
               {
                throw std::runtime_error("Subslice out of range");
               }

        }

        return ARRAY_SLICE_TYPE ( *(slice_in.arr), locOut, dims  );

}

};


#endif // SLICE_BUFFER_H_INCLUDED
