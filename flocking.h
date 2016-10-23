#ifndef FLOCKING_H
#define FLOCKING_H

#include "list.h"
#include "view.h"
#include "boid.h"
#include "flocking.h"
#include "gl_replacement.h"
#include "initshader.h"
#include "common.h"

const GLfloat A_BOID_LEFT[]=
            {0, 0, 0, 1, // position of the centroid
             0, BOID_SIZE*2, 0, 1, // position of the head
             -BOID_SIZE, -BOID_SIZE, 0, 1}; // position of the right vertex

const GLfloat A_BOID_RIGHT[]=
            {0, 0, 0, 1, // position of the centroid
             BOID_SIZE, -BOID_SIZE, 0, 1, // position of the right vertex
	     0, BOID_SIZE*2, 0, 1}; // position of the head

const GLfloat COLOR_I_LEFT[] = {
  1.0, 1.0, 1.0, 
  BOID_COLOUR_FLOCK_I[0], BOID_COLOUR_FLOCK_I[1], BOID_COLOUR_FLOCK_I[2],
  1.0, 1.0, 1.0};

const GLfloat COLOR_I_RIGHT[] = {
  1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
  BOID_COLOUR_FLOCK_I[0], BOID_COLOUR_FLOCK_I[1], BOID_COLOUR_FLOCK_I[2]};

const GLfloat A_SQUARE[][3]= 
            {{0, 0, 0},
            {BG_SQUARE_SIDE, 0, 0},
            {BG_SQUARE_SIDE, BG_SQUARE_SIDE, 0},
            {0, BG_SQUARE_SIDE, 0}};

void init(GLFWwindow* window);
void reshape(GLFWwindow* window, int w, int h);
void framebuffer_resize(GLFWwindow* window, int width, int height);
void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods);
static GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size);
void draw_background();
#endif
