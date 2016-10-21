#ifndef BOID_H 
#define BOID_H

#include "list.h"
#include "goal.h"
#include "common.h"
#include "gl_replacement.h"
#include <time.h>

const vec4 SPAWN_POSITION_I(1000.0, 1000.0, 1500.0, 1);
const vec4 SPAWN_POSITION_II(-1000.0, -1000.0, 500.0, 1);
 //initial speed parallel with y-axis
const vec4 SPAWN_VELOCITY(0, 0.01, 0, 0);
const vec4 EMPTY_POS(0, 0, 0, 1);

// using burgundy for flock I
const vec3 BOID_COLOUR_FLOCK_I(0.474, 0.118, 0.114);
// using aquamarine for flock II
const vec3 BOID_COLOUR_FLOCK_II(0.420, 0.792, 0.886);
const vec3 SHADES_COLOR (0.182, 0.008, 0.235);

const vec4 A_BOID[] =
            {vec4(0, 0, 0, 1), // position of the centroid
             vec4(0, BOID_SIZE*2, 0, 1), // position of the head
             vec4(-BOID_SIZE, -BOID_SIZE, 0, 1), // position of the left vertex
             vec4(BOID_SIZE, -BOID_SIZE, 0, 1)}; // position of the right vertex

const vec3 A_BOID_COLORS[] = {
  vec3(1.0, 1.0, 1.0), 
  vec3(BOID_COLOUR_FLOCK_I[0], BOID_COLOUR_FLOCK_I[1], BOID_COLOUR_FLOCK_I[2]),
  vec3(1.0, 1.0, 1.0), 
  vec3(1.0, 1.0, 1.0)};

const vec3 ANOTHER_BOID_COLORS[] = {
  vec3(1.0, 1.0, 1.0), 
  vec3(BOID_COLOUR_FLOCK_II[0], BOID_COLOUR_FLOCK_II[1], BOID_COLOUR_FLOCK_II[2]),
  vec3(1.0, 1.0, 1.0), 
  vec3(1.0, 1.0, 1.0)};

const vec3 centroid_init(0, 0, 0);
const vec3 head_init(0, BOID_SIZE*2, 0);
const vec3 left_init(-BOID_SIZE, -BOID_SIZE, 0);
const vec3 right_init(BOID_SIZE, -BOID_SIZE, 0);

const GLubyte A_BOID_LEFT[3] = {0, 1, 2};
const GLubyte A_BOID_RIGHT[3] = {0, 3, 1}; //drawing two triangles;

typedef struct _boid{
  GLfloat wing_rotation;          // for flapping extra credit
  int wing_rotation_direction;    // 1 for downwards, 0 for upwards
  int flock_index;  
  vec4 pos;
  vec4 velocity;             // also determines PA direction; and the degrees of rotation   
  float partner_radius;           // the radius within which it looks for partners
} BOID;

typedef struct _predator{
  vec4 pos;
  vec4 velocity;
  float deterrence_range;
  float attack_range;
} PREDATOR;

BOID* new_boid();
BOID* new_boid(vec4 velocity, float radius, vec4 pos);

bool is_partner(BOID* source, BOID* target);
void update_velocity(List* a_flock);
void update_pos(List* a_flock);
void update_wing_rotation(List* a_flock);

vec4 get_current_pos(BOID* a_boid);
vec4 flock_centroid(List* a_flock);
vec4 mid_point(List* a_flock, GOAL* a_goal);
vec4 get_u(List* a_flock, GOAL* a_goal);
float get_d(List* a_flock, GOAL* a_goal);
float flock_radius(List* a_flock);

void add_a_boid(List* a_flock);
void remove_a_boid(List* a_flock);

void init_a_flock(List* a_flock);

void apply_goal_attraction(List* a_flock, GOAL* a_goal);
void draw_a_flock(List* a_flock, GLfloat mv_mat[]);

void print_flock(List* a_flock);
//void update_rotation(BOID* a_boid);
/* To DO */
void apply_predator_deterrence(List* a_flock, PREDATOR* a_predator, float p_w);
#endif
