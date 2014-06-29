#ifndef CONVOLUTION_H_INCLUDED
#define CONVOLUTION_H_INCLUDED


#include <cmath>


#ifdef TEMP_BUFFER

///\todo generic version.  right now assuming a 3d array (2d image)  for convolution.
template <class KernelIt,class DATATYPE, class BUFFERTYPE_IN>
MultidimensionalArray<DATATYPE,3> conv1DY(const MultidimensionalArray<DATATYPE,3,BUFFERTYPE_IN>& img, KernelIt beginKernel, KernelIt endKernel)
{

	///\todo document this
    MultidimensionalArray<DATATYPE,3> returnVal(img.getDimensions() );

    for(int y = 0; y < img.getDimensions()[2]; y++)
    {
        for(int x = 0; x < img.getDimensions()[1]; x++)
        {
            int offset = -((endKernel - beginKernel)/2);

                ///\todo block this off for compatibility
                //double* aggregatePixel = static_cast<double*>( alloca(sizeof(double)*img.getDimensions()[0]) );  //{0.0f,0.0f,0.0f,0.0f};

                std::vector<double> aggregatePixel(img.getDimensions()[0],0);
                //for(int ch = 0; ch < img.getDimensions()[0]; ch++)
                //{
                  //  aggregatePixel[ch] =  0;
                //}

            //sum over a horizontal region
            for(KernelIt it = beginKernel; it != endKernel; it++, offset++)
            {

                int coord= std::max<int>(std::min<int>(offset+y,img.getDimensions()[2]-1),0);

                const DATATYPE* pixel = &img( 0, x, coord);


                for(int ch = 0; ch < img.getDimensions()[0]; ch++)
                {

                    aggregatePixel[ch] +=  (pixel[ch]) * (*it);

                }

            }

            //now that we have summed over a region for this pixel, we'll write
            //the aggregate value out to the output image
            DATATYPE* outputPixel = &returnVal(0,x,y);

            for(int ch = 0; ch < img.getDimensions()[0]; ch++)
            {


                outputPixel[ch] =  aggregatePixel[ch] ;
            }


        }
    }

    return returnVal;

}








///\todo document the assumption that each pixels elements are contiguous in memory

template <class KernelIt,class DATATYPE, class BUFFERTYPE_IN>
MultidimensionalArray<DATATYPE,3> conv1DX(const MultidimensionalArray<DATATYPE,3,BUFFERTYPE_IN>& img, KernelIt beginKernel, KernelIt endKernel)
{
    MultidimensionalArray<DATATYPE,3> returnVal(img.getDimensions());

    //std::cerr<<"DIMS "<<returnVal.getDimensions()<<std::endl;



    for(int y = 0; y < img.getDimensions()[2]; y++)
    {
        for(int x = 0; x < img.getDimensions()[1]; x++)
        {
            int offset = -((endKernel - beginKernel)/2);

            //double* aggregatePixel =  static_cast<double*>(
		//		alloca(sizeof(double)  * img.getDimensions()[0])
		//	);

            std::vector<double> aggregatePixel(img.getDimensions()[0],0);

			//for(int ch = 0; ch < img.getDimensions()[0]; ch++)
            //{aggregatePixel[ch]=0;	}

            //sum over a horizontal region
            for(KernelIt it = beginKernel; it != endKernel; it++, offset++)
            {
                ///\todo inside inner loop?
                int coord= std::max<int>(std::min<int>(offset+x,img.getDimensions()[1]-1),0);


               // std::cerr<<"Taking addr of val "<<coord<<" "<<y<<std::endl;

                const DATATYPE* pixel = &img(0,coord, y);

                for(int ch = 0; ch < img.getDimensions()[0]; ch++)
                {
					///\todo cast necessary?
                    aggregatePixel[ch] +=  (pixel[ch]) * (*it);

                }

            }

           // std::cerr<<"Taking addr of rval"<<std::endl;
            //now that we have summed over a region for this pixel, we'll write
            //the aggregate value out to the output image
            DATATYPE* outputPixel = &returnVal(0,x,y);

            for(int ch = 0; ch < img.getDimensions()[0]; ch++)
            {
               outputPixel[ch] = (aggregatePixel[ch]);
            }


        }
    }
    return returnVal;
}







#else





    ///\todo generic version.  right now assuming a 3d array (2d image)  for convolution.
