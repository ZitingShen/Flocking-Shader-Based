#ifndef MY_MATRIX
#define MY_MATRIX

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
  friend vec dot(vec* vec_i, vec* vec_ii);
  friend vec cross(vec* vec_i, vec* vec_ii);
  friend vec zero(int dimension);
  friend vec identity(int dimension);
  friend vec promote(vec* original, bool append_one);
  friend vec reduce(vec* original);

  protected:
    float* data;
    int width;
    int height;
  public:
    /* put immediates in COLUMN-MAJOR order */
    /* using new/delete for memory allocation */
    vec();
    vec(int width, int height); // returns a all-zero vec/mat
    vec(int width, int height, float* data);
    ~vec();

    float determinant();
    vec* transpose();
    vec* inverse();
    float trace();
    vec operator+  (const vec& other);
    vec operator-  (const vec& other);
    bool operator== (const vec& other);
    vec operator*  (const float& scalar);
    float& operator[] (const int index); // for assigning
    const float& operator[] (const int index) const; // for accessing
    void display();
};

class vec2:
public vec{
  public:
  using vec::vec;
  vec2(float a, float b);
  ~vec2();
};

class vec3:
public vec{
  public:
  using vec::vec;
  vec3(float a, float b, float c);
  ~vec3();
};

class vec4:
public vec{
  public:
  using vec::vec;
  vec4(float a, float b, float c, float d);
  ~vec4();
};

class mat2:
public vec{
  public:
  using vec::vec;
  mat2(float a, float b, float c, float d);
  ~mat2();
};

class mat3:
public vec{
  public:
  using vec::vec;
  mat3(float a1, float a2, float a3,
       float b1, float b2, float b3,
       float c1, float c2, float c3);
  ~mat3();
};

class mat4:
public vec{
  public:
  using vec::vec;
  mat4(float a1, float a2, float a3, float a4,
       float b1, float b2, float b3, float b4,
       float c1, float c2, float c3, float c4,
       float d1, float d2, float d3, float d4);
  ~mat4();
};
#endif
