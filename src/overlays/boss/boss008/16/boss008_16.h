#ifndef OVERLAY_BOSS_BOSS008_16_H
#define OVERLAY_BOSS_BOSS008_16_H

/* The boss/boss008/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */

extern u8       D_800C264C[];
extern u16      D_800C2658[];
extern Callback D_800C2660[];
extern Callback D_800C2690[];
extern Callback D_800C26A8[];
extern Callback D_800C26B0[];
extern Callback D_800C26C0[];
extern Callback D_800C2708[];
extern Callback D_800C2738[];
extern Callback D_800C2744[];
extern Callback D_800C2774[];

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C1D74(s32 mode);
void func_800C1E60(s32 mode);
void func_800C1F4C(s32 mode);
/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in config/symbols/emi+boss+boss008+16.toml. */
void Boss_ChooseBattleEnding4(void);
void Boss_EndBattle4(void);
void func_800C236C(u8 phase);
/* D_801EB630 */

/* The end-of-battle setup of one enemy slot. It takes the slot's record into the scratchpad and finds scene
 * record 0x83; the finish plays script 0 and copies the halfwords at +0x58 and +0x5A of the first enemy record. A
 * member that marks the record writes that statement between the two. */
#define BOSS008_END_BATTLE_BEGIN(slot)          \
    Battle_ShowActorEntry(slot);                \
    g_Task = (PartyMember*)func_800AC754(slot); \
    Area_SceneSelectRecord(0x83)

#define BOSS008_END_BATTLE_FINISH()                              \
    Script_Select(0);                                            \
    TASK(PartyMember)->unk_58 = g_BattleEnemyBattlers[0].unk_58; \
    TASK(PartyMember)->unk_5A = g_BattleEnemyBattlers[0].unk_5A

/* One enemy kind's colour, from kind 8 up. */
typedef struct Boss008Color {
    u8 r;
    u8 g;
    u8 b;
} Boss008Color;

extern Boss008Color D_800C2640[];
void                func_801D9DBC(s16 x, s16 y, u8 template_index, u16 packed_color, u8 semi_trans);

#endif
