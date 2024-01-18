#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

enum gba_state {
  START,
  PLAY,
  WIN,
  LOSE,
  NONE
};

struct pnt {
    int row;
    int col;
};

struct fish {
    int centerRow;
    int centerCol;
    int radius;
    int size;
    int rot;      // tenths of degrees
    int speed;    // tenth of degree per vblank
    int moving;

    struct pnt lastPos;    // for undrawing
    struct pnt currPos;
    
    u32 runBlank;
    int pauseRot;
};

struct ball {
    int anchorRow;
    int anchorCol;
    int size;
    int speed;      // tenths of pixels per vblank
    int rot;        // tenths of degrees
    int spinning;

    struct pnt lastPos;
    struct pnt currPos; // CENTER
    
    u32 runBlank;
    int frame_counter;
};

void transition(enum gba_state state);
void animate(enum gba_state state);

void reset_game(void);
void reset_bol(void);
void reset_phyzy(void);

void undraw_bol(void);
void undraw_phyzy(void);
void undraw_score(void);

void animate_greeting(void);
void draw_bol(void);
void draw_phyzy(void);
void draw_score(void);

void run_bol(void);
void run_phyzy(void);

void checkOOB(enum gba_state *state);
void check_collision(void);

#endif
