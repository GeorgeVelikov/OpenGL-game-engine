void playerMove(float player_angle) {
    player_angle += -player.cameraYaw.x + PI/2;
    float x_move = cosf(player_angle + PI * 2) * MOVEMENT_STEP;
    float y_move = sinf(player_angle + PI * 2) * MOVEMENT_STEP;

    x_move *= fpsNormalise;
    y_move *= fpsNormalise;

    if (map[int(player.location.y + y_move) * MAP_WIDTH + int(player.location.x + x_move)] != '#') { // check if the loc we want to go to is a wall, if it's not, move to loc
        player.location.x += x_move;
        player.location.y += y_move;
    }
}

void rotatationCheck() {
    GetCursorPos(&currentPoint);
    // left - right
    if (windowMidX != currentPoint.x)
    {
        player.cameraYaw.x -= (windowMidX - currentPoint.x) * ROTATIONAL_STEP * fpsNormalise;
        player.cameraYaw.x = fmod(player.cameraYaw.x, 2 * PI);
    }

    // up - down
    if (windowMidY != currentPoint.y)
    {
        if (windowMidY < currentPoint.y - 1 && player.cameraYaw.y <= 360) player.cameraYaw.y += SCREEN_HEIGHT *fpsNormalise;
        else if (windowMidY > currentPoint.y +1 && player.cameraYaw.y >= -360) player.cameraYaw.y -= SCREEN_HEIGHT * fpsNormalise;
    }
}

void shadeWall() {
    if (distanceToWall <= MAX_DEPTH / 6.f)      wallShade = WALL_SHADE_BLACK;
    else if (distanceToWall < MAX_DEPTH / 4.f)  wallShade = WALL_SHADE_DARK;
    else if (distanceToWall < MAX_DEPTH / 2.f)  wallShade = WALL_SHADE_MEDIUM;
    else if (distanceToWall < MAX_DEPTH)        wallShade = WALL_SHADE_LIGHT;
    else                                        wallShade = CLEAR_SHADE;    
    if(blockBoundary)                           wallShade = CLEAR_SHADE; // adds the division between different blocks
}

void setCursorMidScreen() {
    RECT rect = { NULL };
    if (GetWindowRect(GetConsoleWindow(), &rect)) { windowStartX = rect.left; windowStartY = rect.top; }
    windowMidX = windowStartX + (SCREEN_WIDTH * PIXEL_SIZE_WIDTH / 2); 
    windowMidY = windowStartY + (SCREEN_HEIGHT * PIXEL_SIZE_HEIGHT / 2); 
    SetCursorPos(windowMidX, windowMidY);
}

void setWindowCentered() {
    HWND consoleWindow = GetConsoleWindow();
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    int locMidX = desktop.right / 2 - SCREEN_MID_TO_LEFT;
    int locMidY = desktop.bottom / 2 - SCREEN_MID_TO_TOP;
    MoveWindow(consoleWindow, locMidX, locMidY, desktop.right, desktop.bottom, TRUE);
}