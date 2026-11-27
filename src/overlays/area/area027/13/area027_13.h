#ifndef OVERLAY_WORLD00_AREA027_13_H
#define OVERLAY_WORLD00_AREA027_13_H

/* The area027 world overlay's local declarations: the state selectors, the
 * reset sentinel and the work state handler table. Only this image includes
 * the file. */

#include "overlays/area/worlds/world00.h"

/* Reset sentinel stored to g_UIMessageRequest by the request handlers. */
#define RESET_SENTINEL 0xFFFF

extern Callback D_801F3ABC[];

void      func_801F2C74(void);
void      func_801F2D5C(void);
void      func_801F2E3C(AreaTrail* trail);
void      func_801F2F0C(const void* trail);
void      func_801F304C(AreaTrail* trail);
void      func_801F3164(void);
void      func_801F31CC(void);
void      func_801F32B0(void);
void      func_801F33A8(void);
POLY_FT4* func_801F3480(const Pos3s* point, s32 angle, u32 texture);
void      func_801F3618(void);
void      func_801F3650(void);
void      func_801F3710(void);
void      func_801F376C(void);
void      func_801F37E4(void);
void      func_801F394C(void);

#endif
