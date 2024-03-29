#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <time.h>
#ifdef __APPLE__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif
#include "my_matrix.h"

#define RADIAN_TO_DEGREE          57.29578 // 180 over pi
#define	DEGREE_TO_RADIAN		  0.00873

#define PARTNER_RADIUS            300
#define DEFAULT_FLOCK_SIZE        100
#define DEFAULT_FLOCK_NUM         2
#define MIN_FLOCK_RADIUS	      2000.0
#define MAX_FLOCK_RADIUS		  3000.0

#define SEPARATION_WEIGHT         ((float) 0.002)
#define ALIGNMENT_WEIGHT          ((float) 0.0008)
#define COHESION_WEIGHT           ((float) 0.0015)
#define ATTRACTION_WEIGHT         ((float) 0.0005)
#define STAY_IN_FLOCK_WEIGHT	  ((float) 0.003)
#define DETERRENCE_WEIGHT         ((float) 0.1) // the most significant weight

#define MAX_WING_ROTATION         45
#define WING_ROTATION_PER_FRAME   0.01
#define SHADES_HEIGHT                 50

#define RANDOMISE_V_FACTOR        60
#define SPAWN_CUBE_LENGTH         100.0

#define BOID_SIZE                 100
#define GOAL_SIZE				  100

#define DEFAULT_ACCELERATION_FACTOR    0.2
#define DEFAULT_ACCELERATION_MARGIN   0.1
#define TRUE  1
#define FALSE 0


#define TOWER_HEIGHT              8000
#define CAMERA_NEAR               2
#define CAMERA_FAR                (TOWER_HEIGHT*20000)

#define BG_SQUARE_SIDE            2000.0
#define BG_SQUARE_NUM             97   // must be an odd number
#define BG_GREY_NUM               (BG_SQUARE_NUM*BG_SQUARE_NUM/2+1)
#define BG_BLACK_NUM              (BG_SQUARE_NUM*BG_SQUARE_NUM/2)
#endif
