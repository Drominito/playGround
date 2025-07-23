// TODO 
// More O's to collect "Like coins"
// Make it as an labyrinth
// If it detects a wall, it will decide other direction
// Enable not only 4 but 8 directions
// not just diagonal but make a direct angle to the "Coin"




//float shadowsize = 2.50f;
//srand(time(NULL));
//bool cirlce = pow(x-player.x,2)+pow(y-player.y,2) < sqrt(size)*shadowsize;
//int i = getIndex(y,size,x);
//getXYfrom1Darray(&pos, i, size);
//bool rule = (pos.x == pos.y);
//bool rule = (pos.x == pos.y);
//bool rule2 = x==y;
//bool test = rule;
//mvprintw(y,x*2,"A");
//mvprintw(y,x*2, "%s", map[x][y]);

/*
  initscr();
  noecho();
  curs_set(0);

    
  int xm, ym;
  getmaxyx(stdscr, ym, xm);

  WINDOW* win= newwin(ym/2,xm/2,ym/4,xm/4);
  box(win, 0, 0);
  refresh();
  wgetch(win);
  endwin();

  return 0;
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <unistd.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <string.h>

//#define TRUE_P "■" // ■
#define TRUE_P "  " // ■
#define EMPTY_P "."
#define PLAYER "🯅"
//#define OTHER_P "#"
#define TARGET_P "O"

#define TRUE_N '1' 
#define TARGET_N '2' 
#define PLAYER_N '3'

#define con(x) attron(COLOR_PAIR(x))
#define coff(x) attroff(COLOR_PAIR(x))
#define HRES 2


typedef struct {
    int x;
    int y;
    int symbol;
} Vec2;



void goindAround(int res, Vec2 player, int x, int y) {
    panic:
    if ( x < res-2) {
       for (;;x++) {
           getch();
           refresh();
           //loop(res, player);
           player.x = x;
           player.y = y;

           if (x == res-1) {
               y++;
               for (;;x--) {
                   if (x == 0) { break;}
                   getch();
                   refresh();
                   //loop(res, player);
                   player.x = x;
                   player.y = y;
               }
               goto panic;
           }
       }
    }
}

unsigned int current_ticks_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);  // immer vorwärtslaufend

    return (unsigned int)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}


void getRndArea(Vec2* arr, int min, int max, int amnt) {
    srand(current_ticks_ms());
    for (int i = 0; i < amnt; i++) {
        arr[i].x = rand() % (max-min) + min;
        arr[i].y = rand() % (max-min) + min;
    }

}

int getIndex(int x, int y, int WIDTH) { return y*WIDTH+x; }

void createInnerWalls(int arrsize, char (map)[arrsize][arrsize], int density, int collectivedistance, int amount) {
    Vec2 rnd_array[amount];
    bool rules = false;
    getRndArea(rnd_array, 0, arrsize, amount);
    
    for (int x=0; x < arrsize; x++) {
        for (int y=0; y < arrsize; y++) {

            bool outerwalls = (x == arrsize-1 || x == 0 ||
                               y == arrsize-1 || y == 0   );

            rules = outerwalls;


            for (int i = 0; i < amount; i++) {
                if  (rules ) {
                    (map)[x][y] = '1';
                    (map)[rnd_array[i].x][rnd_array[i].y] = '1';
                }
                else { (map)[x][y] = '0'; }

            }

             
        }
    }
}

void createTarget(int s, char (map)[s][s]) {


    srand(current_ticks_ms());
    for (;;) {
        int x = rand() % (s-1)+1;
        int y = rand() % (s-1)+1;
        if (((map)[x][y] == TRUE_N || (map)[x][y] == PLAYER_N))
        { continue; }
        else { map[x][y] = '2'; break;}

    }
}



void getXYfrom1Darray(Vec2* result, int index, int WIDTH) {
    result->x = index % WIDTH;
    result->y = index / WIDTH;
}

void draw(int size, Vec2 player, char map[size][size]) {

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {

            switch (map[x][y]) {
                case '0': {con(0); mvprintw(y, x*HRES, EMPTY_P); coff(0); } break;
                case '1': {con(1); mvprintw(y, x*HRES, TRUE_P ); coff(1); } break;
                case '2': {con(2); mvprintw(y, x*HRES, TARGET_P); coff(2); } break;
            }

            con(3); mvprintw(player.y, (player.x)*HRES, PLAYER ); coff(3);

            
        }
    }
}

void getCinArray(int res, char (map)[res][res], char c, Vec2* out) {
    for (int x = 1; x < res; x++) {
        for (int y = 1; y < res; y++) {
            if (map[x][y] == c) {
                out->x=x; out->y=y;
            }
        }
    }
}

float Dlength(float x, float y) {
    return (sqrt(powf(x, 2)+powf(y, 2)));
}

int SearchIndexInArray(int missed, int s, int* p) {
    for (int i = 0; i < s; i++) {
        if (p[i] == missed) { return i; }
    }
}

void sortArray(int s, float* a) {
    int min = 0;

    for (int it=0; it < 3; it++) {
        for (int i = 0; i < s; i++) {
            if (a[i] > a[i+1]) {
              int tmp = a[i+1];
              a[i+1] = a[i];
              a[i] = tmp;
            }
        }
    }
}

int getMinArr(int s, int* p) {
    int min = *p;
    for (int i = 0; i < s; i++) {
        if (p[i] < min) {
            min = p[i];
        }
    } return SearchIndexInArray(min, s, p);
}

void
PlayerMove(Vec2* player,
           int res,
           char (map)[res][res]) {

   char c = getch();
   Vec2 c_pos; getCinArray(res, map, TARGET_N, &c_pos);
   float l = Dlength((float)(player->x-c_pos.x), (float)(player->y-c_pos.y));
   mvprintw(res, 0, "p.x/py = %d/%d | c.x/c.y = %d/%d\nl=%f", player->x,
            player->y, c_pos.x, c_pos.y, l);


    if (c == 'o') {
                // choose which option of these 8 options would have an smaller distance
        // to the target
        
        // get all these 4 values
        const int size = 4;
        float p[size];
        //fill

        p[0] = Dlength((float)((player->x  )-c_pos.x), (float)((player->y-1)-c_pos.y));
        p[1] = Dlength((float)((player->x-1)-c_pos.x), (float)((player->y  )-c_pos.y));
        p[2] = Dlength((float)((player->x  )-c_pos.x), (float)((player->y+1)-c_pos.y));
        p[3] = Dlength((float)((player->x+1)-c_pos.x), (float)((player->y  )-c_pos.y));
            
        int index = getMinArr(size, p);

        switch (index) {
            case 0: { c = 'w'; break; }
            case 1: { c = 'a'; break; }
            case 2: { c = 's'; break; }
            case 3: { c = 'd'; break; }
        }

        // ok o entscheide mich für d.
        // Aber x+1 ist '1'!
        // Dann brauche ich den nächst kleinsten Index.
        // Und wenn der auch nicht geht, dann so lange bis in dieser Richtung
        // kein '1' ist.
    }

    if (c == 'w' && map[player->x][player->y-1] != '1') {
        player->y--;
    } 
    if (c == 'a' && map[player->x-1][player->y] != '1') {
        player->x--;
    }
    if (c == 's' && map[player->x][player->y+1] != '1') {
        player->y++;
    }
    if (c == 'd' && map[player->x+1][player->y] != '1') {
        player->x++;
    }
    refresh();

}


void
loop(int res, Vec2 player, char (map)[res][res]) {
    for (int t = 0;;t++) {
        refresh();
        draw(res, player, map);

        mvprintw(50, 0, "Timese have moved: %f", (float)t/(res*res)*100);
        PlayerMove(&player, res, map);
        
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_GREEN);

    int res = atoi(argv[1]);
    int mid = res/2;
    Vec2 player; player.x = mid; player.y = mid;
    char map[res][res] = {};

    int density=0, distance=0, amount=res;
    createInnerWalls(res, map, density, distance, amount);
    createTarget(res, map);
    loop(res, player, map);
       
    getch();
    endwin();
}
