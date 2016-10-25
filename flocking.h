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

// using burgundy for flock I
const vec3 BOID_COLOUR_FLOCK_I(0.474, 0.118, 0.114);
// using aquamarine for flock II
const vec3 BOID_COLOUR_FLOCK_II(0.420, 0.792, 0.886);

const GLfloat COLOR_I_LEFT[] = {
  1.0, 1.0, 1.0, 
  BOID_COLOUR_FLOCK_I[0], BOID_COLOUR_FLOCK_I[1], BOID_COLOUR_FLOCK_I[2],
  1.0, 1.0, 1.0};

const GLfloat COLOR_I_RIGHT[] = {
  1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
  BOID_COLOUR_FLOCK_I[0], BOID_COLOUR_FLOCK_I[1], BOID_COLOUR_FLOCK_I[2]};

const GLfloat COLOR_II_LEFT[] = {
  1.0, 1.0, 1.0, 
  BOID_COLOUR_FLOCK_II[0], BOID_COLOUR_FLOCK_II[1], BOID_COLOUR_FLOCK_II[2],
  1.0, 1.0, 1.0};

const GLfloat COLOR_II_RIGHT[] = {
  1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
  BOID_COLOUR_FLOCK_II[0], BOID_COLOUR_FLOCK_II[1], BOID_COLOUR_FLOCK_II[2]};

const GLfloat A_SQUARE[][3]= 
            {{0, 0, 0},
            {BG_SQUARE_SIDE, 0, 0},
            {BG_SQUARE_SIDE, BG_SQUARE_SIDE, 0},
            {0, BG_SQUARE_SIDE, 0}};

const GLfloat CUBE_VERTICES[][4] = {
                           {-GOAL_SIZE, -GOAL_SIZE, GOAL_SIZE, 1},  {-GOAL_SIZE, GOAL_SIZE, GOAL_SIZE, 1}, 
                           {GOAL_SIZE, GOAL_SIZE, GOAL_SIZE, 1},    {GOAL_SIZE, -GOAL_SIZE, GOAL_SIZE, 1}, 
                           {-GOAL_SIZE, -GOAL_SIZE, -GOAL_SIZE, 1}, {-GOAL_SIZE, GOAL_SIZE, -GOAL_SIZE, 1}, 
                           {GOAL_SIZE, GOAL_SIZE, -GOAL_SIZE, 1},   {GOAL_SIZE, -GOAL_SIZE, -GOAL_SIZE, 1}};

const GLfloat CUBE_COLORS[][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, 
                                  {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, 
                                  {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, 
                                  {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};
const GLubyte CUBE_INDICES[36] = {0, 3, 2,
                                0, 2, 1,
                                2, 3, 7,
                                2, 7, 6,
                                0, 4, 7,
                                0, 7, 3,
                                1, 2, 6,
                                1, 6, 5,
                                4, 5, 6,
                                4, 6, 7,
                                0, 1, 5,
                                0, 5, 4};

void init(GLFWwindow* window);
void reshape(GLFWwindow* window, int w, int h);
void framebuffer_resize(GLFWwindow* window, int width, int height);
void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods);
static GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size);
void draw_background();
void draw_a_flock();
void draw_a_goal();
#endif
