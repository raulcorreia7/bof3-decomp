#include "engine/slus/slus.h"

/* lays out the seven sound banks of one layout row (0x1C bytes: header size, sequence size and SPU address per bank):
 * the banks follow one another from the sound heap base; each header and sequence address goes to g_SndBankHeaders and
 * g_SndBankSequences, the SPU address, header, sequence buffer and bank number to the g_EmiBanks records.
 */
MATCH void SND_SetBankLayout(u32 layout) {
    s32 off;
    /* FAKE: pin keeps the accumulator in v1. */
    FAKE_REG(s32, v, "v1");
    /* FAKE: pin keeps the width in a0. */
    FAKE_REG(s32, w, "a0");
    u8* layer2;
    /* FAKE: pin keeps the stride in v0. */
    FAKE_REG(s32, size, "v0");
    /* FAKE: pin keeps the end offset in t0. */
    FAKE_REG(s32, end, "t0");
    /* FAKE: pin keeps the next index in a2. */
    FAKE_REG(s32, next, "a2");
    /* FAKE: pin keeps the last index in a3. */
    FAKE_REG(s32, last, "a3");

    s32 heap_base             = 0x8011A000;
    off                       = (layout & BYTE_MASK) * (SND_BANK_COUNT * sizeof(u32));
    g_EmiBank0VabId           = 0;
    v                         = FIELD(s32, g_SndBankHeaderSize, off);
    layer2                    = D_8014871C;
    g_SndBank0Header          = heap_base;
    ((u32*)g_EmiBankLinks)[0] = heap_base;
    v += heap_base;
    g_EmiBank0SequenceBuffer[0] = v;
    w                           = FIELD(s32, g_SndBankSpuAddress, off);
    g_EmiBank0SeRecords         = D_801486A0;
    g_SndBank0Sequence          = v;
    g_EmiBank1VabId             = 1;
    g_EmiBanks[0].spu_address   = w;
    size                        = FIELD(s32, g_SndBankSequenceSize, off);
    w                           = FIELD(s32, g_SndBankHeaderSize, off + 4);
    v += size;
    w                        = v + w;
    g_SndBank1Header         = v;
    g_EmiBank1SequenceBuffer = w;
    g_EmiBank1VabHeader      = v;
    v                        = FIELD(s32, g_SndBankSpuAddress, off + 4);
    g_EmiBank1SeRecords      = layer2;
    g_SndBank1Sequence       = w;
    g_EmiBank2VabId          = 2;
    g_EmiBank1SpuAddress     = v;
    size                     = FIELD(s32, g_SndBankSequenceSize, off + 4);
    v                        = FIELD(s32, g_SndBankHeaderSize, off + 8);
    w += size;
    v                        = w + v;
    g_SndBank2Header         = w;
    g_EmiBank2SequenceBuffer = v;
    g_EmiBank2VabHeader      = w;
    w                        = FIELD(s32, g_SndBankSpuAddress, off + 8);
    g_EmiBank2SeRecords      = D_80148798;
    g_SndBank2Sequence       = v;
    g_EmiBank3VabId          = 3;
    g_EmiBank2SpuAddress     = w;
    size                     = FIELD(s32, g_SndBankSequenceSize, off + 8);
    w                        = FIELD(s32, g_SndBankHeaderSize, off + 12);
    v += size;
    w = v + w;
    /* FAKE: the order lock steers regalloc. */
    FAKE_ORDER_LOCK_BEGIN
        g_SndBank3Header         = v;
        g_SndBank3Sequence       = w;
        g_EmiBank3SequenceBuffer = w;
        g_EmiBank3VabHeader      = v;
        v                        = FIELD(s32, g_SndBankSpuAddress, off + 12);
        g_EmiBank3SeRecords      = D_80148814;
        g_EmiBank4VabId          = 4;
        g_EmiBank3SpuAddress     = v;
        size                     = FIELD(s32, g_SndBankSequenceSize, off + 12);
        end                      = FIELD(s32, g_SndBankHeaderSize, off + 16);
        w += size;
        end                      = w + end;
        g_EmiBank4SequenceBuffer = end;
        g_EmiBank4VabHeader      = w;
        v                        = FIELD(s32, g_SndBankSpuAddress, off + 16);
        g_EmiBank4SeRecords      = D_80148890;
        g_EmiBank5VabId          = 5;
        g_EmiBank4SpuAddress     = v;
        next                     = FIELD(s32, g_SndBankSequenceSize, off + 16);
        last                     = FIELD(s32, g_SndBankHeaderSize, off + 20);
        next                     = end + next;
        last                     = next + last;
        g_EmiBank5SequenceBuffer = last;
        g_EmiBank5VabHeader      = next;
        v                        = FIELD(s32, g_SndBankSpuAddress, off + 20);
        g_EmiBank5SeRecords      = D_8014890C;
        g_EmiBank6VabId          = 6;
        g_EmiBank5SpuAddress     = v;
        size                     = FIELD(s32, g_SndBankSequenceSize, off + 20);
        v                        = FIELD(s32, g_SndBankHeaderSize, off + 24);
        size                     = last + size;
        v                        = size + v;
        g_EmiBank6SequenceBuffer = v;
        g_EmiBank6VabHeader      = size;
        off                      = FIELD(s32, g_SndBankSpuAddress, off + 24);
        g_SndBank4Header         = w;
        g_SndBank4Sequence       = end;
        g_SndBank5Header         = next;
        g_SndBank5Sequence       = last;
    FAKE_ORDER_LOCK_END;
    g_SndBank6Header     = size;
    g_SndBank6Sequence   = v;
    g_EmiBank6SpuAddress = off;
    g_EmiBank6SeRecords  = D_80148988;
}
