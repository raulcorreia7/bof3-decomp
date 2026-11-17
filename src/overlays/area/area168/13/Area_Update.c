#include "area168_13.h"

#ifdef NON_MATCHING
NON_MATCHING void Area_Update(void) {
    g_Task->header.step = 3;
}
#else
INCLUDE_ASM(Area_Update);
#endif
