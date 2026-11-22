#ifndef PLCHAR_CHAR_CLAIM_HELPER_SLOT_STEP_H
#define PLCHAR_CHAR_CLAIM_HELPER_SLOT_STEP_H

static inline void PlChar_ClaimHelperSlotStep(void) {
    u8 slot;

    if (!(TASK(Actor)->direction & 1)) {
        TASK(Actor)->direction = (TASK(Actor)->direction - 1) & 7;
    }
    slot                          = func_8019601C();
    TASK(Actor)->param.actor_slot = slot;
    if (TASK(Actor)->param.actor_slot != 0xFF) {
        g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 0x1B;
    }
    Script_Request((TASK(Actor)->direction >> 1) + 0x42);
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(TASK(Actor)->unk_2C + 0x100);
    TASK(Actor)->header.step++;
}

#endif
