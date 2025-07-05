#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>



//14 bytes
#pragma pack(push, 1)
struct Header {
    char signature[2];
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

//40 bytes
struct infoHeader {
    uint32_t Size;         // 4 chars für die Größe (uint32_t als Bytes)
    int32_t Width;        // 4 chars für die Breite (uint32_t als Bytes)
    int32_t Height;       // 4 chars für die Höhe (uint32_t als Bytes)
    uint16_t Planes;       // 2 chars für die Anzahl der Planes (uint16_t als Bytes)
    uint16_t Bitcount;          // 2 chars für Bits pro Pixel (uint16_t als Bytes)
    uint32_t Compression;
    uint32_t imageSz;      // 4 chars für die Bildgröße (uint32_t als Bytes)
    int32_t XpixelPerM;   // 4 chars für X-Pixel pro Meter (uint32_t als Bytes)
    int32_t YpixelPerM;   // 4 chars für Y-Pixel pro Meter (uint32_t als Bytes)
    uint32_t colorused;    // 4 chars für die Anzahl der verwendeten Farben (uint32_t als Bytes)
    uint32_t importantColors; // 4 chars für die Anzahl der wichtigen Farben (uint32_t als Bytes)
};

// 4 * NumColors bytes
struct colorTable {
        char red;
        char green;
        char blue;
        char reserved;
};

#pragma pack(pop)

void write_2_bytes(FILE* f, uint16_t val) {
    for (int i = 0; i < 2; ++i)
        fputc((val >> (8 * i)) & 0xFF, f);
}
void write_4_bytes(FILE* f, uint32_t val) {
    for (int i = 0; i < 4; ++i)
        fputc((val >> (8 * i)) & 0xFF, f);
}



int main(int argc, char** argv ) {
   
    int t = atoi(argv[1]);
    int WIDTH = atoi(argv[2]),
        HEIGHT = atoi(argv[3]);

    FILE* fp = fopen("new.bmp", "wb");
    if (!fp) {
        perror("Nope");
        return 1;
    }

    struct Header _header;
    struct infoHeader _infoheader;
    struct colorTable _colortable;

    // Beispiel, wie man die Bytes einzeln zuweist
    //_header.signature = "BM";
    memcpy(_header.signature, "BM", 2);
    _header.fileSize = sizeof(_header) + sizeof(_infoheader)+(WIDTH*HEIGHT*3);
    _header.reserved1 = 0;
    _header.reserved2 = 0;
    _header.dataOffset = sizeof(_header) + sizeof(_infoheader);


    uint32_t Size = 40;
    //
    //
    uint32_t Planes = 1;
    uint16_t Bitcount = 24; // ich dachte 24?
    uint32_t Compression = 0;
    uint32_t imageSz = WIDTH*HEIGHT*3;
    uint32_t XpixelPerM = 0;
    uint32_t YpixelPerM = 0;
    uint32_t colorused = 0; // 2^16 = 256
    uint32_t importantColors = 0;

    _infoheader.Size = Size;
    _infoheader.Width = WIDTH;
    _infoheader.Height = HEIGHT;
    _infoheader.Planes = Planes;
    _infoheader.Bitcount = Bitcount;
    _infoheader.Compression = Compression;
    _infoheader.imageSz = imageSz;
    _infoheader.XpixelPerM = XpixelPerM;
    _infoheader.YpixelPerM = YpixelPerM;
    _infoheader.colorused = colorused;
    _infoheader.importantColors = importantColors;


    //_header section
    fwrite(_header.signature, 2, 1, fp);
    write_4_bytes(fp, _header.fileSize);
    write_2_bytes(fp, _header.reserved1);
    write_2_bytes(fp, _header.reserved2);
    write_4_bytes(fp, _header.dataOffset);

    // _infoheader section
    write_4_bytes(fp, _infoheader.Size);
    write_4_bytes(fp, _infoheader.Width);
    write_4_bytes(fp, _infoheader.Height);
    write_2_bytes(fp, _infoheader.Planes);
    write_2_bytes(fp, _infoheader.Bitcount);
    write_4_bytes(fp, _infoheader.Compression);
    write_4_bytes(fp, _infoheader.imageSz);
    write_4_bytes(fp, _infoheader.XpixelPerM);
    write_4_bytes(fp, _infoheader.YpixelPerM);
    write_4_bytes(fp, _infoheader.colorused);
    write_4_bytes(fp, _infoheader.importantColors);
    
    float alpha = 0.05f;
    unsigned r,g,b;

    int cX = WIDTH/2;
    int cY = HEIGHT/2;
    int xpos = 100*cos(t/20);
    int ypos = 100*sin(t/20);
    int half = WIDTH/6;


    int rowSize = (WIDTH*3+3) & ~3;
    int padding = rowSize-WIDTH*3+3;
    for (int y = 0; y < HEIGHT; y++) {
        //int random = rand();
        for (int x = 0; x < WIDTH; x++) {
            //unsigned char b;
            //unsigned char r = 255-(x);
            //unsigned char g = b+y*tan(alpha-y);
            //b = b+y*tan(alpha-x);
            r = 0;
            g = 0;
            b = 0;
            
            /* 
            // semi-T.V.
            int offset = offset+t;
            if ( x >= offset && x <= WIDTH - offset &&
                 y >= HEIGHT/2 - offset && y <= HEIGHT/2+offset) 
            {
                b=200;
            }
            fputc(b, fp); fputc(b, fp); fputc(b, fp);
            */

            

            float a = t/(6*3.14);
            int dx = cX-x;
            int dy = cY-y;
            float rotx= dx*sinf(a)+dy*cosf(a);
            float roty= dx*cosf(a)-dy*sin(a);
            uint8_t color;

            //spawnpoint
            int offset = WIDTH/(3.33)/fabsf(cosh(1/tan(a*a/100)));
            if (rotx >= -offset && rotx<= +offset &&
                roty >= -offset && roty<= +offset) {
                //color = (fabs(rotx) < half && fabs(roty) < half) ? 255 : 10;
                // wenn du hier von && zu || wechselst bekommst du eine ähnliche
                // Animation.
                // Ein Rechteck das sich dreht (Kreis-Tangente)
                // Und diese Tangente siet auch wie ein Stock das rumfliegt
                if (half-fabs(rotx+(3.14/4)) >= 0.8  ||
                    half-fabs(rotx+(3.14*4)) <= 0.8 )
                    {
                        color = 50;
                    }
                else { color = 10; }

                

                if (half-fabs(rotx) <= 0.9 &&
                    half-fabs(roty) <= 0.9) {
                        b = 255-y*fabsf(cos(a*a));
                }
                else if (fabs(rotx)  < half &&
                         fabs(roty)  < half) {
                        g = 255-sqrt(pow(x-cX, 2)+pow(y-cY, 2))*sin(a/4)*20;
                        b = 255-y*fabsf(sin(a));
                        r = 255-x*fabsf(sin(a));

                }
                else if (half-fabs(rotx+(16)) <= 1-pow((y-0)/22,18)) {
                        r = 255-y*fabsf(sin(a));
                        g = 255-y*fabsf(sin(a));
                }
                else if (half-fabs(rotx+(16+1)) <= 1-pow((x+0)/22,18)) {
                        r = 255-y*fabsf(sin(a));
                        g = 255-y*fabsf(sin(a));
                        //b = 255-y*fabsf(sin(a));
                        //b = 255-y*fabsf(sin(a));
                }

                else if (half-fabs(rotx/roty*sin(t/roty)*rotx) <= 1/pow(y/22,18)) {
                        r = 255-x*fabsf(cos(a));
                        g = 255-y*fabsf(sin(a));
                        b = 255-y*fabsf(sin(a));
                }


                else if (half-fabs(rotx) <= 1/pow(y/22,18)) {
                        r = 255-x*fabsf(cos(pow(a, 1/64)));
                }
                else if (half-fabs(rotx) <= 1/pow(y/22,18)) {
                        r = 255-x*fabsf(cos(a));
                }
                else if (half-fabs(rotx) == 60+pow(x/(40+a),18)) {
                         g = 255-x*fabsf(sin(a));
                }
                else {b = 1;}
            }

            fputc(b, fp); fputc(g, fp); fputc(r, fp);
            fputc(color, fp); fputc(color, fp); fputc(color, fp);

        }

    }
    fclose(fp);
    return 0;
}

