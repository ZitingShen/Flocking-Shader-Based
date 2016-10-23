#include "goal.h"

using namespace std;

GOAL* new_goal(){
  GOAL* a_goal = (GOAL*)malloc(sizeof(GOAL));
  a_goal->pos.reset();
  a_goal->velocity.reset();
  a_goal->pos = DEFAULT_GOAL_SPAWN_POSITION;
  a_goal->velocity = DEFAULT_GOAL_SPAWN_VELOCITY;
  a_goal->MOVE_ALONG_X_NEGATIVE = false;
  a_goal->MOVE_ALONG_X_POSITIVE = false;
  a_goal->MOVE_ALONG_Y_NEGATIVE = false;
  a_goal->MOVE_ALONG_Y_POSITIVE = false;
  a_goal->ACCELERATE = false;
  a_goal->DECELERATE = false;
  return a_goal;
}

void update_goal_velocity(GOAL* a_goal){
  //float temp_z;
  if (a_goal->MOVE_ALONG_X_POSITIVE){
    if (a_goal->velocity[0] < 0){
      a_goal->velocity[0] = -a_goal->velocity[0];
    }
    a_goal->velocity[0] += DEFAULT_ACCELERATION_MARGIN;
  }

  if (a_goal->MOVE_ALONG_X_NEGATIVE){
    if (a_goal->velocity[0] > 0){
      a_goal->velocity[0] = -a_goal->velocity[0];
    }
    a_goal->velocity[0] -= DEFAULT_ACCELERATION_MARGIN;
  }

  if (a_goal->MOVE_ALONG_Y_POSITIVE){
    if (a_goal->velocity[1] < 0){
      a_goal->velocity[1] = -a_goal->velocity[1];
    }
    a_goal->velocity[1] += DEFAULT_ACCELERATION_MARGIN;
  }

  if (a_goal->MOVE_ALONG_Y_NEGATIVE){
    if (a_goal->velocity[1] > 0){
      a_goal->velocity[1] = -a_goal->velocity[1];
    }
    a_goal->velocity[1] -= DEFAULT_ACCELERATION_MARGIN;
  }

  if (a_goal->ACCELERATE){
    a_goal->velocity = a_goal->velocity*float(1 + DEFAULT_ACCELERATION_FACTOR);
    a_goal->velocity[2] = 0.01; // do not accerlate on Z
  }

  if (a_goal->DECELERATE){
    a_goal->velocity =  a_goal->velocity*float(1 - DEFAULT_ACCELERATION_FACTOR);
    a_goal->velocity[2] = 0.01; // do not accerlate on Z
  }
}

void update_goal_pos(GOAL* a_goal){
  a_goal->pos += a_goal->velocity;
}

void teleport_goal(GOAL* a_goal){
  srand(time(NULL));
  a_goal->pos[0] += rand() % 5000 - 10000;
  srand(time(NULL));
  a_goal->pos[1] += rand() % 5000 - 10000;
}

void draw_a_goal(GOAL* a_goal, GLfloat mv_mat[]){
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, CUBE_VERTICES);
  glColorPointer(3, GL_FLOAT, 0, CUBE_COLORS);
  GLfloat mv_mat_copy[16];
  memcpy(mv_mat_copy, mv_mat, sizeof(GLfloat)*16);
  myTranslate(mv_mat_copy, a_goal->pos[0], a_goal->pos[1], a_goal->pos[2]);
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, CUBE_INDICES);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void print_goal(GOAL* a_goal) {
  cout << "The goal's position: " << a_goal->pos[0] << ", "
  << a_goal->pos[1] << ", " << a_goal->pos[2] << endl;
  cout << "The goal's velocity: " << a_goal->velocity[0] << ", "
  << a_goal->velocity[1] << ", " << a_goal->velocity[2] << endl;
  cout << endl;
}
