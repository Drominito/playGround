// Of an image
// Release build -> Cmake

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

int* gTempBuffer;
int* gFrameBuffer;
SDL_Window* gSDLWindow;
SDL_Renderer* gSDLRenderer;
SDL_Texture* gSDLTexture;
static int gDone;
const int WINDOW_WIDTH = 1920 / 2;
const int WINDOW_HEIGHT = 1080 / 2;

bool update()
{
  SDL_Event e;
  if (SDL_PollEvent(&e))
  {
    if (e.type == SDL_EVENT_QUIT)
    {
      return false;
    }
    if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE)
    {
      return false;
    }
  }

  char* pix;
  int pitch;

  SDL_LockTexture(gSDLTexture, NULL, (void**)&pix, &pitch);
  for (int i = 0, sp = 0, dp = 0; i < WINDOW_HEIGHT; i++, dp += WINDOW_WIDTH, sp += pitch)
    memcpy(pix + sp, gFrameBuffer + dp, WINDOW_WIDTH * 4);

  SDL_UnlockTexture(gSDLTexture);
  SDL_RenderTexture(gSDLRenderer, gSDLTexture, NULL, NULL);
  SDL_RenderPresent(gSDLRenderer);
  SDL_Delay(1);
  return true;
}

void init()
{
  gTempBuffer = new int[WINDOW_WIDTH * WINDOW_HEIGHT];
  for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++)
  {
    gFrameBuffer[i] = 0xff000000;
    gTempBuffer[i] = 0xff000000;
  }
}






unsigned int blend_avg(int source, int target)
{
  unsigned int sourcer = ((unsigned int)source >> 0) & 0xff;
  unsigned int sourceg = ((unsigned int)source >> 8) & 0xff;
  unsigned int sourceb = ((unsigned int)source >> 16) & 0xff;
  unsigned int targetr = ((unsigned int)target >> 0) & 0xff;
  unsigned int targetg = ((unsigned int)target >> 8) & 0xff;
  unsigned int targetb = ((unsigned int)target >> 16) & 0xff;

  targetr = (sourcer + targetr) / 2;
  targetg = (sourceg + targetg) / 2;
  targetb = (sourceb + targetb) / 2;

  return (targetr << 0) |
    (targetg << 8) |
    (targetb << 16) |
    0xff000000;
}

unsigned int blend_mul(int source, int target)
{
    unsigned int sourcer = ((unsigned int)source >> 0) & 0xff;
    unsigned int sourceg = ((unsigned int)source >> 8) & 0xff;
    unsigned int sourceb = ((unsigned int)source >> 16) & 0xff;
    unsigned int targetr = ((unsigned int)target >> 0) & 0xff;
    unsigned int targetg = ((unsigned int)target >> 8) & 0xff;
    unsigned int targetb = ((unsigned int)target >> 16) & 0xff;

    targetr = (sourcer * targetr) >> 8;
    targetg = (sourceg * targetg) >> 8;
    targetb = (sourceb * targetb) >> 8;

    return (targetr << 0) |
        (targetg << 8) |
        (targetb << 16) |
        0xff000000;
}

unsigned int blend_add(int source, int target)
{
    unsigned int sourcer = ((unsigned int)source >> 0) & 0xff;
    unsigned int sourceg = ((unsigned int)source >> 8) & 0xff;
    unsigned int sourceb = ((unsigned int)source >> 16) & 0xff;
    unsigned int targetr = ((unsigned int)target >> 0) & 0xff;
    unsigned int targetg = ((unsigned int)target >> 8) & 0xff;
    unsigned int targetb = ((unsigned int)target >> 16) & 0xff;

    targetr += sourcer;
    targetg += sourceg;
    targetb += sourceb;

    if (targetr > 0xff) targetr = 0xff;
    if (targetg > 0xff) targetg = 0xff;
    if (targetb > 0xff) targetb = 0xff;

    return (targetr << 0) |
        (targetg << 8) |
        (targetb << 16) |
        0xff000000;
}

void scaleblit()
{
    int yofs = 0;
    for (int i = 0; i < WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH; j++)
        {
            int c =
                (int)((i * 0.95) + (WINDOW_HEIGHT * 0.025)) * WINDOW_WIDTH +
                (int)((j * 0.95) + (WINDOW_WIDTH * 0.025));
                gFrameBuffer[yofs + j] =
                blend_mul(gFrameBuffer[yofs + j], gTempBuffer[c]);
    }
    yofs += WINDOW_WIDTH;
  }
}


