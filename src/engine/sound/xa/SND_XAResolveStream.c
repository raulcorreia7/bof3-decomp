#include "engine/slus/slus.h"

/* Resolves XA stream stream_id (cue table in bits 12 and up, cue index in the low 12) into its start and end sectors and sets the file and channel of the CdlFILTER the drive filters on. */
MATCH void SND_XAResolveStream(s32 stream_id) {
    s32  scale;
    u8*  filter_channel;
    u16* entry;
    s32  count;
    s32  limit;
    s32  index;
    s32  base;
    /* FAKE: bound stays in v1. */
    FAKE_REG(s32, bound, "v1");
    s32 second_offset;
    /* FAKE: address-taken 8-byte local reserves retail's unused frame slot;
     * the pointer itself is never dereferenced. */
    u8  buffer[8];
    u8* buffer_ptr;
    /* FAKE: extra stays in a1. */
    FAKE_REG(s32, extra, "a1");
    /* FAKE: filter_file pointer stays in a2. */
    FAKE_REG(volatile u8*, filter_file, "a2");

    buffer_ptr      = buffer;
    scale           = ((stream_id >> 12) != 0) ? 0x10 : 8;
    filter_channel  = &g_SndXAFilterChannel;
    *filter_channel = 0;
    entry           = (u16*)g_SndXACues[stream_id >> 12];
    count           = stream_id & 0xFFF;
    index           = 0;
    if (count > 0) {
        limit = count;
        do {
            if (*entry & 0x8000) {
                entry += 1;
                *filter_channel += 1;
            }
            index += 1;
            entry += 1;
        } while (index < limit);
    }
    filter_file  = &g_SndXAFilterFile;
    *filter_file = 1;
    /* FAKE: force the filter_file base back into a2. */
    FAKE_CLOBBER("a2");
    base                        = g_EmiSlotLbas[g_SndXAStreamSlots[stream_id >> 12]];
    g_SndXAEndSector            = base;
    *(s32*)(filter_file - 0x28) = base;
    extra                       = filter_file[1];
    bound                       = base + (((*entry & 0x7FFF) * scale) + extra);
    *(s32*)(filter_file - 0x28) = bound;
    second_offset               = (((entry[1] & 0x7FFF) * scale) + extra);
    base -= 0x96;
    *(s32*)(filter_file - 0x20) = bound;
    g_SndXAEndSector            = base + second_offset;
}
