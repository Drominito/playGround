#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int argtoint(char* c) {

    char *p;
    int num;
    long conv = strtol(c, &p, 10);
    num = conv;
    return num;
}

int main(int argc, char* argv[]) {
    // example input 1:2(2*x²) | 2:2(x²=2x) | 3:4(x²=4x)
    if (argc < 3) { return 1;}

    int parabolaFactor=argtoint(argv[1]); //1
    int firstCutLine=argtoint(argv[2]);  //2x
    int secondCutLine=argtoint(argv[3]); //4x

    const double x=firstCutLine;
    const double xs=secondCutLine;


    double b=firstCutLine*x; // 2*2=4
    double a=secondCutLine*xs; // 4*4=16

    double c=(a+b)/2; // 10
    double median =c;
    
    b=b-secondCutLine; //4-4=0
    c=c-secondCutLine; //10-4=6
    a=a-secondCutLine; //16-4=12


    double targetPointY=parabolaFactor*pow(x, 2); // x=2 -> 4
    double factor= c*x; // 6*2=12
    //correction
    double subtractor=factor-targetPointY; // 12-4=8

    double firstresult=c*(x)-subtractor; // y=6*x-8=4
    double secondresult=c*(xs)-subtractor; // y=6*x-8=4

    // Show calc.

    printf("Checking: Median is %f\n", median);


    printf("parabolaFactor:y=%d*x²\nfirstCutLine:  x²=%dx\nsecondCutLine: x²=%dx\n",
    parabolaFactor, firstCutLine, secondCutLine);

    printf("result:    y=%fx-%f\n", c, subtractor);

    printf("prove(x=%d):y=%f*%f-%f=%f\n", firstCutLine, c, x, subtractor, firstresult);
    printf("prove(x=%d):y=%f*%f-%f=%f\n", secondCutLine, c, xs, subtractor, secondresult);


    // wanted result y=6x-8 | on x 2 (and testing 4 too)
    return 0;
}
