#ifndef OVERLAY_SCENARIO_SCENA10_00_H
#define OVERLAY_SCENARIO_SCENA10_00_H

/* The scenario/scena10/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

extern u32        D_801F6C00;
extern ScratchPad D_1F800000;
extern Callback   D_801FE820[];
extern Callback   D_801FE8F4[];
extern Callback   D_801FE900[];
extern SceneFunc  D_801FE97C[];

extern Callback D_801FE80C[];
extern u8       D_801FE938[];

extern u8  D_801FE950[4];
extern u16 D_801FE954[4];
extern u8  D_801FE95C[5];
extern u16 D_801FE964[5];
extern u8  D_801FE970[3];
extern u16 D_801FE974[3];

/* The party lookups of 370.c: return the value paired with the first id in `ids` that a party member
 * holds, else `none`. The members differ only in table and count. Every change must verify every member. */
#define SCENA10_PARTY_LOOKUP(count, ids, values, none)                                 \
    do {                                                                               \
        u8 slot;                                                                       \
        u8 member;                                                                     \
                                                                                       \
        for (slot = 0; slot < (count); slot++) {                                       \
            for (member = 0; member < g_PartySize; member++) {                         \
                if (g_BattlePartyBattlers[member].stats.character_id == (ids)[slot]) { \
                    return (values)[slot];                                             \
                }                                                                      \
            }                                                                          \
        }                                                                              \
        return (none);                                                                 \
    } while (0)

#endif
