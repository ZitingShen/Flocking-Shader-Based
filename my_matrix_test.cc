#include "my_matrix.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::endl;

bool test_constructor(){
  bool success = true;
  float a[2] = {1,2};
  float b[3] = {1,2,3};
  float c[4] = {1,2,3,4};
  float d[9] = {1,2,3,4,5,6,7,8,9};
  float e[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

  vec2 unit(a);
  success = success && (unit[0] == 1.0 && unit[1] == 2.0);

  vec3 unit_i(b);
  success = success && (unit_i[0] == 1.0) && (unit_i[1] == 2.0) && (unit_i[2] == 3.0);

  vec4 unit_ii(c);
  success = success && (unit_ii[0] == 1.0) && (unit_ii[1] == 2.0) && (unit_ii[2] == 3.0) && (unit_ii[3] == 4.0);

	mat2 one(c);
  success = success && (one[0] == 1.0) && (one[1] == 3.0) 
                    && (one[2] == 2.0) && (one[3] == 4.0);

  mat3 two(d);
  success = success && (two[0] == 1.0) && (two[1] == 4.0) && (two[2] == 7.0) 
                    && (two[3] == 2.0) && (two[4] == 5.0) && (two[5] == 8.0)
                    && (two[6] == 3.0) && (two[7] == 6.0) && (two[8] == 9.0);

  mat4 three(e);
  success = success && (three[0] == 1.0) && (three[1] == 5.0) && (three[2] == 9.0) && (three[3] == 13.0)
                    && (three[4] == 2.0) && (three[5] == 6.0) && (three[6] == 10.0) && (three[7] == 14.0)
                    && (three[8] == 3.0) && (three[9] == 7.0) && (three[10] == 11.0) && (three[11] == 15.0)
                    && (three[12] == 4.0) && (three[13] == 8.0) && (three[14] == 12.0) && (three[15] == 16.0);

  return success;
}

/*
bool test_operators(){
  bool success = true;
  float e[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

  vec* first = new mat4(e);
  vec* second = new mat4(e);
  vec* zero = all_zero(4);
  vec* id_mt = identity(4);

  success = success && ((*first) == (*second));

  vec* result = all_zero(4);

  success = success && ((*result) == (*zero));

  result = (*result) + (*first);

  success = success && ((*result) == (*first));

  first = (*first) * 2;

  for (int i=0; i<16; i++){
    if (i == 0 || i%5 == 0){
      success = success && ((*id_mt)[i] == 1);
      break;
    }
    success = success && ((*id_mt)[i] == 0);
  }

  for (int i=0; i<16; i++){
    success = success && (((*second)[i] * 2) == (*first)[i]);
  }

  delete first;
  delete second;
  delete result;
  delete zero;
  delete id_mt;

  return success;
}
*/
bool test_reduce_promote(){
  bool success = true;
/*  float d[9] = {1,2,3,4,5,6,7,8,9};
  float e[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

  mat4 first(e);
  mat4 another = dynamic_cast<mat4>(first + first);
  mat3 first_reduced = first.reduce();
  vec* first_reduced_promoted = first_reduced->promote(false);
  first_reduced_promoted = (*first_reduced_promoted) + (*first_reduced_promoted);
*/
  //mat4 t = identity_mat4();
  //t.display();
  /*first->display();
  first_reduced->display();
  first_reduced_promoted->display();


  delete first;
  delete first_reduced;
  delete first_reduced_promoted;

  first = new vec4(d);
  first_reduced = first->reduce();
  first_reduced_promoted = first_reduced->promote(true);
  first_reduced_promoted = (*first_reduced_promoted) + (*first_reduced_promoted);

  first->display();
  first_reduced->display();
 first_reduced_promoted->display();

  delete first;
  delete first_reduced;
  delete first_reduced_promoted;
*/
  return success;
}

void test_methods(){
  float a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  float b[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,117};
  float c[16] = {12,32,45,21,4,65,35,27,56,78,69,12,45,65,76,1};    

  float d[9] = {1,2,3,4,5,6,7,8,9};
  float e[9] = {12,32,45,21,4,65,35,27,56};        

  mat4 m1(a);
  mat4 m2(b);
  mat4 m3(c);
  mat3 m4(d);
  mat3 m5(e);
  m2 = m1;
  cout << m1.determinant() << " " << m1.trace() << endl;
  cout << m2.determinant() << " " << m2.trace() << endl;
  cout << m3.determinant() << " " << m3.trace() << endl;
  cout << m4.determinant() << " " << m4.trace() << endl;
  cout << m5.determinant() << " " << m5.trace() << endl;

  m2.display();
  m3.display();
  mat4 m_m = multiply(m2, m3);
  m_m.display();

  m5.display();
  m5.transpose();
  m5.display();
  m5.inverse();
  m5.display();
  
  m3.display();
  m3.transpose();
  m3.display();
  m3.inverse();
  m3.display();

  vec3 v_3_i(1,2,3);
  vec3 v_3_ii(6,7,8);
  float v_dot = dot(v_3_i, v_3_ii);
  vec3 v_cross = cross(v_3_i, v_3_ii);

  cout << v_dot << endl;
  v_cross.display();



}

int main(){
	bool success = true;
  test_methods();
  success = success
  //          && test_constructor()
  //          && test_operators()
            && test_reduce_promote();
  printf(success?"Passed all test\n":"Some tests failed\n");
  return 0;
}
