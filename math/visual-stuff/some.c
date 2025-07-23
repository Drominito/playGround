#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <fenv.h>

int main(void)
{
    initscr();
    int x, y;
    for (y = 0; y < 10; y++) {
        mvprintw(10+y, 10+y, "Hello! :D");
        sleep(1);
        refresh();
    }
    getch();
    endwin();

  return(0);
}
