//float shadowsize = 2.50f;
//srand(time(NULL));
//bool cirlce = pow(x-player1.x,2)+pow(y-player1.y,2) < sqrt(size)*shadowsize;
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

// ACHTUNG: Später überdenken - Es gibt noch eine einfachere Lösung
// Funktion: spectrumIndex()
// Einfach es sortieren:
// 1,4,6,10,200
//
// Dann wieder zurückschauen
// 4,200,1,10,6
// Beim Welchen Index ist es das kleinste?
// Ich wähle das erste Index des sortierten arrays und suche wo die Zahl in dem
// unsortieren Array ist...
// [0](1) -> [2](1)

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

#define WALL '1' 
#define TARGET_N '2' 
#define PLAYER_N '3'

#define con(x) attron(COLOR_PAIR(x))
#define coff(x) attroff(COLOR_PAIR(x))
#define HRES 2
#define DEBUG 1

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define wallCheckM(y)  wallCheck(map.map, *player, y)
#define MAT(m, x, y) ((m->map)[y * m->res + x])
#define MATT(m, x, y) ((m.map)[y * m.res + x])
//#define wallCheckM2(x)  wallCheck(res, map player##x, dire)

struct Map {
    int amount;
    int res;
    bool innerWalls;
    int factor;

    char map[];
};


struct Vec2 {
    int x;
    int y;
    int symbol;
};

typedef struct {
    struct Vec2 pos;
    char skin;
    int color;
} Object;


typedef struct {
    int size;
    //enum direction { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT };
    float length[];
} Route;

typedef enum { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT } Direction;



/*
void goindAround(int res, Vec2 player1, int x, int y) {
    panic:
    if ( x < res-2) {
       for (;;x++) {
           getch();
           refresh();
           //loop(res, player1);
           player1.x = x;
           player1.y = y;

           if (x == res-1) {
               y++;
               for (;;x--) {
                   if (x == 0) { break;}
                   getch();
                   refresh();
                   //loop(res, player1);
                   player1.x = x;
                   player1.y = y;
               }
               goto panic;
           }
       }
    }
}
*/

unsigned int current_ticks_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);  // immer vorwärtslaufend
    return (unsigned int)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}


void getRndArea(struct Vec2* arr, int min, int max, int amnt) {
    srand(current_ticks_ms());
    for (int i = 0; i < amnt; i++) {
        arr[i].x = rand() % (max-min) + min;
        arr[i].y = rand() % (max-min) + min;
    }
}

int getIndex(int x, int y, int WIDTH) { return y*WIDTH+x; }

void createWalls(struct Map* map) {
    const int arrsize = map->res;
    const int amount  = map->amount;

    struct Vec2 rnd_array[map->amount];
    getRndArea(rnd_array, 0, arrsize, map->amount);

    
    for (int x=0; x < arrsize; x++) {
        for (int y=0; y < arrsize; y++) {
            bool outerwalls = (x == arrsize-1 || x == 0 ||
                               y == arrsize-1 || y == 0   );
            bool rules = outerwalls;
            for (int i = 0; i < amount; i++) {
                if  (rules) {
                    MAT(map, x, y) = '1'; // Wall
                    if (map->innerWalls)
                        MAT(map, rnd_array[i].x, rnd_array[i].y) = '1';
                }
                else { MAT(map, x, y) = '0'; }
            }
        }
    }
}

void createTarget(struct Map* map) {
    int s = map->res;
    srand(current_ticks_ms());
    for (;;) {
        int x = rand() % (s-1)+1;
        int y = rand() % (s-1)+1;
        if (MAT(map, x, y) == WALL || MAT(map, x, y) == PLAYER_N)
        { continue; }
        else { MAT(map, x, y) = '2'; break;}

    }
}

void getXYfrom1Darray(struct Vec2* result, int index, int WIDTH) {
    result->x = index % WIDTH;
    result->y = index / WIDTH;
}

void draw(struct Map map, Object player1) {
    int size = map.res;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            switch (MATT(map, x, y)) {
                case '0': {con(0); mvprintw(y, x*HRES, EMPTY_P); coff(0); } break;
                case '1': {con(1); mvprintw(y, x*HRES, TRUE_P ); coff(1); } break;
                case '2': {con(2); mvprintw(y, x*HRES, TARGET_P); coff(2); } break;
            }
            con(3); mvprintw(player1.pos.y, (player1.pos.x)*HRES, PLAYER ); coff(3);
        }
    }
}

struct Vec2 getCinArray(int res, Map map, char c) {
    struct Vec2 out;
    for (int x = 1; x < res; x++) {
        for (int y = 1; y < res; y++) {
            if (MATT(map, x , y) == c) {
                out.x=x; out.y=y;
            }
        }
    }
    return out;
}

float Dlength(float x, float y) {
    return (sqrt(powf(x, 2)+powf(y, 2)));

}




void Delegate(int s, int* p, int args[s][2], float (*f)(float, float)) {
    for (int i = 0; i < s; i++) {
        p[i] = f(args[i][0], args[i][1]);
    }
}


void PrintArr(int s, float* a) {
    char text[1000] = "";  // großer Puffer zum Aufbau des Strings
    char temp[32];         // genügend groß für eine float Ausgabe

    for (int i = 0; i < s; i++) {
        sprintf(temp, "-%.2f-", a[i]);
        strcat(text, temp);
    }

#if DEBUG == 2
    mvprintw(36, 0, "%s", text);
#endif
}


