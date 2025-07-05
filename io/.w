#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv) {

  char buff[64];
  char* path = (argc > 1) ? argv[1] : "output.txt";

  FILE* fp = fopen(path, "r");

  if (!fp) {
    perror(path);
    return 1;
  }

  while (1) {
 // Verschiebt den Dateizeiger um 4 Bytes

        fp = fopen(path, "r");

        fread(buff, sizeof(char), sizeof(buff), fp);
        printf("%s", buff);

        //fseek(fp, -1, SEEK_CUR); 
        sleep(1);
        fclose(fp);

  }

  fclose(fp);
  return 0;
}
