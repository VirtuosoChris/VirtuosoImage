#include <vector>
#include <sstream>
#include <iostream>
#include "ImageProcessing.h"
#include <stdexcept>

#include <Eigen/LU>

#include "Image.h"
#include "ImageProcessing.h"
#include "Gaussian.h"

#include "Gradient.h"

#include "Histogram.h"


void equalizationTest(){

    LDRImage test2 = loadImage("equalizationInput.jpg");

    ///\todo single brace breaks
    LDRImage test = test2.copySubregion({{0,0,0}}, {{1,test2.getDimensions()[1],test2.getDimensions()[2]}});
    std::cerr<<"CHannels "<<test.getDimensions()[0]<<std::endl;

    equalizeImage(test,0u,255u,256u);

    auto mm = minMax(test);

    std::cerr<<"Min Max "<<(int)mm.first<<" "<<(int)mm.second<<std::endl;

    writeImage(test,"equalizedImage.png");

}



void testConvolution()
{

        std::cerr<<"Testing gaussian blur\n";

        std::cerr<<"Kernel size will be "<<idealGaussianKernelSize(5.0)<<std::endl;
        LDRImage img1 = loadImage(//"img.bmp");
            "balloon.png");



      //  const unsigned char* pixel = &img1(0,386, 102);

        LDRImage img2 =
            gaussianBlur2D(img1,5.0);
        //averagingBlur(img1,10);




        if(!writeImage(img2,"balloon5stdev.png"))
        {
            throw std::runtime_error("Unable to write image");
        }



}






void testGradients()
{
    std::cerr<<"Testing gradient images"<<std::endl;

    Image<int,2>

    //HDRImage
    i1 = loadImage("grayballoon.png");

    //HDRImage //<int,2>
    Image<int,2>

    dfdx =
    //i1
     computeHorizontalGradient(i1)

    ;


    dfdx.abs();
   // dfdx.clamp(0,255);

    Image<int,2> dfdy = computeVerticalGradient(i1);

    dfdy.abs();

    LDRImage outX=(dfdx);
    LDRImage outY=(dfdy);

    writeImage(outX,"dfdx.png");
    writeImage(outY,"dfdy.png");

}

/*
void testFloatImages()
{

    std::cerr<<"Loading image, converting to float, convolving, and converting back"<<std::endl;
    Image i1("balloon2.jpg");

    FloatImage i2(i1);

    FloatImage blurred = gaussianBlur(i2, 5.0f);

    Image i3(blurred);

    i3.write("FloatTest.png");

}

*/




/*
template<class DATATYPE, std::size_t DIMENSIONS>
typename Image<DATATYPE,DIMENSIONS>::index_type operator*(const typename Image<DATATYPE,DIMENSIONS>::index_type& l,   const typename Image<DATATYPE,DIMENSIONS>::index_type& r ){

    typename Image<DATATYPE,DIMENSIONS>::index_type rval;

    for(std::size_t i = 0; i < DIMENSIONS; i++){

        rval[i] = l[i] * r[i];

    }

    return rval;

}*/


template<class T>
void doshit(std::vector<T>& vec){

for(T t = 0; t < 10; t++) {

vec.push_back(t);

}

}

template<std::size_t D, class C>
class FUCKME{

    C arr[D];

};

template<std::size_t S, class C>
void doshit2(const FUCKME<S,C>& f){

}




