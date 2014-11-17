#ifndef SETTINGS_H
#define SETTINGS_H

//============================================
// Game constants
//============================================
#define GAME_SEED					42


//============================================
// OpenGL constants
//============================================
#define OPENGL_MAJOR_VERSION		4
#define OPENGL_MINOR_VERSION		4
#define OPENGL_DEPTH_BUFFER_SIZE	24


//============================================
// Display constants
//============================================
#define DISPLAY_INITIAL_HEIGHT		540
#define DISPLAY_INITIAL_WIDTH		960


//============================================
// Terrain constants
//============================================
#define TERRAIN_SQUARE_SIZE			256
#define TERRAIN_NUM_OCTIVES			4
#define TERRAIN_INITIAL_FREQUENCY	1024
#define TERRAIN_HEIGHT				512


//============================================
// Player constants
//============================================
#define PLAYER_WALK_SPEED			0.001f
#define PLAYER_RUN_SPEED			0.01f
#define PLAYER_SPRINT_SPEED			0.07f
#define PLAYER_HEIGHT				4.0f


//============================================
// World constants
//============================================
#define WORLD_GRAVITY				0.0008f


//============================================
// Camera constants
//============================================
#define CAMERA_ORTHO_SCALING		16.0f
#define CAMERA_FLY_HEIGHT			50.0f
#define CAMERA_FOV					60.0f
#define CAMERA_ZNEAR				0.001f
#define CAMERA_ZFAR					1024.0f

//============================================
// Sun constants
//============================================
#define SUN_DAY_TIME				360000	// In ms

#endif