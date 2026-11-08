/* Host stand-in for the game's slus.h: only what the LZ77 stream decoder units use, so
 * tools/tests/test_lz77_model.py can compile their C equivalents natively. */
#ifndef HOST_SLUS_H
#define HOST_SLUS_H

#include <stdint.h>

typedef uint8_t  u8;
typedef uint32_t u32;
typedef int32_t  s32;

#define HAND_ASM
#define INCLUDE_ASM(name)

#include "sys/lz77.h"

#ifndef HOST_WINDOW
#define HOST_WINDOW 0x400u
#endif

extern u8 g_host_scratchpad[];
#define SCRATCH_PAD         ((uintptr_t)g_host_scratchpad)
#define SCRATCH_PAD_SIZE    HOST_WINDOW
#define COPY_KERNEL_ENTRY   0x8016432Cu

typedef struct EMIDecodeContext {
    u8* dst;
    u32 unk04;
    u8* src;
    u32 unk0C;
    u32 state;
    u32 pending;
    u8* limit;
    u8* copy_entry;
    u32 spill[8];
} EMIDecodeContext;

extern EMIDecodeContext D_800327A0[];

u8*  func_801642F4(u8* dst, const u8* src, u32 count);
void LZ77_DecodeBegin(u8* dst);
s32  LZ77_DecodeStep(void);

#endif
