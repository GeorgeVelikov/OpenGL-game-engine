#define PI 3.1415927

// might want to change width and height to your prefferenced window size as rendering is not dynamic just yet
#define SCREEN_WIDTH 150
#define SCREEN_HEIGHT 50
#define SCREEN_PIXEL_COUNT (SCREEN_WIDTH*SCREEN_HEIGHT)
#define SCREEN_DRAW_START {0,0}

#define FOV (PI/3.f)
#define MAX_DEPTH 16.0f
#define RAY_STEP 0.1f
#define ROTATIONAL_STEP (PI/2.f)
#define MOVEMENT_STEP 5.f

#define MAP_HEIGHT 16.0f
#define MAP_WIDTH 32.0f

#define WALL_BOUNDARY_THRESHOLD 0.005f
#define WALL_BOUNDARY_AMOUNT 2
#define WALL_LIGHT_SHADE 0x2591
#define WALL_MEDIUM_SHADE 0x2592
#define WALL_DARK_SHADE 0x2593
#define WALL_BLACK_SHADE 0x2588

#define FLOOR_SHADE 0x002A
#define CLEAR_SHADE 0x0020