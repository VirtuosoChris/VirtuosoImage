#ifndef MULTIDIMENSIONAL_ARRAY_H_INCLUDED
#define MULTIDIMENSIONAL_ARRAY_H_INCLUDED

#include <array>
#include <memory>

#include <iostream>

template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
class SliceBuffer;

template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
class SLICE_TYPE;

template <class ARRAY_TYPE, class SLICE_TYPE>
struct SLICE_MAKER;

#include "ArrayBuffer.h"
#include "linearize.h"

///Multidimensional array type.
///data elements of type DATATYPE, with DIMENSIONS axes
///stored in "rows" of each dimension type.  For instance, with dimensions {3,128,256}
///we have clusters of 256 rows of 128*3.
///This is the reverse of how you'd normally think of indexing in C++ with an array like int x[5][3]
///Also note that lower indexes come first in memory. (eg, row 0 comes in memory before row 1)

///inherit from MDArrayBase with the new buffer as argument.  in constructor fo top level class, initialize the buffer and add constructors.
///basically like a virtual overload of the appropriate operators, except using an intermediate struct to resolve the shit at compile time.

template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE = ArrayBuffer<DATATYPE,DIMENSIONS> >
class MultidimensionalArray : public BUFFERTYPE
{

public:

    typedef typename SLICE_TYPE<DATATYPE,DIMENSIONS, BUFFERTYPE>::type slice_type;

    typedef std::array<std::size_t, DIMENSIONS> index_type;
    typedef DATATYPE data_type;
    const static std::size_t array_dimensions = DIMENSIONS;

    /***** these operators are required in every BufferType****/

    using BUFFERTYPE::operator(); ///require a multidimensional lookup that takes coordinates of type index_type
    using BUFFERTYPE::operator[]; ///require a linear indexing operation
    using BUFFERTYPE::operator bool; ///if(array) indicates whether or not the buffer is valid for lookups

public:

    template <class DATATYPE_2,class BUFFERTYPE_2>
    MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& operator=(const MultidimensionalArray<DATATYPE_2,DIMENSIONS,BUFFERTYPE_2>& arrayIn);

    ///in a sense we are inheriting the constructor from the base class.  the mdarray itself is just an interface and stores no data.  we pass
    ///whatever args are needed by the buffer to actually initialize it so that
    template <typename... Args>
    MultidimensionalArray(const Args&... cargs);

    template <typename... Args>
    MultidimensionalArray(Args&... cargs);

    ///note that this necessitates a default ctor for the buffer type in order to be used.
    MultidimensionalArray(){}

    template <class DATATYPE_2, class BUFFERTYPE_2>
    MultidimensionalArray(const MultidimensionalArray<DATATYPE_2,DIMENSIONS,BUFFERTYPE_2>& arr);

    ///number of elements of type DATATYPE in the array
    std::size_t numElements()const;

    const index_type& getDimensions()const;

    std::size_t axisLength(const std::size_t axis)const;

    /****************other methods**************************************/

    void negate(); ///componentwise in place negative applied to all elements.  For copy inverse, use unary negative operator

    void bitwiseNegation(); ///in place bitwise inverse of each element.  For copy negation, use operator ~

    MultidimensionalArray<DATATYPE,DIMENSIONS> copySubregion(const index_type& location, const index_type& regionSize)const;

    MultidimensionalArray<DATATYPE,DIMENSIONS> copySubregionFromTo(const index_type& startLocation, const index_type& endLocation)const;

    slice_type getSlice(const index_type& loc,const index_type& dims);


    /***********arithmetic operators*********************************/

    ///bitwise inverse of each element in the array
    MultidimensionalArray<DATATYPE,DIMENSIONS> operator~()const;

    /*****scalar comparison operators.  compare each element to the input element scalar****/

    MultidimensionalArray<bool,DIMENSIONS> operator< (const DATATYPE& comparator)const;

    MultidimensionalArray<bool,DIMENSIONS> operator== (const DATATYPE& comparator)const;

    MultidimensionalArray<bool,DIMENSIONS> operator> (const DATATYPE& comparator)const;

    MultidimensionalArray<bool,DIMENSIONS> operator<= (const DATATYPE& comparator)const;

    MultidimensionalArray<bool,DIMENSIONS> operator>= (const DATATYPE& comparator)const;


    /***** array comparison operators.   compare corresponding elements in the two arrays****/

    template <class BUFFERTYPE_2>
    MultidimensionalArray<bool,DIMENSIONS> operator< (const  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& comparator)const;

    template <class BUFFERTYPE_2>
    MultidimensionalArray<bool,DIMENSIONS> operator> (const  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& comparator)const;

    template <class BUFFERTYPE_2>
    MultidimensionalArray<bool,DIMENSIONS> operator<= (const  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& comparator)const;

