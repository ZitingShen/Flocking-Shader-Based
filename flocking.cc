#include "flocking.h"

List* A_FLOCK = NULL;
GOAL* A_GOAL = NULL;

int IS_PAUSED = GLFW_FALSE;
int PAUSE_TIME = 0;
viewMode VIEW_MODE = DEFAULT;
int WIDTH, HEIGHT;
GLfloat SQUARES_GREY[BG_GREY_NUM*16];
GLfloat SQUARES_BLACK[BG_BLACK_NUM*16];

GLfloat MV_MAT[] = {1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1};

GLfloat PROJ_MAT[] = {1, 0, 0, 0,
		      0, 1, 0, 0,
		      0, 0, 1, 0,
		      0, 0, 0, 1};
GLuint pos, color, boid_program, shades_program,
       grey_square_program, black_square_program;

GLuint vao_left, vao_right,
       vbo_left, vbo_right,
       vbo_color_i_left, vbo_color_i_right,
       vbo_color_ii_left, vbo_color_ii_right,
       mv, proj;

GLuint shades_vao_left, shades_vao_right,
       shades_mv, shades_proj;

GLuint vao_grey, vao_black,
       vbo_square,
       mv_grey, mv_black,
       proj_grey, proj_black;

GLuint vao_goal, vbo_goal, vbo_goal_color, vbo_goal_indices;

