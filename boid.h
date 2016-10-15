#ifndef BOID_H 
#define BOID_H

#include "list.h"
#include "goal.h"
#include "common.h"
#include <time.h>

const vec<vec4> SPAWN_POSITION_I  = vec<vec4>(1000.0,1000.0,1500.0,1);
const vec<vec4> SPAWN_POSITION_II = vec<vec4>(-1000.0,-1000.0, 500.0, 1);
 //initial speed parallel with y-axis
const vec<vec4> SPAWN_VELOCITY = vec<vec4>(0,0.01,0,0);

// using burgundy for flock I
const vec<vec3> BOID_COLOUR_FLOCK_I = vec<vec3>(0.474, 0.118, 0.114);
// using aquamarine for flock II
const vec<vec3> BOID_COLOUR_FLOCK_II = vec<vec3>(0.420, 0.792, 0.886);
const vec<vec3> SHADES_COLOR = vec<vec3>(0.182, 0.008, 0.235);

const vec<vec4> A_BOID[] =
            {vec<vec4>(0, 0, 0, 1), // position of the centroid
             vec<vec4>(0, BOID_SIZE*2, 0, 1), // position of the head
             vec<vec4>(-BOID_SIZE, -BOID_SIZE, 0, 1), // position of the left vertex
             vec<vec4>((BOID_SIZE, -BOID_SIZE, 0)}; // position of the right vertex

const vec<vec3> A_BOID_COLORS[] = {
  vec<vec3>(1.0, 1.0, 1.0), 
  vec<vec3>(BOID_COLOUR_FLOCK_I[0], BOID_COLOUR_FLOCK_I[1], BOID_COLOUR_FLOCK_I[2]),
  vec<vec3>(1.0, 1.0, 1.0), 
  vec<vec3>(1.0, 1.0, 1.0)};

const vec<vec3> ANOTHER_BOID_COLORS[] = {
  vec<vec3>(1.0, 1.0, 1.0), 
  vec<vec3>(BOID_COLOUR_FLOCK_II[0], BOID_COLOUR_FLOCK_II[1], BOID_COLOUR_FLOCK_II[2]),
  vec<vec3>(1.0, 1.0, 1.0), 
  vec<vec3>(1.0, 1.0, 1.0)};

const glm::vec3 centroid_init = glm::vec3(0,0,0);
const glm::vec3 head_init = glm::vec3(0,BOID_SIZE*2,0);
const glm::vec3 left_init = glm::vec3(-BOID_SIZE,-BOID_SIZE,0);
const glm::vec3 right_init = glm::vec3(BOID_SIZE,-BOID_SIZE,0);

const GLubyte A_BOID_LEFT[3] = {0, 1, 2};
const GLubyte A_BOID_RIGHT[3] = {0, 3, 1}; //drawing two triangles;

typedef struct _boid{
  GLfloat wing_rotation;          // for flapping extra credit
  int wing_rotation_direction;    // 1 for downwards, 0 for upwards
  int flock_index;  
  glm::vec4 pos;
  glm::vec4 velocity;             // also determines PA direction; and the degrees of rotation   
  float partner_radius;           // the radius within which it looks for partners
} BOID;

typedef struct _predator{
  glm::vec4 pos;
  glm::vec4 velocity;
  float deterrence_range;
  float attack_range;
} PREDATOR;

BOID* new_boid(glm::vec4 velocity, float radius);
BOID* new_boid(glm::vec4 velocity, float radius, glm::vec4 pos);

bool is_partner(BOID* source, BOID* target);
void update_velocity(List* a_flock);
void update_pos(List* a_flock);
void update_wing_rotation(List* a_flock);

glm::vec4 get_current_pos(BOID* a_boid);
glm::vec4 flock_centroid(List* a_flock);
glm::vec4 mid_point(List* a_flock, GOAL* a_goal);
glm::vec4 get_u(List* a_flock, GOAL* a_goal);
float get_d(List* a_flock, GOAL* a_goal);
float flock_radius(List* a_flock);

void add_a_boid(List* a_flock);
void remove_a_boid(List* a_flock);

void init_a_flock(List* a_flock);

void apply_goal_attraction(List* a_flock, GOAL* a_goal);
void draw_a_flock(List* a_flock);

void print_flock(List* a_flock);
//void update_rotation(BOID* a_boid);
/* To DO */
void apply_predator_deterrence(List* a_flock, PREDATOR* a_predator, float p_w);
#endif
