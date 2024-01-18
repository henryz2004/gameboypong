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

#include "bol.h"

const unsigned short* bol_frames[4] =
{
	bol0,
	bol1,
	bol2,
	bol3
};

const unsigned short bol0[36] =
{
	0x073f,0x073f,0x073f,0x073f,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,
	0x073f,0x11ff,0x073f,0x073f,0x073f,0x073f,0x073f,0x11ff,0x073f,0x073f,0x073f,0x073f,0x073f,0x11ff,0x11ff,0x11ff,
	0x11ff,0x11ff,0x11ff,0x11ff
};

const unsigned short bol1[36] =
{
	0x11ff,0x11ff,0x11ff,0x11ff,0x11ff,0x11ff,0x073f,0x073f,0x073f,0x073f,0x073f,0x11ff,0x073f,0x11ff,0x11ff,0x073f,
	0x073f,0x11ff,0x073f,0x073f,0x073f,0x073f,0x073f,0x11ff,0x073f,0x11ff,0x11ff,0x073f,0x073f,0x11ff,0x073f,0x073f,
	0x073f,0x073f,0x073f,0x11ff
};

const unsigned short bol2[36] =
{
	0x11ff,0x11ff,0x11ff,0x11ff,0x11ff,0x11ff,0x11ff,0x073f,0x073f,0x073f,0x073f,0x073f,0x11ff,0x073f,0x073f,0x073f,
	0x073f,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,0x073f,0x11ff,0x073f,
	0x073f,0x073f,0x073f,0x073f
};

const unsigned short bol3[36] =
{
	0x11ff,0x073f,0x073f,0x073f,0x073f,0x073f,0x11ff,0x073f,0x073f,0x11ff,0x11ff,0x073f,0x11ff,0x073f,0x073f,0x073f,
	0x073f,0x073f,0x11ff,0x073f,0x073f,0x11ff,0x11ff,0x073f,0x11ff,0x073f,0x073f,0x073f,0x073f,0x073f,0x11ff,0x11ff,
	0x11ff,0x11ff,0x11ff,0x11ff
};

