

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
