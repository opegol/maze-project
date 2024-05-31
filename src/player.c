PLAYER_STRUCT MovePlayer(PLAYER_STRUCT player)
{
    // Get a snapshot of the keyboard
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    // Check what keys where held down and if we are not at the edge of the screen
    if (keys[SDL_SCANCODE_W] && player.y > PLAYER_STEP_SIZE)
    {
        player.y -= PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_A] && player.x > PLAYER_STEP_SIZE)
    {
        player.x -= PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_S] && player.y < WINDOW_HEIGHT - PLAYER_STEP_SIZE)
    {
        player.y += PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_D] && player.x < WINDOW_WIDTH /3 - PLAYER_STEP_SIZE)
    {
        player.x += PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_Q])
    {
        player.dir -= PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_E])
    {
        player.dir += PLAYER_STEP_SIZE;
    }

    return player;
}

SDL_Point CreateTarget(int x, int y, int dir, int dist)
{
    // Create point dist pixels away in dir direction from x and y
    SDL_Point target;

    double traslated = dir * (M_PI / 180.0); // Convert to radians
    target.x = round(x + dist * cos(traslated));
    target.y = round(y + dist * sin(traslated));

    return target;
}
