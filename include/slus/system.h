#ifndef SLUS_SYSTEM_H
#define SLUS_SYSTEM_H

#include "types.h"
#include "sys/cd_format.h"
#include "common/callback.h"
#include "engine/sys/flags/flags.h"
#include "engine/input/pad/pad.h"
#include "engine/emi/loader/emi.h"
#include "engine/sys/boot/boot.h"
#include "engine/cd/lz77/lz77.h"

/* The executable's system, archive, input and decompression functions, in address order. */
/* func_8014E0A8 */
extern s32 SYS_ReadCd(s32 size, void* buffer, s32 sectors);
/* func_8014EA80 */
void       SYS_StartFrontend(void);
/* func_8014EC64 */
void       SYS_EnterFrontend(void);
/* func_801501E4 */
void       SYS_CopyString(u8* dst, u8* src, s32 limit);
/* func_8015AC8C */
void       SYS_InitScratchpad(u8* panel);

#endif
