#include "my_matrix.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

vec::vec(){
  this->data = NULL;
	this->width = 0;
	this->height = 0;
}

vec::vec(int width, int height, float* data){
  switch(height){
    case 1:
      switch(width){
        case 2:
          vec2::vec2(data[0], data[1]);
          break;
        case 3:
          vec3::vec3(data[0], data[1]);
          break;
        case 4:
          vec4::vec4(data[0], data[1], data[2], data[3]);
          break;
        default: // should not happen
          std::cerr << "VEC CONSTRUCTOR: BAD WIDTH\n";
          break;
        break;
      }
    case 2:
      mat2::mat2(data[0], data[1], data[2], data[3]);
      break;
    case 3:
      mat3::mat3(data[0], data[1], data[2], data[3],
                 data[4], data[5], data[6], data[7], data[8]);
      break;
    case 4:
      mat4::mat4(data[0], data[1], data[2], data[3],
                 data[4], data[5], data[6], data[7],
                 data[8], data[9], data[10], data[11],
                 data[12], data[13], data[14], data[15]);
      break;
    default: // should not happen
      std::cerr << "VEC CONSTRUCTOR: BAD HEIGHT\n";
      break;
  }
}

vec::vec(int width, int height){
  switch(width*height){
    case VEC2:
      vec2::vec2(0, 0);
      break;
    case VEC3:
      vec3::vec3(0, 0, 0);
      break;
    case VEC4: // MAT2 is the duplicate of VEC4
      if (height != 2) {vec4::vec4(0, 0, 0, 0);}
      else{mat2::mat2(0, 0,
                      0, 0);}
      break;
    case MAT3:
      mat3::mat3(0, 0, 0,
                 0, 0, 0,
                 0, 0, 0);
      break;
    case MAT4:
      mat4::mat4(0, 0, 0, 0,
                 0, 0, 0, 0,
                 0, 0, 0, 0,
                 0, 0, 0, 0);
      break;
    default:
      std::cerr << "VEC CONSTRUCTOR: BAD MATRIX\n";
      break;
  }
}

vec2::vec2(float a, float b){
  this->data = new float[2];
  float* m = this->data;
  m[0] = a; m[1] = b;
  this->width = 2;
  this->height = 1;
}

vec3::vec3(float a, float b, float c){
  this->data = new float[3];
  float* m = this->data;
  m[0] = a; m[1] = b; m[2] = c;
  this->width = 3;
  this->height = 1;
}

vec4::vec4(float a, float b, float c, float d){
  this->data = new float[4];
  float* m = this->data;
  m[0] = a; m[1] = c;
  m[2] = b; m[3] = d;
  this->width = 4;
  this-> height =1;
}

mat2::mat2(float a, float b, float c, float d){
  this->data = new float[4];
  float* m = this->data;
  m[0] = a; m[1] = b;
  m[2] = c; m[3] = d;
  this->width = 2;
  this-> height =2;
}

mat3::mat3(float a1, float a2, float a3,
           float b1, float b2, float b3,
           float c1, float c2, float c3){
  this->data = new float[9];
  float* m = this->data;
  m[0] = a1; m[1] = b1; m[2] = c1;
  m[3] = a2; m[4] = b2; m[5] = c2;
  m[6] = a3; m[7] = b3; m[8] = c3;
  this->width = 3;
  this->height = 3;
}

mat4::mat4(float a1, float a2, float a3, float a4,
           float b1, float b2, float b3, float b4,
           float c1, float c2, float c3, float c4,
           float d1, float d2, float d3, float d4){
  this->data = new float[16];
  float* m = this->data;
  m[0] = a1; m[1] = b1; m[2] = c1, m[3] = d1;
  m[4] = a2; m[5] = b2; m[6] = c2, m[7] = d2;
  m[8] = a3; m[9] = b3; m[10] = c3, m[11] = d3;
  m[12] = a4; m[13] = b4; m[14] = c4; m[15] = d4;
  this->width = 4;
  this->height = 4;
}

vec::~vec(){
  delete [] data;
}

float vec::determinant(){
  assert(this->width > 1);
  float* m = this->data;
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

vec* vec::transpose(){
  if (this->width <= 1) return this;
  vec* new_mat = new vec(this->width, this->height);
  float* m = this->data;
  float* n = new_mat->data;
  for (int i=0; i<this->width; i++){
    for (int j=0; j<this->height; j++){
      n[j*this->height+i] = m[i*this->width+j];
    }
  }
  return new_mat;
}

vec* vec::inverse(){
  assert(this->width > 1);
  if (this->determinant() == 0) return NULL;
  vec* new_mat = new vec(this->width, this->height);
  float* m = new_mat->data;
  float* n = this->data;
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
    m[0] = coeff * mat2(n[4],n[5],n[7],n[8]).determinant();
    m[1] = coeff * mat2(n[2],n[1],n[8],n[7]).determinant();
    m[2] = coeff * mat2(n[1],n[2],n[4],n[5]).determinant();
    m[3] = coeff * mat2(n[5],n[4],n[8],n[6]).determinant();
    m[4] = coeff * mat2(n[0],n[2],n[4],n[5]).determinant();
    m[5] = coeff * mat2(n[2],n[0],n[5],n[4]).determinant();
    m[6] = coeff * mat2(n[3],n[4],n[6],n[7]).determinant();
    m[7] = coeff * mat2(n[1],n[0],n[7],n[6]).determinant();
    m[8] = coeff * mat2(n[0],n[1],n[3],n[4]).determinant();
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

float vec::trace() {
	assert(this->width == this->height);
	float result = 0;
	for (int i = 0; i < this->width; i++) {
		result += this->data[i*width + i];
	}
	return result;
}

vec vec::operator+ (const vec& other) {
	assert(this->width == other->width && this->height == other->height);
	vec new_vec = vec(this->width, this->height);
	int index = 0;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i*this->width + j;
			new_vec.data[index] = this->data[index] + other.data[index];
		}
	}
	return new_vec;
}

