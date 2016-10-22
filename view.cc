#include "view.h"
#include "gl_replacement.h"

void change_view(GLfloat mv_mat[], viewMode viewmode, List *flock, GOAL *goal) {
  vec4 centroid = flock_centroid(flock, 0);
  vec4 midpoint = mid_point(flock, goal, 0);
  float distance = get_d(flock, goal, 0);
  distance = distance < MIN_FLOCK_RADIUS? MIN_FLOCK_RADIUS:distance;
  distance = distance > MAX_FLOCK_RADIUS? MAX_FLOCK_RADIUS:distance;
  vec4 camera_pos;
  vec4 flock_direction = normalise(get_u(flock, goal, 0));

  GLfloat eye[] = {0, 2500, TOWER_HEIGHT};
  GLfloat centre[] = {midpoint[0], midpoint[1], midpoint[2]};
  GLfloat up[] = {0, 0, 1};
  glMatrixMode(GL_MODELVIEW);
  switch(viewmode) {
    case TRAILING:
    camera_pos = centroid
                 - flock_direction*distance*2
                 + vec4(0, 0, 1, 0)*TOWER_HEIGHT*0.8f;
    unpack(camera_pos, eye);
    break;

    case SIDE: {
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

void init_background(GLfloat squares_pos[][2]) {
  int index = 0;
  for (int row = 0; row < BG_SQUARE_NUM; row++) {
    for (int column = 0; column < BG_SQUARE_NUM; column++) {
      squares_pos[index][0] = (row - BG_SQUARE_NUM/2.0)*BG_SQUARE_SIDE;
      squares_pos[index][1] = (column - BG_SQUARE_NUM/2.0)*BG_SQUARE_SIDE;
      index++;
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
    glPointSize(5);
    glDrawArrays(GL_QUADS, 0, 4);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}
