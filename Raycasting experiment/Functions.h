void move(float direction) {
    float x_move = direction * float(sinf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
    float y_move = direction * float(cosf(playerYaw) * MOVEMENT_STEP * fpsNormalise);

    if (map[int(playerY + y_move) * MAP_WIDTH + int(playerX + x_move)] != '#') {
        playerX += x_move; playerY += y_move;
    }
}

void rotation(float direction) {
    playerYaw += direction * float(ROTATIONAL_STEP * fpsNormalise);
}