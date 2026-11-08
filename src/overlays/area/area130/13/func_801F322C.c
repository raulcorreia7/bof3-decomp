#include "area130_13.h"

/* Hint: spad init (ea=g_Actors[2] preloaded, task in a0 then reload to v1).
 * First diff at +0x24: candidate hoists header.mode++ before vx/vy/screen_x
 * (retail does vx,vy,screen_x, then lbu mode / lhu g_Actors[2].screen_y / sb mode with
 * screen_y stored in jr delay slot); size 0x54 vs 0x58. */
INCLUDE_ASM(func_801F322C);
