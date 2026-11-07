#ifndef OVERLAY_BOSS_BOSS025_13_H
#define OVERLAY_BOSS_BOSS025_13_H

/* The boss/boss025/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyBattler record in this image. */
#define g_Task ((PartyBattler*)g_Task)

/* The ending hooks of both sets send each live party battler into its ending pose: KO'd battlers
 * take the down script, the rest the stand script for their facing. */
#define BOSS_SEND_PARTY_TO_ENDING_POSE(n)                                                                 \
    if (g_BattlePartyBattlers[n].header.flags & 1) {                                                      \
        Battle_CancelTurn(g_BattlePartyBattlers[n].slot);                                                 \
        TASK_SET(&g_BattlePartyBattlers[n]);                                                              \
        if (g_BattlePartyBattlers[n].chr.status & STATUS_KO) {                                            \
            Actor_SwitchScript(g_BattlePartyBattlers[n].facing + 0x1C, MEM_PTR(u8, 0x800F0800u), 0x1800); \
        } else {                                                                                          \
            Actor_SwitchScript(g_BattlePartyBattlers[n].facing + 4, MEM_PTR(u8, 0x800F0800u), 0x1800);    \
        }                                                                                                 \
    }

extern u8          D_800C3180[];
extern u16         D_800C3194[];
extern Callback    D_800C319C[];
extern Callback    D_800C31CC[];
extern Callback    D_800C31E4[];
extern Callback    D_800C31F0[];
extern Callback    D_800C3220[];
extern Callback    D_800C3238[];
extern Callback    D_800C3244[];
extern Callback    D_800C3274[];
extern Callback    D_800C327C[];
extern Callback    D_800C3294[];
extern Callback    D_800C32A0[];
extern u8          D_800C32B4;
extern u8          D_800C32B8;
extern u16         D_80145F18;
/* The word at g_BattleScrollDir: its bytes are the scroll direction, g_BattleBossFlags, D_801462EE and
 * g_BattleSelectionLatch. func_800C1E34 tests the boss flag bits 3 and 5 together through it. */
extern u32         D_801462EC;
extern volatile u8 D_80146322;
extern s8          D_80146875;
extern u8          D_80148603;
extern u8          D_801FE4E4;
extern u32         D_801FE4E8;
extern u8          D_801FE4EC[];
extern u8          D_801FE4EF;
extern u32         D_801FE4F0;

void func_800C20F0(s32 mode);

#endif
