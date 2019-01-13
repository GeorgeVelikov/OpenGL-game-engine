void moveFB(float direction) {
    float x_move = direction * float(sinf(cameraX) * MOVEMENT_STEP * fpsNormalise);
    float y_move = direction * float(cosf(cameraX) * MOVEMENT_STEP * fpsNormalise);
    if (map[int(playerY + y_move) * MAP_WIDTH + int(playerX + x_move)] != '#') { // check if the loc we want to go to is a wall, if it's not, move to loc
        playerX += x_move; playerY += y_move;
    }
}

void moveLR(float direction)
{
    int x_sign = 1;
    int y_sign = 1;

    // split viewing area into 4 quadrants 
    if (cameraX > -PI && cameraX <= -PI / 2.f) { x_sign = -1; y_sign = +1; }
    else if (cameraX > -PI / 2.f && cameraX <= 0) { x_sign = +1; y_sign = +1; }
    else if (cameraX > 0 && cameraX <= PI / 2.f) { x_sign = +1; y_sign = -1; }
    else if (cameraX > PI / 2.f && cameraX <= PI) { x_sign = -1; y_sign = -1; }

    float x_move = x_sign * direction * float(pow(cosf(cameraX), 2) * MOVEMENT_STEP / 2 * fpsNormalise);
    float y_move = y_sign * direction * float(pow(sinf(cameraX), 2) * MOVEMENT_STEP / 2 * fpsNormalise);

    if (map[int(playerY + y_move) * MAP_WIDTH + int(playerX + x_move)] != '#') { // check if the loc we want to go to is a wall, if it's not, move to loc
        playerX += x_move; playerY += y_move;
    }
}

void rotatationCheck() {
    GetCursorPos(&currentPoint);
    // left - right
    if (windowMidX != currentPoint.x)
    {
        cameraX -= (windowMidX - currentPoint.x) * ROTATIONAL_STEP * fpsNormalise;
        // limit playerYaw to be in the range -PI to PI
        if (cameraX < -PI) cameraX = 2 * PI - cameraX;
        else if (cameraX > +PI) cameraX = cameraX - 2 * PI;
    }

    // up - down
    if (windowMidY != currentPoint.y)
    {
        if (windowMidY < currentPoint.y -1 && cameraY <= 360) cameraY += SCREEN_HEIGHT * fpsNormalise;
        else if (windowMidY > currentPoint.y +1 && cameraY >= -360) cameraY -= SCREEN_HEIGHT * fpsNormalise;
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

void setCursorMidScreen()
{
    RECT rect = { NULL };
    if (GetWindowRect(GetConsoleWindow(), &rect)) { windowStartX = rect.left; windowStartY = rect.top; }
    windowMidX = windowStartX + (SCREEN_WIDTH * PIXEL_SIZE_WIDTH / 2); // 4 pix wide char
    windowMidY = windowStartY + (SCREEN_HEIGHT * PIXEL_SIZE_HEIGHT / 2); // 6 pix wide char
    SetCursorPos(windowMidX, windowMidY);
}

void setWindowCentered()
{
    HWND consoleWindow = GetConsoleWindow();
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    int locMidX = desktop.right / 2 - SCREEN_MID_TO_LEFT;
    int locMidY = desktop.bottom / 2 - SCREEN_MID_TO_TOP;
    MoveWindow(consoleWindow, locMidX, locMidY, desktop.right, desktop.bottom, TRUE);
}