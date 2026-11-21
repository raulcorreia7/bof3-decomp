#ifndef OVERLAY_SYS_FLAGS_H
#define OVERLAY_SYS_FLAGS_H

#include "types.h"

/* func_8015B580 */
void SYS_SetFlag(void* bits, u8 bit_index);
/* func_8015B5A8 */
void SYS_ClearFlag(void* bits, u8 bit_index);
/* func_8015B5D4 */
s32  SYS_TestFlag(void* bits, s32 bit_index);
/* func_8015B5F4 */
void SYS_ToggleFlag(void* bits, u8 bit_index);

#endif
