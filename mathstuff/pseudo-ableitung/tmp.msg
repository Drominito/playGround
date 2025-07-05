int argtoint(char* c) {

    char *p;
    int num;
    long conv = strtol(c, &p, 10);
    num = conv;
    return num;
}


