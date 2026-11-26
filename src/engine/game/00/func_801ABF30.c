#include "game_00.h"

/* Scratchpad spill slot for the incoming work pointer while the call runs. */
#define SAVE_SLOT SP_REF(Actor*, 0x10u)

MATCH VECTOR* func_801ABF30(VECTOR* out, s32 sel, s32 selector_type) {
    Actor* work;
    Actor* cur;
    VECTOR buf;
    u8     i;
    u8     count;
    u8     key;

    SAVE_SLOT = TASK(Actor);
    key       = sel;
    if ((sel & 0x80) != 0) {
        key &= 0x3F;
        i     = 0;
        count = 0;
        for (; i < ENTITY_MAX; i++) {
            if (g_Actors[i].unk_06 == 0x0A) {
                if (count == key) {
                    break;
                }
                count += 1;
            }
        }
        work = &g_Actors[count];
    } else {
        work = &g_PartyActors[key];
    }
    TASK_SET(work);
    /* FAKE: keeps the scratchpad store ahead of the call-argument setup. */
    FAKE_BARRIER();
    func_801AC1DC((s32*)&buf.vx, selector_type);
    cur = TASK(Actor);
    buf.vx += cur->pos.x.fixed;
    buf.vy += cur->pos.y.fixed;
    buf.vz += (s16)COORD_INT(cur->pos.z);
    TASK_SET(SAVE_SLOT);
    *out = buf;
    return out;
}
