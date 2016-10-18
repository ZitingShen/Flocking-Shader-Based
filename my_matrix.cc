#include "my_matrix.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

vec::vec(){
  this->data = NULL;
	this->width = 0;
	this->height = 0;
}

vec::vec(int width, int height){
  this->data = new float[width*height];
  this->width = width;
  this->height = height;
}

vec2::vec2(){
  this->data = new float[2];
  this->width = 2;
  this->height = 1;
}

vec2::vec2(float* data){
  this->data = new float[2];
  this->width = 2;
  this->height = 1;
  memcpy(this->data, data, sizeof(float) * 2);
}

vec2::vec2(float a, float b){
  this->data = new float[2];
  float* m = this->data;
  m[0] = a; m[1] = b;
  this->width = 2;
  this->height = 1;
}

vec3::vec3(){
  this->data = new float[3];
  this->width = 3;
  this->height = 1;
}

vec3::vec3(float* data){
  this->data = new float[3];
  this->width = 3;
  this->height = 1;
  memcpy(this->data, data, sizeof(float) * 3);
}

vec3::vec3(float a, float b, float c){
  this->data = new float[3];
  float* m = this->data;
  m[0] = a; m[1] = b; m[2] = c;
  this->width = 3;
  this->height = 1;
}

vec4::vec4(){
  this->data = new float[4];
  this->width = 4;
  this->height = 1;
}

vec4::vec4(float* data){
  this->data = new float[4];
  this->width = 4;
  this->height = 1;
  memcpy(this->data, data, sizeof(float) * 4);
}

vec4::vec4(float a, float b, float c, float d){
  this->data = new float[4];
  float* m = this->data;
  m[0] = a; m[1] = b; m[2] = c; m[3] = d;
  this->width = 4;
  this-> height = 1;
}

mat2::mat2(){
  this->data = new float[4];
  this->width = 2;
  this->height = 2;
}

mat2::mat2(float* data){
  this->data = new float[4];
  this->width = 2;
  this->height = 2;
  float* m = this->data;
  m[0] = data[0]; m[1] = data[2];
  m[2] = data[1]; m[3] = data[3];
}

mat2::mat2(float a, float b, float c, float d){
  this->data = new float[4];
  float* m = this->data;
  m[0] = a; m[1] = b;
  m[2] = c; m[3] = d;
  this->width = 2;
  this-> height =2;
}

mat3::mat3(){
  this->data = new float[9];
  this->width = 3;
  this->height = 3;
}

