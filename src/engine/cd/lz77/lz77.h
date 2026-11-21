#ifndef OVERLAY_CD_LZ77_H
#define OVERLAY_CD_LZ77_H

#include "types.h"

/* func_80164028 */
void LZ77_DecodeBegin(u8* dst);
/* func_80164064 */
s32  LZ77_DecodeStep(void);

#endif
