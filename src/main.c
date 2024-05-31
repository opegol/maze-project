

int main(int argc, char ** argv)
{
    (void)argc;
    (void)argv; 

    SDL_Window * win;
    SDL_Renderer * ren;
    SDL_Event event;
    PLAYER_STRUCT player = {PLAYER_SPAWN_X, PLAYER_SPAWN_Y, PLAYER_SPAWN_DIR};
    SDL_Point walls[MAX_WALL_COUNT][2];
    int wallsCount = 0;
    int running = TRUE;

    win = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, 0);

    FILE* fp;
    fp = fopen("map.txt", "r");

    char buffer[MAX_BUFFER_SIZE];
    char *token;
    while (fgets(buffer, MAX_BUFFER_SIZE - 1, fp))
    {
        token = strtok(buffer, MAP_DATA_SEPERATOR);
        walls[wallsCount][0].x = atoi(token);
        token = strtok(NULL, MAP_DATA_SEPERATOR);
        walls[wallsCount][0].y = atoi(token);
        token = strtok(NULL, MAP_DATA_SEPERATOR);
        walls[wallsCount][1].x = atoi(token);
        token = strtok(NULL, MAP_DATA_SEPERATOR);
        walls[wallsCount][1].y = atoi(token);
        wallsCount++;
    }

    fclose(fp); // Close your darn files

    // Main event loop
    while (running)
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT)
            {
                running = FALSE;
            }
        }

        // Handle KeyBoard
        player = MovePlayer(player);

        // Render world
        DrawWalls(ren, walls, wallsCount);
        DrawRays(ren, player, walls, wallsCount);
        DrawPlayer(ren, player);
        SendFrame(ren);

        SDL_Delay(FRAME_RENDER_DELAY);
    }

    // Destroy the window and renderer
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    return 0;
}


int PointOnLine(int x1, int y1, int x2, int y2, int tx, int ty)
{
    // Check if a point is on a line segment
    if (fmin(x1, x2) <= tx && tx <= fmax(x1, x2) && fmin(y1, y2) <= ty  && ty <= fmax(y1, y2))
    {
        return TRUE;
    }

    return FALSE;
}

int PointDistance(int x1, int y1, int x2, int y2)
{
    // Find the distance between two points
    int out = sqrt( pow(x2 - x1, 2) + pow(y2 - y1, 2) );
    return out;
}


void SendFrame(SDL_Renderer * ren)
{
    // Push the frame stored in the renderer to the screen
    COLOR_BLACK(ren);
    SDL_RenderPresent(ren);
    SDL_RenderClear(ren);
}
