#include <chrono>
#include <vector>
#include <algorithm>
#include <math.h>
#include <Windows.h>

#define PI 3.1415927

// might want to change width and height to your prefferenced window size as rendering is not dynamic just yet
#define SCREEN_WIDTH 150
#define SCREEN_HEIGHT 50
#define SCREEN_PIXEL_COUNT (SCREEN_WIDTH*SCREEN_HEIGHT)
#define SCREEN_DRAW_START {0,0}

// raycasting
#define FOV (PI/3.f)
#define MAX_DEPTH 16.f
#define RAY_STEP .1f

// wall specific render settings
#define WALL_BOUNDARY_THRESHOLD .005f
#define WALL_BOUNDARY_AMOUNT 2

// movement
#define ROTATIONAL_STEP (PI/2.f)
#define MOVEMENT_STEP 5.f

// map defs should go hand in hand with actual map size for 1:1 accuracy
#define MAP_HEIGHT 16.f
#define MAP_WIDTH 32.f

// shader
#define WALL_SHADE_LIGHT 0x2591
#define WALL_SHADE_MEDIUM 0x2592
#define WALL_SHADE_DARK 0x2593
#define WALL_SHADE_BLACK 0x2588
#define FLOOR_SHADE 0x002A
#define CLEAR_SHADE 0x0020

// player
float playerX = 1.5f;
float playerY = 3.24f;
float playerYaw = .0f;
bool playerTouchWall = false;

// game
bool running = true;
auto timeStamp = std::chrono::system_clock::now();
auto timeStampDynamic = std::chrono::system_clock::now();
std::chrono::duration<float> frameTime;
float fpsNormalise;

// raycasting
float rayAngle;
float distanceToWall;
bool blockBoundary;
float eyeX;
float eyeY;

// world
std::wstring map;
int worldCeiling;
int worldFloor;

// shader
short wallShade;
short floorShade;
