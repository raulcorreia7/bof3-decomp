#include "area088_13.h"

MATCH void func_801F2E04(void) {
    Trail_Update(MEM_PTR(Trail, AREA_WORK));
    Trail_Draw(MEM_PTR(Trail, AREA_WORK));
    D_800E4B3E -= 6;
    if (--TASK(Actor)->timer == 0) {
        TASK(Actor)->header.mode++;
    }
}
