#include "boid.h"
#include <algorithm>

using namespace std;

BOID* new_boid(){
  BOID* a_boid = (BOID*)malloc(sizeof(BOID));
  a_boid->pos.reset();
  a_boid->velocity.reset();
  a_boid->velocity = SPAWN_VELOCITY;
  a_boid->partner_radius = PARTNER_RADIUS;
  a_boid->wing_rotation = rand()%(2*MAX_WING_ROTATION)
                          - MAX_WING_ROTATION;
  a_boid->wing_rotation *= DEGREE_TO_RADIAN;
  a_boid->flock_index = rand()%(DEFAULT_FLOCK_NUM);

  a_boid->pos = (a_boid->flock_index==0)?SPAWN_POSITION_I:SPAWN_POSITION_II;
  a_boid->wing_rotation_direction = 1;
  return a_boid;
}

BOID* new_boid(const vec4& velocity, float radius, const vec4& pos){
  BOID* a_boid = (BOID*)malloc(sizeof(BOID));
  a_boid->pos.reset();
  a_boid->velocity.reset();
  a_boid->pos = pos;
  a_boid->velocity = velocity;
  a_boid->partner_radius = radius;
  a_boid->wing_rotation = rand()%(2*MAX_WING_ROTATION)
                          - MAX_WING_ROTATION;
  a_boid->wing_rotation *= DEGREE_TO_RADIAN;
  a_boid->flock_index = rand()%(DEFAULT_FLOCK_NUM);
  a_boid->wing_rotation_direction = 1;
  return a_boid;
}

bool is_partner(BOID* source, BOID* target){
  return source->partner_radius >= distance(source->pos, target->pos);
}

void update_velocity(List* a_flock, GOAL* a_goal){
  if (a_flock == NULL || a_flock->length < 2) return;
  NODE* current_boid = a_flock->head;
  NODE* potential_partner;
  vec4 s_modifier(0, 0, 0, 0);
  vec4 a_modifier(0, 0, 0, 0);
  vec4 c_modifier(0, 0, 0, 0);
  vec4 f_modifier(0, 0, 0, 0);
  vec4 flock_center;
  int num_of_partners;
  int num_of_boids_other_flocks;
  bool close_to_goal = false;
  float dis_to_partner;

  BOID* source = NULL;
  BOID* target = NULL;
  while (current_boid != NULL){
    num_of_partners = 0; //reset for the next boid
    num_of_boids_other_flocks = 0;
    potential_partner = a_flock->head;
    num_of_partners = 0;
    close_to_goal = length(a_goal->pos - ((BOID*)(current_boid->data))->pos) < APPROACHING_GOAL;
    while (potential_partner != NULL){
      if (potential_partner == current_boid) {
        potential_partner = potential_partner->next;
        continue;
      }
      source = (BOID*)(current_boid->data);
      target = (BOID*)(potential_partner->data);
      if (is_partner(source, target)){
        if (target->flock_index == source->flock_index) {
          num_of_partners++;
          dis_to_partner = distance(source->pos, target->pos);
          if (dis_to_partner > SCATTERING){
            s_modifier += (source->pos - target->pos) * 0.95;
            a_modifier += target->velocity;
            c_modifier += target->pos * 1.05;
          }else if (dis_to_partner < COLLIDING){
            s_modifier += (source->pos - target->pos) * 1.05;
            a_modifier += target->velocity;
            c_modifier += target->pos * 0.95;
          }else{
            s_modifier += source->pos - target->pos;
            a_modifier += target->velocity;
            c_modifier += target->pos;
          }
          if(close_to_goal){// if close to goal, scatter
            //cout << "now near goal" << endl;
            s_modifier = s_modifier * 1.5;
            a_modifier = a_modifier * 0.8;
          } 
        } else {
          num_of_boids_other_flocks++;
          f_modifier += source->pos - target->pos;
        }
      }
      potential_partner = potential_partner->next;
    }
    if (num_of_partners != 0) {
      //cout << "num_of_partners = " << num_of_partners << endl;
      s_modifier = s_modifier*(SEPARATION_WEIGHT/(float)num_of_partners);
      a_modifier = (a_modifier*(1/(float)num_of_partners) - source->velocity)*ALIGNMENT_WEIGHT;
      c_modifier = (c_modifier*(1/(float)num_of_partners) - source->pos)*COHESION_WEIGHT;
      source->velocity += s_modifier + a_modifier + c_modifier;
    }
    if (num_of_boids_other_flocks != 0) {
      f_modifier = f_modifier*(DETERRENCE_WEIGHT/(float)num_of_boids_other_flocks);
      source->velocity += f_modifier;
    }

    flock_center = flock_centroid(a_flock, source->flock_index);
    if (distance(source->pos, flock_center) > FLOCK_RAIUS_CAP){
      source->velocity += (flock_center - source->pos) * STAY_IN_FLOCK_WEIGHT;
    }

    source->velocity[2] = max(-Z_SPEED_CAP, min(source->velocity[2], Z_SPEED_CAP));

    current_boid = current_boid->next;
  }
}

