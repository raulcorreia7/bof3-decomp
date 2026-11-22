#include "engine/slus/slus.h"

/* marks the four selection voice slots free (-1), queues SE se_id through SND_SEPlay (which keys the
 * voices on), then packs the voice numbers' low five bits into the work record's state word at +0x70 (bits 8, 13, 18,
 * 23) and sets ACTOR_FLAG_SELECTION_EFFECT in its flag byte.
 */
/* FAKE: retail accesses the word at +0x70 whole; the member is the byte the entity rows use. */
MATCH void SND_SEQueueSelection(s32 se_id) {
    u32    packed;
    Actor* work;

    D_8018B31C = -1;
    D_8018B344 = -1;
    D_8018B36C = -1;
    D_8018B394 = -1;
    SND_SEPlay(se_id);
    packed = (*(u8*)&D_8018B31C & 0x1F) << 8;
    packed |= (*(u8*)&D_8018B344 & 0x1F) << 13;
    packed |= (*(u8*)&D_8018B36C & 0x1F) << 18;
    packed |= (*(u8*)&D_8018B394 & 0x1F) << 23;
    work                  = g_Task;
    work->voice_flags.raw = work->voice_flags.raw | packed;
    work->header.flags    = (work->header.flags | ACTOR_FLAG_SELECTION_EFFECT);
}
