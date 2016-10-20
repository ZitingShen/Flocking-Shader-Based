#ifndef VIEW_H
#define VIEW_H

#include "common.h"
#include "list.h"
#include "goal.h"
#include "boid.h"

const GLfloat CLEAR_COLOR[3] = {0.182, 0.008, 0.235};				  
const GLfloat A_SQUARE[][3]= 
            {{0, 0, 0},
            {BG_SQUARE_SIDE, 0, 0},
            {BG_SQUARE_SIDE, BG_SQUARE_SIDE, 0},
            {0, BG_SQUARE_SIDE, 0}};

const float CHESS_BOARD_COLOUR_X[3] = {0.449,0.451,0.494};  //grey
const float CHESS_BOARD_COLOUR_Y[3] = {0.0, 0.0, 0.0};     //black

typedef enum viewMode {DEFAULT, TRAILING, SIDE} viewMode;

void change_view(viewMode viewmode, int width, int height, List *flock, 
                GOAL *goal);

void init_background(GLfloat squares_pos[][2]);
void draw_background(GLfloat squares_pos[][2]);
#endif
