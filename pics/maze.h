
#ifndef MAZE_h
#define MAZE_h

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm> 
#include <string.h>


#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define uDiv 1
#define vDiv 1
#define vMove 0.0
#define imgCount 12

#define numSprites 20


typedef struct
{
  SDL_Window* gWindow;
  SDL_Renderer* gRenderer;
  SDL_Surface* pixel_surface;
  SDL_Texture* gTexture;
} sdl_params;

struct Sprite
{
  double x;
  double y;
  int texture;
};

typedef struct
{
  double posX;
  double posY;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
} mazeWorld;



//struct ColorRGBA8bit;
//a color with 4 components: r, g, b and a

struct ColorRGBA
{
  int r;
  int g;
  int b;
  int a;

  ColorRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  // ColorRGBA(const ColorRGBA8bit& color);
  ColorRGBA();
};

ColorRGBA operator+(const ColorRGBA& color, const ColorRGBA& color2);
ColorRGBA operator-(const ColorRGBA& color, const ColorRGBA& color2);
ColorRGBA operator*(const ColorRGBA& color, int a);
ColorRGBA operator*(int a, const ColorRGBA& color);
ColorRGBA operator/(const ColorRGBA& color, int a);
ColorRGBA overlay(const ColorRGBA& color, const ColorRGBA& color2);
bool operator==(const ColorRGBA& color, const ColorRGBA& color2);
bool operator!=(const ColorRGBA& color, const ColorRGBA& color2);

static const ColorRGBA RGB_Black    (  0,   0,   0, 255);
static const ColorRGBA RGB_Red		(255,   0,   0, 255);
static const ColorRGBA RGB_Green	(  0, 255,   0, 255);
static const ColorRGBA RGB_Blue		(  0,   0, 255, 255);
static const ColorRGBA RGB_Cyan		(  0, 255, 255, 255);
static const ColorRGBA RGB_Magenta	(255,   0, 255, 255);
static const ColorRGBA RGB_Yellow	(255, 255,   0, 255);
static const ColorRGBA RGB_White	(255, 255, 255, 255);
static const ColorRGBA RGB_Gray		(128, 128, 128, 255);
static const ColorRGBA RGB_Grey		(192, 192, 192, 255);
static const ColorRGBA RGB_Maroon	(128,   0,   0, 255);
static const ColorRGBA RGB_Darkgreen(  0, 128,   0, 255);
static const ColorRGBA RGB_Navy		(  0,   0, 128, 255);
static const ColorRGBA RGB_Teal		(  0, 128, 128, 255);
static const ColorRGBA RGB_Purple	(128,   0, 128, 255);
static const ColorRGBA RGB_Olive	(128, 128,   0, 255);

void sortSprites(int* order, double* dist, int amount);
void sprite_cast(Uint32 **texture);

bool init();
void close();

void floce_cast(Uint32 **texture);
void wall_cast(Uint32 **texture);

void lock(SDL_Surface *surface);
void unlock(SDL_Surface *surface);
void blitBuffer(Uint32* buf);
void loadImage(Uint32* buf, std::string path);

void render();
void motion_events(double time, double oldtime);
void resetBuffer();

void loadMap(char *fileName);
int *mapParser(char *filename, int width, int height);
//void loadMap(std::string path); 
//int *mapParser(std::string path, int width, int height);



extern sdl_params *sdl;
extern mazeWorld mW;
extern double ZBuffer[SCREEN_WIDTH];
extern Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
//extern std::vector<Uint32> texture;
//extern Uint32 **texture;

extern int worldMap[mapWidth][mapHeight];

#endif
