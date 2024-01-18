#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/poopyocean.h"
#include "images/default_cube.h"
#include "images/default_happy.h"
#include "images/default_hit.h"
#include "images/default_p.h"
#include "images/default_wink.h"
#include "images/bol.h"
#include "images/background_start.h"
#include "images/end_screen.h"
#include "trigtable.h"

volatile u16 playColor = MAGENTA;
enum gba_state tstate = START;

struct fish f = {0};
struct fish *phyzy = &f;

struct ball b = {0};
struct ball *bol = &b;
int cube_skin=0;

u32 lastCollisionBlank = 0;
u32 freezeLength = 16;

int score = 0;
int best = 0;

int main(void) {
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  enum gba_state state = START;
  transition(state);

  reset_game();

  while (1) {

    currentButtons = BUTTONS;

    if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
      state = START;
      transition(state);
      best = 0;
      reset_game();
    }

    switch (state) {
      case START:
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = PLAY;
          transition(state);
          reset_game();

          bol->runBlank = vBlankCounter;
        }
        break;

      case PLAY:
        if (KEY_DOWN(BUTTON_UP, currentButtons)) {
          if (phyzy->speed < 0) {
            phyzy->speed = -phyzy->speed;
          }
          phyzy->moving = 1;
          if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
            phyzy->runBlank = vBlankCounter;
          }
        } else if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
          if (phyzy->speed > 0) {
            phyzy->speed = -phyzy->speed;
          }
          phyzy->moving = 1;
          if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
            phyzy->runBlank = vBlankCounter;
          }
        } else if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
          phyzy->radius = phyzy->radius - 1;
          if (KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {
            phyzy->runBlank = vBlankCounter;
          }
        } else if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
          phyzy->radius = phyzy->radius + 1;
          if (KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {
            phyzy->runBlank = vBlankCounter;
          }
        } else {
          phyzy->moving = 0;
          phyzy->pauseRot = phyzy->rot;
        }

        run_phyzy();
        run_bol();

        check_collision();

        checkOOB(&state);
        break;

      case WIN:
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = PLAY;
          transition(state);
          reset_game();

          bol->runBlank = vBlankCounter;
        }
        break;
      case LOSE:
        break;
      case NONE:
        break;
    }

    previousButtons = currentButtons;
    animate(state);
  }

  return 0;
}

void reset_game(void) {
  score = 0;
  playColor = MAGENTA;
  reset_phyzy();
  reset_bol();
}

void reset_phyzy(void) {
  phyzy->centerRow = HEIGHT/2;
  phyzy->centerCol = WIDTH/2;
  phyzy->radius = HEIGHT/3;
  phyzy->size = 12;
  phyzy->rot = 0;
  phyzy->speed = 60;
  phyzy->moving = 0;
  phyzy->currPos = (struct pnt) {phyzy->centerRow, phyzy->centerCol+phyzy->radius};
  phyzy->lastPos = (struct pnt) {phyzy->centerRow, phyzy->centerCol+phyzy->radius};
  phyzy->runBlank = 0;
  phyzy->pauseRot = 0;
}

void reset_bol(void) {
  bol->anchorRow = HEIGHT / 2;
  bol->anchorCol = WIDTH/2;
  bol->size = 6;
  bol->speed = 15;
  bol->rot = 0;
  bol->spinning = 0;
  bol->lastPos = (struct pnt) {bol->anchorRow, bol->anchorCol};
  bol->currPos = (struct pnt) {bol->anchorRow, bol->anchorCol};
  bol->runBlank = 0;
  bol->frame_counter = 0;
}

void transition(enum gba_state state) {
  tstate = state;
}

void animate(enum gba_state state) {
  waitForVBlank();

  static int flash = 0;
  
  switch (tstate) {
    case START:
      drawFullScreenImageDMA(background_start);
      drawCenteredString(HEIGHT/2-25, WIDTH/2-50, 100, 50, "Press START", BLACK);
      tstate = NONE;
      break;
    case PLAY:
      fillScreenDMA(playColor);
      tstate = NONE;
      break;
    case WIN:
      drawFullScreenImageDMA(end_screen);

      if (score > best) {
        best = score;
        flash = 1;
        drawCenteredString(HEIGHT/2-50, WIDTH/2-50, 100, 50, "NEW BEST!", GREEN);
      } else {
        flash = 0;
        drawCenteredString(HEIGHT/2-50, WIDTH/2-50, 100, 50, "OOF! U CAN DO BETTER!", YELLOW);
      }
      char sbuff[20];
      snprintf(sbuff, 20, "%d", score);
      drawCenteredString(HEIGHT/2-25, WIDTH/2-50, 100, 50, sbuff, YELLOW);

      char bbuff[20];
      snprintf(bbuff, 20, "BEST: %d", best);
      drawCenteredString(HEIGHT/2, WIDTH/2-50, 100, 50, bbuff, GREEN);

      tstate = NONE;
      break;
    case LOSE:

      break;
    case NONE:
      break;
  }

  switch (state) {
    case START:
      animate_greeting();
      break;
    case PLAY:
      undraw_score();
      undraw_bol();
      undraw_phyzy();

      draw_bol();
      draw_phyzy();

      draw_score();
      break;
    case WIN:

      if (flash) {
        if (vBlankCounter % 8 == 4) {
          drawCenteredString(HEIGHT/2-50, WIDTH/2-50, 100, 50, "NEW BEST!", GREEN);
        } else if (vBlankCounter % 8 == 0) {
          drawCenteredString(HEIGHT/2-50, WIDTH/2-50, 100, 50, "NEW BEST!", YELLOW);
        }
      }
      break;
    case LOSE:

      break;
    case NONE:
      break;
  }
}

