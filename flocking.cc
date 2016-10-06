#include "flocking.h"

List* A_FLOCK = NULL;
GOAL* A_GOAL = NULL;
//OBSTACLE* AN_OBSTACLE = NULL;

int IS_PAUSED = GLFW_FALSE;
int PAUSE_TIME = 0;
viewMode VIEW_MODE = DEFAULT;
int WIDTH, HEIGHT;
GLfloat SQUARES_POS[BG_SQUARE_NUM*BG_SQUARE_NUM][2];

int main(){
  GLFWwindow* window;

  if (!glfwInit())
    exit(EXIT_FAILURE);

  window = glfwCreateWindow(500, 500, "Flocking", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetWindowPos(window, 100, 0);

  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, reshape);
  glfwSetKeyCallback(window, keyboard);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize);

  init();

  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();

    if(!IS_PAUSED || PAUSE_TIME > 0) {
      glfwGetWindowSize(window, &WIDTH, &HEIGHT);
      change_view(VIEW_MODE, WIDTH, HEIGHT, A_FLOCK, A_GOAL);
      update_goal_velocity(A_GOAL);
      update_goal_pos(A_GOAL);
      update_velocity(A_FLOCK);
      update_wing_rotation(A_FLOCK);
      apply_goal_attraction(A_FLOCK, A_GOAL);
      //if (AN_OBSTACLE->enable){
      //  apply_obstacle_avoidance(A_FLOCK, AN_OBSTACLE);
      //  draw_an_obstacle(AN_OBSTACLE);
      //}
      update_pos(A_FLOCK);
      if(glfwGetWindowAttrib(window, GLFW_VISIBLE)){
        draw_background(SQUARES_POS);
        draw_a_flock(A_FLOCK);
        draw_a_goal(A_GOAL);
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
