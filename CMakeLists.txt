cmake_minimum_required(VERSION 2.8)
project(VirtuosoImage)

if(NOT MSVC)
set(CMAKE_CXX_FLAGS "--std=c++0x  -fopenmp -Wall -Wpedantic")
endif(NOT MSVC)

set(IMAGESRC
	Image.h
	Image.cpp
	Image.tcc
	stb_image.c
	stb_image.h
	stb_image_write.h
	ImageProcessing.h
	ImageProcessing.cpp
	MultidimensionalArray.h
	MultidimensionalArray.tcc
	SharedPtrDeleters.h
	mdarrayConstructors.tcc 
	mdarrayIO.tcc 
	mdarrayFunctions.tcc 
	mdarrayAccessors.tcc 
	SubregionHelper.tcc
	InterpolationHelper.tcc
	mdarrayOperators.tcc
	SliceBuffer.h
	ArrayBuffer.h
	ArrayBuffer.tcc
	Gaussian.h
	Convolution.h
	Gradient.h	
	Histogram.h
	
)


add_library(image_library ${IMAGESRC} )

set(Eigen_DIR "" CACHE PATH "Eigen Include Directory")

include_directories(${Eigen_DIR})








