#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#else
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif
#include "my_matrix.h"

#define RADIAN_TO_DEGREE          57.29578 // 180 over pi

#define PARTNER_RADIUS            100
#define DEFAULT_FLOCK_SIZE        20
#define DEFAULT_FLOCK_NUM         2

#define SEPARATION_WEIGHT         ((float) 0.02)
#define ALIGNMENT_WEIGHT          ((float) 0.01)
#define COHESION_WEIGHT           ((float) 0.01)
#define ATTRACTION_WEIGHT         ((float) 0.05)
#define DETERRENCE_WEIGHT         ((float) 0.5) // the most significant weight
#define MAX_ATTRACTION_INFLUENCE  ((float) 10.0)

#define MAX_WING_ROTATION         45
#define WING_ROTATION_PER_FRAME   0.1

#define RANDOMISE_V_FACTOR        45
#define SPAWN_CUBE_LENGTH         100.0

#define SHADES_HEIGHT             50.0

#define BOID_SIZE                 100

#endif