#ifndef BOSS_FAMILY_H
#define BOSS_FAMILY_H

/* Declarations shared by two or more boss images; an image header that
 * reads one includes this file. */

#include "game.h"
#include "work/actor.h"
#include "sys/exe.h"
#include <memory.h>

/* A boss module's head. The rest of the head is the per-boss callback block
 * measured from each image's own bytes. */
typedef struct BossModule {
    EmiModuleId id; /* 0x00; 0x11E-0x140 */
} BossModule;

ASSERT_SIZE(BossModule, 4);

extern u8                  D_800C1990[];
extern Callback            D_800C19A4[];
extern Callback            D_800C19D4[];
extern Callback            D_800C1ADC[];
extern u8                  D_800C1B1C[];
extern Callback            D_800C1B30[];
extern Callback            D_800C1B60[];
extern Callback            D_800C1B6C[];
extern Callback            D_800C1B74[];
extern Callback            D_800C1B9C[];
extern Callback            D_800C1D2C[];
extern Callback            D_800C1D5C[];
extern Callback            D_800C21BC[];
extern Callback            D_800C26CC[];
extern Callback            D_800C26FC[];
extern BossBattleEventFunc g_BossBattleEventHook;

void func_800C1978(s32 mode);
void func_800C1998(s32 mode);
/* func_800C1ACC (boss014), func_800C1AE8 (boss024), func_800C1E74 (boss002), func_800C1FE8 (boss004), func_800C20C0 (boss008), func_800C2430 (boss018) */
u8   Boss_HandleBattleEvent2(u32 mode);
/* func_800C1AD4 (boss014), func_800C1AF0 (boss024), func_800C1E7C (boss002), func_800C20C8 (boss008), func_800C2188 (boss004), func_800C253C (boss018) */
void Boss_ChooseBattleEnding2(void);
void func_800C1AF0(s32 mode);
/* func_800C1B20 (boss014), func_800C1B3C (boss024), func_800C1EE8 (boss002), func_800C2114 (boss008), func_800C2208 (boss004), func_800C265C (boss018) */
void Boss_EndBattle2(void);
/* func_800C1928 (boss015), func_800C1928 (boss029), func_800C1934 (boss037), func_800C1934 (boss042), func_800C1940 (boss050), func_800C1968 (boss054), func_800C19BC (boss023), func_800C19FC (boss017), func_800C1A00 (boss031), func_800C1A00 (boss032), func_800C1A14 (boss030), func_800C1A20 (boss014), func_800C1A20 (boss024), func_800C1A2C (boss040), func_800C1A2C (boss049), func_800C1A40 (boss022), func_800C1A44 (boss007), func_800C1A4C (boss051), func_800C1B08 (boss021), func_800C1B44 (boss052), func_800C1B78 (boss028), func_800C1B84 (boss035), func_800C1BA0 (boss012), func_800C1BB4 (boss038), func_800C1C44 (boss004), func_800C1D88 (boss002), func_800C1DA8 (boss033), func_800C1DB0 (boss036), func_800C1E88 (boss001), func_800C1FD4 (boss008), func_800C2044 (boss013), func_800C214C (boss018), func_800C2378 (boss034), func_800C24D8 (boss055), func_800C2B98 (boss025) */
u8   Boss_HandleBattleEvent(u32 mode);
/* func_800C1930 (boss015), func_800C1930 (boss029), func_800C193C (boss037), func_800C193C (boss042), func_800C1948 (boss050), func_800C1970 (boss054), func_800C19C4 (boss023), func_800C1A04 (boss017), func_800C1A08 (boss031), func_800C1A08 (boss032), func_800C1A1C (boss030), func_800C1A28 (boss014), func_800C1A28 (boss024), func_800C1A34 (boss040), func_800C1A34 (boss049), func_800C1A48 (boss022), func_800C1A54 (boss051), func_800C1B4C (boss052), func_800C1B80 (boss028), func_800C1BA8 (boss012), func_800C1BBC (boss038), func_800C1BF0 (boss035), func_800C1C18 (boss021), func_800C1CB4 (boss007), func_800C1DB0 (boss033), func_800C1DB8 (boss036), func_800C1DD4 (boss002), func_800C1DE4 (boss004), func_800C1FDC (boss008), func_800C1FF8 (boss001), func_800C204C (boss013), func_800C2258 (boss018), func_800C2380 (boss034), func_800C24E0 (boss055), func_800C2D7C (boss025) */
void Boss_ChooseBattleEnding(void);
/* func_800C197C (boss015), func_800C1988 (boss029), func_800C1988 (boss037), func_800C1988 (boss042), func_800C19A0 (boss050), func_800C19BC (boss054), func_800C1A10 (boss023), func_800C1A50 (boss017), func_800C1A6C (boss031), func_800C1A74 (boss014), func_800C1A80 (boss040), func_800C1A80 (boss049), func_800C1A84 (boss030), func_800C1A90 (boss024), func_800C1AA0 (boss051), func_800C1ABC (boss022), func_800C1BCC (boss028), func_800C1BEC (boss032), func_800C1C00 (boss012), func_800C1C08 (boss038), func_800C1C3C (boss035), func_800C1C64 (boss021), func_800C1D14 (boss052), func_800C1D50 (boss007), func_800C1E04 (boss036), func_800C1E24 (boss033), func_800C1E34 (boss002), func_800C1E64 (boss004), func_800C2028 (boss008), func_800C2060 (boss001), func_800C20B0 (boss013), func_800C2378 (boss018), func_800C23CC (boss034), func_800C26B4 (boss055), func_800C2F74 (boss025) */
void Boss_EndBattle(void);
void func_800C1B18(s32 mode);
void func_800C1C08(s32 mode);
void func_800C1E58(s32 mode);
/* func_800C1F40 (boss002), func_800C21BC (boss008), func_800C2384 (boss004), func_800C2714 (boss018) */
u8   Boss_HandleBattleEvent3(u32 mode);
/* func_800C1F48 (boss002), func_800C21C4 (boss008), func_800C2524 (boss004), func_800C2820 (boss018) */
void Boss_ChooseBattleEnding3(void);
/* func_800C1F94 (boss002), func_800C2210 (boss008), func_800C25A4 (boss004), func_800C292C (boss018) */
void Boss_EndBattle3(void);

#endif
