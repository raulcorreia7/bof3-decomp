#include "engine/slus/slus.h"

/* One 8-byte scene entry: its id and the area byte at +7. */
typedef struct SceneSlot {
    u16 id;
    u8  pad_02[5];
    u8  scene;
} SceneSlot;

/* steps the 30 field actor slots: when the selected slot is live it refreshes its state byte and runs the
 * type-10 step, or looks its scene up in the loaded scene table and D_80183A70 and runs the type step only on a
 * listed scene.
 */
#define SCENE_SLOTS ((SceneSlot*)g_SceneActorDefs)

#ifdef NON_MATCHING
NON_MATCHING void func_80167E00(void) {
    u8 i;
    u8 slot;
    u8 j;

    for (i = 0; i < 30; i++) {
        g_Task = &g_Actors[i];
        if (!(TASK(Actor)->header.flags & ACTOR_FLAG_IN_USE)) {
            continue;
        }
        if (TASK(Actor)->unk_06 != 9) {
            if (TASK(Actor)->active_flags & 0x10) {
                TASK(Actor)->draw_layer = 4;
            } else {
                TASK(Actor)->draw_layer = g_AreaDrawMode;
            }
        } else if (g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) {
            continue;
        }
        if (TASK(Actor)->unk_06 == 10) {
            Actor_ProjectForDraw();
            continue;
        }
        for (slot = 0; slot < FAKE_VOLATILE(u8, D_800E3800); slot++) {
            if (SCENE_SLOTS[slot].scene == TASK(Actor)->unk_2C) {
                break;
            }
        }
        for (j = 0; D_80183A70[j] != 0xFFFF; j++) {
            if (SCENE_SLOTS[slot].id == D_80183A70[j]) {
                Area_AddGridActor();
                break;
            }
        }
    }
}
#else
INCLUDE_ASM(func_80167E00);
#endif
