template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator< (const  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& comparator)const{

        MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

        for(std::size_t i =0; i < numElements();i++){
            rval[i] =  (*this)[i] < comparator[i];
        }

        return rval;
}




template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator> (const  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& comparator)const{

        MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

        for(std::size_t i =0; i < numElements();i++){
            rval[i] =  (*this)[i] > comparator[i];
        }
        return rval;
}




template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator<= (const  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& comparator)const{

        MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

        for(std::size_t i =0; i < numElements();i++){
            rval[i] =  (*this)[i] <= comparator[i];
        }
        return rval;
    }




template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator>= (const  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& comparator)const{

        MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

        for(std::size_t i =0; i < numElements();i++){
            rval[i] =  (*this)[i] >= comparator[i];
        }
        return rval;
}





/************componentwise*******************/
template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator< (const DATATYPE& comparator)const{

        MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

        for(std::size_t i =0; i < numElements();i++){
            rval[i] =  (*this)[i] < comparator;
        }
        return rval;
    }



template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
    MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator== (const DATATYPE& comparator)const{

        MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

        for(std::size_t i =0; i < numElements();i++){
            rval[i] =  (*this)[i] == comparator;
        }
        return rval;
    }



template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator> (const DATATYPE& comparator)const{


    MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

    for(std::size_t i =0; i < numElements();i++){
        rval[i] =  (*this)[i] > comparator;


    }
    return rval;
}




template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator<= (const DATATYPE& comparator)const{

        MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

        for(std::size_t i =0; i < numElements();i++){
            rval[i] =  (*this)[i] <= comparator;
        }
        return rval;
    }




template <class DATATYPE,std::size_t DIMENSIONS,class BUFFERTYPE>
    MultidimensionalArray<bool,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,  BUFFERTYPE>::operator>= (const DATATYPE& comparator)const{

        MultidimensionalArray<bool, DIMENSIONS> rval(getDimensions());

        for(std::size_t i =0; i < numElements();i++){
            rval[i] =  (*this)[i] >= comparator;
        }
        return rval;
}



/********************others ***************************/


///bitwise inverse of each element in the array

template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator~()const{

        MultidimensionalArray<DATATYPE,DIMENSIONS> rval(BUFFERTYPE::getDimensions());

        for(std::size_t i = 0; i < rval.numElements(); i++){

            rval[i] = ~(*this)[i];

        }

        return rval;
}



template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS>  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator-()const {

    MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = -(*this)[i];
    }

    return rval;
}





template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator+=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in){

    for(std::size_t i = 0; i < numElements(); i++){

        (*this)[i] += in[i];
    }

}



template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator*=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in){

        for(std::size_t i = 0; i < numElements(); i++){

            (*this)[i] *= in[i];
        }
}


template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator-=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in){


        for(std::size_t i = 0; i < numElements(); i++){

            (*this)[i] -= in[i];
        }
}



template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator/=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in){


        for(std::size_t i = 0; i < numElements(); i++){

            (*this)[i] /= in[i];
        }
}




template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator%=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in){

        for(std::size_t i = 0; i < numElements(); i++){

            (*this)[i] %= in[i];
        }
}






template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator+(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,  BUFFERTYPE_2>& r){

    MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] + r[i];
    }

    return rval;
}



template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator*(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r){

    MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] * r[i];
    }

    return rval;
}


template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator-(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r){
  MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] - r[i];
    }

    return rval;
}




template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator/(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r){

  MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] / r[i];
    }

    return rval;

}




template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE_1,class BUFFERTYPE_2>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator%(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_1>& l, const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& r){

    MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] % r[i];
    }

    return rval;
}





template <class DATATYPE, std::size_t DIMENSIONS,  class SCALAR,class BUFFERTYPE >
MultidimensionalArray<DATATYPE,DIMENSIONS> operator-(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar){

    MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] - scalar;
    }

    return rval;
}




template <class DATATYPE, std::size_t DIMENSIONS,  class SCALAR,class BUFFERTYPE >
MultidimensionalArray<DATATYPE,DIMENSIONS> operator*(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar){
   MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] *scalar;
    }

    return rval;

}






template <class DATATYPE, std::size_t DIMENSIONS,  class SCALAR,class BUFFERTYPE >
MultidimensionalArray<DATATYPE,DIMENSIONS> operator*( const SCALAR& scalar,const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& r){

    return r * scalar;
}








template <class DATATYPE, std::size_t DIMENSIONS,  class SCALAR,class BUFFERTYPE >
MultidimensionalArray<DATATYPE,DIMENSIONS> operator+(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar){

  MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] + scalar;
    }

    return rval;
}




template <class DATATYPE, std::size_t DIMENSIONS,  class SCALAR,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS> operator/(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar){

    MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] /scalar;
    }

    return rval;
}




template <class DATATYPE, std::size_t DIMENSIONS,  class SCALAR,class BUFFERTYPE >
MultidimensionalArray<DATATYPE,DIMENSIONS> operator%(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& l, const SCALAR& scalar){

    MultidimensionalArray<DATATYPE,DIMENSIONS>  rval(l.getDimensions());

    for(std::size_t i = 0; i < rval.numElements(); i++){

        rval[i] = l[i] %scalar;
    }

    return rval;

}



template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
bool MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator!=(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in)const{
    return !(*this == in);
}


template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
bool MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator==(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in)const{
    for(std::size_t i = 0; i < numElements(); i++)
    {
        if((*this)[i] != in[i])return false;
    }
    return true;
}




template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class BUFFERTYPE_2>
MultidimensionalArray<bool,DIMENSIONS> MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::compareElements(const MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE_2>& in)const{
    MultidimensionalArray<bool,DIMENSIONS>  rval(getDimensions());

    for(std::size_t i = 0; i < rval.numElements();i++){

        rval[i] = (*this)[i] == in[i];
    }

    return rval;
}




template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator++(){


    for(std::size_t i = 0; i < numElements(); i++){
       ++(*this[i]);
    }

    return *this;

}


template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator--(){
   for(std::size_t i = 0; i < numElements(); i++){
       --(*this[i]);
    }

    return *this;
}






template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator++(int){

    auto tmp = *this;

    for(std::size_t i = 0; i < numElements(); i++){
       (*this[i])++;
    }

    return tmp;

}


template <class DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>& MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator--(int){

   auto tmp = *this;

   for(std::size_t i = 0; i < numElements(); i++){
       (*this[i])--;
    }

    return tmp;
}



/***********************************************/





template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class SCALAR>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator+=(const SCALAR& in){

    for(std::size_t i = 0; i < numElements(); i++){

        (*this)[i] += in;
    }

}



template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class SCALAR>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator*=(const SCALAR& in){

        for(std::size_t i = 0; i < numElements(); i++){

            (*this)[i] *= in ;
        }
}


template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class SCALAR>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator-=(const SCALAR& in){

    for(std::size_t i = 0; i < numElements(); i++){

        (*this)[i] -= in ;
    }
}



template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class SCALAR>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator/=(const SCALAR& in){


        for(std::size_t i = 0; i < numElements(); i++){

            (*this)[i] /= in ;
        }
}




template <typename DATATYPE, std::size_t DIMENSIONS,class BUFFERTYPE>
template <class SCALAR>
void  MultidimensionalArray<DATATYPE,DIMENSIONS,BUFFERTYPE>::operator%=(const SCALAR& in){

    for(std::size_t i = 0; i < numElements(); i++){

        (*this)[i] %= in;
    }
}