vec vec::operator- (const vec& other) {
	assert(this->width == other->width && this->height == other->height);
	vec new_vec = vec(this->width, this->height);
	int index = 0;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i*this->width + j;
			new_vec.data[index] = this->data[index] - other.data[index];
		}
	}
	return new_vec;
}

bool vec::operator== (const vec& other) {
	if (!(this->width == other.width && this->height == other.height)) return false;
	int index = 0;
	bool same = true;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i*this->width + j;
			same = same && (this->data[index] == other.data[index]);
		}
	}
	return same;
}

vec vec::operator* (const float& scalar) {
	vec new_vec = vec(this->width, this->height);
	int index = 0;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i*this->width + j;
			new_vec[index] = this->data[index] * scalar;
		}
	}
	return new_vec;
}

float& vec::operator[] (const int index){
  assert(index < (this->width * this->height) && index >= 0);
  return this->data[index];
}

const float& vec::operator[] (const int index) const{
  assert(index < (this->width * this->height) && index >= 0);
  return this->data[index];
}

void vec::display() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			printf("%lf ", this->data[j*this->width + i]);
		}
		printf("\n");
	}
}

// dot and cross proudct
vec dot(vec* vec_i, vec* vec_ii){
	if (vec_i->height != vec_ii->width){
    std::cerr << "DOT: BAD MATRIX\n";
    return vec(vec_i->width, vec_i->height);
  }
  int sum = 0;
	int dimension = vec_i->height;
	vec new_vec = vec(vec_ii->width, vec_i->height);
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			sum = 0;
			for (int k = 0; k < dimension; k++) {
				sum += vec_i->data[i*vec_i->width + k] * vec_ii->data[k*vec_ii->width + j];
			}
			new_vec[i*dimension + j] = sum;
		}
	}
	return new_vec;
}

vec cross(vec* vec_i, vec* vec_ii){
	if (vec_i->width != 1 || vec_i->height != 3 || vec_ii->width != 1 || vec_ii->height != 3){
    std::cerr << "CROSS: BAD MATRIX\n";
    return vec(vec_i->width, vec_i->height);
  }
	float* a = vec_i->data;
	float* b = vec_ii->data;
	float* entries = new float[3];
  entries[0] = a[2]*b[3] - a[3]*b[2];
  entries[1] = a[3]*b[1] - a[1]*b[3];
	entries[2] = a[1]*b[2] - a[2]*b[1];
	vec new_vec = vec(vec_ii->width, vec_i->height, entries);
	return new_vec;
}

//generate identity or zeor matrix with specified dimension
vec zero(int dimension){
  if (dimension<=0 || dimension>4){
    std::cerr << "ZERO: BAD DIMENSION\n";
    return vec(4, 4);
  }
	vec new_vec =  vec(dimension, dimension);
  for (int i=0; i< dimension*dimension; i++){
    new_vec.data[i] = 0.0;
  }
  return new_vec;
}

vec identity(int dimension){
  if (dimension<=0 || dimension>4){
    std::cerr << "IDENTITY: BAD DIMENSION\n";
    return vec(4, 4);
  }
  vec new_vec =  vec(dimension, dimension);
  for (int i=0; i<dimension; i++){
    for (int j=0; j<dimension; j++){
      new_vec.data[i] = i==j?1.0:0.0;
    }
  }
  return new_vec;
}

vec promote(vec* original, bool append_one){
  if (original->width != 3){
    std::cerr << "PROMOTE: BAD DIMENSION\n";
    return vec(4, 4);
  }
  float* m = original->data;
  if (original->height == 3){
   vec promoted = mat4(m[0], m[1], m[2], 0,
                       m[3], m[4], m[5], 0,
                       m[6], m[7], m[8], 0,
                       0,0,0, append_one?1:0);
    return promoted;
  }else{
    assert(original->height == 1);
    vec promoted = vec4(m[0], m[1], m[2], append_one?1:0);
    return promoted;
  }
}

vec reduce(vec* original){
  if (original->width != 4){
    std::cerr << "REDUCE: BAD DIMENSION\n";
    return vec(3, 3);
  }
  float* m = original->data;
  if (original->height == 4){
    vec reduced = mat3(m[0], m[1], m[2],
                       m[4], m[5], m[6],
                       m[8], m[9], m[10]);
    return reduced;
  }else{
    assert(original->height == 1);
    vec reduced = vec3(m[0], m[1], m[2]);
    return reduced;
  }
}
