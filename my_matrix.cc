#include "my_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

template <typename T>
vec<T>::vec() {
	this->local = NULL;
	this->width = 0;
	this->height = 0;
}

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
vec<T>::vec(float a, float b, float c, float d){
  this->width = 2;
  this-> height =2;
  this->local = malloc(sizeof(float) * width * height);
  this->local[0] = a; this->local[1] = b;
  this->local[2] = c; this->local[3] = d;
}

template <typename T>
vec<T>::~vec(){
  free(this->local);
}

template <typename T>
float vec<T>::determinant(){
  assert(this->width > 1);
  float* m = this->local->data;
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
      new_mat->local->data[j*this->height+i] = this->local->data[i*this->width+j];
    }
  }
  return new_mat;
}

template <typename T>
T* vec<T>::inverse(){
  assert(this->width > 1);
  if (this->determinant() == 0) return NULL;
  T* new_mat = malloc(sizeof(this));
  float* m = new_mat->local->data;
  float* n = this->local->data;
  float coeff = 1;
  if (this->width == 2){
    coeff = 1.0/(this->determinant());
    m[0] = coeff * n[3];
    m[1] = coeff * -n[1];
    m[2] = coeff * -n[2];
    m[3] = coeff * n[0];
  }else
  if (this->width == 3){
    coeff = (1.0)/(this->determinant());
    m[0] = coeff * vec(n[4],n[5],n[7],n[8]).determinant();
    m[1] = coeff * vec(n[2],n[1],n[8],n[7]).determinant();
    m[2] = coeff * vec(n[1],n[2],n[4],n[5]).determinant();
    m[3] = coeff * vec(n[5],n[4],n[8],n[6]).determinant();
    m[4] = coeff * vec(n[0],n[2],n[4],n[5]).determinant();
    m[5] = coeff * vec(n[2],n[0],n[5],n[4]).determinant();
    m[6] = coeff * vec(n[3],n[4],n[6],n[7]).determinant();
    m[7] = coeff * vec(n[1],n[0],n[7],n[6]).determinant();
    m[8] = coeff * vec(n[0],n[1],n[3],n[4]).determinant();
  }else{
    assert(this->width == 4);
    m[0] = n[5]  * n[10] * n[15] -
           n[5]  * n[11] * n[14] -
           n[9]  * n[6]  * n[15] +
           n[9]  * n[7]  * n[14] +
           n[13] * n[6]  * n[11] -
           n[13] * n[7]  * n[10];

    m[4] = -n[4]  * n[10] * n[15] +
            n[4]  * n[11] * n[14] +
            n[8]  * n[6]  * n[15] -
            n[8]  * n[7]  * n[14] -
            n[12] * n[6]  * n[11] +
            n[12] * n[7]  * n[10];

     m[8] = n[4]  * n[9] * n[15] -
            n[4]  * n[11] * n[13] -
            n[8]  * n[5] * n[15] +
            n[8]  * n[7] * n[13] +
            n[12] * n[5] * n[11] -
            n[12] * n[7] * n[9];

   m[12] = -n[4]  * n[9] * n[14] + 
            n[4]  * n[10] * n[13] +
            n[8]  * n[5] * n[14] - 
            n[8]  * n[6] * n[13] - 
            n[12] * n[5] * n[10] + 
            n[12] * n[6] * n[9];

    m[1] = -n[1]  * n[10] * n[15] + 
            n[1]  * n[11] * n[14] + 
            n[9]  * n[2] * n[15] - 
            n[9]  * n[3] * n[14] - 
            n[13] * n[2] * n[11] + 
            n[13] * n[3] * n[10];

     m[5] = n[0]  * n[10] * n[15] - 
            n[0]  * n[11] * n[14] - 
            n[8]  * n[2] * n[15] + 
            n[8]  * n[3] * n[14] + 
            n[12] * n[2] * n[11] - 
            n[12] * n[3] * n[10];

     m[9] = -n[0]  * n[9] * n[15] + 
             n[0]  * n[11] * n[13] + 
             n[8]  * n[1] * n[15] - 
             n[8]  * n[3] * n[13] - 
             n[12] * n[1] * n[11] + 
             n[12] * n[3] * n[9];

     m[13] = n[0]  * n[9] * n[14] - 
             n[0]  * n[10] * n[13] - 
             n[8]  * n[1] * n[14] + 
             n[8]  * n[2] * n[13] + 
             n[12] * n[1] * n[10] - 
             n[12] * n[2] * n[9];

      m[2] = n[1]  * n[6] * n[15] - 
             n[1]  * n[7] * n[14] - 
             n[5]  * n[2] * n[15] + 
             n[5]  * n[3] * n[14] + 
             n[13] * n[2] * n[7] - 
             n[13] * n[3] * n[6];

      m[6] = -n[0]  * n[6] * n[15] + 
              n[0]  * n[7] * n[14] + 
              n[4]  * n[2] * n[15] - 
              n[4]  * n[3] * n[14] - 
              n[12] * n[2] * n[7] + 
              n[12] * n[3] * n[6];

      m[10] = n[0]  * n[5] * n[15] - 
              n[0]  * n[7] * n[13] - 
              n[4]  * n[1] * n[15] + 
              n[4]  * n[3] * n[13] + 
              n[12] * n[1] * n[7] - 
              n[12] * n[3] * n[5];

      m[14] = -n[0]  * n[5] * n[14] + 
               n[0]  * n[6] * n[13] + 
               n[4]  * n[1] * n[14] - 
               n[4]  * n[2] * n[13] - 
               n[12] * n[1] * n[6] + 
               n[12] * n[2] * n[5];

      m[3] = -n[1] * n[6] * n[11] + 
              n[1] * n[7] * n[10] + 
              n[5] * n[2] * n[11] - 
              n[5] * n[3] * n[10] - 
              n[9] * n[2] * n[7] + 
              n[9] * n[3] * n[6];

      m[7] = n[0] * n[6] * n[11] - 
             n[0] * n[7] * n[10] - 
             n[4] * n[2] * n[11] + 
             n[4] * n[3] * n[10] + 
             n[8] * n[2] * n[7] - 
             n[8] * n[3] * n[6];

      m[11] = -n[0] * n[5] * n[11] + 
               n[0] * n[7] * n[9] + 
               n[4] * n[1] * n[11] - 
               n[4] * n[3] * n[9] - 
               n[8] * n[1] * n[7] + 
               n[8] * n[3] * n[5];

      m[15] = n[0] * n[5] * n[10] - 
              n[0] * n[6] * n[9] - 
              n[4] * n[1] * n[10] + 
              n[4] * n[2] * n[9] + 
              n[8] * n[1] * n[6] - 
              n[8] * n[2] * n[5];
      coeff = 1.0/ (n[0] * m[0] + n[1] * m[4] + n[2] * m[8] + n[3] * m[12]);
      for (int i = 0; i < 16; i++)
m[i] = m[i] * coeff;
	}
	return new_mat;
}

