#ifndef OVERLAY_WORLD03_AREA135_14_H
#define OVERLAY_WORLD03_AREA135_14_H

/* The world03/area135/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "work/actor.h"
#include "overlays/area/world03.h"
#include "work/area_spad.h"
#include "menu/party.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The shared flag word the close path clears a bit of. */

/* The battle-step selector and the pan word the callers step. */
/* The shared message buffer the setup publishes and its frame extent. */
/* The battle-step selector the close path clears. */
/* The shared flag word the cancel path clears a bit of. */

/* The request selector and the bytes the cancel path sets. */
/* The field mode bytes the height steps test. */
/* The shared camera-position words the view step copies. */
/* The camera seed halfword the request step stores. */
/* The field focus point the camera step copies. */
/* D_80147A90 */
extern s32      g_AreaFocusY;
/* The state handler tables the dispatchers index. */
extern u8       D_801F61F8[];
extern Callback D_801F6200[];
extern Callback D_801F6218[];
extern Callback D_801F6258[];
extern u8       D_801F626C[];
extern Callback D_801F6B34[];
extern Callback D_801F6B40[];
extern Callback D_801F6B48[];
extern Callback D_801F6B6C[];

/* The x/y entry-coordinate pairs the request step indexes. */
extern u8 D_801F6AAC[];
extern u8 D_801F6AB4[];

/* The panel box words func_80159B9C draws: x, y, width and height. */
extern u16 D_801F6210;
extern u16 D_801F6212;
extern u16 D_801F6214;
extern u16 D_801F6216;

/* The camera and view steps the handlers enter. */
void func_801F32A0(s32 value);

/* The shared flag byte the request path sets a bit of. */
extern u8 D_80143FBC;

/* The scaled grid position and size the step checks compare against. */
extern u8  D_80147C29;
extern s32 D_80147C2C;
extern s32 D_80147C30;
extern s32 D_80147C54;
extern s32 D_80147C58;
extern u8  D_80147C90;
void       func_801F37C4(void);
void       func_801F3830(s32 arg0, s32 arg1);
void       func_801F3CA8(void);
s32        func_801F5BCC(s32);
s32        func_801F5D1C(void);
/* The overlay's companion steps the wrappers enter. */
void       func_801F5D98(void);
void       func_801F5F28(void);

extern u8 D_80147AAC[];

#endif
