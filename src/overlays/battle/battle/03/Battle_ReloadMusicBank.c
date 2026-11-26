#include "battle_03.h"

MATCH void Battle_ReloadMusicBank(void) {
    u32          action;
    u8           unk_02;
    u8           unk_03;
    u8           state;
    u8           flag;
    u16          template_id;
    volatile u8* counter;

    if (EMI_IsReady() != 0) {
        g_Battle.end_hook();
        if ((g_Battle.outcome.options & BATTLE_OPT_KEEP_BGM) == 0u) {
            SND_SeqStopAll();
            action = g_SndBGMId;
            if (action != 0xFFu) {
                unk_02           = g_BGMTracks[action].sep_slot;
                state            = g_EmiStreamFlags;
                flag             = g_Battle.outcome.result;
                D_80146855       = unk_02;
                unk_03           = g_BGMTracks[action].sequence;
                g_EmiStreamFlags = state | 0x20u;
                D_80146856       = unk_03;
                if ((flag & 0x10u) != 0u) {
                    g_EmiStreamFlags = state | 0x60u;
                }
                template_id = g_BGMTracks[action].bank_slot;
                D_801463B0  = template_id;
                EMI_ArchiveLoad(template_id);
            } else {
                g_Battle.outcome.result |= BATTLE_RESULT_NO_BGM;
            }
        }
        counter = &g_Battle.phase.sub_step;
        *counter += 1u;
    }
}
