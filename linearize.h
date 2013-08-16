#ifndef VIRTUOSO_IMAGE_LINEARIZE_H_INCLUDED
#define VIRTUOSO_IMAGE_LINEARIZE_H_INCLUDED

//functions to linearize and unlinearize multidimensional array indices.

///takes a multidimensional index and linearizes it.  Assumes standard array layout of contiguous rows.
///requires the index, and the max dimensions of each axis of the array
template<std::size_t DIMS>
std::size_t linearizeMultidimensionalIndex(
                                            const std::array<std::size_t,DIMS>& index,
                                            const std::array<std::size_t,DIMS>& dimensions);

template<std::size_t DIMS, typename... Args>
inline std::size_t linearizeMultidimensionalIndex(
                                                  const std::array<std::size_t,DIMS>& dimensions,
                                                  const Args&... cargs
                                                  );

///unlinearize a linear index for a multidimensional array.  This version creates and returns a value
template <std::size_t DIMS>
inline std::array<std::size_t, DIMS> unlinearizeMultidimensionalIndex(std::size_t index, const std::array<std::size_t, DIMS>& dimensions );

///unlinearize a linear index for a multidimensional array.  This version takes a reference to the return value
template < std::size_t DIMS>
void unlinearizeMultidimensionalIndex(std::array<std::size_t, DIMS>& returnIndex, std::size_t index, const std::array<std::size_t, DIMS>& dimensions );

#include "linearize.tcc"

#endif
