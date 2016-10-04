#ifndef MY_MATRIX
#define MY_MATRIX


  typedef struct _vec2{
    float data[2];
  } vec2;

  typedef struct _vec3{
    float data[3];
  } vec3;

  typedef struct _vec4{
    float data[4];
  } vec4;

  typedef struct _mat2{
    float data[4];
  } mat2;

  typedef struct _mat3{
    float data[9];
  } mat3;

  typedef struct _mat4{
    float data[16];
  } mat4;

  template <typename T>
  class vec{
    private:
      T* local;
      int width;
      int height;
    public:
      vec();
      vec(int width, int height);
      vec(int width, int height, float* data);
      vec(float a, float b, float c, float d);
      ~vec();

      float determinant();
      T* transpose();
      T* inverse();
      float trace();
      vec operator+  (const vec& other);
      vec operator-  (const vec& other);
      vec operator== (const vec& other);
      vec operator*  (const float& scalar);
  };
/*
 * - vec2, vec3, vec4, mat2, mat3, mat4
 * – zero, identify, addition, multiplication
 * – dot product, cross product
 * – transpose, inverse, trace, determinant
 */
#endif
