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
/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 72.50%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_80167E00(void) {
    EntitySlot* entity;
    u16*        list;
    s32         index;
    s32         slot;
    u8          found;
    u8          i;
    s32         four;
    u16         scene_id;
    u32         next;

    index = 0;
    four  = 4;
    list  = D_80183A70;
    do {
        slot   = index & BYTE_MASK;
        entity = (EntitySlot*)((u8*)g_Actors + slot * ACTOR_SIZE);
        g_Task = entity;
        if (ACTOR_IN_USE(*entity)) {
            if (entity->unk_06 != 9) {
                if (entity->flags_24 & 0x10) {
                    entity->unk_29 = four;
                } else {
                    entity->unk_29 = g_AreaDrawMode;
                }
                goto block_7; /* retail branch */
            }
            if (g_AreaDrawMode == four) {
                goto block_10; /* retail branch */
            }
        block_7:
            entity = g_Task;
            if (entity->unk_06 == 0xA) {
                index += 1;
                func_8015A944();
                next = index & BYTE_MASK;
            } else {
                u16 end = 0xFFFF;

                found = 0;
                if (D_800E3800 != 0) {
                    scene_id = entity->unk_2C;
                    while ((u32)found < (u32)D_800E3800) {
                        if (D_801459F4[found * 8 + 7] == scene_id) {
                            break;
                        }
                        found += 1;
                    }
                }
                if (list[0] != end) {
                    scene_id = *(u16*)(D_801459F4 + found * 8);
                    i        = 0;
                    do {
                        if (scene_id == list[i]) {
                            index += 1;
                            func_8014D290();
                            next = index & BYTE_MASK;
                            goto next_slot; /* retail branch */
                        }
                        i += 1;
                    } while (list[i] != end);
                }
            block_10:
                index += 1;
                next = index & BYTE_MASK;
            }
        } else {
            goto block_10; /* retail branch */
        }
    next_slot:;
    } while (next < 0x1E);
}
#else
INCLUDE_ASM(func_80167E00);
#endif