int SearchIndexInArray(float target, int s, float* p) {
#if DEBUG == 2
    mvprintw(37, 0, "---w-----a-----s-----d---", target);
    PrintArr(s, p);
    mvprintw(38, 0, "target : %f", target);
    refresh();
#endif

    for (int i = 0; i < s; i++) {
        

        if (p[i] == target) {
#if DEBUG == 2
            mvprintw(40, 0, "p[%d](%f) == target(%f)", i, p[i], target);
            refresh();
            getch();
#endif
            return i;

        }
    }
#if DEBUG == 2
    clear();
#endif
}

void sortArray(int s, float* a) {
    int min = 0;
    for (int it=0; it < s-1; it++) {
        for (int i = 0; i < s; i++) {
            if (a[i] > a[i+1]) {
              float tmp = a[i+1];
              a[i+1] = a[i];
              a[i] = tmp;
            }
        }
    }
}

int spectrumIndex(int s, int* arr, int offset) {
    float ref[s]; memcpy(ref, arr, sizeof(float)*(s+1)); // s should be bigger.
    sortArray(s, ref);
    int o = MIN(s-1, offset);

    int index = SearchIndexInArray(ref[o], s, arr);

#if DEBUG == 2
    mvprintw(41, 0, "min-index: %d <-> min-value: %.2f", index, ref[index]);
    refresh();
    getch();
    clear();
#endif
    return index;
}

int getMinArr(int s, float* p) { float min = *p;
    for (int i = 0; i < s; i++) {
        if (p[i] < min) { min = p[i]; }
    }

#if DEBUG == 2
    int index = SearchIndexInArray(min, s, p);
    mvprintw(41, 0, "min-index: %d <-> min-value: %.2f", index, min);
    refresh();
    getch();
    clear();
    return index;
#else
    return SearchIndexInArray(min, s, p);
#endif
}



bool wallCheck(int res, char (map)[res][res], Object player, Direction dir) {
    //dire.DIR_UP = 0;
    //p[dire.DIR_UP] ^= 'w'
    switch (dir) {
        case DIR_UP:    { return map[player.pos.x  ][player.pos.y-1] != WALL; }
        case DIR_LEFT:  { return map[player.pos.x-1][player.pos.y  ] != WALL; }
        case DIR_DOWN:  { return map[player.pos.x  ][player.pos.y+1] != WALL; }
        case DIR_RIGHT: { return map[player.pos.x+1][player.pos.y  ] != WALL; }
    }
}

void PlayerMove(struct Map map,
                Object* player) {
   char c = getch();
   struct Vec2 c_pos = getCinArray(map.res, map, TARGET_N);
   float l = Dlength((float)(player->pos.x-c_pos.x), (float)(player->pos.y-c_pos.y));

#if DEBUG == 1
   mvprintw(map.res, 0, "p.x/py = %d/%d | c.x/c.y = %d/%d\nl=%f", player->pos.x,
            player->pos.y, c_pos.x, c_pos.y, l);
#endif

   refresh();

   if (c == 'o') {
       const int size = 4;
       float p[size];
       p[0] = Dlength((float)((player->pos.x  )-c_pos.x), (float)((player->pos.y-1)-c_pos.y));
       p[1] = Dlength((float)((player->pos.x-1)-c_pos.x), (float)((player->pos.y  )-c_pos.y));
       p[2] = Dlength((float)((player->pos.x  )-c_pos.x), (float)((player->pos.y+1)-c_pos.y));
       p[3] = Dlength((float)((player->pos.x+1)-c_pos.x), (float)((player->pos.y  )-c_pos.y));

       //int index = getMinArr(size, p);
       int index = 0;
       
       // walls should be checked. bool Wallcheck(DIR_UP).
       for (int i = 0; i < 4; i++) {
           int raw_index = spectrumIndex(size, p, i);
           if (wallCheckM(raw_index)) {
                   index = raw_index;
                   break;
           }
       }

       int count = 0;
       Direction availDir[4];

       for (int i = 0; i < size; i++) {
           if (wallCheckM(i))
               availDir[count] = i;
       }

       if (count == 0) {
           // you are in a wall/have none ways left to move.
       }

       for (int i = 0; i < count; i++) {
           index = wallCheckM(availDir[i]);
       }
       
       
       switch (index) {
           case 0: { c = 'w'; break; }
           case 1: { c = 'a'; break; }
           case 2: { c = 's'; break; }
           case 3: { c = 'd'; break; }
       }
   }

        // make it maybe as an array?
        //bool wallNearby = wallCheck(res, map, *player);

        if (c == 'w' && wallCheckM(DIR_UP)) {
            player->pos.y--;
        } 

        if (c == 'a' && wallCheckM(DIR_LEFT)) {
            player->pos.x--;
        }

        if (c == 's' && wallCheckM(DIR_DOWN)) {
            player->pos.y++;
        }

        if (c == 'd' && wallCheckM(DIR_RIGHT)) {
            player->pos.x++;
        }
}


void loop(struct Map map, Object player) {
    for (int t = 0;;t++) {
        refresh();
        draw(map, player);

        mvprintw(50, 0, "Timese have moved: %f", (float)t/(map.res*map.res)*100);
        //autoPilot();
        PlayerMove(&player, map.res, map);
        //createTarget(&map);
        //createWalls(&map);

    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN); // wall
    init_pair(2, COLOR_RED, COLOR_BLACK);   // object
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // player

    
    struct Map map = alloca(sizeof(char)*map.res*map.res); 
    map.res        = atoi(argv[1]);
    map.innerWalls = atoi(argv[2]);
    map.factor     = atoi(argv[3]);
    map.amount     = map.res*(map.factor);
    map.map        = 


    int mid = map.res/2;
    Object player1 = {
        .pos = { .x = mid, .y = mid}
    };


    // build before the game-loop
    createWalls(&map);
    createTarget(&map);

    loop(map, player1);
       
    getch();
    endwin();
}
