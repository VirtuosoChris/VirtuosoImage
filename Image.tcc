#ifndef IMAGE_TCC_INCLUDED
#define IMAGE_TCC_INCLUDED

#include <cmath>


///\todo array version, image version, returnvalue version
template <class DATATYPE, std::size_t DIMENSIONS, class COORDTYPE>
void clampPixelCoordinates(const Image<DATATYPE, DIMENSIONS>& arr,
                           std::array<COORDTYPE, DIMENSIONS>& coords)
{

    for(std::size_t i = 0; i < DIMENSIONS; i++)
    {
        coords[i] = std::max<COORDTYPE>(0, coords[i]);
        coords[i] = std::min<COORDTYPE>(arr.getDimensions()[i+1]-1, coords[i]);
    }

}



///\todo this should just be generic scale.
template <class DATATYPE, std::size_t DIMENSIONS>
Image<DATATYPE,DIMENSIONS> upsample(const Image<DATATYPE,DIMENSIONS>& img, const std::size_t& scale)
{

    std::cerr<<"\nold DImensions are ";
    for(std::size_t i= 0 ; i < DIMENSIONS+1u; i++)
    {

        std::cerr<< img.getDimensions()[i]<<',';
    }
    std::cerr<<std::endl;

    if(!scale)
    {
        throw std::runtime_error("Scale for upsample image is 0");
    }
    if(!img)
    {
        throw std::runtime_error("Trying to upsample null image");
    }

///\todo operator for this
    typename Image<DATATYPE,DIMENSIONS>::index_type newDims;

    newDims[0] = img.getDimensions()[0]; //keep channels the same

    for(std::size_t i = 1u; i < DIMENSIONS+1u; i++)
    {
        ///start at 1 since we are dealing with images
        newDims[i] = img.getDimensions()[i] * scale;
    }

    Image<DATATYPE, DIMENSIONS> rval(newDims);

    std::cerr<<"DImensions are ";
    for(std::size_t i= 0u ; i < DIMENSIONS+1u; i++)
    {

        std::cerr<< rval.getDimensions()[i]<<',';
    }

    double invscale = 1.0 / scale;

    std::size_t totalElements = rval.numElements();///pixels to iterate over

    std::cerr<<"\nelements: "<<totalElements<<std::endl;

///increment by pixel size
    for(std::size_t i = 0; i < totalElements; i += rval.getDimensions()[0] )
    {

        auto coordsi = unlinearizeMultidimensionalIndex(i,rval.getDimensions());

        // std::cerr<<"integer coords for "<<i<<std::endl;
        //for(std::size_t d = 0; d < DIMENSIONS+1; d++){
        //   std::cerr<<coordsi[d]<<std::endl;
        //}std::cerr<<"\n\n"<<std::endl;


        std::array<double, DIMENSIONS> coordsf;

        for(std::size_t d = 0; d < DIMENSIONS; d++)
        {

            coordsf[d] = coordsi[d+1] * invscale;

        }

        clampPixelCoordinates(img,coordsf);

        filteredLookup(img, coordsf,&rval[i]);
    }

///\todo some operator for this divide

///stuff goes here.


    return rval;///todo check if this copies

}





template<class DATATYPE>
void flipVertical(Image2D<DATATYPE>& img){


    std::size_t rowsize = img.getDimensions()[0] * img.getDimensions()[1];


    DATATYPE* first1 = img.dataPtr();
    DATATYPE* last1 = img.dataPtr() + rowsize;
    DATATYPE* first2 = (img.dataPtr() + (rowsize * img.getDimensions()[2]) )  - rowsize;

    while(first1 < first2){

        std::swap_ranges(first1, last1, first2);

        first1 += rowsize;
        first2 -= rowsize;
        last1 += rowsize;
    }

}





