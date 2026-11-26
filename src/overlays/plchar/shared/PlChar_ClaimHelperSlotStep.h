#ifndef PLCHAR_CHAR_CLAIM_HELPER_SLOT_STEP_H
#define PLCHAR_CHAR_CLAIM_HELPER_SLOT_STEP_H

static inline void PlChar_ClaimHelperSlotStep(void) {
    u8 slot;

    if (!(SELF(Actor)->direction & 1)) {
        SELF(Actor)->direction = (SELF(Actor)->direction - 1) & 7;
    }
    slot                          = func_8019601C();
    SELF(Actor)->param.actor_slot = slot;
    if (SELF(Actor)->param.actor_slot != 0xFF) {
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 0x1B;
    }
    Script_Request((SELF(Actor)->direction >> 1) + 0x42);
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + 0x100);
    SELF(Actor)->header.step++;
}

#endif