int main(){
  if (!glfwInit ()) {
    std::cerr << "ERROR: could not start GLFW3" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* window = glfwCreateWindow(500, 500, "Flocking", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetWindowPos(window, 100, 0);
  glfwMakeContextCurrent (window);

  glewExperimental = GL_TRUE;
  glewInit();
  init(window);

  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, reshape);
  glfwSetKeyCallback(window, keyboard);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize);
  
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();

    if(!IS_PAUSED || PAUSE_TIME > 0) {
      change_view(MV_MAT, VIEW_MODE, A_FLOCK, A_GOAL);
      update_background(SQUARES_GREY, SQUARES_BLACK, MV_MAT);
      update_goal_velocity(A_GOAL);
      update_goal_pos(A_GOAL);
      update_velocity(A_FLOCK, A_GOAL);
      update_wing_rotation(A_FLOCK);
      apply_goal_attraction(A_FLOCK, A_GOAL);
      update_pos(A_FLOCK);
      if(glfwGetWindowAttrib(window, GLFW_VISIBLE)){
        glGetFloatv(GL_MODELVIEW_MATRIX, MV_MAT);
        draw_background();
        draw_a_flock();
        draw_a_goal();
      }
      glfwSwapBuffers(window);
      if (IS_PAUSED && PAUSE_TIME > 0) {
        print_goal(A_GOAL);
        print_flock(A_FLOCK);
        PAUSE_TIME--;
      }
    }
  }
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void init(GLFWwindow* window) {

  glClearColor(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], 1.0);
  glColor3f(0.0, 0.0, 0.0);
  A_FLOCK = list_new();
  A_GOAL = new_goal();
  srand(time(NULL));
  init_a_flock(A_FLOCK);

  glfwGetWindowSize(window, &WIDTH, &HEIGHT);
  myPerspective(PROJ_MAT, 45, WIDTH*1.0/HEIGHT, CAMERA_NEAR, CAMERA_FAR);

  //shader-based for boids
  vbo_left = make_bo(GL_ARRAY_BUFFER, A_BOID_LEFT, sizeof(A_BOID_LEFT));
  vbo_right = make_bo(GL_ARRAY_BUFFER, A_BOID_RIGHT, sizeof(A_BOID_RIGHT));
  vbo_color_i_left = make_bo(GL_ARRAY_BUFFER, COLOR_I_LEFT,
			     sizeof(COLOR_I_LEFT));
  vbo_color_i_right = make_bo(GL_ARRAY_BUFFER, COLOR_I_RIGHT,
			     sizeof(COLOR_I_RIGHT));
  vbo_color_ii_left = make_bo(GL_ARRAY_BUFFER, COLOR_II_LEFT,
			      sizeof(COLOR_II_LEFT));
  vbo_color_ii_right = make_bo(GL_ARRAY_BUFFER, COLOR_II_RIGHT,
			      sizeof(COLOR_II_RIGHT));

  boid_program = initshader("boid_vs.glsl", "boid_fs.glsl");
  glGenVertexArrays(1, &vao_left);
  glBindVertexArray(vao_left);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_left);
  pos = glGetAttribLocation(boid_program, "vPos");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  glGenVertexArrays(1, &vao_right);
  glBindVertexArray(vao_right);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_right);
  pos = glGetAttribLocation(boid_program, "vPos");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  mv = glGetUniformLocation(boid_program, "modelview");
  proj = glGetUniformLocation(boid_program, "proj");


  shades_program = initshader("boid_vs.glsl", "shades_fs.glsl");
  
  glGenVertexArrays(1, &shades_vao_left);
  glBindVertexArray(shades_vao_left);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_left);
  pos = glGetAttribLocation(shades_program, "vPos");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  glGenVertexArrays(1, &shades_vao_right);
  glBindVertexArray(shades_vao_right);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_right);
  pos = glGetAttribLocation(shades_program, "vPos");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  shades_mv = glGetUniformLocation(shades_program, "modelview");
  shades_proj = glGetUniformLocation(shades_program, "proj");

  //shader-based for background
  vbo_square = make_bo(GL_ARRAY_BUFFER, A_SQUARE, sizeof(A_SQUARE));

  grey_square_program = initshader("square_vs.glsl", "square_fs_grey.glsl");
  glGenVertexArrays(1, &vao_grey);
  glBindVertexArray(vao_grey);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_square);
  pos = glGetAttribLocation(grey_square_program, "vPos");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  mv_grey = glGetUniformLocation(grey_square_program, "modelview");
  proj_grey = glGetUniformLocation(grey_square_program, "proj");

  black_square_program = initshader("square_vs.glsl", "square_fs_black.glsl");
  glGenVertexArrays(1, &vao_black);
  glBindVertexArray(vao_black);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_square);
  pos = glGetAttribLocation(black_square_program, "vPos");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  mv_black = glGetUniformLocation(black_square_program, "modelview");
  proj_black = glGetUniformLocation(black_square_program, "proj");

  //shader-based for goal
  vbo_goal = make_bo(GL_ARRAY_BUFFER, CUBE_VERTICES, sizeof(CUBE_VERTICES));
  vbo_goal_color = make_bo(GL_ARRAY_BUFFER, CUBE_COLORS, sizeof(CUBE_COLORS));
  vbo_goal_indices = make_bo(GL_ELEMENT_ARRAY_BUFFER, CUBE_INDICES, sizeof(CUBE_INDICES));
  glGenVertexArrays(1, &vao_goal);
  glBindVertexArray(vao_goal);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_goal);
  pos = glGetAttribLocation(boid_program, "vPos");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_goal_color);
  color = glGetAttribLocation(boid_program, "vColor");
  glEnableVertexAttribArray(color);
  glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
}

void framebuffer_resize(GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
}

void reshape(GLFWwindow* window, int w, int h) {
  change_view(MV_MAT, VIEW_MODE, A_FLOCK, A_GOAL);
}

