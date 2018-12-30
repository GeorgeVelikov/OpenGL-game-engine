#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Definitions.h"

int main() {
	// game time
	auto timeStamp = std::chrono::system_clock::now();
	auto timeStampDynamic = std::chrono::system_clock::now();

	// buffer
	wchar_t *screen = new wchar_t[SCREEN_PIXEL_COUNT];
	HANDLE consoleBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(consoleBuffer);
	DWORD bytesWritten = 0;

	// map
	std::wstring map;
	map += L"################";
	map += L"#..............#";
	map += L"#######....#...#";
	map += L"#..........#...#";
	map += L"#..........#...#";
	map += L"#..........#...#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#......##......#";
	map += L"#......##......#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";

	// player location and local orientation
	float playerX = 8.0f;
	float playerY = 8.0f;
	float playerYaw = 0.0f;
	bool running = true;

	while (running) {
		timeStampDynamic = std::chrono::system_clock::now();
		std::chrono::duration<float> frameTime = timeStampDynamic - timeStamp; // get the time it takes for a tick
		timeStamp = timeStampDynamic; // reset current time and prepare to measure new frametime on upcoming tick
		float fpsNormalise = frameTime.count(); // allows for consistency in movement independent of FPS

		if (GetAsyncKeyState('A'))
			playerYaw -= ROTATIONAL_STEP * fpsNormalise;
		if (GetAsyncKeyState('D'))
			playerYaw += ROTATIONAL_STEP * fpsNormalise;
		if (GetAsyncKeyState('W')) {
			playerX += sinf(playerYaw) * MOVEMENT_STEP * fpsNormalise;
			playerY += cosf(playerYaw) * MOVEMENT_STEP * fpsNormalise;
		}
		if (GetAsyncKeyState('S')) {
			playerX -= sinf(playerYaw) * MOVEMENT_STEP * fpsNormalise;
			playerY -= cosf(playerYaw) * MOVEMENT_STEP * fpsNormalise;
		}

		for (int col = 0; col < SCREEN_WIDTH; col++) {
			float rayAngle = (playerYaw - FOV / 2.f) + (float(col) / float(SCREEN_WIDTH)) * FOV;
			float distanceToWall = 0;
			bool touchWall = false;
			
			float eyeX = sinf(rayAngle);
			float eyeY = cosf(rayAngle);

			while (!touchWall && distanceToWall < MAX_DEPTH) {
				distanceToWall += .1f;
				int testX = int(playerX + eyeX * distanceToWall);
				int testY = int(playerY + eyeY * distanceToWall);

				// ray is out of bounds
				if (testX < 0 || testX >= MAP_WIDTH || testY < 0 || testY >= MAP_HEIGHT) {
					touchWall = true;
					distanceToWall = MAX_DEPTH;
				}
				else
					if (map[testY*MAP_WIDTH + testX] == '#')
						touchWall = true;
			}

			int ceiling = float(SCREEN_HEIGHT / 2.) - SCREEN_HEIGHT / float(distanceToWall);
			int floor = SCREEN_HEIGHT - ceiling;

			short wallShade;
			short floorShade;

			// close walls become darker and those outside of the MAX_DEPTH reach are not rendered
			if (distanceToWall <= MAX_DEPTH / 4.f)		wallShade = WALL_BLACK_SHADE;
			else if (distanceToWall < MAX_DEPTH / 3.f)	wallShade = WALL_DARK_SHADE;
			else if (distanceToWall < MAX_DEPTH / 2.f)	wallShade = WALL_MEDIUM_SHADE;
			else if (distanceToWall < MAX_DEPTH)		wallShade = WALL_LIGHT_SHADE;
			else										wallShade = WALL_EMPTY_SHADE;

			for (int row = 0; row < SCREEN_HEIGHT; row++) {
				if (row < ceiling)
					screen[row*SCREEN_WIDTH + col] = ' '; // sky
				else if(row >= ceiling && row < floor)
					screen[row*SCREEN_WIDTH + col] = wallShade; // wall
				else {
					float floorDistance = 1.f - ((float(row) - float(SCREEN_HEIGHT) / 2.f) / (float(SCREEN_HEIGHT) / 2.f));
					if (floorDistance < .25f)			floorShade = FLOOR_BLACK_SHADE;
					else if (floorDistance < 0.50f)		floorShade = FLOOR_DARK_SHADE;
					else if (floorDistance < 0.75f)		floorShade = FLOOR_MEDIUM_SHADE;
					else if (floorDistance < 0.90f)		floorShade = FLOOR_LIGHT_SHADE;
					else								floorShade = FLOOR_EMPTY_SHADE;
					screen[row*SCREEN_WIDTH + col] = floorShade; // floor
				}
			}
		}
		// set last char to end of str 
		screen[SCREEN_PIXEL_COUNT] = '\0';
		// draw the screen array to the buffer
		WriteConsoleOutputCharacter(consoleBuffer, screen, SCREEN_PIXEL_COUNT, SCREEN_DRAW_START, &bytesWritten);
	}
	return 0;
}