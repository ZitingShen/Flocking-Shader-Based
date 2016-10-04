#include "my_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

template <typename T>
vec<T>::vec(int width, int height){
  this->local = malloc(sizeof(float) * width * height);
  this->width = width;
  this->height = height;
}

template <typename T>
vec<T>::vec(int width, int height, float* data){
  this->local = malloc(sizeof(float) * width * height);
  this->width = width;
  this->height = height;
  memcpy(local, data, sizeof(float));
}

template <typename T>
vec<T>::~vec(){
  free(this->local);
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
    for (int j=0; j<this->height; j++){
      new_mat->data[j*this->height+i] = this->data[i*this->width+j];
    }
  }
  return new_mat;
}

template <typename T>
T* vec<T>::inverse(){
  assert(this->width > 1);
  T* new_mat = malloc(sizeof(this));
  if (this->width == 2){
  }
}

template <typename T>
vec<T> vec<T>::operator+ (const vec& other){
  assert(this->width == other->width && this->height == other->height);
  vec<T> new_vec = vec<T>(this->width, this->height);
  int index = 0;
  for (int i=0; i<this->width;i++){
    for (int j=0; j<this->height; j++){
      index = i*this->width + j;
      new_vec[index] = this->data[index] + other->data[index];
    }
  }
  return new_vec;
}

template <typename T>
vec<T> vec<T>::operator- (const vec& other){
  assert(this->width == other->width && this->height == other->height);
  vec<T> new_vec = vec<T>(this->width, this->height);
  int index = 0;
  for (int i=0; i<this->width;i++){
    for (int j=0; j<this->height; j++){
      index = i*this->width + j;
      new_vec[index] = this->data[index] - other->data[index];
    }
  }
  return new_vec;
}

template <typename T>
vec<T> vec<T>::operator== (const vec& other){
  if (!(this->width == other->width && this->height == other->height)) return false;
  int index = 0;
  bool same = true;
  for (int i=0; i<this->width;i++){
    for (int j=0; j<this->height; j++){
      index = i*this->width + j;
      same = same && (this->data[index] == other->data[index]);
    }
  }
  return same;
}

template <typename T>
vec<T> vec<T>::operator* (const float& scalar){
  vec<T> new_vec = vec<T>(this->width, this->height);
  int index = 0;
  for (int i=0; i<this->width;i++){
    for (int j=0; j<this->height; j++){
      index = i*this->width + j;
      new_vec[index] = this->data[index] * scalar;
    }
  }
  return new_vec;
}