void cleanup(){
  free(A_GOAL);
  list_destroy(A_FLOCK);
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch(key) {
      case GLFW_KEY_EQUAL:
      add_a_boid(A_FLOCK);
      break;

      case GLFW_KEY_MINUS:
      remove_a_boid(A_FLOCK);
      break;

      case GLFW_KEY_P:
      IS_PAUSED = GLFW_TRUE;
      PAUSE_TIME++;
      break;

      case GLFW_KEY_R:
      IS_PAUSED = GLFW_FALSE;
      PAUSE_TIME = 0;
      break;

      case GLFW_KEY_V:
      VIEW_MODE  = DEFAULT;
      glfwGetWindowSize(window, &WIDTH, &HEIGHT);
      myPerspective(PROJ_MAT, 45, WIDTH*1.0/HEIGHT, CAMERA_NEAR, CAMERA_FAR);
      break;

      case GLFW_KEY_T:
      VIEW_MODE = TRAILING;
      glfwGetWindowSize(window, &WIDTH, &HEIGHT);
      myPerspective(PROJ_MAT, 30, WIDTH*1.0/HEIGHT, CAMERA_NEAR, CAMERA_FAR);
      break;

      case GLFW_KEY_G:
      VIEW_MODE = SIDE;
      glfwGetWindowSize(window, &WIDTH, &HEIGHT);
      myPerspective(PROJ_MAT, 40, WIDTH*1.0/HEIGHT, CAMERA_NEAR, CAMERA_FAR);
      break;

      case GLFW_KEY_A:
      A_GOAL->MOVE_ALONG_X_NEGATIVE = true;
      break;

      case GLFW_KEY_D:
      A_GOAL->MOVE_ALONG_X_POSITIVE = true;
      break;

      case GLFW_KEY_W:
      A_GOAL->MOVE_ALONG_Y_POSITIVE = true;
      break;

      case GLFW_KEY_S:
      A_GOAL->MOVE_ALONG_Y_NEGATIVE = true;
      break;

      case GLFW_KEY_RIGHT:
      A_GOAL->ACCELERATE = true;
      break;

      case GLFW_KEY_LEFT:
      A_GOAL->DECELERATE = true;
      break;

      case GLFW_KEY_B:
        teleport_goal(A_GOAL);
      break;

      case GLFW_KEY_Q:
      case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, GLFW_TRUE);
      break;
      default:
      break;
    }
  } else if (action == GLFW_RELEASE) {
    switch(key) {
      case GLFW_KEY_A:
      A_GOAL->MOVE_ALONG_X_NEGATIVE = false;
      break;

      case GLFW_KEY_D:
      A_GOAL->MOVE_ALONG_X_POSITIVE = false;
      break;

      case GLFW_KEY_W:
      A_GOAL->MOVE_ALONG_Y_POSITIVE = false;
      break;

      case GLFW_KEY_S:
      A_GOAL->MOVE_ALONG_Y_NEGATIVE = false;

      case GLFW_KEY_RIGHT:
      A_GOAL->ACCELERATE = false;
      break;

      case GLFW_KEY_LEFT:
      A_GOAL->DECELERATE = false;
      break;

      default:
      break;
    }
  }
}

static GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size) {
  GLuint bufnum;
  glGenBuffers(1, &bufnum);
  glBindBuffer(type, bufnum);
  glBufferData(type, buf_size, buf, GL_STATIC_DRAW);
  return bufnum;
}

