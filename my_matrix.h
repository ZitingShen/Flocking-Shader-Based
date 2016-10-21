#ifndef MY_MATRIX
#define MY_MATRIX

#ifdef __APPLE__
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#else
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif
/*
#define VEC2 2
#define VEC3 3
#define VEC4 4
#define MAT2 4
#define MAT3 9
#define MAT4 16
*/

/* Data-type and relevant operations
 * - vec2, vec3, vec4, mat2, mat3, mat4
 * – zero, identify, addition, multiplication
 * – dot product, cross product
 * – transpose, inverse, trace, determinant
 */

class vec;
class vec2;
class vec3;
class vec4;
class mat2;
class mat3;
class mat4;

class vec{
  protected:
    int width;
    int height;
  public:
    float* data;
    /* put immediates in COLUMN-MAJOR order */
    /* using new/delete for memory allocation */
    vec();
    vec(int width, int height);
    ~vec();

    int get_height() const;
    int get_width() const;
    float determinant() const;
    float trace() const;
    bool operator== (const vec& other) const;
    vec& operator= (const vec& other);
    vec& operator+= (const vec& other);
    vec& operator-= (const vec& other);
    void operator++ (); // for doubling all values
    void transpose();
    float& operator[] (const int index); // mutator
    const float& operator[] (const int index) const; // accessor
    void display() const; // column-major display
};

class vec2:
public vec{
  public:
  vec2();
  vec2(float* data);
  vec2(float a, float b);
  vec2 operator+  (const vec2& other) const;
  vec2 operator-  (const vec2& other) const;
  vec2 operator*  (const float& scalar) const;
};

class vec3:
public vec{
  public:
  vec3();
  vec3(float* data);
  vec3(float a, float b, float c);
  vec3 operator+  (const vec3& other) const;
  vec3 operator-  (const vec3& other) const;
  vec3 operator*  (const float& scalar) const;
  vec4 promote(bool append_one);
};

class vec4:
public vec{
  public:
  vec4();
  vec4(float* data);
  vec4(float a, float b, float c, float d);
  vec4 operator+  (const vec4& other) const;
  vec4 operator-  (const vec4& other) const;
  vec4 operator*  (const float& scalar) const;
  vec3 reduce();
  void reset();
};

class mat2:
public vec{
  public:
  mat2();
  mat2(float* data);
  mat2(float a, float b, float c, float d);
  mat2 operator+  (const mat2& other) const;
  mat2 operator-  (const mat2& other) const;
  mat2 operator*  (const float& scalar) const;
  void inverse();
};

class mat3:
public vec{
  public:
  mat3();
  mat3(float* data);
  mat3(float a1, float a2, float a3,
       float b1, float b2, float b3,
       float c1, float c2, float c3);
  mat3 operator+  (const mat3& other) const;
  mat3 operator-  (const mat3& other) const;
  mat3 operator*  (const float& scalar) const;
  void inverse();
  mat4 promote(bool append_one);
};

class mat4:
public vec{
  public:
  mat4();
  mat4(float* data);
  mat4(float a1, float a2, float a3, float a4,
       float b1, float b2, float b3, float b4,
       float c1, float c2, float c3, float c4,
       float d1, float d2, float d3, float d4);
  mat4 operator+  (const mat4& other) const;
  mat4 operator-  (const mat4& other) const;
  mat4 operator*  (const float& scalar) const;
  void inverse();
  mat3 reduce();
};

vec3 cross(const vec3& vec_i, const vec3& vec_ii);
mat4 multiply(const mat4& m_i, const mat4& m_ii);

float dot(const vec& vec_i, const vec& vec_ii);
float distance(const vec& vec_i, const vec& vec_ii);
float length(const vec& vec_i);   // OK to give a vec2, vec3, vec4
vec3 normalise(const vec3& vec_i);
vec4 normalise(const vec4& vec_i);
float oriented_angle(const vec3& vec_i, const vec3& vec_ii, const vec3& normal); //returns angle in RADIAN
void unpack(const vec& vec_i, GLfloat arr[]);

mat2 all_zero_mat2(mat2 m = mat2(0,0,
                            0,0));
mat3 all_zero_mat3(mat3 m = mat3(0,0,0,
                            0,0,0,
                            0,0,0));
mat4 all_zero_mat4(mat4 m = mat4(0,0,0,0,
                            0,0,0,0,
                            0,0,0,0,
                            0,0,0,0));

mat2 identity_mat2(mat2 m = mat2(0,1,1,0));
mat3 identity_mat3(mat3 m = mat3(1,0,0,
                            0,1,0,
                            0,0,1));
void identity_mat4(mat4& m);

#endif
