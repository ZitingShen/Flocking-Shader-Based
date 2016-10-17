#ifndef FLOCKING_H
#define FLOCKING_H

#include "list.h"
#include "view.h"
#include "boid.h"
#include "flocking.h"
#include "gl_replacement.h"
//#include "obstacle.h"
#include "common.h"

void init();
void reshape(GLFWwindow* window, int w, int h);
void framebuffer_resize(GLFWwindow* window, int width, int height);
void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods);
#endif
