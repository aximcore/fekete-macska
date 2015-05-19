#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define KARTYASZ 52

// treff 2 - 2 - 0

typedef enum {
    ketto = 0, harom = 1,
    negy = 2, ot = 3,
    hat = 4, het = 5,
    nyolc = 6, kilenc = 7,
    tiz = 8,j = 9,
    q = 10,k = 11,
    a = 12
} rangType;

typedef enum {
    pikk,karo,treff,kor
} szinType;

typedef struct {
    rangType rang;
    szinType szin;
    int jatekos;
} kartyaType;