template <class KernelIt,class DATATYPE, class BUFFERTYPE_IN>
MultidimensionalArray<DATATYPE,3> conv1DY(const MultidimensionalArray<DATATYPE,3,BUFFERTYPE_IN>& img, KernelIt beginKernel, KernelIt endKernel)
{

	///\todo document this
    MultidimensionalArray<DATATYPE,3> returnVal(img.getDimensions() );

    for(int y = 0; y < img.getDimensions()[2]; y++)
    {
        for(int x = 0; x < img.getDimensions()[1]; x++)
        {
            int offset = -((endKernel - beginKernel)/2);

                ///\todo block this off for compatibility
                //double* aggregatePixel = static_cast<double*>( alloca(sizeof(double)*img.getDimensions()[0]) );  //{0.0f,0.0f,0.0f,0.0f};

                std::vector<double> aggregatePixel(img.getDimensions()[0],0);
                //for(int ch = 0; ch < img.getDimensions()[0]; ch++)
                //{
                  //  aggregatePixel[ch] =  0;
                //}

            DATATYPE* outputPixel = &returnVal(0,x,y);



            //sum over a horizontal region

            KernelIt it = beginKernel;

            if(it != endKernel){

                int coord= std::max<int>(std::min<int>(offset+y,img.getDimensions()[2]-1),0);

                const DATATYPE* pixel = &img( 0, x, coord);


                for(int ch = 0; ch < img.getDimensions()[0]; ch++)
                {

                    outputPixel[ch] =  (pixel[ch]) * (*it);

                }

                it++;
                offset++;
            }


            for(; it != endKernel; it++, offset++)
            {

                int coord= std::max<int>(std::min<int>(offset+y,img.getDimensions()[2]-1),0);

                const DATATYPE* pixel = &img( 0, x, coord);


                for(int ch = 0; ch < img.getDimensions()[0]; ch++)
                {

                    outputPixel[ch] +=  (pixel[ch]) * (*it);

                }

            }


        }
    }

    return returnVal;

}








///\todo document the assumption that each pixels elements are contiguous in memory
///\todo conv functions that take a return argument.  set a channel to a blurred grayscale
template <class KernelIt,class DATATYPE, class BUFFERTYPE_IN>
MultidimensionalArray<DATATYPE,3> conv1DX(const MultidimensionalArray<DATATYPE,3,BUFFERTYPE_IN>& img, KernelIt beginKernel, KernelIt endKernel)
{
    MultidimensionalArray<DATATYPE,3> returnVal(img.getDimensions());

    //std::cerr<<"DIMS "<<returnVal.getDimensions()<<std::endl;



    for(int y = 0; y < img.getDimensions()[2]; y++)
    {
        for(int x = 0; x < img.getDimensions()[1]; x++)
        {
            int offset = -((endKernel - beginKernel)/2);


            DATATYPE* outputPixel = &returnVal(0,x,y);

            KernelIt it = beginKernel;

            if(it != endKernel){

                 int coord= std::max<int>(std::min<int>(offset+x,img.getDimensions()[1]-1),0);

               // std::cerr<<"Taking addr of val "<<coord<<" "<<y<<std::endl;

                const DATATYPE* pixel = &img(0,coord, y);


                for(int ch = 0; ch < img.getDimensions()[0]; ch++)
                {

                    outputPixel[ch] =  (pixel[ch]) * (*it);

                }

                it++;
                offset++;
            }

            //sum over a horizontal region
            for( ; it != endKernel; it++, offset++)
            {
                ///\todo inside inner loop?
                int coord= std::max<int>(std::min<int>(offset+x,img.getDimensions()[1]-1),0);




               // std::cerr<<"Taking addr of val "<<coord<<" "<<y<<std::endl;

                const DATATYPE* pixel = &img(0,coord, y);

                for(int ch = 0; ch < img.getDimensions()[0]; ch++)
                {
					///\todo cast necessary?
                    outputPixel[ch] +=  (pixel[ch]) * (*it);

                }

            }

        }
    }
    return returnVal;
}










#endif






template <class DATATYPE,std::size_t DIMENSIONS, class BUFFERTYPE_IN>
MultidimensionalArray<DATATYPE,DIMENSIONS> averagingBlur(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_IN>& imageIn, unsigned int radius)
{
    double invrad = 1.0 / radius;

    std::vector<double> kernel(radius, invrad);

    return conv1DY(
               conv1DX(imageIn, kernel.begin(),kernel.end()),
               kernel.begin(),kernel.end()
           );
}



#endif // CONVOLUTION_H_INCLUDED
