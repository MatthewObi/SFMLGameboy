#ifndef GBDEF_H
#define GBDEF_H

typedef unsigned char BYTE;
typedef char SIGNED_BYTE;
typedef unsigned short WORD;
typedef signed short SIGNED_WORD;

typedef unsigned char COLOR;
#define WHITE 0b00
#define LIGHT_GRAY 0b01
#define DARK_GRAY 0b10
#define BLACK 0b11

#define FLAG_Z 7
#define FLAG_N 6
#define FLAG_H 5
#define FLAG_C 4

#define TIMA 0xFF05
#define TMA 0xFF06
#define TMC 0xFF07 

#define BUTTON_RIGHT 0
#define BUTTON_LEFT 1
#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define BUTTON_A 4
#define BUTTON_B 5
#define BUTTON_SELECT 6
#define BUTTON_START 7

#endif //GBDEF_H