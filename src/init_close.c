#include "maze.h"

bool init();
void close();


bool init()
{
	//Initialization flag
	bool success = true;
	int imgFlags;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		sdl->gWindow = SDL_CreateWindow( "ALX MAZE PROJECT REVIEW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( sdl->gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			sdl->gRenderer = SDL_CreateRenderer( sdl->gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( sdl->gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( sdl->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
      sdl->pixel_surface = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGBA8888);
		  if ( sdl->pixel_surface == NULL)
		  {
			  printf("Unable to set surface: %s\n", SDL_GetError());
			  success = false;
		  }
    
      sdl->gTexture = SDL_CreateTexture(sdl->gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
      if (sdl->gTexture == NULL)
      {
        printf("Unable to set texture: %s\n", SDL_GetError());
        success = false;
      }
      //SDL_SetTextureBlendMode(sdl->gTexture, SDL_BLENDMODE_BLEND);
	}
	}

	return success;
}


void close()
{
	//Free loaded image
	SDL_DestroyTexture( sdl->gTexture );
	sdl->gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( sdl->gRenderer );
	SDL_DestroyWindow( sdl->gWindow );
	SDL_FreeSurface(sdl->pixel_surface);
	sdl->gWindow = NULL;
	sdl->gRenderer = NULL;
	sdl->pixel_surface = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