void draw_background() {
  glUseProgram(grey_square_program);
  glBindVertexArray(vao_grey);
  glUniformMatrix4fv(proj_grey, 1, GL_FALSE, PROJ_MAT);
  for(int i = 0; i < BG_GREY_NUM; i++) {
    glUniformMatrix4fv(mv_grey, 1, GL_FALSE, &SQUARES_GREY[i*16]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }
  
  glUseProgram(black_square_program);
  glBindVertexArray(vao_black);
  glUniformMatrix4fv(proj_black, 1, GL_FALSE, PROJ_MAT);
  for(int i = 0; i < BG_BLACK_NUM; i++) {
    glUniformMatrix4fv(mv_black, 1, GL_FALSE, &SQUARES_BLACK[i*16]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }
  
}


void draw_a_flock(){
  if (A_FLOCK == NULL) return;
  NODE* current = A_FLOCK->head;
  BOID* some_boid = NULL;
  for (int i = 0; i < A_FLOCK->length; i++){
    some_boid = (BOID*)(current->data);
    vec3 velocity3 = normalise(reduce(some_boid->velocity));
    vec3 initial3 = normalise(reduce(SPAWN_VELOCITY));
    vec3 rotate_normal = normalise(cross(velocity3, initial3));
    float angle = oriented_angle(initial3, velocity3, 
                                rotate_normal);
    float shades_angle = oriented_angle(initial3, velocity3, 
                                       vec3(0, 0, 1)); 
    GLfloat trans[16];

    glUseProgram(boid_program);
    glBindVertexArray(vao_left);
    glUniformMatrix4fv(proj, 1, GL_FALSE, PROJ_MAT);
    
    if (some_boid->flock_index == 0) {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_color_i_left);
      color = glGetAttribLocation(boid_program, "vColor");
      glEnableVertexAttribArray(color);
      glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    } else {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_color_ii_left);
      color = glGetAttribLocation(boid_program, "vColor");
      glEnableVertexAttribArray(color);
      glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    }
    
    memcpy(trans, MV_MAT, sizeof(GLfloat)*16);
    myTranslate(trans, some_boid->pos[0], some_boid->pos[1], some_boid->pos[2]);
    myRotate(trans, angle, rotate_normal[0], rotate_normal[1], rotate_normal[2]);
    myRotate(trans, -some_boid->wing_rotation, 0, 1, 0);
    glUniformMatrix4fv(mv, 1, GL_FALSE, trans);
    glDrawArrays(GL_TRIANGLES, 0, 3);
   
    glUseProgram(shades_program);
    glBindVertexArray(shades_vao_left);
    glUniformMatrix4fv(shades_proj, 1, GL_FALSE, PROJ_MAT);
    memcpy(trans, MV_MAT, sizeof(GLfloat)*16);
    myTranslate(trans, some_boid->pos[0], some_boid->pos[1], SHADES_HEIGHT);
    myRotate(trans, shades_angle, 0, 0, 1);
    glUniformMatrix4fv(shades_mv, 1, GL_FALSE, trans);
    glDrawArrays(GL_TRIANGLES, 0, 3);
   
    current = current->next;
  }

  current = A_FLOCK->head;
  for (int i = 0; i < A_FLOCK->length; i++){
    some_boid = (BOID*)(current->data);
    vec3 velocity3 = normalise(reduce(some_boid->velocity));
    vec3 initial3 = normalise(reduce(SPAWN_VELOCITY));
    vec3 rotate_normal = normalise(cross(velocity3, initial3));
    float angle = oriented_angle(initial3, velocity3, 
                                rotate_normal);
    float shades_angle = oriented_angle(initial3, velocity3, 
                                       vec3(0, 0, 1));
    GLfloat trans[16];

    glUseProgram(boid_program);
    glBindVertexArray(vao_right);
    glUniformMatrix4fv(proj, 1, GL_FALSE, PROJ_MAT);
    if (some_boid->flock_index == 0) {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_color_i_right);
      color = glGetAttribLocation(boid_program, "vColor");
      glEnableVertexAttribArray(color);
      glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    } else {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_color_ii_right);
      color = glGetAttribLocation(boid_program, "vColor");
      glEnableVertexAttribArray(color);
      glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    }
    memcpy(trans, MV_MAT, sizeof(GLfloat)*16);
    myTranslate(trans, some_boid->pos[0], some_boid->pos[1], some_boid->pos[2]);
    myRotate(trans, angle, rotate_normal[0], rotate_normal[1], rotate_normal[2]);
    myRotate(trans, some_boid->wing_rotation, 0, 1, 0);
    glUniformMatrix4fv(mv, 1, GL_FALSE, trans);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shades_program);
    glBindVertexArray(shades_vao_right);
    glUniformMatrix4fv(shades_proj, 1, GL_FALSE, PROJ_MAT);
    memcpy(trans, MV_MAT, sizeof(GLfloat)*16);
    myTranslate(trans, some_boid->pos[0], some_boid->pos[1], SHADES_HEIGHT);
    myRotate(trans, shades_angle, 0, 0, 1);
    glUniformMatrix4fv(shades_mv, 1, GL_FALSE, trans);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    current = current->next;
  }
  
}

void draw_a_goal(){
  glUseProgram(boid_program);
  glBindVertexArray(vao_goal);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_goal_indices);
  GLfloat trans[16];
  memcpy(trans, MV_MAT, sizeof(GLfloat)*16);
  myTranslate(trans, A_GOAL->pos[0], A_GOAL->pos[1], A_GOAL->pos[2]);
  glUniformMatrix4fv(proj, 1, GL_FALSE, PROJ_MAT);
  glUniformMatrix4fv(mv, 1, GL_FALSE, trans);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (void*) 0);
}
