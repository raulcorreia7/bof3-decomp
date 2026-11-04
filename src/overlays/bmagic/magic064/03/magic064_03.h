#ifndef OVERLAY_BMAGIC_MAGIC064_03_H
#define OVERLAY_BMAGIC_MAGIC064_03_H

/* The bmagic/magic064/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* Signed here: the exe's Area_ProbeCell reads this cell with `lh`; scena00/00 reads the
 * same address with `lhu`, so its unsigned view stays in that image header. */
/* D_80149322 */
extern s16 g_AreaTileOriginY;

/* The twelve step callbacks at D_801EEC10, copied to the stack and indexed by the work state byte. */
typedef struct BMagic064Steps {
    Callback handlers[12];
} BMagic064Steps;

extern BMagic064Steps      D_801EEC10;
extern BattleHandlerTable3 D_801EEC70;
extern BattleResultRings   D_801EEC40;
extern BattleHandlerTable3 D_801EEC50;
extern void*               D_801F28B4;
extern u8                  g_BattleActingBattler;

void GFX_FreePaletteFadeTarget(void* target);
void func_801EF8F4(void);
void func_801F001C(void);
void func_801F04A0(void);
void func_801F05A4(void);

#endif
