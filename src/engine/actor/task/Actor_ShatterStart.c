#include "engine/game/00/game_00.h"

/* func_8019F75C */
/* Copies the actor's model, builds its shards and starts the dust with a 16-frame timer. */
MATCH void Actor_ShatterStart(void) {
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);
    u8* dst;
    s32 index;
    s32 limit;

    dst   = MEM_PTR(u8, BATTLE_SCRIPT_TABLE);
    limit = *TASK(Actor)->range_54.table * 0x28;
    index = 0;
    if (limit > 0) {
        do {
            *dst = *TASK(Actor)->script;
            TASK(Actor)->script += 1;
            index += 1;
            dst += 1;
        } while (index < limit);
    }
    TASK(Actor)->script = MEM_PTR(u8, BATTLE_SCRIPT_TABLE);
    Actor_ShatterBuildShards();
    Actor_ShatterStartDust();
    TASK(Actor)->timer = 16;
}
