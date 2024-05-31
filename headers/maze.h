#include <SDL2/SDL.h>   // Library for drawing
#include <stdio.h>
#include <string.h>

#define WINDOW_TITLE "Raycasting with SDL2 (MapEditor)"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#define TRUE 1
#define FALSE 0

// Macros to set the color of the renderer
#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255);
#define COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255);

#define MAX_WALL_COUNT 128
#define MAX_BUFFER_SIZE 20
#define MAP_DATA_SEPERATOR "," // Character used to split the data in map.txt

void DrawWalls(SDL_Renderer * ren, SDL_Point walls[MAX_WALL_COUNT][2], int wallCount);
void SendFrame(SDL_Renderer * ren);
