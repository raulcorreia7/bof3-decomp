#ifndef PLCHAR_CHAR_CLAIM_HELPER_SLOT_STEP_H
#define PLCHAR_CHAR_CLAIM_HELPER_SLOT_STEP_H

static inline void PlChar_ClaimHelperSlotStep(void) {
    u8 slot;

    if (!(g_Task->direction & 1)) {
        g_Task->direction = (g_Task->direction - 1) & 7;
    }
    slot                     = func_8019601C();
    g_Task->param.actor_slot = slot;
    if (g_Task->param.actor_slot != 0xFF) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0x1B;
    }
    Script_Request((g_Task->direction >> 1) + 0x42);
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(g_Task->unk_2C + 0x100);
    g_Task->header.step++;
}

#endif
