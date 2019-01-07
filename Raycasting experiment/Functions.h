void move(float direction){
    playerX += direction * float(sinf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
    playerY += direction * float(cosf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
    if (map[int(playerY) * MAP_WIDTH + int(playerX)] == '#') {
        playerX -= direction * float(sinf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
        playerY -= direction * float(cosf(playerYaw) * MOVEMENT_STEP * fpsNormalise);
    }
}

void rotation(float direction) {
    playerYaw += direction * float(ROTATIONAL_STEP * fpsNormalise);
}