void renderwaves(Uint64 aTicks)
{
  float t = SDL_GetTicks()/300;
  int pos     = 200,
      speed   = 25,
     high     = 5  ,
      modus   = 10,
      strength = 100 ;

  float mx = 3.1415+(2500/speed)/high;
  float my = 3.1415+(2500/speed)/high;

  int viewx = 100,
      viewy = 100;

  

  for (int i = 0, c = 0; i < WINDOW_HEIGHT; i++) {
      for (int j = 0; j < WINDOW_WIDTH; j++, c++) {
        gFrameBuffer[c] = 0xff000000;
      }
  }

  for (int i = 0; i < 500; i++) {
      for (int j = 0; j < 500; j++) {
          if ((j*j+i*i)/2 > 500/2+(SDL_GetTicks()/100))
          {
            drawsprite(j- sin(mx/viewx*i/modus)*strength, i+ cos(my/viewy*j/modus+t)*strength, i*i+j*j | 0xffff0000);
          }
          else 
          {
            drawsprite(j+ sin(mx/viewx*i/modus)*strength, i+ cos(my/viewy*j/modus)*strength, 0x01ff0000);
          }
      }
  }
}

void pseudo3D(Uint64 aTicks)
{
  float rxm, rym;
  SDL_GetMouseState(&rxm, &rym);
  float xm = rxm / 50;
  float ym = rym / 50;

  
  for (int i = 0, c = 0; i < WINDOW_HEIGHT; i++) {
    for (int j = 0; j < WINDOW_WIDTH; j++, c++) {
      gFrameBuffer[c] = 0xff000000;
    }
  }

  for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        if (i == i + j || j == i + j) {
            drawsprite(500+j*sin(xm)+i*cos(xm),200+j*cos(ym)-i*sin(ym), 0xffff0000);
        }
        else if (i < j) {
            drawsprite(500+j*sin(xm)+i*cos(xm),200+j*cos(ym)-i*sin(ym), 0xff00ff00);
        }
        else if (i > j) {
            drawsprite(500+j*sin(xm)+i*cos(xm),200+j*cos(ym)-i*sin(ym), 0xff0000ff);
        }

      }
  }
}
