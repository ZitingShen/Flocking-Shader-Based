#ifndef MY_MATRIX
#define MY_MATRIX

#ifdef __APPLE__
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#else
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif

#define VEC2 2
#define VEC3 3
#define VEC4 4
#define MAT2 4
#define MAT3 9
#define MAT4 16


/* Data-type and relevant operations
 * - vec2, vec3, vec4, mat2, mat3, mat4
 * – zero, identify, addition, multiplication
 * – dot product, cross product
 * – transpose, inverse, trace, determinant
 */

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
    float determinant();
    vec* transpose();
    vec* inverse();
    float trace();
    vec* operator+  (const vec& other);
    vec* operator-  (const vec& other);
    bool operator== (const vec& other);
    void operator= (const vec& other);
    void operator+= (const vec& other);
    void operator-= (const vec& other);
    void operator++ (); // for doubling all values
    vec* operator*  (const float& scalar);
    float& operator[] (const int index); // mutator
    const float& operator[] (const int index) const; // accessor
    void display(); // column-major display
    vec* promote(bool append_one);
    vec* reduce();
};

class vec2:
public vec{
  public:
  //using vec::vec;
  vec2();
  vec2(float* data);
  vec2(float a, float b);
};

class vec3:
public vec{
  public:
  using vec::vec;
  vec3();
  vec3(float* data);
  vec3(float a, float b, float c);
};

class vec4:
public vec{
  public:
  using vec::vec;
  vec4();
  vec4(float* data);
  vec4(float a, float b, float c, float d);
};

class mat2:
public vec{
  public:
  using vec::vec;
  mat2();
  mat2(float* data);
  mat2(float a, float b, float c, float d);
};

class mat3:
public vec{
  public:
  using vec::vec;
  mat3();
  mat3(float* data);
  mat3(float a1, float a2, float a3,
       float b1, float b2, float b3,
       float c1, float c2, float c3);
};

class mat4:
public vec{
  public:
  using vec::vec;
  mat4();
  mat4(float* data);
  mat4(float a1, float a2, float a3, float a4,
       float b1, float b2, float b3, float b4,
       float c1, float c2, float c3, float c4,
       float d1, float d2, float d3, float d4);
};

vec* get_vec(int width, int height, float* data);
vec* all_zero(int dimension);
vec* identity(int dimension);
vec* dot(const vec& vec_i, const vec& vec_ii);
vec3 cross(const vec& vec_i, const vec& vec_ii);
float distance(const vec& vec_i, const vec& vec_ii);
float length(const vec& vec_i);
vec3 normalise(const vec& vec_i);
void unpack(const vec& vec_i, GLfloat arr[]);

#endif
