
template <typename DATATYPE, std::size_t DIMENSIONS, std::size_t DIMENSION_TO_ITERATE,class INBUFFER>
struct subregionIterateOverDimension
{

    static void copy (
        std::size_t& outIndex,
          MultidimensionalArray<DATATYPE,DIMENSIONS>& outArray,
        const MultidimensionalArray<DATATYPE, DIMENSIONS,INBUFFER>& arr, ///array we're copying from
        const  typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& current_loc,  ///accululator
        const typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& location, ///base of copy subregion
        const typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& regionSize   ///size of subregion
    )
    {

        std::size_t begin = location[DIMENSION_TO_ITERATE];
        std::size_t end = begin + regionSize[DIMENSION_TO_ITERATE];

        typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type imgLoc = current_loc;

        for(std::size_t it = begin; it < end; it++)
        {

            imgLoc[DIMENSION_TO_ITERATE] = it;

            subregionIterateOverDimension<DATATYPE,DIMENSIONS,DIMENSION_TO_ITERATE-1,INBUFFER>::copy(
                outIndex,
                outArray,
                arr,
                imgLoc,
                location,
                regionSize
            );
        }



    }
};



template <typename DATATYPE, std::size_t DIMENSIONS >
struct subregionIterateOverDimension<DATATYPE,DIMENSIONS, 0u,ArrayBuffer<DATATYPE,DIMENSIONS> >
{

    static void copy (

        std::size_t& outIndex,
          MultidimensionalArray<DATATYPE,DIMENSIONS>& outArray,
        const MultidimensionalArray<DATATYPE, DIMENSIONS,ArrayBuffer<DATATYPE,DIMENSIONS> >& arr, ///array we're copying from
        const  typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& current_loc,  ///accululator
        const typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& location, ///base of copy subregion
        const typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& regionSize   ///size of subregion
    )
    {

       // std::cerr<<reinterpret_cast<std::size_t>(outPtr)<<std::endl;

        std::size_t increment = regionSize[0];/// sizeof was here... but pretty sure that's wrong* sizeof(DATATYPE); //size of smallest section of memory to memcpy

        memcpy(&outArray[outIndex],

               const_cast<DATATYPE*>(&arr(current_loc)),

               increment * sizeof(DATATYPE)
        );

        outIndex += increment;

    }

};





template <typename DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE >
struct subregionIterateOverDimension<DATATYPE,DIMENSIONS, 0u,BUFFERTYPE >
{

    static void copy (

        std::size_t& outIndex,
          MultidimensionalArray<DATATYPE,DIMENSIONS>& outArray,
        const MultidimensionalArray<DATATYPE, DIMENSIONS,BUFFERTYPE >& arr, ///array we're copying from
        const  typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& current_loc,  ///accululator
        const typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& location, ///base of copy subregion
        const typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type& regionSize   ///size of subregion
    )
    {



        std::size_t begin = location[0u];
        std::size_t end = begin + regionSize[0u];

        typename MultidimensionalArray<DATATYPE,DIMENSIONS>::index_type imgLoc = current_loc;

        for(std::size_t it = begin; it < end; outIndex++,current_loc[0]++)
        {

            imgLoc[0] = it;

            outArray[outIndex] = arr(imgLoc);

        }

    }

};



