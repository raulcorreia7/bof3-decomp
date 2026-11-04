#ifndef OVERLAY_BOSS_BOSS002_16_H
#define OVERLAY_BOSS_BOSS002_16_H

/* The boss/boss002/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8           D_800C1F9C[];
extern u16          D_800C1FAC[];
extern u16          D_800C1FB4[];
extern Callback     D_800C1FBC[];
extern Callback     D_800C1FEC[];
extern Callback     D_800C1FF4[];
extern Callback     D_800C2000[];
extern Callback     D_800C2030[];
extern Callback     D_800C2048[];
extern Callback     D_800C2054[];
extern Callback     D_800C2084[];
extern EnemyBattler D_801EB630[];

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss002/16] of config/symbols.toml. */

s32  func_800AC7D0(u8 entry_id);
void func_800AC870(s32 entry_id, PartyBattler* source_record, s32 mode);
/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C19C8(s32 mode);
void func_800C1D00(s32 mode);
s32  Actor_RunHandler(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, u8 flags);

#endif
