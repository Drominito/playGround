#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <fenv.h>

#define s 46
#define o s
#define pi 3.14
#define scale 2

#define xcols 191
#define ylines 104

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Matrix {
    char x[xcols];
    char y[ylines];
};



int main(void)
{
    float y;
    float rx, ry;
    float t;
    float limit = 3.14*2;
    float fps = 10;
    float latency = 1 / fps;
    float duration = 10; // in seconds
    int scaling = 6; // the smaller the bigger the object
    float quality=2;
    float t_steps=0.005;
    int mframes=20;
    // 0.25 * x

    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);


    struct Matrix mesharr[5]; 

    int count = 0;
    // time
    for (t = 0; t < duration; t+=t_steps*mframes) {
        for (int i = 9; i < mframes; i++) {
            y = 0;
          // mesh function
          for (y = 0; y < limit * 2; y += 0.0005) {
                  float nx = quality * cos(y + t+(i*t_steps)) * s * scale + o * scale;
                  float ny = quality * sin(y + t+(i*t_steps)) * s + o;
                  float r_nx = ny * sin(t) / scaling + 50;
                  float r_ny = nx * cos(-t) / scaling + 100;

                  mesharr[i].x[MIN(xcols, (int)y)] = r_nx;
                  mesharr[i].y[MIN(ylines, (int)y)] = r_ny;

                  // 
                  //mvprintw(r_nx, r_ny, "X");


                  attron(COLOR_PAIR(1));
                  mvprintw(mesharr[i+1].x[MIN(xcols, (int)y)],
                  mesharr[i+1].y[MIN(ylines, (int)y)] , "X");
                  attroff(COLOR_PAIR(1));
                  //count++;
          }
          refresh();
          clear();

        }


        
    }

   /*
   for (int i = 0; i < mframes; i++) {
          // mesh function
          for (y = 0; y < limit * 2; y += t_steps) {
                mvprintw(mesharr[i].x[(int)y],
                         mesharr[i].y[(int)y],
                         "-");

                mvprintw(mesharr[i].x[MIN(xcols, (int)y)],
                         mesharr[i].y[MIN(ylines, (int)y)],
                         "0");

                
          }    
          sleep(latency);
          refresh();

        clear();
        } 

*/
    
    refresh();
    printf("Bye!\n");
    getch();
    endwin();

  return(0);
}