int main()
{

    std::vector<int> tmpv;
    doshit(tmpv);

    FUCKME<2,unsigned char> f;
    doshit2(f);


//  SLICE_TYPE<unsigned char, 2, ArrayBuffer<unsigned char, 2> >::print();
//  SLICE_TYPE < unsigned char, 2, SliceBuffer<unsigned char, 2, ArrayBuffer<unsigned char, 2> > >::print();

    //system("pause");


//    std::array<unsigned char, 3> arr = {{1,2,3}};

 //   std::array<unsigned char,4> arr2 = arr;


    try
    {
        const std::string& testImage("gc.jpg");
        const std::string& testImageOut("gc-out1.png");
        const std::string& testNegImageOut("gc-neg.png");
        const std::string& testHalfZeroOut("gc-half0.png");

        equalizationTest();

        {

            testConvolution();///\todo document the clamp in convolution
            testGradients();

            LDRImage balloon = loadImage("balloon.png");

            LDRImage desat = saturation (balloon,0.50);

            LDRImage sat = saturation(balloon,1.50);

            LDRImage::index_type loc = {{0,0,0}};

            LDRImage::index_type dims = {{3,25,25}};

            LDRImageSlice satSlice = sat.getSlice(loc,dims);

             LDRImageSlice slice2 = satSlice.getSlice(loc,dims);

            ///\todo assignment of slice to img and img to slice
            LDRImage slice3 = slice2.copy();

             writeImage(slice3,"slice-copy.png");


            MultidimensionalArray<int,3>
            //HDRImage
            fl(balloon);

            MultidimensionalArray<int,3>
            //HDRImage
            satf = saturation(fl,2.0);

            satf.clamp(0.0,255.0);



            LDRImage fu(satf);

            writeImage(fu,"tested-float-clamp.png");

            writeImage(desat,"desaturated.png");

            writeImage(sat,"saturated.png");
        }


        std::cerr<<"Loading image "<<testImage<<std::endl;

        LDRImage img1 = loadImage(testImage);

        std::cerr<<"About to upsample"<<std::endl;
        LDRImage upsampled = upsample<unsigned char, 2>(img1,2);

        writeImage(upsampled,"upsampled-gc.png");

        std::cerr<<"Flipping image vertical"<<std::endl;

        flipVertical(img1);

        std::cerr<<"Flipping image horizontal"<<std::endl;

        flipHorizontal(img1);

        std::cerr<<"Testing write-out to "<<testImageOut<<std::endl;

        if(!writeImage(img1,testImageOut))
        {
            throw std::runtime_error("Unable to write image out!");
        }
        else
        {
            std::cerr<<"Write successful\n\n";
        }


        LDRImage neg = ~img1;


        //tests the copy constructor.  since neg and halfzero are written after the copy, they should have visually distinct data if the copy ctor works
        LDRImage halfzero;
        halfzero= neg;


        for(std::size_t y = 0; y < halfzero.getDimensions()[2]; y++){
        for(std::size_t x = 0; x < halfzero.getDimensions()[1]; x++){

            double red = double(x) / halfzero.getDimensions()[1];
            double green= double(y) / halfzero.getDimensions()[2];

           // halfzero.ptr({{x,y}})[1]
            halfzero({{2,x,y}})
            = (size_t)(red * 255);
            //
            halfzero.ptr({{0,x,y}})[1]
            //*halfzero.ptr({{1,x,y}})
             = (size_t)(green * 255);

            halfzero({{0,x,y}})
            //*halfzero.ptr({{1,x,y}})
             = 0;
        }
        }

        std::cerr<<"Testing iteration semantics"<<std::endl;
        if(!writeImage(halfzero,testHalfZeroOut))
        {
            throw std::runtime_error("Unable to write image out!");
        }
        else
        {
            std::cerr<<"Write successful\n\n";
        }


        std::cerr<<"Testing image negative "<<std::endl;
        if(!writeImage(neg,testNegImageOut))
        {
            throw std::runtime_error("Unable to write image out!");
        }
        else
        {
            std::cerr<<"Write successful\n\n";
        }
        std::cerr<<"Now testing copy-on write semantics.  All three of the pointers below should be the same."<<std::endl;
        std::cerr<<"Before copy, img1's pointer value is "<< reinterpret_cast<std::size_t>(img1.dataPtr())<<std::endl;

        LDRImage img2 = img1;

        std::cerr<<"Copy's ptr is "<<    reinterpret_cast<std::size_t>(img2.dataPtr())<<std::endl;
        std::cerr<<"original's ptr is "<<    reinterpret_cast<std::size_t>(img1.dataPtr())<<std::endl;

        std::cerr<<"Accessing first element of img1."<<std::endl;


        std::cerr<<"First with the new shit"<<std::endl;


        unsigned char tempChar = img1( {{0,0,0}});


        std::cerr<<static_cast<std::size_t>(tempChar)<<std::endl;

        std::cerr<<"\nAfter access: pointers should be the same still"<<std::endl;
        std::cerr<<"Copy's ptr is "<<    reinterpret_cast<std::size_t>(img2.dataPtr())<<std::endl;
        std::cerr<<"original's ptr is "<<    reinterpret_cast<std::size_t>(img1.dataPtr())<<std::endl;


        img1( {{0,0,0}}) = 0;

        std::cerr<<"\nAfter a write: pointers should be different"<<std::endl;
        std::cerr<<"Copy's ptr is "<<    reinterpret_cast<std::size_t>(img2.dataPtr())<<std::endl;
        std::cerr<<"original's ptr is "<<    reinterpret_cast<std::size_t>(img1.dataPtr())<<std::endl;


        LDRImage::index_type beginR = {{0,img2.getDimensions()[1]/2,img2.getDimensions()[2]/2 }};

        LDRImage region = img2.copySubregionFromTo(beginR, img2.getDimensions());

        writeImage(region, "region.png");

        LDRImage graytest = loadImage("gc.jpg");

        LDRImage lum = toLuminance(graytest);
        LDRImage gray = grayscale (graytest);


        LDRImage papertest = loadImage("paper3.png");

        LDRImage lumP = toLuminance(papertest);

        writeImage(lumP, "paper.png");


        auto redOnly = resizeChannels<unsigned char,2>(gray,3);

        writeImage(redOnly,"redOnly.png");

        auto combined = halfzero + redOnly;

        writeImage(combined,"combined.png");

        auto backToGray = resizeChannels<unsigned char, 2>(combined,1);



        graytest = loadImage("balloon.png");
        lum = toLuminance(graytest);
        gray = grayscale (graytest);

        writeImage(backToGray,"backToGrayAgain.png");

        std::cerr<<"Writing grayscales"<<std::endl;
        writeImage(lum, "luminance.png");
        writeImage(gray, "avggrayscale.png");



        //testGrayscaleConversion();
        //testConvolution();
        //testJpeg();
        //testFloatImages();
        //testGradients();
        //testHarrisMask();

    }

    catch(const std::exception& ex)
    {

        std::cerr<<"Caught an exception"<<std::endl;
        std::cerr<<ex.what()<<std::endl;

    }

    return 0;

}

