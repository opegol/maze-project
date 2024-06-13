#include "maze.h"

void floce_cast(Uint32 **texture);
void wall_cast(Uint32 **texture);



void floce_cast(Uint32 **texture)
{
  int x, y, p, ty, tx;
  int checkerBoardPattern, floorTexture, ceilingTexture;
  Uint32 color;
  float posZ, rowDistance, floorX, floorY, cellX, cellY;
  float rayDirX0, rayDirY0, rayDirX1, rayDirY1;
  float floorStepX, floorStepY;

  //FLOOR CASTING
  for(y = SCREEN_HEIGHT / 2 + 1; y < SCREEN_HEIGHT; ++y)
  {
    // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
    rayDirX0 = mW.dirX - mW.planeX;
    rayDirY0 = mW.dirY - mW.planeY;
    rayDirX1 = mW.dirX + mW.planeX;
    rayDirY1 = mW.dirY + mW.planeY;

    // Current y position compared to the center of the screen (the horizon)
    p = y - SCREEN_HEIGHT / 2;

    // Vertical position of the camera.
    posZ = 0.5 * SCREEN_HEIGHT;

    // Horizontal distance from the camera to the floor for the current row.
    // 0.5 is the z position exactly in the middle between floor and ceiling.
    rowDistance = posZ / p;

    // calculate the real world step vector we have to add for each x (parallel to camera plane)
    // adding step by step avoids multiplications with a weight in the inner loop
    floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
    floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

    // real world coordinates of the leftmost column. This will be updated as we step to the right.
    floorX = mW.posX + rowDistance * rayDirX0;
    floorY = mW.posY + rowDistance * rayDirY0;

    for( x = 0; x < SCREEN_WIDTH; ++x)
    {
      // the cell coord is simply got from the integer parts of floorX and floorY
      cellX = (int)(floorX);
      cellY = (int)(floorY);

      // get the texture coordinate from the fractional part
      tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
      ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

      floorX += floorStepX;
      floorY += floorStepY;

      // choose texture and draw the pixel
      checkerBoardPattern = (int(cellX + cellY)) & 1;
      //floorTexture;
      if(checkerBoardPattern == 0) floorTexture = 3;
      else floorTexture = 4;
      ceilingTexture = 6;
      //Uint32 color;

      // floor
      color = texture[floorTexture][texWidth * ty + tx];
      color = (color >> 1) & 8355711; // make a bit darker
      buffer[y][x] = color;

      //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
      color = texture[ceilingTexture][texWidth * ty + tx];
      color = (color >> 1) & 8355711; // make a bit darker
      //buffer[SCREEN_HEIGHT - y - 1][x] = color;
      buffer[SCREEN_HEIGHT - y + 1][x] = color;
    }
  }
}


void wall_cast(Uint32 **texture)
{
  int x, y, stepX, stepY, side, texX, texY;
  int hit;
  double cameraX, rayDirX, rayDirY, texPos, step, wallX;
  double deltaDistX, deltaDistY, perpWallDist, sideDistX, sideDistY;
  int mapX, mapY, lineHeight, pitch, texNum, drawStart, drawEnd;
  Uint32 color;
            
  //WALL CASTING
  for(x = 0; x < SCREEN_WIDTH; x++)
  {
    //calculate ray position and direction
    cameraX = 2 * x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
    rayDirX = mW.dirX + mW.planeX * cameraX;
    rayDirY = mW.dirY + mW.planeY * cameraX;
    //which box of the map we're in
    mapX = int(mW.posX);
    mapY = int(mW.posY);

    //length of ray from current position to next x or y-side
    //double sideDistX;
    //double sideDistY;

    deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

    //double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    //stepY;
    //stepX;

    hit = 0; //was there a wall hit?
    //int side; //was a NS or a EW wall hit?
    //calculate step and initial sideDist
    if(rayDirX < 0)
    {
      stepX = -1;
      sideDistX = (mW.posX - mapX) * deltaDistX;
    }
    else
    {
      stepX = 1;
      sideDistX = (mapX + 1.0 - mW.posX) * deltaDistX;
    }
    if(rayDirY < 0)
    {
      stepY = -1;
      sideDistY = (mW.posY - mapY) * deltaDistY;
    }
    else
    {
      stepY = 1;
      sideDistY = (mapY + 1.0 - mW.posY) * deltaDistY;
    }
    //perform DDA
    while(hit == 0)
    {
      //jump to next map square, either in x-direction, or in y-direction
      if(sideDistX < sideDistY)
      {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;
      }
      else
      {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;
      }
      //Check if ray has hit a wall
      if(worldMap[mapX][mapY] > 0) hit = 1;
    }
    
    if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);

    //Calculate height of line to draw on screen
    lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

    pitch = 50;

    //calculate lowest and highest pixel to fill in current stripe
    drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;
    if(drawStart < 0) drawStart = 0;
    drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;
    if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

    //texturing calculations
    texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

    //calculate value of wallX
    //wallX; //where exactly the wall was hit
    if(side == 0) wallX = mW.posY + perpWallDist * rayDirY;
    else          wallX = mW.posX + perpWallDist * rayDirX;
    wallX -= floor((wallX));

    //x coordinate on the texture   
    texX = int(wallX * double(texWidth));
    if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
    if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
    // How much to increase the texture coordinate per screen pixel
    step = 1.0 * texHeight / lineHeight;
    // Starting texture coordinate
    texPos = (drawStart - pitch - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
    for(y = drawStart; y < drawEnd; y++)
    {
      // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
      texY = (int)texPos & (texHeight - 1);
      texPos += step;
      //if (texNum < 0) texNum = 0;
      color = texture[texNum][texHeight * texY + texX];
      //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
      if(side == 1) color = (color >> 1) & 8355711;
      buffer[y][x] = color;
    }    
      ZBuffer[x] = perpWallDist; //perpendicular distance is used
  }
}


    
        