#ifndef OVERLAY_BOSS_BOSS038_16_H
#define OVERLAY_BOSS_BOSS038_16_H

/* The boss/boss038/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */

/* D_800C1C10 */
extern u8       g_BossEnemyScript[];
/* D_800C1C1C */
extern u16      g_BossEnemyActions[];
extern Callback D_800C1C24[];
extern Callback D_800C1C54[];
extern Callback D_800C1C60[];
extern Callback D_800C1C90[];

void func_800C18EC(u8 index);

u8   func_800C1B08(u32 mode);
void func_800C1B10(void);
void func_800C1B74(void);

/* func_800C19E4 */
void Boss_EnemyScriptMode(s32 mode);

#endif
