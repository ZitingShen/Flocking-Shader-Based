#include "my_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

template <typename T>
vec<T>::vec(int width, int height, float* data){
  this->local = malloc(sizeof(float) * width * height);
  this->width = width;
  memcpy(local, data, sizeof(float));
}

template <typename T>
float vec<T>::determinant(){
  assert(this->width > 1);
  float* m = local->data;
  if (this->width == 2){
    return m[0]*m[3] - m[1]*m[2];
  }else
  if (this->width == 3){
    return m[0] * m[4] * m[8]
          -m[2] * m[4] * m[6]
          +m[1] * m[5] * m[6]
          -m[1] * m[3] * m[8]
          +m[2] * m[3] * m[7]
          -m[0] * m[5] * m[7];
  }else{
    assert(this->width == 4);
    return m[0]*(m[5]*(m[10]*m[15] - m[11]*m[14]) - m[6]*(m[9]*m[15] - m[11]*m[13]) + m[7]*(m[9]*m[14] - m[10]*m[13]))
          -m[1]*(m[4]*(m[10]*m[15] - m[11]*m[14]) - m[6]*(m[8]*m[15] - m[11]*m[12]) + m[7]*(m[8]*m[14] - m[10]*m[12]))
          +m[2]*(m[4]*(m[9] *m[15] - m[11]*m[13]) - m[5]*(m[8]*m[15] - m[11]*m[12]) + m[7]*(m[8]*m[13] - m[9]* m[12]))
          -m[3]*(m[4]*(m[9] *m[14] - m[10]*m[13]) - m[5]*(m[8]*m[14] - m[10]*m[12]) + m[6]*(m[8]*m[13] - m[9]* m[12]));
  }

}

template <typename T>
T* vec<T>::transpose(){
  if (this->width == 1) return this->local;
  T* new_mat = malloc(sizeof(this));
  for (int i=0; i<this->width; i++){
    for (int j=0; j<this->width; j++){
      new_mat->data[j*this->width+i] = this->data[i*this->width+j];
    }
  }
  return new_mat;
}

template <typename T>
T* vec<T>::inverse(){
  assert(this->width > 1);
  T* new_mat
  if (this->width == 2){
  
  }
}

template <class T>
vec<T>::operator+ (const vec&){


}


