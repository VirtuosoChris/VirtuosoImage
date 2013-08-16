//implementation file of index linearization functions

template<std::size_t DIMS>
std::size_t linearizeMultidimensionalIndex(const std::array<std::size_t,DIMS>& index,
                                           const std::array<std::size_t,DIMS>& dimensions){

std::size_t rval = 0;
std::size_t accumulator = 1;

    for(std::size_t it = 0; it < DIMS; it++){

        rval += index[it] * accumulator;

        accumulator *= dimensions[it];

    }

return rval;

}




template<std::size_t DIMS, typename... Args>
inline std::size_t linearizeMultidimensionalIndex(const std::array<std::size_t,DIMS>& dimensions,const Args&... cargs)
{
	return linearizeMultidimensionalIndex( std::array<std::size_t, DIMS>{{static_cast<std::size_t>(cargs)...}},dimensions);
}





template <std::size_t DIMS>
inline std::array<std::size_t, DIMS> unlinearizeMultidimensionalIndex(std::size_t index, const std::array<std::size_t, DIMS>& dimensions )
{

std::array<std::size_t, DIMS> rval;

    unlinearizeMultidimensionalIndex(rval, index, dimensions);

return rval;


}



template <std::size_t DIMS>
void unlinearizeMultidimensionalIndex(std::array<std::size_t, DIMS>& returnIndex, std::size_t index, const std::array<std::size_t, DIMS>& dimensions )
{

 std::size_t accumulator=1;

 for(std::size_t it = 0; it < DIMS; it++){

    returnIndex[it] = (index / accumulator) % dimensions[it];

    accumulator *= dimensions[it];

 }


}