void drawsprite(int x, int y, unsigned int color)
{

  int d = 6;
  int i, j, c, yofs;
  yofs = y * WINDOW_WIDTH + x;
  for (i = 0, c = 0; i < d; i++)
  {
    for (j = 0; j < d; j++, c++)
    {
        gFrameBuffer[yofs + j] = color;
    }
    yofs += WINDOW_WIDTH;
  }
}

void newsnow()
{
  float rxm, rym;
  SDL_GetMouseState(&rxm, &rym);
  float xm = rxm / 50;
  float ym = rym / 50;
  int a = 50;

  for (int i = 0; i < 8; i++) {
    //the cloud
    drawsprite(80+xm*45, 40+ym*45, 0xffaaaaaa);

    gFrameBuffer[rand() % 33 + 50] = 0xffffffff;
  }
}

void snowfall()
{

  for (int j = WINDOW_HEIGHT; j >= 0; j--)
  {
    int ypos = j * WINDOW_WIDTH;
    for (int i = 1; i < WINDOW_WIDTH; i++)
    {
      if (gFrameBuffer[ypos + i] == 0xffffffff)
      {
            if (gFrameBuffer[ypos + i + WINDOW_WIDTH] == 0xff000000 )
            {
              gFrameBuffer[ypos + i + WINDOW_WIDTH] = 0xffffffff;
              gFrameBuffer[ypos + i] = 0xff000000;
            }
            else {
                if (gFrameBuffer[ypos + i + WINDOW_WIDTH - 1] == 0xff000000)
                {
                  gFrameBuffer[ypos + i + WINDOW_WIDTH - 1] = 0xffffffff;
                  gFrameBuffer[ypos + i] = 0xff000000;
                }
                else {
                    if (gFrameBuffer[ypos + i + WINDOW_WIDTH + 1] == 0xff000000)
                    {
                      gFrameBuffer[ypos + i + WINDOW_WIDTH + 1] = 0xffffffff;
                      gFrameBuffer[ypos + i] = 0xff000000;
                    }
                }
            }
      }
    }
  }
}

void render(Uint64 aTicks)
{
  for (int i = 0; i < 128; i++)
  {
    int d = (int)aTicks + i * 4;
    drawsprite((int)(WINDOW_WIDTH / 2 + sin(d * 0.0034) * sin(d * 0.0134) * (WINDOW_WIDTH / 2 - 20)),
        (int)(WINDOW_HEIGHT / 2 + sin(d * 0.0033) * sin(d * 0.0234) * (WINDOW_HEIGHT / 2 - 20)),
        ((int)(sin((aTicks * 0.2 + i) * 0.234897) * 12+12) << 16) |
        ((int)(sin((aTicks * 0.2 + i) * 0.123489) * 12+12) << 8) |
        ((int)(sin((aTicks * 0.2 + i) * 0.312348) * 12+12) << 0));
  }

  //memcpy(gTempBuffer, gFrameBuffer, sizeof(int) * WINDOW_WIDTH * WINDOW_HEIGHT);

  //scaleblit();
}


void loop()
{
  if (!update())
  {
    gDone = 1;
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
#endif
  }
  else
  {
    render(SDL_GetTicks());
  }
}

int main(int argc, char** argv)
{
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
  {
    return -1;
  }

  gFrameBuffer = new int[WINDOW_WIDTH * WINDOW_HEIGHT];
  gSDLWindow = SDL_CreateWindow("SDL3 window", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  gSDLRenderer = SDL_CreateRenderer(gSDLWindow, NULL);
  gSDLTexture = SDL_CreateTexture(gSDLRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

  if (!gFrameBuffer || !gSDLWindow || !gSDLRenderer || !gSDLTexture)
    return -1;

  init();
  gDone = 0;
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#else
  while (!gDone)
  {
    loop();
  }
#endif

  SDL_DestroyTexture(gSDLTexture);
  SDL_DestroyRenderer(gSDLRenderer);
  SDL_DestroyWindow(gSDLWindow);
  SDL_Quit();

  return 0;
}
