/* When the effect ticker runs down. */
/* func_801EF6AC (magic008), func_801EF150 (magic015), func_801EF594 (magic015) */
#define EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE()                          \
    if (g_Task->param.unk_0B == 0) {                                         \
        func_800AFC54();                                                     \
        func_800AEF98(4, 0);                                                 \
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY; \
        g_Task->header.mode += 1;                                            \
    }
