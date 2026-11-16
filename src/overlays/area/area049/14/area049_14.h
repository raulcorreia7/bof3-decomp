#ifndef OVERLAY_WORLD01_AREA049_14_H
#define OVERLAY_WORLD01_AREA049_14_H

/* The world01/area049/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"

#define g_SceneFlags ((void*)g_SceneFlags)

extern u8 D_801F398C[];

extern u8 D_801F5C08[];

/* The facing and event flag of each six-byte trigger-box row. */
extern u8 D_801F5C0C[];
extern u8 D_801F5C0D[];

extern u16 D_801F5CD4[];

extern u16 D_801F5CD8[];

/* The cell pair, facing and cue id of the nine trigger slots; each row starts at a multiple of 4. */
extern u8 D_801F5CDC[];
extern u8 D_801F5CDD[];
extern u8 D_801F5CDE[];
extern u8 D_801F5CDF[];

/* A bare statement macro, used as a member's whole body. Clear the interaction bit; when the party confirmed
 * (the leader is character 6), run the script and store the two step bytes. */
#define AREA_INTERACT_CONFIRM(step_next)                                      \
    if (g_Game.members[0].chr.character_id == 6) {                            \
        g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING; \
        Game_SetScriptActive();                                               \
        g_SceneState.state_04 = 4;                                            \
        g_SceneState.step_05  = (step_next);                                  \
    } else {                                                                  \
        g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING; \
    }

s32 func_8019601C();

/* The area-change flag handover; the trigger box containing a party member, or 0xFF. */
void func_801F2C80(void);
s32  func_801F2D00(u8 member);

#endif
