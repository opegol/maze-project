#include "maze.h"


void loadMap(char *filename)
//void loadMap(std::string path)
{
  int map[mapWidth][mapHeight];
  int x, y;
  int *map_buff;
  map_buff = mapParser(filename, mapWidth, mapHeight);
  if (map_buff)
  {
    for (x = 0; x < mapWidth; x++)
    {
      for(y = 0; y < mapHeight; y++)
        worldMap[x][y] = map_buff[x * mapWidth + y];
    }
  }
}


void resetBuffer()
{ 
  for(int y = 0; y < SCREEN_HEIGHT; y++) 
    for(int x = 0; x < SCREEN_WIDTH; x++) 
      buffer[y][x] = 0;
}

sdl_params *sdl = (sdl_params *)malloc(sizeof(sdl_params)); //NULL; //{NULL, NULL, NULL, NULL}
  //sdl->gWindow = NULL;
  //sdl->gRenderer = NULL;
  //sdl->pixel_surface = NULL;
  //sdl->gTexture = NULL;

Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH]; // = [resetBuffer()];

/*
int worldMap[mapWidth][mapHeight]=
  { 
    {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
    {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
    {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
    {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
    {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
    {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
    {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
    {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
    {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
    {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
    {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
    {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
    {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
    {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
    {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
    {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
    {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
    {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
    {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
  };
  */
  //int worldMap[mapWidth][mapHeight];
  loadMap("map1");

  mazeWorld mW = {22.0, 11.5, -1.0, 0.0, 0.0, 0.66};

  //std::vector<Uint32> texture[12];
  //for(int i = 0; i < 12; i++) texture[i].resize(texWidth * texHeight);


//1D Zbuffer
double ZBuffer[SCREEN_WIDTH];

//Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

int main( int argc, char* args[] )
{ 
  int i;

  //mW.posX = 22.0, mW.posY = 11.5;
  //mW.dirX = -1.0, mW.dirY = 0.0;
  //mW.planeX = 0, mW.planeY = 0.66; 
  bool quit = false;
  SDL_Event e;
  //std::vector<Uint32> texture[12];
  double time = 0;
  double oldtime = 0;
  Uint32 **texture;

  texture = (Uint32**)malloc(imgCount * sizeof(Uint32*));
  for(i = 0; i < imgCount; i++) 
    texture[i] = (Uint32 *)malloc(sizeof(Uint32) * texWidth * texHeight);


  //resetBuffer();
  //Start up SDL and create window
  if( !init() )
  {
    printf( "Failed to initialize!\n" );
  }
  else
    {
      loadImage(texture[0], "pics/eagle.png");
      loadImage(texture[1], "pics/redbrick.png");
      loadImage(texture[2], "pics/purplestone.png");
      loadImage(texture[3], "pics/greystone.png");
      loadImage(texture[4], "pics/bluestone.png");
      loadImage(texture[5], "pics/mossy.png");
      loadImage(texture[6], "pics/wood.png");
      loadImage(texture[7], "pics/colorstone.png");
  
      //load some sprite textures
      loadImage(texture[8], "pics/barrel.png");
      loadImage(texture[9], "pics/pillar.png");
      loadImage(texture[10], "pics/greenlight.png");

      loadImage(texture[11], "pics/shooter.png");

      //if(error) { std::cout << "error loading images" << std::endl; return 1; }

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
        }

        floce_cast(texture);
        wall_cast(texture);
        sprite_cast(texture);
        blitBuffer(buffer[0]); 
        resetBuffer();
        //render();
        motion_events(time, oldtime);
      }
    }
  
  close();

  return 0;
}