void undraw_phyzy(void) {
  drawRectDMA(phyzy->lastPos.row - phyzy->size/2, phyzy->lastPos.col - phyzy->size/2, phyzy->size, phyzy->size, playColor);
}
void undraw_bol(void) {
  drawRectDMA(bol->lastPos.row - bol->size/2, bol->lastPos.col - bol->size/2, bol->size, bol->size, playColor);
}
void undraw_score(void) {
  drawRectDMA(5, 5, 50, 20, playColor);
}

void animate_greeting(void) {
  static int f = 0;
  static const u16 *frames[5] = {default_cube, default_happy, default_hit, default_p, default_wink};
  if (vBlankCounter % 25 == 0) {
    f = (f + 1) % 5;
  }
  drawImageDMA(HEIGHT/2-25, WIDTH/2-6, 12, 12, frames[f]);
}
void draw_phyzy(void) {
  if (vBlankCounter - lastCollisionBlank <= freezeLength) {
    drawImageDMA(
      phyzy->currPos.row - phyzy->size/2,
      phyzy->currPos.col - phyzy->size/2,
      phyzy->size,
      phyzy->size,
      default_hit
    );

  } else {
    drawImageDMA(
      phyzy->currPos.row - phyzy->size/2,
      phyzy->currPos.col - phyzy->size/2,
      phyzy->size,
      phyzy->size,
      default_cube
    );
  }
  
}
void draw_bol(void) {
  if (vBlankCounter - lastCollisionBlank > freezeLength && bol->spinning && vBlankCounter%6 == 0) {
    bol->frame_counter = (bol->frame_counter + 1) % 4;
  }
  drawImageDMA(
      bol->currPos.row - bol->size/2,
      bol->currPos.col - bol->size/2,
      bol->size,
      bol->size,
      bol_frames[bol->frame_counter]
    );
}
void draw_score(void) {
  char buff[20];
  snprintf(buff, 20, "%d", score);
  drawString(5, 5, buff, BLACK);
}

void run_phyzy(void) {
  phyzy->lastPos = phyzy->currPos;

  if (vBlankCounter - lastCollisionBlank <= freezeLength) {
    phyzy->runBlank = vBlankCounter;
    phyzy->pauseRot = phyzy->rot;
  }
  if (phyzy->moving) {
    phyzy->rot = (phyzy->pauseRot+3600 + phyzy->speed * (vBlankCounter-phyzy->runBlank)) % 3600;
  }
  int x = (phyzy->radius * cos_[phyzy->rot]) / 100;
  int y = (phyzy->radius * sin_[phyzy->rot]) / 100;

  int row = (int) (HEIGHT/2.0 - y);
  int col = (int) (WIDTH/2.0 + x);

  phyzy->currPos = (struct pnt) {row, col};
}
void run_bol(void) {
  bol->lastPos = bol->currPos;

  if (vBlankCounter - lastCollisionBlank <= freezeLength) {
    bol->runBlank = vBlankCounter;
  }
  int radius = (vBlankCounter - bol->runBlank) * bol->speed;  // in tenths of pixels
  int x = (radius * cos_[bol->rot]) / 1000;  // 1000 = 100*10
  int y = (radius * sin_[bol->rot]) / 1000;
  int row = (int) (bol->anchorRow - y);
  int col = (int) (bol->anchorCol + x);

  bol->currPos = (struct pnt) {row, col};
}

void check_collision(void) {

  if (vBlankCounter - lastCollisionBlank < 20 + freezeLength) {
    return;
  }

  int dcol = phyzy->currPos.col-bol->currPos.col;
  int drow = phyzy->currPos.row-bol->currPos.row;
  int sep = phyzy->size + bol->size;
  if (((dcol >= 0 && 2*dcol <= sep) || (dcol < 0 && -2*dcol <= sep))
        && ((drow >= 0 && 2*drow <= sep) || (drow < 0 && -2*drow <= sep))) {
    lastCollisionBlank = vBlankCounter;

    // collision detected;
    bol->rot = (1800 + 2*phyzy->rot - bol->rot) % 3600;
    if (phyzy->moving && !bol->spinning) {
      bol->rot = (bol->rot + 3400) % 3600;
      bol->spinning = 1;
    } else if (!phyzy->moving && bol->spinning) {
      bol->rot = (bol->rot + 200) % 3600;
      bol->spinning = 0;
    }
    bol->runBlank = vBlankCounter;
    bol->anchorRow = bol->currPos.row;
    bol->anchorCol = bol->currPos.col;

    playColor = COLOR(randint(0,32), randint(0,32), randint(0,32));
    tstate = PLAY;    // force redraw of background
    score++;
  }
}
void checkOOB(enum gba_state *state) {
  if (bol->currPos.col > WIDTH || bol->currPos.col < 0 || bol->currPos.row < 0 || bol->currPos.row > HEIGHT) {
    *state = WIN;
    transition(*state);
  }
}