#ifndef OVERLAY_SCENARIO_SCENA10_00_H
#define OVERLAY_SCENARIO_SCENA10_00_H

/* The scenario/scena10/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

extern u8       D_80144908[];
extern u32      D_801F6C00;
/* D_801FE80C */
extern Callback g_SceneEntityDispatch[];
extern Callback D_801FE820[];
extern Callback D_801FE8F4[];

extern Callback D_801FE900[];
extern u8       D_801FE938[];

extern u8        D_801FE950[4];
extern u8        D_801FE9DC;
extern s8        D_801FE94C[4];
extern u16       D_801FE954[4];
extern u8        D_801FE95C[5];
extern u16       D_801FE964[5];
extern u8        D_801FE970[3];
extern u16       D_801FE974[3];
/* D_801FE97C */
extern SceneFunc g_SceneActorDispatch[];

/* The actor-start members of 368.c: reset the scene state, set the actor to mode 4 with a fixed
 * state and step, and raise a scene flag. They differ only in the three constants. Every change
 * here must verify every member. */
#define SCENA10_ACTOR_START(scene, step, flag) \
    do {                                       \
        func_801BE1B0(scene);                  \
        actor->header.mode = 4;                \
        actor->unk_78      = 2;                \
        actor->unk_77      = (step);           \
        actor->unk_7E      = 0;                \
        SYS_SetFlag(g_SceneFlags, (flag));     \
    } while (0)

/* The party lookups of 368.c: return the value paired with the first id in `ids` that a party member
 * holds, else `none`. The members differ only in table and count. Every change must verify every member. */
#define SCENA10_PARTY_LOOKUP(count, ids, values, none)                        \
    do {                                                                      \
        u8 slot;                                                              \
        u8 member;                                                            \
                                                                              \
        for (slot = 0; slot < (count); slot++) {                              \
            for (member = 0; member < g_Game.party_size; member++) {          \
                if (g_Game.members[member].chr.character_id == (ids)[slot]) { \
                    return (values)[slot];                                    \
                }                                                             \
            }                                                                 \
        }                                                                     \
        return (none);                                                        \
    } while (0)

void func_801F6FAC(void);

s32 Item_Count(s32 category, s32 item, s32 mode);

#endif
