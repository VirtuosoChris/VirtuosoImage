#include <stdlib.h>

#define COPY_OPTIMIZATION


template<class DATATYPE,std::size_t DIMENSIONS, std::size_t FIX_DIM, std::size_t FLAGS,class BUFFERTYPE = ArrayBuffer<DATATYPE,DIMENSIONS+1> >
struct INTERPOLATOR{

    #ifndef COPY_OPTIMIZATION
    inline static void interpolate(

            DATATYPE* rval,

            const std::array<std::size_t, DIMENSIONS>& floors,

            const std::array<std::size_t, DIMENSIONS>& ceils,

            const std::array<double, DIMENSIONS>& fracts,

            const std::size_t& channels,

            const Image<DATATYPE, DIMENSIONS>& img

    ){


        #ifndef VIRTUOSO_FULLY_PORTABLE_IMG_LIB
        const size_t pixelSize = channels*sizeof(DATATYPE);

        DATATYPE* left  = static_cast<DATATYPE*>(alloca(pixelSize));
        DATATYPE* right = static_cast<DATATYPE*>(alloca(pixelSize));

        #else
            std::vector<DATATYPE> leftV(channels);
            std::vector<DATATYPE> rightV(channels);

            DATATYPE*  left = &leftV[0];
            DATATYPE*  right = &rightV[0];

        #endif



        INTERPOLATOR<DATATYPE,DIMENSIONS,FIX_DIM-1, FLAGS >::interpolate(

                                                                  left,
                                                                  floors,
                                                                  ceils,
                                                                  fracts,
                                                                  channels,
                                                                  img
                                                                  );


        INTERPOLATOR<DATATYPE,DIMENSIONS,FIX_DIM-1,(FLAGS | (1u<<FIX_DIM)) >::interpolate(right,
                                                                  floors,
                                                                  ceils,
                                                                  fracts,
                                                                  channels,
                                                                  img
                                                                  );


        interpolatePixel( rval, left, right, channels, fracts[FIX_DIM]);

    }
    #else
     inline static void interpolate(

            DATATYPE* rval,

            const std::array<std::size_t, DIMENSIONS>& floors,

            const std::array<std::size_t, DIMENSIONS>& ceils,

            const std::array<double, DIMENSIONS>& fracts,

            const std::size_t& channels,

            const Image<DATATYPE, DIMENSIONS,BUFFERTYPE>& img

    ){

    if(fracts[FIX_DIM]){

        #ifndef VIRTUOSO_FULLY_PORTABLE_IMG_LIB
        const size_t pixelSize = channels*sizeof(DATATYPE);

        DATATYPE* left  = static_cast<DATATYPE*>(alloca(pixelSize));
        DATATYPE* right = static_cast<DATATYPE*>(alloca(pixelSize));

        #else
            std::vector<DATATYPE> leftV(channels);
            std::vector<DATATYPE> rightV(channels);

            DATATYPE*  left = &leftV[0];
            DATATYPE*  right = &rightV[0];

        #endif



        INTERPOLATOR<DATATYPE,DIMENSIONS,FIX_DIM-1, FLAGS,BUFFERTYPE >::interpolate(

                                                                  left,
                                                                  floors,
                                                                  ceils,
                                                                  fracts,
                                                                  channels,
                                                                  img
                                                                  );


        INTERPOLATOR<DATATYPE,DIMENSIONS,FIX_DIM-1,(FLAGS | (1u<<FIX_DIM)), BUFFERTYPE >::interpolate(right,
                                                                  floors,
                                                                  ceils,
                                                                  fracts,
                                                                  channels,
                                                                  img
                                                                  );


        interpolatePixel( rval, left, right, channels, fracts[FIX_DIM]);

    }else{ //we just want to copy instead

             INTERPOLATOR<DATATYPE,DIMENSIONS,FIX_DIM-1, FLAGS, BUFFERTYPE >::interpolate(

                                                                  rval,
                                                                  floors,
                                                                  ceils,
                                                                  fracts,
                                                                  channels,
                                                                  img
                                                                  );

        }

    }
    #endif


};


///ASSUMES DIMENSIONS AS IMAGE DIMENSIONS
///base case: we locked in coordinates for the higher dimensions.  but this is an image, so the "0th" dimension is the actual pixels themselves.
///These require no interpolation so we just return
///NOTE: this does not assume that all memory is contiguous, but it does take the address of individual pixels for interpolation.
///That is, a slice will work for instance, but the 0th dimension given in the coordinates must have contiguous memory for some fixed combination of other elements.
///for example.  2d image with rgba.  given as a 3d array with coordinates channel,x,y.  0,x,y 1,x,y, 2,x,y must be contiguous for some x,y
///actually, pixel iterator should fix that.
template<class DATATYPE,std::size_t DIMENSIONS,std::size_t FLAGS, class BUFFERTYPE>
struct INTERPOLATOR<DATATYPE,DIMENSIONS,0, FLAGS,BUFFERTYPE>{

#ifndef COPY_OPTIMIZATION
inline static void  interpolate(

            DATATYPE* rval,

            const std::array<std::size_t, DIMENSIONS>& floors,

            const std::array<std::size_t, DIMENSIONS>& ceils,

            const std::array<double, DIMENSIONS>& fracts,

            const std::size_t& channels,

            const Image<DATATYPE, DIMENSIONS>& img
        )
{


        std::array<std::size_t,DIMENSIONS+1> leftCoords;

        std::array<std::size_t,DIMENSIONS+1> rightCoords;

        leftCoords[0] = rightCoords[0]=0;
        leftCoords[1] = floors[0];
        rightCoords[1] = ceils[0];

        ///\todo unroll?
        for(std::size_t d = 1; d < DIMENSIONS; d++){

            bool isCeil = (FLAGS & (1u<<d) );



            rightCoords[d+1] = leftCoords[d+1] = isCeil ? ceils[d] : floors[d];

        }


       interpolatePixel( rval, &(img(leftCoords)), &(img(rightCoords)), channels, fracts[0]);


}

#else
inline static void  interpolate(

            DATATYPE* rval,

            const std::array<std::size_t, DIMENSIONS>& floors,

            const std::array<std::size_t, DIMENSIONS>& ceils,

            const std::array<double, DIMENSIONS>& fracts,

            const std::size_t& channels,

            const Image<DATATYPE, DIMENSIONS, BUFFERTYPE>& img
        )
{


if(fracts[0]){
        std::array<std::size_t,DIMENSIONS+1> leftCoords;

        std::array<std::size_t,DIMENSIONS+1> rightCoords;

        leftCoords[0] = rightCoords[0]=0;
        leftCoords[1] = floors[0];
        rightCoords[1] = ceils[0];

        for(std::size_t d = 1; d < DIMENSIONS; d++){

            bool isCeil = (FLAGS & (1u<<d) );

            rightCoords[d+1] = leftCoords[d+1] = isCeil ? ceils[d] : floors[d];

        }


       interpolatePixel( rval, &(img(leftCoords)), &(img(rightCoords)), channels, fracts[0]);

}else{

       std::array<std::size_t,DIMENSIONS+1> coords;

        coords[0]=0;
        coords[1] = floors[0];

        for(std::size_t d = 1; d < DIMENSIONS; d++){

            bool isCeil = (FLAGS & (1u<<d) );

            coords[d+1] = isCeil ? ceils[d] : floors[d];

        }


     const DATATYPE* ptr = &(img(coords));

    for(std::size_t i = 0; i< img.getDimensions()[0]; i++){

        rval[i] = ptr[i];

    }


}


}

#endif
};