template <typename T>
float vec<T>::trace() {
	assert(this->width == this->height);
	float result;
	for (int i = 0; i < this->width; i++) {
		result += this->local->data[i*width + i];
	}
	return result;
}

template <typename T>
vec<T> vec<T>::operator+ (const vec& other) {
	assert(this->width == other->width && this->height == other->height);
	vec<T> new_vec = vec<T>(this->width, this->height);
	int index = 0;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i*this->width + j;
			new_vec[index] = this->local->data[index] + other->local->data[index];
		}
	}
	return new_vec;
}

template <typename T>
vec<T> vec<T>::operator- (const vec& other) {
	assert(this->width == other->width && this->height == other->height);
	vec<T> new_vec = vec<T>(this->width, this->height);
	int index = 0;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i*this->width + j;
			new_vec[index] = this->local->data[index] - other->local->data[index];
		}
	}
	return new_vec;
}

template <typename T>
vec<T> vec<T>::operator== (const vec& other) {
	if (!(this->width == other->width && this->height == other->height)) return false;
	int index = 0;
	bool same = true;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i*this->width + j;
			same = same && (this->local->data[index] == other->local->data[index]);
		}
	}
	return same;
}

template <typename T>
vec<T> vec<T>::operator* (const float& scalar) {
	vec<T> new_vec = vec<T>(this->width, this->height);
	int index = 0;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i*this->width + j;
			new_vec[index] = this->local->data[index] * scalar;
		}
	}
	return new_vec;
}

template <typename T>
void vec<T>::display() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			printf("%lf ", this->local->data[j*this->width + i]);
		}
		printf("\n");
	}
}

// dot and cross proudct
template <typename T>
vec<T>* dot(vec<T>* vec_i, vec<T>* vec_ii) {
	if (vec_i->height != vec_ii->width) return NULL;
	int sum = 0;
	int dimension = vec_i->height;
	vec<T>* new_vec = new vec<T>(vec_ii->width, vec_i->height);
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			sum = 0;
			for (int k = 0; k < dimension; k++) {
				sum += vec_i[i*vec_i->width + k] * vec_ii[k*vec_ii->width + j];
			}
			new_vec[i*dimension + j] = sum;
		}
	}
	return new_vec;
}

template <typename T>
vec<T>* cross(vec<T>* vec_i, vec<T>* vec_ii){
	if (vec_i->width != 1 || vec_i->height != 3 || vec_ii->width != 1 || vec_ii->height != 3) return NULL;
	float* a = vec_i->local->data;
	float* b = vec_ii->local->data;
	float* entries = new float[3](a[2]*b[3] - a[3]*b[2],
														    a[3]*b[1] - a[1]*b[3],
																a[1]*b[2] - a[2]*b[1]);
	vec<T>* new_vec = new vec<T>(vec_ii->width, vec_i->height, entries);
	return new_vec;
}