void update_pos(List* a_flock){
  if (a_flock == NULL || a_flock->length == 0) return;
  BOID* a_boid;
  NODE* current = a_flock->head;
  while (current != NULL){
    a_boid = (BOID*)(current->data);
    a_boid->pos += a_boid->velocity;
    current = current->next;
  }
}

void update_wing_rotation(List* a_flock){
  if (a_flock == NULL || a_flock->length == 0) return;
  BOID* a_boid;
  NODE* current = a_flock->head;
  while (current != NULL){
    a_boid = (BOID*)(current->data);
    if (a_boid->wing_rotation > MAX_WING_ROTATION*DEGREE_TO_RADIAN ||
        a_boid->wing_rotation < -MAX_WING_ROTATION*DEGREE_TO_RADIAN)
      a_boid->wing_rotation_direction *= -1;
    a_boid->wing_rotation += a_boid->wing_rotation_direction* WING_ROTATION_PER_FRAME;
    current = current->next;
  }
}

vec4 flock_centroid(List* a_flock, int flock_index){
  if (a_flock == NULL || a_flock->length == 0)
    return vec4(0, 0, 0, 1);
  NODE* current = a_flock->head;
  vec4 centroid(0, 0, 0, 1);
  
  int counter = 0;
  while (current != NULL){
    if (((BOID*)(current->data))->flock_index != flock_index) {
      current = current->next;
      continue;
    }
    centroid += ((BOID*)(current->data))->pos;
    counter++;
    current = current->next;
  }
  return centroid*(1.0f/counter);
}

vec4 mid_point(List* a_flock, GOAL* a_goal, int flock_index){
  if (a_flock == NULL || a_flock->length == 0)
    return vec4(0, 0, 0, 1);
  return (flock_centroid(a_flock, flock_index)+(a_goal->pos))*(0.5f);
}

vec4 get_u(List* a_flock, GOAL* a_goal, int flock_index){
  if (a_flock == NULL || a_flock->length == 0)
    return vec4(0, 0, 0, 0);
  return (a_goal->pos - flock_centroid(a_flock, flock_index));
}

float get_d(List* a_flock, GOAL* a_goal, int flock_index){
  if (a_flock == NULL || a_flock->length == 0)
    return 0;
  return distance(flock_centroid(a_flock, flock_index), a_goal->pos);
}

float flock_radius(List* a_flock, int flock_index){
  if (a_flock == NULL || a_flock->length == 0)
    return 0;
  float max_r = 0;
  float dis   = 0;
  NODE* current = a_flock->head;
  vec4 centroid = flock_centroid(a_flock, flock_index);
  while (current != NULL){
    dis = distance(((BOID*) (current->data))->pos, centroid);
    max_r = max_r < dis ? dis : max_r;
    current = current->next;
  }
  return max_r;
}