mat3::mat3(float* data){
  this->data = new float[9];
  this->width = 3;
  this->height = 3;
  float* m = this->data;
  m[0] = data[0]; m[1] = data[3]; m[2] = data[6];
  m[3] = data[1]; m[4] = data[4]; m[5] = data[7];
  m[6] = data[2]; m[7] = data[5]; m[8] = data[8];
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

mat4::mat4(){
  this->data = new float[16];
  this->width = 4;
  this->height = 4;
}

mat4::mat4(float* data){
  this->data = new float[16];
  this->width = 4;
  this->height = 4;
  float* m = this->data;
  m[0] = data[0]; m[1] = data[4]; m[2] = data[8], m[3] = data[12];
  m[4] = data[1]; m[5] = data[5]; m[6] = data[9], m[7] = data[13];
  m[8] = data[2]; m[9] = data[6]; m[10] = data[10], m[11] = data[14];
  m[12] = data[3]; m[13] = data[7]; m[14] = data[11]; m[15] = data[15];
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

int vec::get_height() const{
  return this->height;
}

int vec::get_width() const{
  return this->width;
}

float vec::determinant() const{
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

float vec::trace() const{
  assert(this->width == this->height);
  float result = 0;
  for (int i = 0; i < this->width; i++) {
    result += this->data[i*width + i];
  }
  return result;
}

mat2 mat2::transpose(){
  mat2 new_mat;
  float* m = this->data;
  float* n = new_mat.data;
  for (int i=0; i<this->width; i++){
    for (int j=0; j<this->height; j++){
      n[j*this->height+i] = m[i*this->width+j];
    }
  }
  return new_mat;
}

mat3 mat3::transpose(){
  mat3 new_mat;
  float* m = this->data;
  float* n = new_mat.data;
  for (int i=0; i<this->width; i++){
    for (int j=0; j<this->height; j++){
      n[j*this->height+i] = m[i*this->width+j];
    }
  }
  return new_mat;
}

mat4 mat4::transpose(){
  mat4 new_mat;
  float* m = this->data;
  float* n = new_mat.data;
  for (int i=0; i<this->width; i++){
    for (int j=0; j<this->height; j++){
      n[j*this->height+i] = m[i*this->width+j];
    }
  }
  return new_mat;
}

mat2 mat2::inverse(){
  if (this->determinant() == 0){
    std::cerr << "INVERSE: BAD MATRIX\n";
    return (*this);
  }
  mat2 new_mat;
  float* m = new_mat.data;
  float* n = this->data;
  float coeff = (1.0f)/(this->determinant());

  m[0] = coeff * n[3];  m[1] = coeff * -n[1];
  m[2] = coeff * -n[2]; m[3] = coeff * n[0];
  return new_mat;
}

mat3 mat3::inverse(){
  if (this->determinant() == 0){
    std::cerr << "INVERSE: BAD MATRIX\n";
    return (*this);
  }
  mat3 new_mat;
  float* m = new_mat.data;
  float* n = this->data;
  float coeff = (1.0f)/(this->determinant());

  m[0] = coeff * mat2(n[4],n[5],n[7],n[8]).determinant();
  m[1] = coeff * mat2(n[2],n[1],n[8],n[7]).determinant();
  m[2] = coeff * mat2(n[1],n[2],n[4],n[5]).determinant();
  m[3] = coeff * mat2(n[5],n[4],n[8],n[6]).determinant();
  m[4] = coeff * mat2(n[0],n[2],n[4],n[5]).determinant();
  m[5] = coeff * mat2(n[2],n[0],n[5],n[4]).determinant();
  m[6] = coeff * mat2(n[3],n[4],n[6],n[7]).determinant();
  m[7] = coeff * mat2(n[1],n[0],n[7],n[6]).determinant();
  m[8] = coeff * mat2(n[0],n[1],n[3],n[4]).determinant();

  return new_mat;
}

mat4 mat4::inverse(){
  if (this->determinant() == 0){
    std::cerr << "INVERSE: BAD MATRIX\n";
    return (*this);
  }
  mat4 new_mat;
  float* m = new_mat.data;
  float* n = this->data;
  float coeff = 1.0f;

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
  for (int i = 0; i < 16; i++){
    m[i] = m[i] * coeff;
  }

  return new_mat;
}

vec2 vec2::operator+ (const vec2& other){
	vec2 new_vec;
	int index = 0;
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			index = i*this->width + j;
			new_vec.data[index] = this->data[index] + other.data[index];
		}
	}
	return new_vec;
}

vec2 vec2::operator- (const vec2& other){
	vec2 new_vec;
	int index = 0;
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			index = i*this->width + j;
			new_vec.data[index] = this->data[index] - other.data[index];
		}
	}
	return new_vec;
}

vec3 vec3::operator+ (const vec3& other){
  vec3 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] + other.data[index];
    }
  }
  return new_vec;
}

vec3 vec3::operator- (const vec3& other){
  vec3 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] - other.data[index];
    }
  }
  return new_vec;
}

vec4 vec4::operator+ (const vec4& other){
  vec4 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] + other.data[index];
    }
  }
  return new_vec;
}

vec4 vec4::operator- (const vec4& other){
  vec4 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] - other.data[index];
    }
  }
  return new_vec;
}

mat2 mat2::operator+ (const mat2& other){
  mat2 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] + other.data[index];
    }
  }
  return new_vec;
}

mat2 mat2::operator- (const mat2& other){
  mat2 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] - other.data[index];
    }
  }
  return new_vec;
}

mat3 mat3::operator+ (const mat3& other){
  mat3 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] + other.data[index];
    }
  }
  return new_vec;
}

mat3 mat3::operator- (const mat3& other){
  mat3 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] - other.data[index];
    }
  }
  return new_vec;
}

