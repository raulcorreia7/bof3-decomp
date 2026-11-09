#ifndef OVERLAY_BOSS_BOSS013_16_H
#define OVERLAY_BOSS_BOSS013_16_H

/* The boss/boss013/16 overlay: one file per split function and its data. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

extern u8          D_800C25F0[];
extern u8          D_800C25FC;
extern u16         D_800C2618[];
extern Callback    D_800C2620[];
extern Callback    D_800C2650[];
extern Callback    D_800C265C[];
extern Callback    D_800C268C[];
extern Callback    D_800C2698[];
extern Callback    D_800C26C8[];
extern Callback    D_800C26D4[];
extern u8          D_800C26E0;
extern u8          D_80146322;
/* The selection-kind byte: battle/records.h names the cell as g_Battle.active_battler but declares only the 6375 byte. */
extern u8          D_80181B11;
extern PartyMember D_801EB860;
extern u8          D_800C25D8;
extern u16         D_800C2608;
extern u8          D_800C25E4;
extern u16         D_800C2610;

/* The mode handler sets the image installs into the battle hooks. */

u8   func_800C2138(u32 mode);
void func_800C2348(void);
void func_800C243C(void);

/* func_801C1254 */
void Party_LoadMemberSprite(s32 character_id, s32 party_slot);

void func_800C18FC(s32 mode);

void func_800C1B14(s32 mode);

#endif
