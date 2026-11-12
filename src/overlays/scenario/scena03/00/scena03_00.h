#ifndef OVERLAY_SCENARIO_SCENA03_00_H
#define OVERLAY_SCENARIO_SCENA03_00_H

/* The scenario/scena03/00 overlay's local declarations. Only this image
 * includes the file. */

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"

extern SVECTOR  D_1F800014[];
extern s8       D_80144EA0;
extern u8       D_801468E4[];
extern u32      D_801F6C00;
/* D_801FCF24 */
extern Callback g_SceneEntityDispatch[];
extern u8       D_801FCF30[];
extern s16      D_801FCF40;
extern s16      D_801FCF42;
extern Callback D_801FCF50[];
extern u8       D_801FCF5C[];
extern Callback D_801FCF70[];
extern Callback D_801FCF88[];
extern Callback D_801FCF94[];
extern Callback D_801FCFA0[];
extern Callback D_801FCFAC[];
extern Callback D_801FCFD4[];
extern Callback D_801FCFE0[];

/* D_801FD00C */
extern SceneFunc g_SceneActorDispatch[];

s32 func_801FC5A4(void);

/* Sets one scene flag bit, then runs func_801FC5A4. */
static inline void Scene_SetFlagThenContinue(void* flags, u8 bit) {
    SYS_SetFlag(flags, bit);
    func_801FC5A4();
}

extern u8 D_80144EA2;
extern u8 D_80144F5B;
extern u8 D_80144F5C;
extern u8 D_80144F5F;

s32 func_8019601C();

extern u16      D_80146876;
extern u16      D_8014600E;
extern s8       D_801FD004[4];
extern s8       D_801FD008[2];
extern u8       D_801FD030;
extern Callback D_801FD038[];

/* The camera nudges of 270.c: step the scroll words by the table entry picked with the low bits of the facing counter. They differ only in table and mask. */
#define SCENA03_NUDGE_SCROLL(table, mask) \
    do {                                  \
        u16* scroll;                      \
        u16  dir;                         \
                                          \
        dir    = D_80146876 & (mask);     \
        scroll = (u16*)&D_80145ECE;       \
        *scroll += (table)[dir] * 16;     \
        D_8014600E += (table)[dir] * 16;  \
    } while (0)

s8 func_801FCD1C(s32 arg0, s32 arg1);

void func_801F8170(s32 arg0);

void func_801F7FFC(s32 arg0);

s8 func_801A7AD8(u8* entry, u8 count, u16 x, u16 y);

#endif
