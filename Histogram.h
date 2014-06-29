///range, bins.

///\todo store bin increment or calc?
///\todo double typing for integers, later
#include <vector>
#include <stdexcept>
#include "MultidimensionalArray.h"
#include <cstdlib>

template <class DATATYPE>
class Histogram{

	DATATYPE minVal;
	DATATYPE maxVal;
	std::vector<double> count;

	public:

	const DATATYPE& minValue()const{return minVal;}
	const DATATYPE& maxValue()const{return maxVal;}
    std::size_t  numBins()const{return count.size();}


	Histogram(const DATATYPE& min,const DATATYPE& max, const std::size_t& bins):minVal(min),maxVal(max), count(bins,0){

		if(!numBins() ){
			throw std::runtime_error("Can't create a histogram with less than one bin");
		}

		if( (  maxValue() <minValue()) ){
			throw std::runtime_error("max value of histogram is smaller than the min value");
		}
	}

	///[] operator accesses a bin with a particular index and returns a reference
	const double& operator[](const std::size_t& index)const{
		return count[index];
	}

	double& operator[](const std::size_t& index){
		return count[index];
	}


    double binInterval()const{
        return  (maxValue() - minValue()) / double(numBins()-1);
    }


    ///value that starts a bin
    double binValue(const std::size_t& bin)const{
        return minValue() + (bin * binInterval());
    }


	std::size_t valueToBin(const DATATYPE& val)const{

		DATATYPE diff = val < minVal? 0: val-minVal;

        std::size_t bin = std::min<std::size_t>(diff / binInterval(), numBins()-1);

        return bin;

    }

	///parentheses operator converts the datatypy to a bin and returns a ref to the bin value
	const double& operator()(const DATATYPE& dat)const{
		return count[valueToBin(dat)];
	}

	double& operator()(const DATATYPE& dat){
		return count[valueToBin(dat)];
	}


	void normalize(){

        double sum = 0.0;

        for(std::size_t i = 0; i < numBins(); i++){

            sum += (*this)[i];

        }

        for(std::size_t i = 0; i < numBins(); i++){

            (*this)[i] /= sum;

        }
	}

};





template <class TYPE>
struct RoundIfIntegerType{

    static inline double round(const double& in){
       // std::cerr<<"ROUNDED"<<std::endl;
        return std::round (in);
    }
};


///for any floating point type we will just do our calcs in double but not round

template<>
struct RoundIfIntegerType<double>{

    static inline double round(const double& in){return in;}

};

template<>
struct RoundIfIntegerType<float>{

   static inline double round(const double& in){return in;}

};

template<>
struct RoundIfIntegerType<long double>{

   static inline double round(const double& in){return in;}

};



///inverse of a discrete cdf
///\todo non linear interp
///assumes that the last value of the cdf is 1.0, and that the normalized val is in the range 0 to 1
///\todo check corner cases
template <class DATATYPE>
DATATYPE inverseCDF(const Histogram<DATATYPE>& cdf, const double& normalizedVal){

    if( cdf.numBins()==1){
        return cdf.binValue(0);
    }

    std::size_t leftBin = 0;
    std::size_t rightBin = 1;

    double interpolatedVal;

    for(; rightBin < cdf.numBins();leftBin++,rightBin++){
        if(cdf[rightBin] >= normalizedVal){ //our target value is in between leftBin's value and rightBin's value
            break;
        }
    }

    //so now we will interpolate the output range based on the two bins that closest match our target value

    double valLeft = cdf.binValue(leftBin);
    double valRight = cdf.binValue(rightBin);

    //std::cerr<<"Binval of "<<i<<" is "<<valLeft<<std::endl;


    //std::cerr<<"interpolating "<<valLeft<<"  "<<valRight<<std::endl;

    double interpolant = std::max(0.0,(normalizedVal - cdf[leftBin]) / (cdf[rightBin] - cdf[leftBin]));
    interpolant = std::min(1.0,interpolant);

    interpolatedVal = ( (1.0 - interpolant) * valLeft ) + ( interpolant * valRight );

  //  if(interpolatedVal < 0){
      //  std::cerr<<"interpolant "<<interpolant<<std::endl;
     //   std::cerr<<"norm "<<normalizedVal<<'\n'<<cdf[leftBin]<<std::endl<<cdf[rightBin]<<std::endl;
     //   system("pause");
    //}

    //std::cerr<<"Returning interpolatedval "<<interpolatedVal<<std::endl;

    return RoundIfIntegerType<DATATYPE>::round(interpolatedVal);

}


/*template <class DATATYPE>///\todo this is completely wrong, just have this here as backup until the new one works
DATATYPE inverseCDF(const Histogram<DATATYPE>& cdf, const double& normalizedVal){
    std::size_t i = 0;

    double interpolatedVal;

    for(; i < cdf.numBins(); i++){
        if(cdf[i] >= normalizedVal){
            break;
        }
    }

    double valLeft = cdf.binValue(i);

    //std::cerr<<"Binval of "<<i<<" is "<<valLeft<<std::endl;

    if(i == cdf.numBins()-1){

        interpolatedVal = valLeft;

    }else{

        double valRight = cdf.binValue(i+1);

        std::cerr<<"interpolating "<<valLeft<<"  "<<valRight<<std::endl;

        double interpolant = (normalizedVal - valLeft) / (valRight - valLeft);

        interpolatedVal = ( (1.0 - interpolant) * valLeft ) + ( interpolant * valRight );

    }

    return RoundIfIntegerType<DATATYPE>::round(interpolatedVal);

}*/


