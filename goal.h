#ifndef GOAL_H
#define GOAL_H

#include "common.h"
#include "gl_replacement.h"

const vec4 DEFAULT_GOAL_SPAWN_VELOCITY(10, 10, 0.01, 0); // initiated with a positive speed on Z-axis
const vec4 DEFAULT_GOAL_SPAWN_POSITION(0, 5000, 3000, 1);

const GLfloat CUBE_VERTICES[][3] = {
                           {-GOAL_SIZE, -GOAL_SIZE, GOAL_SIZE},  {-GOAL_SIZE, GOAL_SIZE, GOAL_SIZE}, 
                           {GOAL_SIZE, GOAL_SIZE, GOAL_SIZE},    {GOAL_SIZE, -GOAL_SIZE, GOAL_SIZE}, 
                           {-GOAL_SIZE, -GOAL_SIZE, -GOAL_SIZE}, {-GOAL_SIZE, GOAL_SIZE, -GOAL_SIZE}, 
                           {GOAL_SIZE, GOAL_SIZE, -GOAL_SIZE},   {GOAL_SIZE, -GOAL_SIZE, -GOAL_SIZE}};

const GLfloat CUBE_COLORS[][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, 
                                  {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, 
                                  {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, 
                                  {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};
const GLubyte CUBE_INDICES[24] = {0, 3, 2, 1,
                                  2, 3, 7, 6,
                                  0, 4, 7, 3,
                                  1, 2, 6, 5,
                                  4, 5, 6, 7,
                                  0, 1, 5, 4};

typedef struct _goal{
  vec4 pos;
  vec4 velocity;
  bool MOVE_ALONG_X_POSITIVE;  // to control goal
  bool MOVE_ALONG_X_NEGATIVE;
  bool MOVE_ALONG_Y_POSITIVE;
  bool MOVE_ALONG_Y_NEGATIVE;
  bool ACCELERATE;
  bool DECELERATE;
} GOAL;


GOAL* new_goal();
void update_goal_velocity(GOAL* a_goal);
void update_goal_pos(GOAL* a_goal);
void draw_a_goal(GOAL* a_goal, GLfloat mv_mat[]);
void print_goal(GOAL* a_goal);
#endif
