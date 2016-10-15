#include "my_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
struct vec2;
struct vec3;
struct vec4;
struct mat2;
struct mat3;
struct mat4;
*/

bool test_constructor(){
  bool success = true;
  vec<vec2> test = vec<vec2>();
  vec <vec3> unit (1.0, 2.0, 3,0);
  success = success && (unit[0] == 1.0) && (unit[1] == 2.0) && (unit[2] == 3.0);;

  vec<vec4> unit_ii = vec<vec4>(1.0, 2.0, 3,0, 4.0, false);
  success = success && (unit[0] == 1.0) && (unit[1] == 2.0) && (unit[2] == 3.0) && unit_ii[3] == 4.0;;

  float a[4] = {1.0, 2.0, 3.0, 4.0};
	vec<mat4> one = vec<mat4>(2, 2, a);
  std::cout << one[0] << one[1] << one[2] << one[3] << std::endl;
  success = success && (one[0] == 1.0) && (one[1] == 3.0)
                    && (one[2] == 2.0) && (one[3] == 4.0);
  return success;
}

int main(){
	bool success = true;
  success = success && test_constructor();
  printf(success?"Passed all test\n":"Some tests failed\n");
  return 0;
}
