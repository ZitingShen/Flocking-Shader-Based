#include "view.h"
#include "gl_replacement.h"

void change_view(GLfloat mv_mat[], viewMode viewmode, List *flock, GOAL *goal, int index) {
  vec4 centroid = (flock_centroid(flock, 0) + flock_centroid(flock, 1)) * 0.5;
  vec4 midpoint = (mid_point(flock, goal, 0) + mid_point(flock, goal, 1)) * 0.5;
  float distance = (get_d(flock, goal, 0) + get_d(flock, goal, 1)) * 0.5;
  vec4 camera_pos;
  vec4 flock_direction = normalise((get_u(flock, goal, 0) + get_u(flock, goal, 1)) * 0.5);
  vec4 velocity_direction = normalise(get_average_v(flock, index)); 

  GLfloat eye[] = {0, 2500, TOWER_HEIGHT};
  GLfloat centre[] = {midpoint[0], midpoint[1], midpoint[2]};
  GLfloat up[] = {0, 0, 1};
  glMatrixMode(GL_MODELVIEW);
  switch(viewmode){
    case TRAILING:
    centroid = (flock_centroid(flock, index));
    distance = (get_d(flock, goal, index));
    distance = (distance < 4000)?4000:distance;
    //std::cout << distance << std::endl;
    camera_pos = centroid
                 - flock_direction*distance*0.9
                 - velocity_direction*distance*1.1
                 + vec4(0, 0, 1, 0)*TOWER_HEIGHT*0.8f;
    unpack(camera_pos, eye);
    break;

    case SIDE:{
    vec3 side_v3 = cross(reduce(flock_direction), vec3(0, 0, 1));
    vec4 side_v = side_v3.promote(false);
    camera_pos = centroid
                 + normalise(side_v)*distance*3
                 + vec4(0, 0, 1, 0)*distance*0.3f;
    unpack(camera_pos, eye);
    }
    break;
    default:
    break;
  }
  myLookAt(mv_mat, eye, centre, up);
}

void update_background(GLfloat squares_grey[], GLfloat squares_black[],
		       GLfloat mv_mat[]) {
  int i = 0;
  int index_grey = 0;
  int index_black = 0;
  GLfloat x, y;
  for (int row = 0; row < BG_SQUARE_NUM; row++) {
    for (int column = 0; column < BG_SQUARE_NUM; column++) {
      x = (row - BG_SQUARE_NUM/2.0)*BG_SQUARE_SIDE;
      y = (column - BG_SQUARE_NUM/2.0)*BG_SQUARE_SIDE;
      GLfloat trans[16];
      memcpy(trans, mv_mat, sizeof(GLfloat)*16);
      if (i % 2 == 0) {
	myTranslate(trans, x, y, 0);
	memcpy(squares_grey+index_grey, trans, sizeof(GLfloat)*16);
	index_grey+=16;
      } else {
	myTranslate(trans, x, y, 0);
	memcpy(squares_black+index_black, trans, sizeof(GLfloat)*16);
	index_black+=16;
      }
      i++;
    }
  }
}

//TODO: change draw to shader_based
void draw_background(GLfloat squares_pos[][2], GLfloat mv_mat[]) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, A_SQUARE);
  GLfloat mv_mat_copy[16];
  for (int i = 0; i < BG_SQUARE_NUM*BG_SQUARE_NUM; i++) {
    if(i % 2 == 0) {
      glColor3f(CHESS_BOARD_COLOUR_X[0], CHESS_BOARD_COLOUR_X[1], CHESS_BOARD_COLOUR_X[2]);
    } else {
      glColor3f(CHESS_BOARD_COLOUR_Y[0], CHESS_BOARD_COLOUR_Y[1], CHESS_BOARD_COLOUR_Y[2]);
    }

    memcpy(mv_mat_copy, mv_mat, sizeof(GLfloat)*16);
    myTranslate(mv_mat_copy, squares_pos[i][0], squares_pos[i][1], -10);
    //if(i == 0) {
    //  std::cout << mv_mat_copy[0] << mv_mat_copy[1] << mv_mat_copy[2] << mv_mat_copy[3] << std::endl;
    //}
    glPointSize(5);
    glDrawArrays(GL_QUADS, 0, 4);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}