template<class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
void populateHistogram(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& arr, Histogram<DATATYPE>& histo){

	for(std::size_t i = 0; i < arr.numElements(); i++){
		histo(arr[i])+=1.0;
	}

}



template<class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
void populateHistogram(const MultidimensionalArray<unsigned char,DIMENSIONS,BUFFERTYPE>& arr, Histogram<DATATYPE>& histo){

	///basic histogram is just find and increment
	if(   (!histo.minValue())  && (histo.maxValue() == 255u) && (histo.numBins() == 255u)){

		for(std::size_t i = 0; i < arr.numElements(); i++){
			histo[ arr[i]]+=1.0;
		}
	}
	else{

		for(std::size_t i = 0; i < arr.numElements(); i++){
			histo(arr[i])+=1.0;
		}
	}
}




template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
void generatePDF(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& img, Histogram<DATATYPE>& histo ){

    double inc = 1.0 / img.numElements();

    for(int i = 0; i < img.numElements(); i++){
        histo(img[i])+= inc;
    }
}



template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
void generateCDF(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& img, Histogram<DATATYPE>& cdf){

    generatePDF(img,cdf);

    generateCDF(cdf,cdf);

}




template <class DATATYPE>
void generateCDF(const Histogram<DATATYPE>& pdfIn, Histogram<DATATYPE>& cdfOut){

    if(pdfIn.numBins() != cdfOut.numBins()){
        throw std::runtime_error("PDF in and CDF out must have same number of bins");
    }

    cdfOut[0] = pdfIn[0];

    for(std::size_t i = 1 ; i < cdfOut.numBins();i++){
        cdfOut[i] = pdfIn[i] + cdfOut[i-1];
    }
}


/*
template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
inline void matchPDF(
                MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& img,
                const Histogram<DATATYPE>& pdfTarget,
                const Histogram<DATATYPE>& pdfBase
    ){

  }
*/



template <class DATATYPE>
DATATYPE remapLuminanceToHistogram(
                                   const DATATYPE& valueIn,
                                   const Histogram<DATATYPE>& cdfTarget,
                                   const Histogram<DATATYPE>& cdfIn
                                   ){


    double find = cdfIn[valueIn];

  //  std::cerr<<"Looking for"<<find<<std::endl;

    double error = std::numeric_limits<double>::max();

    int rval = 0;

    double testError = error;

    //keep iterating while the error is decreasing
    for(int i = 0; i < cdfTarget.size() &&   ((testError= abs(find - cdfTarget[i])) <= error); i++){
       // std::cerr<<"::"<<i<<std::endl;
       //std::cerr<<"Compared "<<cdfTarget[i]<<" to "<<find<<std::endl;

        rval = i;
        error = testError;

    }

    return rval;

}


///\todo document the fact that all the histogram matching shit assumes single channel

template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
void matchCDF(
                MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& img,
                const Histogram<DATATYPE>& cdfTarget,
                const Histogram<DATATYPE>& cdfBase
){

    Histogram<DATATYPE> mapping(cdfBase.minValue(), cdfBase.maxValue(),cdfBase.numBins());


    for(std::size_t val = 0; val < cdfBase.numBins(); val++){
        mapping[val] = inverseCDF(cdfTarget,cdfBase[val]);///\todo op version with []
    }

    ///\todo this doesn't do any interpolation on the input range

    for(std::size_t i = 0; i< img.numElements(); i++){
        img[i] =  mapping(img[i]);///\todo test this with [] operators
    }


//    system("pause");

}









template <class DATATYPE, std::size_t DIMENSIONS, class BUFFERTYPE>
void equalizeImage(
                   MultidimensionalArray<DATATYPE,DIMENSIONS, BUFFERTYPE>& img,
                    ///wtf c++? why can't i make these DATATYPE
                    const typename MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::data_type& rangeBegin,
                    const typename MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::data_type& rangeEnd,
                    const std::size_t& numBins
){
    ///create and populate the cdf of the input array
    Histogram<DATATYPE> cdf(rangeBegin,rangeEnd,numBins);
    generateCDF(img, cdf);

    double interval = cdf.binInterval();

    for(std::size_t i = 0; i < img.numElements(); i++){

        double landedInBin = (cdf.numBins() - 1) * cdf(img[i]);

        ///if the output will be continuous (floating point) we don't need to truncate to a particular bin.
        ///if its integral, then we need to round to a specific bin number
        //img[i] = std::round(landedInBin) * interval + cdf.minValue();

        img[i] = RoundIfIntegerType<DATATYPE>::round(   (landedInBin  * interval + cdf.minValue() ) );

    }
}

