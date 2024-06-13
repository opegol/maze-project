#include "maze.h"

void lock(SDL_Surface *surface);
void unlock(SDL_Surface *surface);
void blitBuffer(Uint32* buf);
void loadImage(Uint32* buf, std::string path);



//Create surface from pixels
SDL_Surface* pixel_surface = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

  //4(bytes) is 32 pixel-bits/8bits
 


//Locks the screen
	void lock(SDL_Surface *surface)
	{
		if (SDL_MUSTLOCK(surface))
			if (SDL_LockSurface(surface) < 0)
				return;
	}

	//Unlocks the screen
	void unlock(SDL_Surface *surface)
	{
		if (SDL_MUSTLOCK(surface))
			SDL_UnlockSurface(surface);
	}

//Draws a buffer of pixels to the screen
void blitBuffer(Uint32* buf)
{
  Uint32* bpix;
  int pitch = SCREEN_WIDTH * 4; 
  int x, y;

  bpix = (Uint32*)sdl->pixel_surface->pixels;

  for (y = 0; y < SCREEN_HEIGHT; y++)
  {
    for (x = 0; x < SCREEN_WIDTH; x++)
    {
      *bpix = buf[y * SCREEN_WIDTH + x];
      bpix++;
    }
    //bpix += pixel_surface->pitch / 4;
    //bpix -= SCREEN_WIDTH;
  }
}

void loadImage(Uint32* buf, std::string path)
{
  int  x, y;
	//Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	
  SDL_Surface* fmtSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
  
  //int width = fmtSurface->w;
  //int height = fmtSurface->h;
  //int pitch = fmtSurface->pitch;
  
  /*
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = texWidth;
  stretchRect.h = texHeight;
  SDL_BlitScaled( fmtSurface, NULL, BfmtSurface, &stretchRect );
  */
  lock(fmtSurface);
  Uint32 *pixels =(Uint32*)fmtSurface->pixels;
  unlock(fmtSurface);
  for (int  y = 0; y < texWidth; y++)
  {
    for (int x = 0; x < texHeight; x++)
    {
      buf[y * texWidth + x] = pixels[y * texWidth + x];
    }
  }
  SDL_FreeSurface( loadedSurface );
}

