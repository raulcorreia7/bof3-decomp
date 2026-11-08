#ifndef OVERLAY_BMAGIC_MAGIC092_03_H
#define OVERLAY_BMAGIC_MAGIC092_03_H

/* The bmagic/magic092/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F07C0[];
void            func_801EFB04(void);

extern Callback     D_801F07D8[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F07F8[];
#define BMAGIC_EFFECT_SLOTS D_801F07F8
#define BMAGIC_EFFECT_COUNT BATTLE_EFFECT_COUNT
void            func_801EF580(void);
void            func_801EED04(void);
void            func_801EF7FC(void);
void            func_801F04BC(void);
extern Callback D_801F07E8[];

/* The pixels func_801F0260 moves the effect each frame: toward the side param.unk_0B picks, and up. */
#define MAGIC092_STEP_X 16
#define MAGIC092_RISE_Y 12

#endif
