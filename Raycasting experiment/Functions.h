void move(float direction) {
    float x_move = direction * float(sinf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
    float y_move = direction * float(cosf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
    if (map[int(playerY + y_move) * MAP_WIDTH + int(playerX + x_move)] != '#') { // check if the loc we want to go to is a wall, if it's not, move to loc
        playerX += x_move; playerY += y_move;
    }
}

void rotate(float direction) {
    playerYaw += direction * float(ROTATIONAL_STEP * fpsNormalise);
}

void shadeWall() {
    if (distanceToWall <= MAX_DEPTH / 6.f)      wallShade = WALL_SHADE_BLACK;
    else if (distanceToWall < MAX_DEPTH / 4.f)  wallShade = WALL_SHADE_DARK;
    else if (distanceToWall < MAX_DEPTH / 2.f)  wallShade = WALL_SHADE_MEDIUM;
    else if (distanceToWall < MAX_DEPTH)        wallShade = WALL_SHADE_LIGHT;
    else                                        wallShade = CLEAR_SHADE;    
    if(blockBoundary)                           wallShade = CLEAR_SHADE; // adds the division between different blocks
}