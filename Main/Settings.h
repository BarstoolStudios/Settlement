#ifndef SETTINGS_H
#define SETTINGS_H

const int GAME_SEED = 42;

const int OPENGL_MAJOR_VERSION = 4;
const int OPENGL_MINOR_VERSION = 4;
const int OPENGL_DEPTH_BUFFER_SIZE = 24;

const int DISPLAY_INITIAL_HEIGHT = 540;
const int DISPLAY_INITIAL_WIDTH = 960;

const int TERRAIN_SQUARE_SIZE = 256;
const int TERRAIN_NUM_OCTIVES = 4;
const int TERRAIN_INITIAL_FREQUENCY = 1024;
const int TERRAIN_HEIGHT = 512;

const float CAMERA_WALK_SPEED = 0.001f;
const float CAMERA_RUN_SPEED = 0.01f;
const float CAMERA_SPRINT_SPEED = 0.07f;
const float CAMERA_PLAYER_HEIGHT = 4.0f;
const float CAMERA_GRAVITY = 0.0008f;
const float CAMERA_ORTHO_SCALING = 16.0f;
const float CAMERA_FLY_HEIGHT = 50.0f;
const float CAMERA_FOV = 60.0f;
const float CAMERA_ZNEAR = 0.001f;
const float CAMERA_ZFAR = 256.0f;

#endif