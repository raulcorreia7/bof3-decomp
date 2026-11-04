#ifndef OVERLAY_SCENARIO_SCENA13_00_H
#define OVERLAY_SCENARIO_SCENA13_00_H

/* The scenario/scena13/00 overlay's local declarations. Only this image
 * includes the file. */

#define GRAPHICS_PALETTE_PENDING_VOLATILE
#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"

extern u32       D_801F6C00;
extern u8        D_801468E4[];
extern u8        D_801FBF20[];
extern u8        D_801FBF78[];
extern u8        D_801FBF98[];
extern Callback  D_801FBEFC[];
extern Callback  D_801FBF10[];
extern Callback  D_801FBF48[];
extern Callback  D_801FBF54[];
extern SceneFunc D_801FBFB8[];

void func_801F6FF8(void);
void func_801F70DC(void);
void func_801F7568(void);

extern Callback D_801FBEF0[];

extern u8 D_80144908[];
extern u8 D_8014490B[];

/* Reserve two actor slots and start the same pair of scripts on them; the
 * second script sits 0x10 bytes after the first. Every change must verify
 * every member. */
#define SCENE_START_SCRIPT_PAIR(script)                          \
    do {                                                         \
        s32 first;                                               \
        s32 second;                                              \
        s32 first_index;                                         \
        s32 second_index;                                        \
                                                                 \
        first       = Actor_FindFree();                          \
        first_index = first & BYTE_MASK;                         \
        if (first_index != GAME_NONE) {                          \
            g_Actors[first_index].flags_00 = 1;                  \
            second                         = Actor_FindFree();   \
            second_index                   = second & BYTE_MASK; \
            if (second_index == GAME_NONE) {                     \
                g_Actors[first_index].flags_00 = 0;              \
                return;                                          \
            }                                                    \
            g_Actors[second_index].flags_00 = 1;                 \
            *(s16*)D_1F800000               = (u8)first;         \
            func_801A65A0(script);                               \
            *(s16*)D_1F800000 = (u8)second;                      \
            func_801A65A0((script) + 0x10);                      \
        }                                                        \
    } while (0)

#endif
