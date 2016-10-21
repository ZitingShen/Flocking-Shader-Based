#include "boid.h"

using namespace std;

BOID* new_boid(){
  BOID* a_boid = (BOID*)malloc(sizeof(BOID));
  a_boid->pos.reset();
  a_boid->velocity.reset();
  a_boid->velocity = SPAWN_VELOCITY;
  a_boid->partner_radius = PARTNER_RADIUS;
  a_boid->wing_rotation = rand()%(2*MAX_WING_ROTATION)
                          - MAX_WING_ROTATION;
  a_boid->flock_index = rand()%(DEFAULT_FLOCK_NUM);

  a_boid->pos = (a_boid->flock_index==0)?SPAWN_POSITION_I:SPAWN_POSITION_II;
  a_boid->wing_rotation_direction = 1;
  return a_boid;
}

BOID* new_boid(vec4 velocity, float radius, vec4 pos){
  BOID* a_boid = (BOID*)malloc(sizeof(BOID));
  a_boid->pos.reset();
  a_boid->velocity.reset();
  a_boid->pos = pos;
  a_boid->velocity = velocity;
  a_boid->partner_radius = radius;
  a_boid->wing_rotation = rand()%(2*MAX_WING_ROTATION)
                          - MAX_WING_ROTATION;
  a_boid->flock_index = rand()%(DEFAULT_FLOCK_NUM);
  a_boid->wing_rotation_direction = 1;
  return a_boid;
}

bool is_partner(BOID* source, BOID* target){
  return source->partner_radius >= distance(source->pos, target->pos);
}

void update_velocity(List* a_flock){
  if (a_flock == NULL || a_flock->length < 2) return;
  NODE* current_boid = a_flock->head;
  NODE* potential_partner;
  vec4 s_modifier(0, 0, 0, 0);
  vec4 a_modifier(0, 0, 0, 0);
  vec4 c_modifier(0, 0, 0, 0);
  vec4 f_modifier(0, 0, 0, 0);
  int num_of_partners;
  int num_of_boids_other_flocks;

  BOID* source = NULL;
  BOID* target = NULL;
  while (current_boid != NULL){
    num_of_partners = 0; //reset for the next boid
    num_of_boids_other_flocks = 0;
    potential_partner = a_flock->head;
    num_of_partners = 0;
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
          s_modifier += source->pos - target->pos;
          a_modifier += target->velocity;
          c_modifier += target->pos;
        } else {
          num_of_boids_other_flocks++;
          f_modifier += source->pos - target->pos;
        }
      }
      potential_partner = potential_partner->next;
    }
    if (num_of_partners != 0) {
      s_modifier = s_modifier*(SEPARATION_WEIGHT/(float)num_of_partners);
      a_modifier = (a_modifier*(1/(float)num_of_partners) - source->velocity)*ALIGNMENT_WEIGHT;
      c_modifier = (c_modifier*(1/(float)num_of_partners) - source->pos)*COHESION_WEIGHT;
      source->velocity += s_modifier + a_modifier + c_modifier;
    }
    if (num_of_boids_other_flocks != 0) {
      f_modifier = f_modifier*(DETERRENCE_WEIGHT/(float)num_of_boids_other_flocks);
      source->velocity += f_modifier;
    }
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
    if (a_boid->wing_rotation > MAX_WING_ROTATION ||
        a_boid->wing_rotation < -MAX_WING_ROTATION)
      a_boid->wing_rotation_direction *= -1;
    a_boid->wing_rotation += a_boid->wing_rotation_direction* WING_ROTATION_PER_FRAME;
    current = current->next;
  }
}

vec4 flock_centroid(List* a_flock){
  if (a_flock == NULL || a_flock->length == 0)
    return vec4(0, 0, 0, 1);
  NODE* current = a_flock->head;
  vec4 centroid(0, 0, 0, 1);
  
  while (current != NULL){
     centroid += ((BOID*)(current->data))->pos;
     current = current->next;
  }
  return centroid*((1.0f/(float)a_flock->length));
}

