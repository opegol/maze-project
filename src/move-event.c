#include "maze.h"

void render();
void motion_events(double time, double oldTime);

void render()
{
  SDL_UpdateTexture(sdl->gTexture, NULL, sdl->pixel_surface->pixels, sdl->pixel_surface->pitch);
  SDL_RenderClear( sdl->gRenderer );
  SDL_RenderCopy( sdl->gRenderer, sdl->gTexture, NULL, NULL );
  SDL_RenderPresent( sdl->gRenderer);
}

       
void motion_events(double time, double oldTime)
{        
  //double *time = 0; //time of current frame
  //Uint32 oldtime; //time of previous frame
  double frameTime, moveSpeed, rotSpeed, oldDirX, oldPlaneX;
  const Uint8* currentKeyStates;


  oldTime = time;
  time = SDL_GetTicks();
  frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
  
  /*
  SDL_UpdateTexture(gTexture, NULL, pixel_surface->pixels, pixel_surface->pitch);
  SDL_RenderClear( gRenderer );
  SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
  SDL_RenderPresent( gRenderer);
  */
  render();
  //speed modifiers
  moveSpeed = 0.02; //frameTime * 5.0; //the constant value is in squares/second
  rotSpeed = 0.01; //frameTime * 3.0; //the constant value is in radians/second
  
  //move forward if no wall in front of you
  currentKeyStates = SDL_GetKeyboardState( NULL );
  if( currentKeyStates[ SDL_SCANCODE_UP ] )
  {
  
  if(worldMap[int(mW.posX + mW.dirX * moveSpeed)][int(mW.posY)] == false) mW.posX += mW.dirX * moveSpeed;
  if(worldMap[int(mW.posX)][int(mW.posY + mW.dirY * moveSpeed)] == false) mW.posY += mW.dirY * moveSpeed;
  }
  //move backwards if no wall behind you  //move backwards if no wall behind you
  else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
  {
    //currentTexture = &gDownTexture;
    if(worldMap[int(mW.posX - mW.dirX * moveSpeed)][int(mW.posY)] == false) mW.posX -= mW.dirX * moveSpeed;
    if(worldMap[int(mW.posX)][int(mW.posY - mW.dirY * moveSpeed)] == false) mW.posY -= mW.dirY * moveSpeed;
  }
  else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
  {
      //both camera direction and camera plane must be rotated
    oldDirX = mW.dirX;
    mW.dirX = mW.dirX * cos(rotSpeed) - mW.dirY * sin(rotSpeed);
    mW.dirY = oldDirX * sin(rotSpeed) + mW.dirY * cos(rotSpeed);
    oldPlaneX = mW.planeX;
    mW.planeX = mW.planeX * cos(rotSpeed) - mW.planeY * sin(rotSpeed);
    mW.planeY = oldPlaneX * sin(rotSpeed) + mW.planeY * cos(rotSpeed);
  }
  else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
  {
    //currentTexture = &gRightTexture;
    //both camera direction and camera plane must be rotated
    oldDirX = mW.dirX;
    mW.dirX = mW.dirX * cos(-rotSpeed) - mW.dirY * sin(-rotSpeed);
    mW.dirY = oldDirX * sin(-rotSpeed) + mW.dirY * cos(-rotSpeed);
    oldPlaneX = mW.planeX;
    mW.planeX = mW.planeX * cos(-rotSpeed) - mW.planeY * sin(-rotSpeed);
    mW.planeY = oldPlaneX * sin(-rotSpeed) + mW.planeY * cos(-rotSpeed);
  }
  else
  {
    
  }
}      
      
