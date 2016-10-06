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

typedef struct _vec2{
  float data[VEC2];
} vec2;

typedef struct _vec3{
  float data[VEC3];
} vec3;

typedef struct _vec4{
  float data[VEC4];
} vec4;

typedef struct _mat2{
  float data[MAT2];
} mat2;

typedef struct _mat3{
  float data[MAT3];
} mat3;

typedef struct _mat4{
  float data[MAT4];
} mat4;

template <typename T>
class vec{
  private:
    T* local;
    int width;
    int height;
  public:
    vec();
    /* put immediates in COLUMN-MAJOR order */
    /* using new/delete for memory allocation */
    vec(float a, float b);
    vec(float a, float b, float c);
    vec(float a, float b, float c, float d, bool matrix);
    vec(float a1, float a2, float a3,
        float b1, float b2, float b3,
        float c1, float c2, float c3);
    vec(float a1, float a2, float a3, float a4,
        float b1, float b2, float b3, float b4,
        float c1, float c2, float c3, float c4,
        float d1, float d2, float d3, float d4);
    vec(int width, int height);
    vec(int width, int height, float* data);
    ~vec();

    float determinant();
    T* transpose();
    T* inverse();
    float trace();
    vec operator+  (const vec& other);
    vec operator-  (const vec& other);
    vec operator== (const vec& other);
    vec operator*  (const float& scalar);
    void display();
};

template <typename T>
vec<T>* dot(vec<T>* vec_i, vec<T>* vec_ii);

template <typename T>
vec<T>* cross(vec<T>* vec_i, vec<T>* vec_ii);

template <typename T>
vec<T>* zero(int dimension);

template <typename T>
vec<T>* identity(int dimension);

template <typename T>
vec<T>* promote(vec<T>* original, bool append_one);

template <typename T>
vec<T>* reduce(vec<T>* original);

#endif
