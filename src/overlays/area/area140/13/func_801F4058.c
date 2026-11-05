#include "area140_13.h"

MATCH s32 func_801F4058(s16 arg0, s16 arg1) {
    if ((func_801A1AE4(g_CurrentActor) != 0) && ((Area_GetCellCode((s32)arg0, (s32)arg1) & 0xFF) != 0x89)) {
        return 1;
    }
    return 0;
}
