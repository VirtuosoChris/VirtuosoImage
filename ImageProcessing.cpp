#ifdef IMAGE_PROCESSING

#include "ImageProcessing.h"
#include <limits>
#include <cmath>
#include <stdexcept>



///\todo multichannel thresh.  eg, a vec4
/*void thresholdImage(FloatImage& imageIn, float thresh){

    for(int i = 0; i < imageIn.channels * imageIn.width * imageIn.height; i++){

        imageIn.pixels[i] = imageIn.pixels[i] < thresh ? 0.0f : 1.0f;

    }
}
*/










Image thresholdImage(const FloatImage& imageIn, float thresh)
{

    const ImageFormat& form = imageIn;

    Image returnVal(form);

    for(int i = 0; i < imageIn.channels * imageIn.width * imageIn.height; i++)
    {
        returnVal.pixels[i] = imageIn.pixels[i] > thresh ?  255:0;
    }

    return returnVal;
}







///\todo this is operating under a single channel assumption.  fix this
FloatImage nonMaximumSuppressionBlock(const FloatImage& imageIn, int windowRegion)
{


    const ImageFormat& imageInF = imageIn;

    FloatImage returnValue(imageInF);

    int winStart = -(windowRegion>>1);
    int winEnd = winStart + windowRegion;

    for(int y = 0; y < imageIn.height; y++)
    {
        for(int x = 0; x < imageIn.width; x++)
        {
            //negative infinity to start.
            float maxVal  = -std::numeric_limits<float>::max();

            for(int winY = winStart + y; winY < winEnd + y; winY++)
            {
                for(int winX = winStart + x; winX < winEnd + x; winX++)
                {

                    maxVal = std::max<float>(maxVal,*(imageIn(winX,winY)));

                }
            }



            if(*(imageIn(x,y))!= maxVal)
            {

                (*(returnValue(x,y))) = 0.0f;

            }
            else
            {

                (*(returnValue(x,y))) = *imageIn(x,y);

            }

        }
    }

    return returnValue;
}









#endif
