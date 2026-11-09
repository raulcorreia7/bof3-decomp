#ifndef AUDIO_BANK_H
#define AUDIO_BANK_H

#include "types.h"

#define EMI_BANK_RECORD_SIZE 0x14

/* One audio bank record of the main executable's EMI loader (seven records at 0x8014677C). */
typedef struct EMIBank {
    u32 spu_address;     /* 0x00 SPU sound-buffer address, SsVabOpenHeadSticky argument 3 */
    u32 source;          /* 0x04 VAB header address, argument 1; also the next-record link of a free record */
    u32 cue_table;       /* 0x08 cue table chunk (the bank's row of g_SndBankCues) */
    u32 sequence_buffer; /* 0x0C sequence package buffer */
    s16 resource_id;     /* 0x10 VAB id, argument 2 */
    u16 flags;           /* 0x12 bit 1: sequence loaded */
} EMIBank;

ASSERT_SIZE(EMIBank, EMI_BANK_RECORD_SIZE);
ASSERT_OFFSET(EMIBank, source, 0x04);
ASSERT_OFFSET(EMIBank, resource_id, 0x10);

#endif
