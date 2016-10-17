#ifndef GL_REPLACEMENT_H
#define GL_REPLACEMENT_H

#ifdef __APPLE__
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#else
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>
#include "common.h"

void myLookAt(GLfloat eye[3], GLfloat center[3], GLfloat up[3]);
void myPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);
void myTranslate(GLfloat x, GLfloat y, GLfloat z);
void myRotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void myScale(GLfloat x, GLfloat y, GLfloat z);
void myMultMatrix(mat4 trans_matrix);

#endif
