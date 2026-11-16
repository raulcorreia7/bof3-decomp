#include "engine/slus/slus.h"

/* One 0x98-byte entity slot, viewed at the fields this routine steps. */
typedef struct EntitySlot {
    u8  flags;
    u8  pad_01[5];
    u8  unk_06;
    u8  pad_07[0x1D];
    u8  flags_24;
    u8  pad_25[4];
    u8  unk_29;
    u8  pad_2A[2];
    u16 unk_2C;
    u8  pad_2E[0x6A];
} EntitySlot;

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
#define TASK_SLOT   ((EntitySlot*)g_Task)
#define SCENE_SLOTS ((SceneSlot*)D_801459F4)

#ifdef NON_MATCHING
NON_MATCHING void func_80167E00(void) {
    u8 i;
    u8 slot;
    u8 j;

    for (i = 0; i < 30; i++) {
        g_Task = (Actor*)&g_Actors[i];
        if (!(TASK_SLOT->flags & ACTOR_FLAG_IN_USE)) {
            continue;
        }
        if (TASK_SLOT->unk_06 != 9) {
            if (TASK_SLOT->flags_24 & 0x10) {
                TASK_SLOT->unk_29 = 4;
            } else {
                TASK_SLOT->unk_29 = g_AreaDrawMode;
            }
        } else if (g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) {
            continue;
        }
        if (TASK_SLOT->unk_06 == 10) {
            func_8015A944();
            continue;
        }
        for (slot = 0; slot < D_800E3800; slot++) {
            if (SCENE_SLOTS[slot].scene == TASK_SLOT->unk_2C) {
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