template<class DATATYPE>
void flipHorizontal(Image2D<DATATYPE>& img){

    const std::size_t& channels     =     img.getDimensions()[0];
    const std::size_t& elements_row =     img.getDimensions()[1];
    const std::size_t& rows         =     img.getDimensions()[2];

    const std::size_t rowlength= elements_row * channels;

    //what we need to do is look at each row in isolation and swap the first and last elements

    DATATYPE* rowbegin = img.dataPtr();

    for(std::size_t r = 0; r < rows; r++){

        DATATYPE* pix = rowbegin;
        DATATYPE* pix2 = pix + (elements_row - 1) * channels;

        while(pix < pix2){
            std::swap_ranges(pix, pix+channels, pix2);

            pix+= channels;
            pix2-=channels;
        }

        rowbegin+= rowlength;
    }

}




template <class DATATYPE>
inline void interpolatePixel( DATATYPE* rval, const DATATYPE* left, const DATATYPE* right, const std::size_t& channels, const double& interpolationValue ){

    const double oneminus = 1.0 - interpolationValue;
    for(std::size_t i = 0; i < channels; i++){

            rval[i] = (oneminus * left[i] ) + (interpolationValue * right[i]);

    }

}


#include "InterpolationHelper.tcc" ///helper TM class that generates the image lookups and interpolation weights


template <class DATATYPE, int DIMENSIONS>
inline std::vector<DATATYPE> filteredLookup(const Image<DATATYPE,DIMENSIONS>& img, const std::array<DATATYPE,DIMENSIONS>& coords)
{
    std::vector<DATATYPE> vals(img.getDimensions()[0]);
    filteredLookup(img, coords, &vals[0]);
    return vals;
}



template<class DATATYPE, std::size_t DIMENSIONS>
void filteredLookup(const Image<DATATYPE, DIMENSIONS>& img, const std::array<double, DIMENSIONS>& coords, DATATYPE* returnVal)
{

    std::array<std::size_t, DIMENSIONS> floors;

    std::array<std::size_t, DIMENSIONS> ceils;

    std::array<double, DIMENSIONS> fracts;

    const std::size_t& imgChannels = img.getDimensions()[0];

   /* std::cerr<<"Incoming coordinates "<<std::endl;
    for(int i = 0 ; i < DIMENSIONS; i++){
        std::cerr<<coords[i]<<", ";
    }

    std::cerr<<std::endl;
*/

    for(std::size_t i = 0; i < DIMENSIONS; i++){
        double tmp;///\todo is modf the best?
        fracts[i] =  modf(coords[i],&tmp);
        ceils[i] = std::ceil(coords[i]);
        floors[i] = coords[i];
    }


//    const size_t pixelSize = imgChannels*sizeof(DATATYPE);

    ///\todo explain
    ///minus one because the indexing for a 2d tex coord is 0,1
    INTERPOLATOR<DATATYPE,DIMENSIONS,DIMENSIONS-1,0>::interpolate(
                                                            returnVal,
                                                            floors,
                                                            ceils,
                                                            fracts,
                                                            imgChannels,
                                                            img
                                                            );


}




template<class DATATYPE, std::size_t DIMENSIONS>
void filteredLookupNorm(const Image<DATATYPE, DIMENSIONS>& img, const std::array<double, DIMENSIONS>& coords, DATATYPE* returnVal)
{

    std::array<double, DIMENSIONS> coords2;

    for(std::size_t i = 0; i < DIMENSIONS; i++){
        coords2[i] =coords[i] * img.getDimensions()[i+1]; //scale
    }

    filteredLookup(img,coords,returnVal);

}




template <class DATATYPE, int DIMENSIONS>
inline std::vector<DATATYPE> filteredLookupNorm(const Image<DATATYPE,DIMENSIONS>& img, const std::array<DATATYPE,DIMENSIONS>& coords)
{
    std::vector<DATATYPE> arr(img.getDimensions()[0]);

    filteredLookupNorm(img,coords,&arr[0]);

    return arr;

}




#endif // IMAGE_TCC_INCLUDED

