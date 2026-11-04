#include "engine/slus/slus.h"

/* marks the four selection voice slots free (-1), queues cue cue_id through SND_PlayCue (which keys the
 * voices on), then packs the voice numbers' low five bits into the work record's state word at +0x70 (bits 8, 13, 18,
 * 23) and sets bit 3 of its flag byte.
 */
/* FAKE: retail accesses the word at +0x70 whole; the member is the byte the entity rows use. */
/* func_8015D71C */
MATCH void SND_QueueSelectionFx(s32 cue_id) {
    u32    packed;
    Actor* work;

    D_8018B31C = -1;
    D_8018B344 = -1;
    D_8018B36C = -1;
    D_8018B394 = -1;
    SND_PlayCue(cue_id);
    packed = (u32)(*(u8*)&D_8018B31C & 0x1F) << 8;
    packed |= (u32)(*(u8*)&D_8018B344 & 0x1F) << 13;
    packed |= (u32)(*(u8*)&D_8018B36C & 0x1F) << 18;
    packed |= (u32)(*(u8*)&D_8018B394 & 0x1F) << 23;
    work                = g_SpadWork;
    work->state_70.word = work->state_70.word | packed;
    work->flags_00      = (u8)(work->flags_00 | 8);
}
