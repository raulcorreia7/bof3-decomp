#include "engine/slus/slus.h"

/* One 8-byte scene entry: its id and the area byte at +7. */
typedef struct SceneSlot {
    u16 id;
    u8  pad_02[5];
    u8  scene;
} SceneSlot;

/* steps the 30 field actor slots: when the selected slot is live it refreshes its state byte and runs the
 * kind-10 step, or looks its scene up in the loaded scene table and D_80183A70 and runs the kind step only on a
 * listed scene.
 */
#define SCENE_SLOTS ((SceneSlot*)D_801459F4)

#ifdef NON_MATCHING
NON_MATCHING void func_80167E00(void) {
    u8 i;
    u8 slot;
    u8 j;

    for (i = 0; i < 30; i++) {
        g_Task = &g_Actors[i];
        if (!(g_Task->header.flags & ACTOR_FLAG_IN_USE)) {
            continue;
        }
        if (g_Task->unk_06 != 9) {
            if (g_Task->active_flags & 0x10) {
                g_Task->draw_layer = 4;
            } else {
                g_Task->draw_layer = g_AreaDrawMode;
            }
        } else if (g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) {
            continue;
        }
        if (g_Task->unk_06 == 10) {
            Actor_ProjectForDraw();
            continue;
        }
        for (slot = 0; slot < D_800E3800; slot++) {
            if (SCENE_SLOTS[slot].scene == g_Task->unk_2C) {
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
