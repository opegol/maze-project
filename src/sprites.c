#include "maze.h"


void sortSprites(int* order, double* dist, int amount);
void sprite_cast(Uint32 **texture);


void sortSprites(int* order, double* dist, int amount)
{
  std::vector<std::pair<double, int>> sprites(amount);
  for(int i = 0; i < amount; i++) {
    sprites[i].first = dist[i];
    sprites[i].second = order[i];
  }
  std::sort(sprites.begin(), sprites.end());
  // restore in reverse order to go from farthest to nearest
  for(int i = 0; i < amount; i++) {
    dist[i] = sprites[amount - i - 1].first;
    order[i] = sprites[amount - i - 1].second;
  }
}

void sprite_cast(Uint32 **texture)
{
  int i, y, d, spriteScreenX, vMoveScreen, spriteHeight, spriteWidth, stripe;
  int drawStartX, drawStartY, drawEndX, drawEndY, texX, texY;
  double spriteX, spriteY, invDet, transformX, transformY;
  Uint32 color;
  int order[numSprites];
  double dist[numSprites];

  Sprite sprite[numSprites] =
  {
    {20.5, 11.5, 10}, //green light in front of playerstart
    
    //green lights in every room
    {18.5,4.5, 10},
    {10.0,4.5, 10},
    {10.0,12.5,10},
    {3.5, 6.5, 10},
    {3.5, 20.5,10},
    {3.5, 14.5,10},
    {14.5,20.5,10},

    //row of pillars in front of wall: fisheye test
    {18.5, 10.5, 9},
    {18.5, 11.5, 9},
    {18.5, 12.5, 9},

    //some barrels around the map
    {21.5, 1.5, 8},
    {15.5, 1.5, 8},
    {16.0, 1.8, 8},
    {16.2, 1.2, 8},
    {3.5,  2.5, 8},
    {9.5, 15.5, 8},
    {10.0, 15.1,8},
    {10.5, 15.8,8},
    
    //player
    {mW.dirX+20, mW.dirY+20, 11}

  };


  //SPRITE CASTING
  //sort sprites from far to close
  for(i = 0; i < numSprites; i++)
  {
    order[i] = i;
    dist[i] = ((mW.posX - sprite[i].x) * (mW.posX - sprite[i].x) + (mW.posY - sprite[i].y) * (mW.posY - sprite[i].y)); //sqrt not taken, unneeded
  }
  sortSprites(order, dist, numSprites);

  //after sorting the sprites, do the projection and draw them
  for(i = 0; i < numSprites; i++)
  {
    //translate sprite position to relative to camera
    spriteX = sprite[order[i]].x - mW.posX;
    spriteY = sprite[order[i]].y - mW.posY;

    //transform sprite with the inverse camera matrix
    // [ mW.planeX   mW.dirX ] -1                                       [ mW.dirY      -mW.dirX ]
    // [               ]       =  1/(mW.planeX*mW.dirY-mW.dirX*mW.planeY) *   [                 ]
    // [ mW.planeY   mW.dirY ]                                          [ -mW.planeY  mW.planeX ]

    invDet = 1.0 / (mW.planeX * mW.dirY - mW.dirX * mW.planeY); //required for correct matrix multiplication

    transformX = invDet * (mW.dirY * spriteX - mW.dirX * spriteY);
    transformY = invDet * (-mW.planeY * spriteX + mW.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(dist[i])

    spriteScreenX = int((SCREEN_WIDTH / 2) * (1 + transformX / transformY));

    //parameters for scaling and moving the sprites
    //#define uDiv 1
    //#define vDiv 1
    //#define vMove 0.0
    vMoveScreen = int(vMove / transformY);

    //calculate height of the sprite on screen
    spriteHeight = abs(int(SCREEN_HEIGHT / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
    //calculate lowest and highest pixel to fill in current stripe
    drawStartY = -spriteHeight / 2 + SCREEN_HEIGHT / 2 + vMoveScreen;
    if(drawStartY < 0) drawStartY = 0;
    drawEndY = spriteHeight / 2 + SCREEN_HEIGHT / 2 + vMoveScreen;
    if(drawEndY >= SCREEN_HEIGHT) drawEndY = SCREEN_HEIGHT - 1;

    //calculate width of the sprite
    spriteWidth = abs(int (SCREEN_HEIGHT / (transformY))) / uDiv; // same as height of sprite, given that it's square
    drawStartX = -spriteWidth / 2 + spriteScreenX;
    if(drawStartX < 0) drawStartX = 0;
    drawEndX = spriteWidth / 2 + spriteScreenX;
    if(drawEndX > SCREEN_WIDTH) drawEndX = SCREEN_WIDTH;

    //loop through every vertical stripe of the sprite on screen
    for(stripe = drawStartX; stripe < drawEndX; stripe++)
    {
      texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
      //the conditions in the if are:
      //1) it's in front of camera plane so you don't see things behind you
      //2) ZBuffer, with perpendicular distance
      if(transformY > 0 && transformY < ZBuffer[stripe])
      {
        for(y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          d = (y - vMoveScreen) * 256 - SCREEN_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          texY = ((d * texHeight) / spriteHeight) / 256;
          color = texture[sprite[order[i]].texture][texWidth * texY + texX]; //get current color from the texture
          if((color & 0xFFFFFF00) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
    }
  }
}
