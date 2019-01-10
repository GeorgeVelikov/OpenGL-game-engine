#include "stdafx.h"
#include "Definitions.h"
#include "Functions.h"

int main() {
    consoleName = GetForegroundWindow();
	// buffer
	wchar_t *screen = new wchar_t[SCREEN_PIXEL_COUNT];
	HANDLE consoleBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(consoleBuffer);
	DWORD bytesWritten = 0;

	// map
    map += L"################################";
	map += L"#...............##.............#";
	map += L"#..........##.....#....#.#.#...#";
	map += L"#..........##......#...........#";
	map += L"#........########...#...#.#....#";
	map += L"#...##....######...............#";
	map += L"#...##......#........#####.....#";
	map += L"#........##.....##.............#";
	map += L"#..#......##.....##............#";
	map += L"#..........##.....##.......##..#";
	map += L"#...#.......##....##......#....#";
	map += L"#...#........##..##.......#.#..#";
	map += L"#...#.........###....##...#....#";
	map += L"#...#####..........#....###..#.#";
	map += L"#.............##...............#";
	map += L"################################";

	while (running) {
        // pause game state if window not focused
        while (consoleName != GetForegroundWindow()) continue;

        // sets cursor to the middle of the screen
        setCursorMidScreen();

        // start game clock
		timeStampDynamic = std::chrono::system_clock::now();
		frameTime = timeStampDynamic - timeStamp; // get the time it takes for a tick
		timeStamp = timeStampDynamic; // reset current time and prepare to measure new frametime on upcoming tick
		fpsNormalise = frameTime.count(); // allows for consistency in movement independent of FPS

		// controls
        if (GetAsyncKeyState('W')) moveFB(+1);
        if (GetAsyncKeyState('A')) moveLR(-1);
        if (GetAsyncKeyState('S')) moveFB(-1);
        if (GetAsyncKeyState('D')) moveLR(+1);
        if (GetAsyncKeyState(VK_ESCAPE)) running = false;

		// ray casting
		for (int col = 0; col < SCREEN_WIDTH; col++) {
			ray = (playerYaw - FOV / 2.f) + (float(col) / float(SCREEN_WIDTH)) * FOV;
            eyeX = sinf(ray); eyeY = cosf(ray);
            distanceToWall = 0;
            blockBoundary = false;
			playerTouchWall = false;

			// incrementing to see if a wall is hit by our rays
			while (!playerTouchWall && distanceToWall < MAX_DEPTH) {
				distanceToWall += RAY_STEP;
				rayHitX = int(playerX + eyeX * distanceToWall);
			    rayHitY = int(playerY + eyeY * distanceToWall);

				// object is out of bounds
				if (rayHitX < 0 || rayHitX >= MAP_WIDTH || rayHitY < 0 || rayHitY >= MAP_HEIGHT) 
                    distanceToWall = MAX_DEPTH+1; // object is out of our render distance
				else
					if (map[rayHitY*MAP_WIDTH + rayHitX] == '#') {
						playerTouchWall = true;
						std::vector<std::pair<float, float>> blockCorners;
						for (int x = 0; x < WALL_BOUNDARY_AMOUNT; x++) 
							for (int y = 0; y < WALL_BOUNDARY_AMOUNT; y++) {
								float vectorX = rayHitX + x - playerX;
								float vectorY = rayHitY + y - playerY;
								float distance = sqrt(pow(vectorX, 2) + pow(vectorY, 2)); // eucledian distance
								float area = (eyeX * vectorX / distance) + (eyeY * vectorY / distance);
								blockCorners.push_back(std::make_pair(distance, area));
							}
						// sort pairs
						std::sort(blockCorners.begin(), blockCorners.end(), [](const std::pair<float, float> &left, const std::pair<float, float> &right) 
                        { return left.first < right.first; });

						for (int i = 0; i < WALL_BOUNDARY_AMOUNT; i++) 
                            if (acos(blockCorners.at(i).second) < WALL_BOUNDARY_THRESHOLD) 
                                blockBoundary = true;
					}		
			}
            shadeWall();

            // draw world 
            worldCeiling = float(SCREEN_HEIGHT / 2.) - SCREEN_HEIGHT / float(distanceToWall) - lookY;
            worldFloor = SCREEN_HEIGHT - worldCeiling - 2 * lookY;
			for (int row = 0; row < SCREEN_HEIGHT; row++) {
                if (row < worldCeiling)
                    screen[row*SCREEN_WIDTH + col] = CLEAR_SHADE; // sky
                else if (row >= worldCeiling && row < worldFloor)
                    screen[row*SCREEN_WIDTH + col] = wallShade; // wall
				else {
					screen[row*SCREEN_WIDTH + col] = FLOOR_SHADE; // floor
				}
			}
		}

        // check how much the mouse has moved (not optimal place to put it as it greatly depends on frame time
        rotatationCheck();

        // frame counter
        swprintf_s(screen, 10, L" FPS %3.0f", 1.f / fpsNormalise);

		// draw the screen array to the buffer
		WriteConsoleOutputCharacter(consoleBuffer, screen, SCREEN_PIXEL_COUNT, SCREEN_DRAW_START, &bytesWritten);
	}
    return 0;
}