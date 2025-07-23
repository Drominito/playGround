// C2 -> Condition 2
// I know that the biggest sentence may have 128 chars.
// so I can find out the "sortedtxt" without using heap.
// The disadvantange is that often the sentences may have less than
// 128 chars.

//that's the cost that i have not calculated the actual char count.
// Oh nope, it does not matter.

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ncurses.h>
#include <locale.h>
#include <time.h>

#define DEBUG 1
#define CHAR_LIMIT 128 // depends also at CULS and char-size.
#define SENTENCES 2
#define SPC_SZ 3 // SPlit_Character_SiZe

bool multiple_charcheck(char a, char* b, const int b_size) {
    for (int i = 0; i < b_size; i++) {
        if (a == b[i]) { return true; }
    }
    return false;
}

// split every string after ".", "!" and "?" 
char** sp_str_to_sentc(char* str, int sz, int* sentences) {
    char** result = NULL;
    const char split_chars[SPC_SZ] = ".!?";
    const int offset = 2; // \0, 0, '!'

    int s_index=0, //splitter/sentences
    splitpoints[SENTENCES];

    // find positions & Amount - where to split.
    for (int i = 0; i < sz; i++) {
        if (multiple_charcheck(str[i], split_chars, SPC_SZ)) {
            // C2: The last splitter does not count.
            if (i == sz-offset)  { break; } 
            splitpoints[s_index++] = i;

            #if DEBUG == 1
            mvprintw(0, 0, "Split-Points-Positions (1D):");
            mvprintw(10,10+(i/4),"-<%d>-", i);
            #endif
        } 
    }

    #if DEBUG == 1
    getch();
    clear();
    #endif


    //transport it
    result = (char**)malloc(s_index*sizeof(char*));
    for (int i = 0; i < s_index; i++) {
        result[i] = (char*)malloc(CHAR_LIMIT);
    }

    if (result == NULL || result[0] == 0) { sleep(1); puts("My ptr is NULL! D:");sleep(1);}


    for (int i = 0; i < s_index; i++) {
        int boffset = splitpoints[i-1] + 1;
        if (i == 0) { memcpy(result[i], str, splitpoints[i]+1); }
        else { memcpy(result[i], str+boffset, (splitpoints[i]+1)-(splitpoints[i-1]-0) ); }
        #if DEBUG == 1
        mvprintw(i*2, 10, "%s", result[i]);
        #endif
    }

    #if DEBUG == 1
    printf("\nsplitter_points: %d\n", s_index);
    getch();
    clear();
    refresh();
    curs_set(0);
    #endif

    *sentences = s_index;
    return result;
    //return s_index; //sentences

    // Testing manually
    //int a = 1;
    //int boffset=splitpoints[a-1]+1;
    //memcpy(result[a], str+boffset, (splitpoints[a]+1)-(splitpoints[a-1]-0) ); 
    //printf("Text: %s\n", result[a]);
    //int byteoffset=splitpoints[1-1];
    //memcpy(result[0], str, splitpoints[0]+1); 
    //memcpy(result[0], str+byteoffset, (splitpoints[1]+1)-(splitpoints[0]) ); 
    //printf("Text: %s\n", result[0]);
     

}
void crypticAnimation(int yoff, int xoff, const char* str) {
    for (int j = 0; j < strlen(str); j++) {
        for (int i = 64; i <= str[j]; i++) {
            srand(time(NULL));
            mvprintw(0+yoff, 0+j+xoff, "%c ",i | str[j]) % rand()==1; // without % it'faster'
            refresh();
            usleep(1000);
        }
    }
}


int main() {
    setlocale(LC_ALL, "");
    char buf[CHAR_LIMIT*2];
    FILE* f = fopen("input.txt", "r");
    size_t bytesRead=fread(buf, sizeof(char), sizeof(buf), f);
    if (f==NULL) { perror("No D:"); return 1;}
    if (bytesRead < sizeof(buf)) { buf[bytesRead] = '\0'; }
         
    fclose(f);

    char* rawtxt = buf;

        int x, y;
    char** txt = NULL;

    initscr(); x = COLS, y = LINES;
    int centerX=x/2, centerY=y/2;
    //int sz = sizeof(rawtxt)/sizeof(rawtxt[0]);
    // rawtext isnt an array anymore. so just strlen().
    int sz = strlen(buf);
    int sentences_amnt = 0;

    //const char str[] = "I think that should not be like that, but what ever!ü";
    //crypticAnimation(str);



    txt=sp_str_to_sentc(rawtxt, sz, &sentences_amnt);

    //mvprintw(10, 10, "%s", splitted_txt[0][0]);    
    for (int i = 0; i < sentences_amnt; i++) {
        const char* tmp_str = txt[i];
        //mvprintw(centerY + i, centerX - (strlen(txt[i]) / 2), txt[i]);
        crypticAnimation(centerY + i, centerX - (strlen(txt[i]) / 2), txt[i]);
        refresh();
        sleep(1);
    }
    

    free(txt);
    refresh();
    getch();
    endwin();
    return 0;
}