mat4 mat4::operator+ (const mat4& other){
  mat4 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] + other.data[index];
    }
  }
  return new_vec;
}

mat4 mat4::operator- (const mat4& other){
  mat4 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] - other.data[index];
    }
  }
  return new_vec;
}

bool vec::operator== (const vec& other) const{
	if (!(this->width == other.width && this->height == other.height)) return false;
	int index = 0;
	bool same = true;
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			index = i*this->width + j;
			same = same && (this->data[index] == other.data[index]);
		}
	}
	return same;
}

void vec::operator= (const vec& other){
  int index = 0;
  if (!(this->width == other.width && this->height == other.height)){
    std::cerr << "OPERATOR+=: BAD ASSIGNMENT\n";
    for (int i=0; i<this->height; i++){
      for (int j=0; j<this->width; j++){
        index = i*this->width + j;
        this->data[index] = 0;
      }
    }
   }
  for (int i=0; i<this->height; i++){
    for (int j=0; j<this->width; j++){
      index = i*this->width + j;
      this->data[index] = other.data[index];
    }
  }
}

void vec::operator+= (const vec& other){
  int index = 0;
  if (!(this->width == other.width && this->height == other.height)){
    std::cerr << "OPERATOR+=: BAD ASSIGNMENT\n";
    for (int i=0; i<this->height; i++){
      for (int j=0; j<this->width; j++){
        index = i*this->width + j;
        this->data[index] = 0;
      }
    }
   }
  for (int i=0; i<this->height; i++){
    for (int j=0; j<this->width; j++){
      index = i*this->width + j;
      this->data[index] = this->data[index] + other.data[index];
    }
  }
}

void vec::operator-= (const vec& other){
  int index = 0;
  if (!(this->width == other.width && this->height == other.height)){
    std::cerr << "OPERATOR+=: BAD ASSIGNMENT\n";
    for (int i=0; i<this->height; i++){
      for (int j=0; j<this->width; j++){
        index = i*this->width + j;
        this->data[index] = 0;
      }
    }
   }
  for (int i=0; i<this->height; i++){
    for (int j=0; j<this->width; j++){
      index = i*this->width + j;
      this->data[index] = this->data[index] - other.data[index];
    }
  }
}

void vec::operator++ (){
  int index = 0;
  for (int i=0; i<this->height; i++){
    for (int j=0; j<this->width; j++){
      index = i*this->width + j;
      this->data[index] = this->data[index] * 2;
    }
  }
}

vec2 vec2::operator* (const float& scalar) {
	vec2 new_vec;
	int index = 0;
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			index = i*this->width + j;
			new_vec.data[index] = this->data[index] * scalar;
		}
	}
	return new_vec;
}

vec3 vec3::operator* (const float& scalar) {
  vec3 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] * scalar;
    }
  }
  return new_vec;
}

vec4 vec4::operator* (const float& scalar) {
  vec4 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] * scalar;
    }
  }
  return new_vec;
}

mat2 mat2::operator* (const float& scalar) {
  mat2 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] * scalar;
    }
  }
  return new_vec;
}

mat3 mat3::operator* (const float& scalar) {
  mat3 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] * scalar;
    }
  }
  return new_vec;
}

