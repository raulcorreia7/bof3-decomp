#ifndef OVERLAY_SCENARIO_SCENA13_00_H
#define OVERLAY_SCENARIO_SCENA13_00_H

/* The scenario/scena13/00 overlay's local declarations. Only this image
 * includes the file. */

#define FAKE_DECL_GRAPHICS_PALETTE_PENDING_VOLATILE
#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"

extern u8       D_80144908[];
extern u8       D_8014490B[];
extern u8       D_801468E4[];
extern u32      D_801F6C00;
/* D_801FBEF0 */
extern Callback g_SceneEntityDispatch[];
extern Callback D_801FBEFC[];
extern Callback D_801FBF10[];
extern u8       D_801FBF20[];
extern Callback D_801FBF48[];
extern Callback D_801FBF54[];

void func_801F70DC(void);
void func_801F7568(void);
void func_801F9E70(u16 phase);

extern u8 D_801460FB;

extern u8        D_8014623B;
extern u16       D_80146258;
extern u32       D_80147B5C;
extern u8        D_801FBF78[];
extern u8        D_801FBF98[];
/* D_801FBFB8 */
extern SceneFunc g_SceneActorDispatch[];
/* A byte the scene handlers store and reload. */
extern u8        D_801FBFEC;

/* Reserve two actor slots and start the same pair of scripts on them; the second script sits 0x10 bytes after the first. */
#define SCENE_START_SCRIPT_PAIR(script)                                 \
    do {                                                                \
        s32 first;                                                      \
        s32 second;                                                     \
        s32 first_index;                                                \
        s32 second_index;                                               \
                                                                        \
        first       = Actor_FindFreeField();                            \
        first_index = first & BYTE_MASK;                                \
        if (first_index != GAME_NONE) {                                 \
            g_Actors[first_index].header.flags = 1;                     \
            second                             = Actor_FindFreeField(); \
            second_index                       = second & BYTE_MASK;    \
            if (second_index == GAME_NONE) {                            \
                g_Actors[first_index].header.flags = 0;                 \
                return;                                                 \
            }                                                           \
            g_Actors[second_index].header.flags = 1;                    \
            g_ScratchPad.cells.halves[0]        = (u8)first;            \
            func_801A65A0(script);                                      \
            g_ScratchPad.cells.halves[0] = (u8)second;                  \
            func_801A65A0((script) + 0x10);                             \
        }                                                               \
    } while (0)

#endif
