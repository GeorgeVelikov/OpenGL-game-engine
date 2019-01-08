void moveFB(float direction) {
    float x_move = direction * float(sinf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
    float y_move = direction * float(cosf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
    if (map[int(playerY + y_move) * MAP_WIDTH + int(playerX + x_move)] != '#') { // check if the loc we want to go to is a wall, if it's not, move to loc
        playerX += x_move; playerY += y_move;
    }
}

void moveLR(float direction)
{
    int x_sign = 1;
    int y_sign = 1;

    // split viewing area into 4 quadrants 
    if (playerYaw > -PI && playerYaw <= -PI / 2.f) { x_sign = -1; y_sign = +1; }
    else if (playerYaw > -PI / 2.f && playerYaw <= 0) { x_sign = +1; y_sign = +1; }
    else if (playerYaw > 0 && playerYaw <= PI / 2.f) { x_sign = +1; y_sign = -1; }
    else if (playerYaw > PI / 2.f && playerYaw <= PI) { x_sign = -1; y_sign = -1; }

    float x_move = x_sign * direction * float(pow(cosf(playerYaw), 2) * MOVEMENT_STEP / 2 * fpsNormalise);
    float y_move = y_sign * direction * float(pow(sinf(playerYaw), 2) * MOVEMENT_STEP / 2 * fpsNormalise);

    if (map[int(playerY + y_move) * MAP_WIDTH + int(playerX + x_move)] != '#') { // check if the loc we want to go to is a wall, if it's not, move to loc
        playerX += x_move; playerY += y_move;
    }
}

void rotate(float direction) {
    playerYaw += direction * float(ROTATIONAL_STEP * fpsNormalise);
    if (playerYaw < -PI) playerYaw = 2*PI - playerYaw;
    if (playerYaw > +PI) playerYaw = playerYaw - 2*PI ;
}

void shadeWall() {
    if (distanceToWall <= MAX_DEPTH / 6.f)      wallShade = WALL_SHADE_BLACK;
    else if (distanceToWall < MAX_DEPTH / 4.f)  wallShade = WALL_SHADE_DARK;
    else if (distanceToWall < MAX_DEPTH / 2.f)  wallShade = WALL_SHADE_MEDIUM;
    else if (distanceToWall < MAX_DEPTH)        wallShade = WALL_SHADE_LIGHT;
    else                                        wallShade = CLEAR_SHADE;    
    if(blockBoundary)                           wallShade = CLEAR_SHADE; // adds the division between different blocks
}