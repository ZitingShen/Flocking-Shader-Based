#include "view.h"
#include "gl_replacement.h"

void change_view(GLfloat mv_mat[], viewMode viewmode, List *flock, GOAL *goal) {
  vec4 center = flock_centroid(flock);
  vec4 midpoint = mid_point(flock, goal);
  float max_distance =  flock_radius(flock);
  float distance = get_d(flock, goal);
  vec4 camera_pos;
  vec4 flock_direction = normalise(get_u(flock, goal));

  GLfloat eye[3];
  GLfloat centre[3];
  GLfloat up[3];
  switch(viewmode) {
    case DEFAULT:
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0, 2, TOWER_HEIGHT, midpoint[0], midpoint[1], midpoint[2], 0, 0, 1);
    eye[0] = 0;
    eye[1] = 0.01;
    eye[2] = TOWER_HEIGHT;
    centre[0] = midpoint[0];
    centre[1] = midpoint[1];
    centre[2] = midpoint[2];
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;
    myLookAt(mv_mat, eye, centre, up);
    break;

    case TRAILING:
    glMatrixMode(GL_MODELVIEW);

    camera_pos = center
                 - flock_direction*(distance + 2*max_distance)
                 + vec4(0, 0, 1, 0)*(distance + max_distance);
    //gluLookAt(camera_pos.x, camera_pos.y, camera_pos.z, midpoint.x, midpoint.y, 
    //          midpoint.z, 0, 0, 1);
    eye[0] = camera_pos[0];
    eye[1] = camera_pos[1];
    eye[2] = camera_pos[2];
    centre[0] = midpoint[0];
    centre[1] = midpoint[1];
    centre[2] = midpoint[2];
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;
    myLookAt(mv_mat, eye, centre, up);
    break;

    case SIDE: {
    glMatrixMode(GL_MODELVIEW);

    vec3 v3 = reduce(flock_direction);
    vec3 side_v3 = cross(v3, vec3(0, 0, 1));
    vec4 side_v = vec4(side_v3[0], side_v3[1], side_v3[2], 0.0);
    camera_pos = midpoint
                 + normalise(side_v)*(distance + 2*max_distance)
                 + vec4(0, 0, 1, 0)*(distance + max_distance);
    //gluLookAt(camera_pos.x, camera_pos.y, camera_pos.z, midpoint.x, midpoint.y, 
    //          midpoint.z, 0, 0, 1);
    eye[0] = camera_pos[0];
    eye[1] = camera_pos[1];
    eye[2] = camera_pos[2];
    centre[0] = midpoint[0];
    centre[1] = midpoint[1];
    centre[2] = midpoint[2];
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;
    myLookAt(mv_mat, eye, centre, up);
    }
    break;
    default:
    break;
  }
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
