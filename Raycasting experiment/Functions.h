void moveFB(float direction) {
    float x_move = direction * float(sinf(player.cameraX) * MOVEMENT_STEP * fpsNormalise);
    float y_move = direction * float(cosf(player.cameraX) * MOVEMENT_STEP * fpsNormalise);
    if (map[int(player.location.y + y_move) * MAP_WIDTH + int(player.location.x + x_move)] != '#') { // check if the loc we want to go to is a wall, if it's not, move to loc
        player.location.x += x_move; player.location.y += y_move;
    }
}

void moveLR(float direction) {
    int x_sign = 1;
    int y_sign = 1;

    // split viewing area into 4 quadrants 
    if (player.cameraX > -PI && player.cameraX <= -PI / 2.f) { x_sign = -1; y_sign = +1; }
    else if (player.cameraX > -PI / 2.f && player.cameraX <= 0) { x_sign = +1; y_sign = +1; }
    else if (player.cameraX > 0 && player.cameraX <= PI / 2.f) { x_sign = +1; y_sign = -1; }
    else if (player.cameraX > PI / 2.f && player.cameraX <= PI) { x_sign = -1; y_sign = -1; }

    float x_move = x_sign * direction * float(pow(cosf(player.cameraX), 2) * MOVEMENT_STEP / 2 * fpsNormalise);
    float y_move = y_sign * direction * float(pow(sinf(player.cameraX), 2) * MOVEMENT_STEP / 2 * fpsNormalise);

    if (map[int(player.location.y + y_move) * MAP_WIDTH + int(player.location.x + x_move)] != '#') { // check if the loc we want to go to is a wall, if it's not, move to loc
        player.location.x += x_move; player.location.y += y_move;
    }
}

void rotatationCheck() {
    GetCursorPos(&currentPoint);
    // left - right
    if (windowMidX != currentPoint.x)
    {
        player.cameraX -= (windowMidX - currentPoint.x) * ROTATIONAL_STEP * fpsNormalise;
        // limit playerYaw to be in the range -PI to PI
        if (player.cameraX < -PI) player.cameraX = 2 * PI - player.cameraX;
        else if (player.cameraX > +PI) player.cameraX = player.cameraX - 2 * PI;
    }

    // up - down
    if (windowMidY != currentPoint.y)
    {
        if (windowMidY < currentPoint.y -1 && player.cameraY <= 360) player.cameraY += SCREEN_HEIGHT * fpsNormalise;
        else if (windowMidY > currentPoint.y +1 && player.cameraY >= -360) player.cameraY -= SCREEN_HEIGHT * fpsNormalise;
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