mat4 mat4::operator* (const float& scalar) {
  mat4 new_vec;
  int index = 0;
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      index = i*this->width + j;
      new_vec.data[index] = this->data[index] * scalar;
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

void vec::display() const{
	for (int i=0; i<this->height; i++){
		for (int j=0; j<this->width; j++){
			printf("%lf ", this->data[i*this->width + j]);
		}
		printf("\n");
	}
}

vec4 vec3::promote(bool append_one){
  float* m = this->data;
  return vec4(m[0], m[1], m[2], append_one?1:0);
}

mat4 mat3::promote(bool append_one){
  float* m = this->data;
  return mat4(m[0], m[3], m[6], 0,
              m[1], m[4], m[7], 0,
              m[2], m[5], m[8], 0,
              0,0,0, append_one?1:0);
}

vec3 vec4::reduce(){
  float* m = this->data;
  return vec3(m[0], m[1], m[2]);
}

mat3 mat4::reduce(){
  float* m = this->data;
  return mat3(m[0], m[4], m[8],
              m[1], m[5], m[9],
              m[2], m[6], m[10]);
}

// dot and cross proudct

vec2 dot(const vec2& vec_i, const vec2& vec_ii){
  return vec2::vec2(vec_i[0]*vec_ii[0],
                    vec_i[1]*vec_ii[1]);
}

vec3 dot(const vec3& vec_i, const vec3& vec_ii){
  return vec3::vec3(vec_i[0]*vec_ii[0],
                    vec_i[1]*vec_ii[1],
                    vec_i[2]*vec_ii[2]);
}

vec4 dot(const vec4& vec_i, const vec4& vec_ii){
  return vec4::vec4(vec_i[0]*vec_ii[0],
                    vec_i[1]*vec_ii[1],
                    vec_i[2]*vec_ii[2],
                    vec_i[3]*vec_ii[3]);
}

vec3 cross(const vec& vec_i,const vec& vec_ii){
  if (vec_i.get_width() != 1 || vec_i.get_height() != 3
    || vec_ii.get_width() != 1 || vec_ii.get_height() != 3){
    std::cerr << "CROSS: BAD MATRIX\n";
  }
  float* a = vec_i.data;
  float* b = vec_ii.data;
  float entries[3];
  entries[0] = a[2]*b[3] - a[3]*b[2];
  entries[1] = a[3]*b[1] - a[1]*b[3];
  entries[2] = a[1]*b[2] - a[2]*b[1];
  vec3 new_vec(entries);
  return new_vec;
}

float distance(const vec& vec_i, const vec& vec_ii){
  assert(vec_i.get_height() == 1 && vec_ii.get_height() == 1
         && (vec_i.get_width() == 3 || vec_i.get_width() == 4)
         && (vec_ii.get_width() == 3 || vec_ii.get_width() == 4));
  return sqrt((vec_i[0] - vec_ii[0])*(vec_i[0] - vec_ii[0])
        +(vec_i[1] - vec_ii[1])*(vec_i[1] - vec_ii[1])
        +(vec_i[2] - vec_ii[2])*(vec_i[2] - vec_ii[2]));
}

float length(const vec& vec_i){
  assert(vec_i.get_height() == 1);
  float result = 0;
  for (int i=0; i<vec_i.get_width();i++){
    result += vec_i[i]*vec_i[i];
  }
  return sqrt(result);
}

vec3 normalise(const vec& vec_i){
  assert(vec_i.get_height() == 1);
  vec3 new_vec3;
  float len = length(vec_i);
  new_vec3.data[0] = vec_i[0] / len;
  new_vec3.data[1] = vec_i[1] / len;
  new_vec3.data[2] = vec_i[2] / len;
  return new_vec3;
}

void unpack(const vec& vec_i, GLfloat arr[]){
  int index = 0;
  int count = 0;
  for (int i = 0; i < vec_i.get_height(); i++) {
    for (int j = 0; j < vec_i.get_width(); j++) {
      index = i*vec_i.get_width() + j;
      arr[count] = vec_i.data[index];
    }
  }

}

//generate identity or zeor matrix with specified dimension
mat2 all_zero_mat2(mat2 m){
  return m;
}

mat3 all_zero_mat3(mat3 m){
  return m;
}

mat4 all_zero_mat4(mat4 m){
  return m;
}

mat2 identity_mat2(mat2 m){
  return m;
}

mat3 identity_mat3(mat3 m){
  return m;
}

mat4 identity_mat4(mat4 m){
  return m;
}

mat4 multiply(const mat4& m_i, const mat4& m_ii){
  int sum = 0;
  int dimension = m_i.get_height();
  mat4 new_mat = mat4(m_i.get_width(), m_ii.get_height());
  for (int i = 0; i<dimension; i++){
    for (int j = 0; j<dimension; j++){
      sum = 0;
      for (int k = 0; k < dimension; k++){
        sum += m_i.data[i*m_i.get_width() + k] * m_ii.data[k*m_ii.get_width() + j];
      }
      new_mat[i*dimension + j] = sum;
    }
  }
  return new_mat;
}