vec4 mid_point(List* a_flock, GOAL* a_goal){
  if (a_flock == NULL || a_flock->length == 0)
    return vec4(0, 0, 0, 1);
  return (flock_centroid(a_flock)+(a_goal->pos))*(0.5f);
}

vec4 get_u(List* a_flock, GOAL* a_goal){
  if (a_flock == NULL || a_flock->length == 0)
    return vec4(0, 0, 0, 0);
  return (a_goal->pos - flock_centroid(a_flock));
}

float get_d(List* a_flock, GOAL* a_goal){
  if (a_flock == NULL || a_flock->length == 0)
    return 0;
  return distance(flock_centroid(a_flock), a_goal->pos);
}

float flock_radius(List* a_flock){
  if (a_flock == NULL || a_flock->length == 0)
    return 0;
  float max_r = 0;
  float dis   = 0;
  NODE* current = a_flock->head;
  vec4 centroid = flock_centroid(a_flock);
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
  list_delete(a_flock, rand() % a_flock->length);
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

//TODO: redo draw in shader_based
void draw_a_flock(List* a_flock){
  if (a_flock == NULL) return;
  NODE* current = NULL;
  BOID* some_boid = NULL;

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, A_BOID);
  

  current = a_flock->head;
  for (int i = 0; i < a_flock->length; i++){

    some_boid = (BOID*)(current->data);
    vec3 velocity3 = normalise(reduce(some_boid->velocity));
    vec3 initial3 = normalise(reduce(SPAWN_VELOCITY));
    vec3 rotate_normal = normalise(cross(velocity3, initial3));
    float angle = oriented_angle(initial3, velocity3, 
                                rotate_normal)*RADIAN_TO_DEGREE;
    float shades_angle = oriented_angle(initial3, velocity3, 
                                       vec3(0, 0, 1))*RADIAN_TO_DEGREE;

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, (some_boid->flock_index==0)?A_BOID_COLORS:ANOTHER_BOID_COLORS);

    glPushMatrix(); // tranformation for boids
    glTranslatef(some_boid->pos[0], some_boid->pos[1], some_boid->pos[2]);
    glRotatef(angle, rotate_normal[0], rotate_normal[1], rotate_normal[2]);
    
    glPushMatrix(); // draw left wings
    glRotatef(-some_boid->wing_rotation, 0, 1, 0);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, A_BOID_LEFT);
    glPopMatrix();
    
    glRotatef(some_boid->wing_rotation, 0, 1, 0); // draw right wings
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, A_BOID_RIGHT);  
    glPopMatrix();

    glDisableClientState(GL_COLOR_ARRAY);
    glColor3f(SHADES_COLOR[0], SHADES_COLOR[1], SHADES_COLOR[2]);
    
    glPushMatrix(); // transformation for shades
    glTranslatef(some_boid->pos[0], some_boid->pos[1], 0);
    glRotatef(shades_angle, 0, 0, 1);
    
    glPushMatrix(); // draw left wings
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, A_BOID_LEFT);
    glPopMatrix();
    
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, A_BOID_RIGHT); // draw right wings
    glPopMatrix();

    current = current->next;
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void apply_goal_attraction(List* a_flock, GOAL* a_goal){
  NODE* current=a_flock->head;
  vec4 v_modifier(0, 0, 0, 0);
  while (current!=NULL){
    v_modifier = a_goal->pos - ((BOID*)(current->data))->pos;
    if (length(v_modifier) > MAX_ATTRACTION_INFLUENCE) {
      v_modifier = normalise(v_modifier)*MAX_ATTRACTION_INFLUENCE;
    }
    v_modifier = v_modifier*ATTRACTION_WEIGHT;
    ((BOID*)(current->data))->velocity += v_modifier;
    current = current->next;
  }
}

void print_flock(List* a_flock) {
  vec4 centroid = flock_centroid(a_flock);
  cout << "The flock's centroid: " << centroid[0] << ", " 
  << centroid[1] << ", " << centroid[2] << endl;
  float radius = flock_radius(a_flock);
  cout << "The flock's radius: " << radius << endl;
  cout << endl;
}