    template <class BUFFERTYPE_2>
    MultidimensionalArray<bool,DIMENSIONS> operator>= (const  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& comparator)const;

    MultidimensionalArray<DATATYPE,DIMENSIONS>  operator-()const;

    /**** arithmetic operators****/

    template <class BUFFERTYPE_2>
    void operator+=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in);

    template <class BUFFERTYPE_2>
    void operator*=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in);

    template <class BUFFERTYPE_2>
    void operator-=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in);

    template <class BUFFERTYPE_2>
    void operator/=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in);

    template <class BUFFERTYPE_2>
    void operator%=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in);


    template <class SCALAR>
    void operator-=(const SCALAR& in);

    template <class SCALAR>
    void operator*=(const SCALAR& in);

    template <class SCALAR>
    void operator+=(const SCALAR& in);

    template <class SCALAR>
    void operator/=(const SCALAR& in);

    template <class SCALAR>
    void operator%=(const SCALAR& in);

    MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& operator++();///prefix
    MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& operator--();///prefix
    MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& operator++(int); ///postfix
    MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& operator--(int);///postfix

    template <class BUFFERTYPE_2>
    bool operator==(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in)const;

    template <class BUFFERTYPE_2>
    MultidimensionalArray<bool,DIMENSIONS> compareElements(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in)const;

    template <class BUFFERTYPE_2>
    bool operator!=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in)const;

    void abs();///in place absolute value of each elemnent
    void floor(); ///in place floor of each element
    void ceil(); ///in place ceil of each element

    ///clamp all values to the range (min_val,max_val)
    void clamp(const DATATYPE& min_val, const DATATYPE& max_val);

};


template <std::size_t DIMENSIONS, class BUFFERTYPE>
bool  any(const MultidimensionalArray<bool, DIMENSIONS,BUFFERTYPE>& arr);

template <std::size_t DIMENSIONS,class BUFFERTYPE>
bool  all(const MultidimensionalArray<bool, DIMENSIONS,BUFFERTYPE>& arr);

template <std::size_t DIMENSIONS,class BUFFERTYPE>
bool  none(const MultidimensionalArray<bool, DIMENSIONS,BUFFERTYPE>& arr);

template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator+(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r);

template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator*(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r);

template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator-(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r);

template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator/(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r);

template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator%(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r);

template <class DATATYPE, std::size_t DIMENSIONS, class SCALAR,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator-(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar);

template <class DATATYPE, std::size_t DIMENSIONS, class SCALAR,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator*(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar);

///multiplication is communtative, so we can do scalar*image
template <class DATATYPE, std::size_t DIMENSIONS, class SCALAR,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator*( const SCALAR& scalar,const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& r);

template <class DATATYPE, std::size_t DIMENSIONS, class SCALAR,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator+(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar);

template <class DATATYPE, std::size_t DIMENSIONS, class SCALAR,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator/(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar);

template <class DATATYPE, std::size_t DIMENSIONS, class SCALAR,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator%(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar);


#include "SubregionHelper.tcc" ///template helper class to generate nested for loops that do the heavy lifting of the copysubregion method


/*********************Helper methods*******************************/



///reinterpret as an image of smaller dimensionality.  Pop dimensions from the left.
///Eg, 4* 128 * 1 => 512*1
template <class DATATYPE, std::size_t DIMS1, std::size_t DIMS_TO_DROP,class BUFFERTYPE>
MultidimensionalArray<DATATYPE, DIMS1 - DIMS_TO_DROP,BUFFERTYPE> collapseDimensionsLeft(const MultidimensionalArray<DATATYPE, DIMS1,BUFFERTYPE>& imgIn);

///reinterpret as an image of smaller dimensionality. Pop dimensions from the right
///Eg, 4*128*
template <class DATATYPE, std::size_t DIMS1, std::size_t DIMS_TO_DROP,class BUFFERTYPE>
MultidimensionalArray<DATATYPE, DIMS1 - DIMS_TO_DROP,  BUFFERTYPE> collapseDimensionsRight(const MultidimensionalArray<DATATYPE, DIMS1>& imgIn);


template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> abs(const MultidimensionalArray<DATATYPE,DIMENSIONS, BUFFERTYPE>& arr);


template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> floor(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& arr);


template<class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> ceil(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& arr);

template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE>
std::pair<DATATYPE,DATATYPE> minMax(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& arr);


template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
DATATYPE mean(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& img);

///print function that goes element by element
template <std::size_t DIMENSIONS>
std::ostream& operator<<(std::ostream& str, const std::array<std::size_t, DIMENSIONS>& arr);

#include "SliceBuffer.h"

#include "MultidimensionalArray.tcc"


#endif // MULTIDIMENSIONAL_ARRAY_H_INCLUDED
