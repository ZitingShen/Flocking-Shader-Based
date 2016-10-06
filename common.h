#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#else
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp> // for rotate
#include <glm/gtx/quaternion.hpp>    // for rotation angle

#endif