void add_a_boid(List* a_flock){
  if (a_flock == NULL){return;}  // use init_a_flock to create a new flock
  int default_cube_length = PARTNER_RADIUS*sqrt(2);
  int half_cube_length    = default_cube_length/2;
  vec4 pos;
  if (a_flock->length == 0) {
    vec4 pos;
    pos[0] = (rand() % default_cube_length) - half_cube_length;
    pos[1] = (rand() % default_cube_length) - half_cube_length;
    pos[2] = (rand() % default_cube_length) - half_cube_length;
    pos[3] = 1;
    list_insert(a_flock, new_boid(SPAWN_VELOCITY, PARTNER_RADIUS, pos), 0);
    return;
  }

  BOID* target = (BOID*)list_get(a_flock, rand() % a_flock->length);
  // spawning within the partner radius of the target
  pos[0] = target->pos[0] + (rand() % default_cube_length) - half_cube_length;
  pos[1] = target->pos[1] + (rand() % default_cube_length) - half_cube_length;
  pos[2] = target->pos[2] + (rand() % default_cube_length) - half_cube_length;
  pos[3] = 1;

  list_insert(a_flock, new_boid(target->velocity, PARTNER_RADIUS, pos), 0);
}

void remove_a_boid(List* a_flock){
  if (a_flock == NULL || a_flock->length == 0) return; //nothing to remove
  int index = rand() % a_flock->length;
  BOID* a_boid = (BOID*) list_get(a_flock, index);
  delete[] a_boid->pos.data;
  delete[] a_boid->velocity.data;
  list_delete(a_flock, index);
}

void init_a_flock(List* a_flock){
  int default_cube_length = SPAWN_CUBE_LENGTH*sqrt(2);
  int half_cube_length = default_cube_length/2;

  for (int i = 0; i < DEFAULT_FLOCK_SIZE; i++){
    BOID* a_boid= new_boid();
    a_boid->pos[0] += (rand() % default_cube_length) - half_cube_length;
    a_boid->pos[1] += (rand() % default_cube_length) - half_cube_length;
    a_boid->pos[2] += (rand() % default_cube_length) - half_cube_length;
    list_insert(a_flock, a_boid, 0);
  }
}

void draw_a_flock(List* a_flock, GLfloat mv_mat[]){
  /*
  GLfloat mv_mat_copy[16];
  GLfloat mv_mat_copy2[16];
  GLfloat mv_mat_copy3[16];

  if (a_flock == NULL) return;
  NODE* current = NULL;
  BOID* some_boid = NULL;

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(4, GL_FLOAT, 0, A_BOID_LEFT);
  current = a_flock->head;
  for (int i = 0; i < a_flock->length; i++){

    some_boid = (BOID*)(current->data);
    vec3 velocity3 = normalise(reduce(some_boid->velocity));
    vec3 initial3 = normalise(reduce(SPAWN_VELOCITY));
    vec3 rotate_normal = normalise(cross(velocity3, initial3));
    float angle = oriented_angle(initial3, velocity3, 
                                rotate_normal);
    float shades_angle = oriented_angle(initial3, velocity3, 
                                       vec3(0, 0, 1));

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, (some_boid->flock_index==0)?COLOR_I_LEFT:ANOTHER_BOID_COLORS);

    memcpy(mv_mat_copy, mv_mat, sizeof(GLfloat)*16);
    myTranslate(mv_mat_copy, some_boid->pos[0], some_boid->pos[1], some_boid->pos[2]);
    myRotate(mv_mat_copy, angle, rotate_normal[0], rotate_normal[1], rotate_normal[2]);

    memcpy(mv_mat_copy2, mv_mat_copy, sizeof(GLfloat)*16);
    myRotate(mv_mat_copy2, -some_boid->wing_rotation, 0, 1, 0);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, A_BOID_LEFT);

    memcpy(mv_mat_copy2, mv_mat_copy, sizeof(GLfloat)*16);
    myRotate(mv_mat_copy2, some_boid->wing_rotation, 0, 1, 0); // draw right wings
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, A_BOID_RIGHT);  

    glDisableClientState(GL_COLOR_ARRAY);
    glColor3f(SHADES_COLOR[0], SHADES_COLOR[1], SHADES_COLOR[2]);
    
    memcpy(mv_mat_copy3, mv_mat, sizeof(GLfloat)*16);
    myTranslate(mv_mat_copy3, some_boid->pos[0], some_boid->pos[1], 0);
    myRotate(mv_mat_copy3, shades_angle, 0, 0, 1);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, A_BOID_LEFT);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, A_BOID_RIGHT); // draw right wings

    current = current->next;
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  */
}

