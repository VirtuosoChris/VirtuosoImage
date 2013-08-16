#ifndef ARRAY_BUFFER_H_INCLUDED
#define ARRAY_BUFFER_H_INCLUDED

#include "SharedPtrDeleters.h"
#include "linearize.h"

template <class DATATYPE,std::size_t DIMENSIONS>
class ArrayBuffer{

    private:

        typedef std::array<std::size_t, DIMENSIONS> index_type;

        index_type dimensions;
        std::shared_ptr<DATATYPE> data;  ///ptr to the raw data


        ///copies over the data pointed to by ptr into my buffer.
        void copyData(const DATATYPE* ptr);

    protected:

         ArrayBuffer(std::istream& stream);

        ///copy constructor.  makes a copy of the data.  optimized to copy straight from another arraybuffer
        ArrayBuffer(const ArrayBuffer<DATATYPE,DIMENSIONS>& arrayIn);

        ///given the dimensions, allocate new memory
        ArrayBuffer(const index_type& dimensionsIn);

         ///given the dimensions, allocate new memory
        ArrayBuffer(const index_type& dimensionsIn, const DATATYPE& initial_value);

        ///given some shared_ptr to an outside resource, and dimensions and type to interpret it,
        ///we can construct a multidimensional array object to represent it
        ArrayBuffer(const std::shared_ptr<DATATYPE>& ptrIn, const index_type& dimensionsIn);


    public:

        const index_type& getDimensions()const;


        void read(std::istream&); ///initialize from a stream

        void write(std::ostream&)const; ///write to a stream


        ///given some ptr to an outside resource, construct a multidimensional array object to represent it.
        ///Will act as a *reference* to the original data if copyData is set to false.  Will copy the data into
        ///a unique buffer if copyData is set to true.
        ArrayBuffer(DATATYPE* ptrIn, const index_type& dimensionsIn, bool copyData=true);

        ///default ctor.  set all the dimensions to 0 and data ptr to null
        ArrayBuffer();

        ///copy constructor that takes in an array of a different datatype.  Useful for upcasting, downcasting, etc eg from hdr to ldr
        template <class DATATYPE_2>
        ArrayBuffer(const ArrayBuffer<DATATYPE_2, DIMENSIONS>& imgIn);


        /***************query methods*********************************/

        const DATATYPE* dataPtr() const;

        ///checks if this is a valid array.  That is, the number of elements > 0 and the data pointer is not null
        operator bool()const;

        const DATATYPE* ptr(const std::array<std::size_t,DIMENSIONS>& idx)const;

        DATATYPE* ptr(const std::array<std::size_t,DIMENSIONS>& idx);

        template <typename... Args>
        const DATATYPE* ptr(const Args&... args )const;

        template <typename... Args>
        DATATYPE* ptr(const Args&... args );

          /**************manipulation methods*****************************/
        ///reallocate the memory to be of the appropriate size to store the array of dimensions *dimensionsIn*, then copy the data from the pointer
        void copyData(const DATATYPE* ptr, const index_type& dimensionsIn);

        DATATYPE* dataPtr();

        ArrayBuffer<DATATYPE,DIMENSIONS>& operator=(const ArrayBuffer<DATATYPE,DIMENSIONS>& r)
        {
            copyData(r.dataPtr(),r.getDimensions());
            return *this;
        }


        DATATYPE& operator()(const index_type& idx);
        const DATATYPE& operator()(const index_type& idx)const;

        DATATYPE& operator[](const std::size_t& idx);
        const DATATYPE& operator[](const std::size_t& idx)const;

        template <typename... Args>
        const DATATYPE& operator()(const Args&... args )const;

        template <typename... Args>
        DATATYPE& operator()(const Args&... args );

        ///gives ptr to a particular element
        const DATATYPE* ptrToIndex(const index_type& index)const;

        ///size in bytes allocated for this entire array
        std::size_t sizeBytes()const;

        std::size_t numElements()const;


};


#include "ArrayBuffer.tcc"

#endif // ARRAY_BUFFER_H_INCLUDED
