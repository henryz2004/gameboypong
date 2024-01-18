/*
 * Exported with nin10kit v1.8
 * Invocation command was nin10kit --mode=3 bol bol.gif 
 * Time-stamp: Wednesday 04/05/2023, 00:21:56
 * 
 * Image Information
 * -----------------
 * bol.gif (frame 0) 6@6
 * bol.gif (frame 1) 6@6
 * bol.gif (frame 2) 6@6
 * bol.gif (frame 3) 6@6
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef BOL_H
#define BOL_H

extern const unsigned short bol0[36];

extern const unsigned short bol1[36];

extern const unsigned short bol2[36];

extern const unsigned short bol3[36];

extern const unsigned short* bol_frames[4];
#define BOL_FRAMES 4

#define BOL_SIZE 72
#define BOL_LENGTH 36
#define BOL_WIDTH 6
#define BOL_HEIGHT 6

#endif