void apply_goal_attraction(List* a_flock, GOAL* a_goal){
  NODE* current=a_flock->head;
  vec4 v_modifier(0, 0, 0, 0);
  float dis_to_goal;
  float max_attraction;
  BOID* a_boid = NULL;
  while (current!=NULL){
    a_boid = (BOID*)(current->data);
    v_modifier = a_goal->pos - a_boid->pos;
    dis_to_goal = length(v_modifier);
    max_attraction = 0.6*length(a_boid->velocity);
    if (APPROACHING_GOAL<dis_to_goal){ // not near the goal
      if (length(v_modifier) > max_attraction) {
        //cout << "exceed max attraction " << endl;
        v_modifier = normalise(v_modifier)*max_attraction;
      }
      v_modifier = v_modifier*ATTRACTION_WEIGHT;
      a_boid->velocity += v_modifier;
    }else{ // near goal scenario
      /* Let's slow down */
      if (length(a_boid->velocity) > 3.0*length(a_goal->velocity)){
        //cout << "slowing down" << endl;
        a_boid->velocity = a_boid->velocity * 0.99;
      }
    }
    if (length(a_boid->velocity) > 4.0*length(a_goal->velocity)){
      //cout << "applying absolute cap" << endl;
      if(length(a_boid->velocity) > BOID_SPEED_FLOOR){
        a_boid->velocity = normalise(a_boid->velocity) * 4.0*length(a_goal->velocity);
      }
    }
    current = current->next; 
  }
}

void print_flock(List* a_flock) {
  for (int i = 0; i < DEFAULT_FLOCK_NUM; i++) {
    vec4 centroid = flock_centroid(a_flock, i);
    cout << "Flock" << i << "'s centroid: " << centroid[0] << ", " 
    << centroid[1] << ", " << centroid[2] << endl;
    float radius = flock_radius(a_flock, i);
    cout << "Flock" << i << "'s radius: " << radius << endl;
    cout << endl;
  }
}

PREDATOR* create_a_predator(List* a_flock, GOAL* a_goal, bool& guardian){
  PREDATOR* a_predator = new PREDATOR;
  a_predator->pos = (a_goal->pos + (flock_centroid(a_flock, 0) + flock_centroid(a_flock, 1)) * 0.5) * 0.5;
  a_predator->velocity = a_goal->velocity;
  a_predator->deterrence_range = 1000;
  guardian = true; // enable predator
  return a_predator;
}

void draw_predator(PREDATOR* a_predator, bool& guardian){
  if (!guardian){
    return;
  }
}

void move_predator(PREDATOR* a_predator, GOAL* a_goal){ // orbiting the goal
  vec4 acceleration = (a_goal->pos - a_predator->pos) * 0.1;
  a_predator->velocity += acceleration;
  a_predator->pos += a_predator->velocity;
}

void apply_predator_deterrence(List* a_flock, PREDATOR* a_predator, bool& guardian){
  if (!guardian){
    return;
  }
  NODE* current=a_flock->head;
  BOID* a_boid = NULL;
  vec4 dis_to_predator;
  while (current!=NULL){
    a_boid = (BOID*)current->data;
    if (distance(a_boid->pos, a_predator->pos) < a_predator->deterrence_range){
      dis_to_predator = a_boid->pos - a_predator->pos;
      a_boid->velocity += dis_to_predator * DETERRENCE_WEIGHT;
    }
    current = current->next;
  }
}

void delete_predator(PREDATOR* a_predator, bool& guardian){
  guardian = false;
  delete a_predator;
}
