#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <math.h>
#include <Windows.h>

#define PI 3.1415927
#define VXP(x1,y1, x2,y2) (x1*y2 - x2*y1)

// might want to change width and height to your prefferenced window size as rendering is not dynamic just yet
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 110
#define SCREEN_PIXEL_COUNT (SCREEN_WIDTH*SCREEN_HEIGHT)
#define SCREEN_DRAW_START {0,0}
#define PIXEL_SIZE_WIDTH 4
#define PIXEL_SIZE_HEIGHT 6
#define SCREEN_MID_TO_LEFT (SCREEN_WIDTH*PIXEL_SIZE_WIDTH / 2);
#define SCREEN_MID_TO_TOP (SCREEN_HEIGHT*PIXEL_SIZE_HEIGHT / 2)

// raycasting
#define FOV (PI/3.f)
#define MAX_DEPTH 16.f
#define RAY_STEP .025f

// wall specific render settings
#define WALL_BOUNDARY_THRESHOLD .002f
#define WALL_BOUNDARY_AMOUNT 2

// movement
#define ROTATIONAL_STEP .1f
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

struct Vertex2D { float x, y; };
struct Vertex3D { float x, y, z; };

// player
struct Player {
    Vertex2D location;
    Vertex2D cameraYaw;
    bool touchWall;
    float moveDirection;
    int sector;
} player;

// game
bool running = true;
auto timeStamp = std::chrono::system_clock::now();
auto timeStampDynamic = std::chrono::system_clock::now();
std::chrono::duration<float> frameTime;
float fpsNormalise;

// console
HWND consoleName;
HANDLE consoleBuffer;
POINT midPoint;
POINT currentPoint;
CONSOLE_FONT_INFOEX cfi;
wchar_t *screen;
int windowStartX, windowStartY;
int windowMidX, windowMidY;

// raycasting
float ray;
float distanceToWall;
bool blockBoundary;
float eyeX, eyeY;
int rayHitX, rayHitY;

// world
std::wstring map;
int worldCeiling;
int worldFloor;

// shader
short wallShade;
short floorShade;